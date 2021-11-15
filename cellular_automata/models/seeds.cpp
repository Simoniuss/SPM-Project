#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../ca.h"
#include "../ca_thread.h"
#include "../ca_ff.h"

using namespace std;

int main (int argc, char *argv[]) {

    if (argc<2) {
        cerr << "Use: " << argv[0] << " steps parallel_degree" << endl;;
        return -1;
    }

    int steps = atoi(argv[1]);
    int parDegree = atoi(argv[2]);

    if (steps<=0 || parDegree<=0) {
        cerr << "steps/parallel_degree cannot be <=0" << endl;;
        return -1;
    }

    //cout << "Seeds" << endl;
    ca ca(10,10);
    ca_thread ca1(10,10);
    ca_ff ca2(10,10);


    vector<string> states = {"off", "on"};
    ca.setStates(states);
    ca1.setStates(states);
    ca2.setStates(states);
    
    
    vector<ca::Rule> rules = {  // off with exactly 2 neighbors on --> on 
                                {0,{6,2},1},
                                // on --> off
                                {1,{0,0},0}};

    
    ca.setRules(rules);
    ca1.setRules(rules);
    ca2.setRules(rules);
    //ca.printRules();

    // chaotic exploding pattern
    vector<vector<int>> grid = {{0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,1,0,0,0,0,0},
                                {0,0,0,0,0,1,1,0,0,0},
                                {0,0,0,1,0,1,0,0,0,0},
                                {0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0}};
    ca.initializeGrid(grid);
    ca1.initializeGrid(grid);
    ca2.initializeGrid(grid);
    

    //ca.initializeRandomGrid();
    //ca1.initializeRandomGrid();
    //ca2.initializeRandomGrid();
    //ca.printGrid();


    ca.executeCA(steps);
    //ca.printGrid();


    ca1.executeCA(steps,parDegree);
    //ca1.printGrid();


    ca2.executeCA(steps,parDegree,true);
    //ca2.printGrid();

    // Print times
    cout << "Tseq: " << ca.getTime() << " Tpar: " << ca1.getTime() << " Tpar_ff: " << ca2.getTime() << endl;
 
    return 0;
}