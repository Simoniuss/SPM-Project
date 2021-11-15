#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "ca_ff.h"
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

using namespace ff;


ca_ff::ca_ff(int rows, int columns): ca(rows,columns) {};


void ca_ff::executeCA(int steps, int parDegree, bool verbose) {
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
    
    // Initialize copyGrid
    copyGrid.assign(grid.begin(), grid.end());

    // Map function with chunks for FF parallel_for_idx
    auto map = [&, this](const long start, const long stop, const long thid) {
            for(int i=start; i<stop; i++) {
                std::pair<int,int> p = getCellByPosition(i);
                copyGrid[p.first][p.second] = getCellUpdate(p.first, p.second);
            }
        };
    
    for(int i=0; i<steps; i++) {

        // parallel_for_idx(first_index, last_index, stepsize, chunksize, function, nworkers)
        parallel_for_idx(0, rows*columns, 1, 0, map, parDegree);

        // save copyGrid into grid
        grid = copyGrid;

        if(verbose) {
            std::cout << "STEP: " << i << std::endl;
            printGrid();
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // Print result
    //std::cout << "FINAL RESULT AFTER " << steps << " STEPS" << std::endl;
    //printGrid();  
}