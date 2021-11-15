#include <iostream>
#include <vector>
#include <tuple>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cmath>
#include <chrono>
#include "ca_thread.h"


ca_thread::ca_thread(int rows, int columns): ca(rows,columns) {};


void ca_thread::executeCA(int steps, int parDegree, bool verbose) {
    // To compute the execution time
    auto start = std::chrono::high_resolution_clock::now();

    if(states.empty() || rules.empty()) {
        std::cerr << "ERROR: states/rules/grid not setted" << std::endl;
        return;   
    }
    if(steps<=0 || parDegree<1) {
        std::cerr << "ERROR: steps<=0 or parDegree<1" << std::endl;
        return;
    }

    // Split the grid in chunk considering the parallel degree
    std::vector<std::pair<int,int>> chunks(parDegree);
    int delta = (int)ceil(rows*columns/parDegree); 
    for(int i=0; i<parDegree; i++)
        chunks[i] = std::pair(i*delta, (i!=(parDegree-1) ? (i+1)*delta : rows*columns));
    
    // Initialize copyGrid
    copyGrid.assign(grid.begin(), grid.end());
    // Initialize barrier
    init_counter = parDegree;
    counter = parDegree;

    // Create threads
    std::vector<std::thread> tids;
    for(int i=0; i<parDegree; i++) 
        tids.push_back(std::thread(&ca_thread::updateChunk,this,steps,chunks[i],verbose));
    
    // Wait for thread completion
    for(auto& t: tids)
        t.join();

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // Print result
    //std::cout << "FINAL RESULT AFTER " << steps << " STEPS" << std::endl;
    //printGrid();  
}


void ca_thread::updateChunk(int steps, std::pair<int,int> range, bool verbose) {
    for(int i=0; i<steps; i++) {
        // copyChunk has tuple (row, column, newCellState). It is used to copy one-shot the new values
        // in copyGrid to reduce the number of mutex call for synch.
        std::vector<std::tuple<int,int,int>> copyChunk(range.second-range.first);

        for(int pos=range.first; pos<range.second; pos++) {
            // Read from grid --> no need of synchronization
            std::pair<int,int> p = getCellByPosition(pos);
            // Write tuple in copyChunk getting the newState of a cell
            copyChunk[pos-range.first] = std::make_tuple(p.first, p.second, getCellUpdate(p.first, p.second));
        }

        // I don't know if the writes on different parts of vector are thread-safe so
        // I have to synchronize them with lock
        {
            // Lock for the writing of copyGrid
            std::lock_guard<std::mutex> lock(copyGrid_mtx);
            // For each c: get<0> = row, get<1> = col, get<2> = newState
            for(auto c : copyChunk) 
                copyGrid[std::get<0>(c)][std::get<1>(c)] = std::get<2>(c);
        }

        //std::cout << "Thread: " << std::this_thread::get_id() << " Step: " << i << std::endl;

        barrierWait(i,verbose);
    }
}


void ca_thread::barrierWait(int step, bool verbose) {
    std::unique_lock<std::mutex> lk(barrier_mtx);
    counter--;
    if(counter==0)
        barrierComplete(step,verbose);
    else
        barrier_cv.wait(lk);
}


void ca_thread::barrierComplete(int step, bool verbose) {
    grid = copyGrid;
    counter = init_counter;

    //std::cout << "Barrier step: " << step << " completed" << std::endl;

    if(verbose) {
        std::cout << "STEP: " << step << std::endl;
        printGrid();
    }
    barrier_cv.notify_all();
}

