#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include "ca.h"

ca::ca(int rows, int columns)
    : rows(rows), columns(columns), grid(rows, std::vector<int>(columns,0)) {}


int ca::setStates(std::vector<std::string> states) {

    if(this->states.empty()) {
        n_states = states.size();
        for(int i=0; i<states.size(); i++)
            this->states.insert({i, states[i]});
        return 0;
    }

    else {
        std::cerr << "ERROR: States already setted" << std::endl;
        return 1;
    }
}


int ca::setRules(std::vector<Rule> rules) {

    if(states.empty()) {
        std::cerr << "ERROR: States not setted" << std::endl;
        return 1;
    }

    else { 
        // Boundaries check for the rules
        for(int i=0; i<rules.size(); i++) {
            Rule r = rules[i];

            if(r.currentState<0 || r.currentState >= n_states ||
                r.newState<0 || r.newState >= n_states) {
                std::cerr << "ERROR: currentState/newState in rule not valid" << std::endl;
                return 1;  
            }

            else {
                // Neighbors vector size must be n_states
                if(r.neighbors.size()!=n_states) {
                    std::cerr << "ERROR: neighbors in rule not valid" << std::endl;
                    return 1; 
                }

                // Insert rule in the map. (currentState, neighbors) --> newState
                else
                    this->rules.insert({std::pair(r.currentState, r.neighbors), r.newState}); 
            }
        }
        return 0;
    }
}


int ca::addRule(Rule rule) {

    if(states.empty()) {
        std::cerr << "ERROR: States not setted" << std::endl;
        return 1;
    }

    else { 
        // Boundaries check for the rules
        if(rule.currentState<0 || rule.currentState >= n_states ||
            rule.newState<0 || rule.newState >= n_states) {
            std::cerr << "ERROR: currentState/newState in rule not valid" << std::endl;
            return 1;  
        }

        else {
            // Neighbors vector size must be n_states
            if(rule.neighbors.size()!=n_states) {
                std::cerr << "ERROR: neighbors in rule not valid" << std::endl;
                return 1; 
            }
            // Insert rule in the map. (currentState, neighbors) --> newState
            else
                rules.insert({std::pair(rule.currentState, rule.neighbors), rule.newState}); 
        }
        return 0;
    }
}


int ca::initializeGrid(std::vector<std::vector<int>> grid) {

    if(states.empty()) {
        std::cerr << "ERROR: States not setted" << std::endl;
        return 1;
    }

    else {
        if(grid.size()!=rows) {
            std::cerr << "ERROR: different rows" << std::endl;
            return 1;
        }

        else {

            for(int i=0; i<grid.size(); i++) {
                if(grid[i].size()!=columns) {
                    std::cerr << "ERROR: different columns" << std::endl;
                    return 1;
                }

                else {
                    for(int j=0; j<grid[i].size(); j++) {
                        if(grid[i][j]<0 || grid[i][j] >= n_states) {
                            std::cerr << "ERROR: state not valid" << std::endl;
                            return 1; 
                        }
                    }
                }
            }
            this->grid = grid;
            return 0;
        }
    }
}


int ca::initializeRandomGrid(float density) {

    if(this->states.empty()) {
        std::cerr << "ERROR: States not setted" << std::endl;
        return 1;
    }

    else {
        // Generator of pseudo-random number
        std::mt19937 randomGen(std::random_device{}()); 
        if(density<=0) {
            // Uniform distribution of states
            std::uniform_int_distribution<int> statesDist(0,n_states-1);
            for(int i=0; i<rows; i++) {
                for (int j=0; j<columns; j++) {
                    int state = statesDist(randomGen);
                    grid[i][j] = state;
                }
            }
        }

        // density!=0
        else {
            if(density>1)
                density = 1;

            // fill matrix with empty states (0 by default)
            for(int i=0; i<rows; i++) 
                std::fill(grid[i].begin(),grid[i].end(),0);
            
            // number of elements != 0 in the matrix
            int n_elements = (int)ceil(rows*columns*density);
            std::uniform_int_distribution<int> rowsDist(0,rows-1);
            std::uniform_int_distribution<int> columnsDist(0,columns-1);
            std::uniform_int_distribution<int> statesDist(1,n_states-1);
            for(int i=0; i<n_elements; i++) {
                int r = rowsDist(randomGen);
                int c = columnsDist(randomGen);
                int s = statesDist(randomGen);
                grid[r][c] = s;
            }
        }
        return 0;
    }   
}


