#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "ca.h"
#include "ca_thread.h"
#include "ca_ff.h"

using namespace std;

int main (int argc, char *argv[]) {

    if (argc<4) {
        cerr << "Use: " << argv[0] << " rows columns steps parallel_degree" << endl;;
        return -1;
    }

    int rows = atoi(argv[1]);
    int columns = atoi(argv[2]);
    int steps = atoi(argv[3]);
    int parDegree = atoi(argv[4]);

    if (rows<=0 || columns<=0 || steps<=0 || parDegree<=0) {
        cerr << "rows/columns/steps/parallel_degree cannot be <=0" << endl;;
        return -1;
    }

    //cout << "Game of Life" << endl;
    ca ca(rows,columns);
    ca_thread ca1(rows,columns);
    ca_ff ca2(rows,columns);


    vector<string> states = {"dead", "live"};
    ca.setStates(states);
    ca1.setStates(states);
    ca2.setStates(states);

    vector<ca::Rule> rules = {  // live with less than 2 neighbors live --> dead (underpopulation) 
                                {1,{8,0},0},
                                {1,{7,1},0},
                                // live with more than 3 neighbors live --> dead (overpopulation)
                                {1,{4,4},0},
                                {1,{3,5},0},
                                {1,{2,6},0},
                                {1,{1,7},0},
                                {1,{0,8},0},
                                // dead with exactly 3 neighbors live --> live
                                {0,{5,3},1} };
    ca.setRules(rules);
    ca1.setRules(rules);
    ca2.setRules(rules);
    //ca.printRules();

    // beacon + tub
    /*vector<vector<int>> grid = { {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,1,0,0,0,0,0},
                                {0,0,0,1,1,0,0,0,0,0},
                                {0,0,0,0,0,1,1,0,0,0},
                                {0,0,0,0,0,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0},
                                {0,1,0,1,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0} };
    ca.initializeGrid(grid);
    ca1.initializeGrid(grid);
    ca2.initializeGrid(grid);
    */
    

    ca.initializeRandomGrid();
    ca1.initializeRandomGrid();
    ca2.initializeRandomGrid();
    //ca.printGrid();


    ca.executeCA(steps);
    //ca.printGrid();


    ca1.executeCA(steps,parDegree);
    //ca1.printGrid();


    ca2.executeCA(steps,parDegree);
    //ca2.printGrid();

    // Print times
    cout << "Tseq: " << ca.getTime() << " Tpar: " << ca1.getTime() << " Tpar_ff: " << ca2.getTime() << endl;
 
    return 0;
}