int ca::getCellState(int row, int col) {

    if(row<0 || row>=rows || col<0 || col>=columns) {
         std::cerr << "ERROR: row/col not valid or grid empty" << std::endl;
        return -1;
    }
    return grid[row][col];
}


std::pair<int,int> ca::getCellByPosition(int pos) {

    if(pos<0 || pos>=rows*columns) {
        std::cerr << "ERROR: position not valid or grid empty" << std::endl;
        return std::pair(-1,-1);
    }
    return std::pair((int)pos/columns, pos%columns);
}


std::vector<int> ca::getNeighborhoodStates(int row, int col) {

    std::vector<int> neighbors(n_states,0);
    if(row<0 || row>=rows || col<0 || col>=columns)
        return neighbors;

    int n = getCellState((row-1+rows) % rows, col);
    int s = getCellState((row+1+rows) % rows, col);
    int w = getCellState(row, (col-1+columns) % columns);
    int e = getCellState(row, (col+1+columns) % columns);
    int nw = getCellState((row-1+rows) % rows, (col-1+columns) % columns);
    int ne = getCellState((row-1+rows) % rows, (col+1+columns) % columns);
    int se = getCellState((row+1+rows) % rows, (col+1+columns) % columns);
    int sw = getCellState((row+1+rows) % rows, (col-1+columns) % columns);
    neighbors[n]++;
    neighbors[s]++;
    neighbors[w]++;
    neighbors[e]++;
    neighbors[nw]++;
    neighbors[ne]++;
    neighbors[se]++;
    neighbors[sw]++;
    return neighbors;
}


int ca::getCellUpdate(int row, int col) {
    if(row<0 || row>=rows || col<0 || col>=columns) {
        std::cerr << "ERROR: row/col not valid or grid empty" << std::endl;
        return -1;
    }

    std::vector<int> any(n_states,0);
    int currState = getCellState(row,col);
    std::pair<int,std::vector<int>> any_key(currState, any);
    auto search = rules.find(any_key); 
    if(search != rules.end())
        return search->second;
    else {
        std::vector<int> neighbors = getNeighborhoodStates(row,col);
        std::pair<int,std::vector<int>> key(currState, neighbors);
        search = rules.find(key);
        if(search != rules.end())
            return search->second;
        else  
            return currState;
    }      
}


void ca::executeCA(int steps, bool verbose) {
    // To compute the execution time
    auto start = std::chrono::high_resolution_clock::now();

    if(states.empty() || rules.empty()) {
        std::cerr << "ERROR: states/rules/grid not setted" << std::endl;
        return;   
    }
    if(steps<=0) {
        std::cerr << "ERROR: steps<=0" << std::endl;
        return;
    }

    // Update done on the copy. After each step save save the copy in the grid.
    std::vector<std::vector<int>> copy(grid.begin(), grid.end());
    for(int s=0; s<steps; s++) {
        for(int i=0; i<rows; i++) {
            for(int j=0; j<columns; j++)
                // getCellUpdate works on the grid.
                copy[i][j] = getCellUpdate(i,j);
        }
        grid = copy;
        
        if(verbose) {
            std::cout << "STEP: " << s << std::endl;
            printGrid();
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    //std::cout << "FINAL RESULT AFTER " << steps << " STEPS" << std::endl;
    //printGrid();
}


void ca::printStates() {
    for (auto s : states) {
        std::cout << s.first << ": " << s.second << "   ";
    }
    std::cout << std::endl;
}


void ca::printRules() {
    std::cout << "currentState - {neighbors} --> newState" << std::endl;
    int currentState;
    std::string stateDescr;
    // r = (key, val). key = (state, vector). val = state
    for (auto r : rules) {
        // currentState
        currentState = r.first.first;
        stateDescr = states.find(currentState)->second;
        std::cout << stateDescr << "(" << currentState <<  ") - ";

        // neighbors
        std::vector<int> neighbors = r.first.second;
        std::cout << "{ ";
        for (int i=0; i<neighbors.size(); i++) {
            currentState = i;
            stateDescr = states.find(currentState)->second; 
            std::cout << neighbors[i] << " " << stateDescr << "(" << currentState << ") ";
        }
        std::cout << "}";
        
        // newState
        currentState = r.second;
        stateDescr = states.find(currentState)->second;
        std::cout << " --> " << stateDescr << "(" << currentState <<  ")" << std::endl;
    }   
}


void ca::printGrid() {
    ca::printStates();
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int ca::getTime() {
    return execution_time;
}