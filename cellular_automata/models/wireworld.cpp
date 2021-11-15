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

    //cout << "Wireworld" << endl;
    ca ca(10,10);
    ca_thread ca1(10,10);
    ca_ff ca2(10,10);


    vector<string> states = {"empty", "head", "tail", "conductor"};
    ca.setStates(states);
    ca1.setStates(states);
    ca2.setStates(states);

    vector<ca::Rule> rules = {  // head --> tail
                                {1,{0,0,0,0},2},
                                // tail --> conductor
                                {2,{0,0,0,0},3},
                                // conductor with 1 or 2 head as neighbors --> head
                                {3,{7,1,0,0},1},
                                {3,{6,1,1,0},1},
                                {3,{6,1,0,1},1},
                                {3,{5,1,2,0},1},
                                {3,{5,1,1,1},1},
                                {3,{5,1,0,2},1},
                                {3,{4,1,3,0},1},
                                {3,{4,1,2,1},1},
                                {3,{4,1,1,2},1},
                                {3,{4,1,0,3},1},
                                {3,{3,1,4,0},1},
                                {3,{3,1,3,1},1},
                                {3,{3,1,2,2},1},
                                {3,{3,1,1,3},1},
                                {3,{3,1,0,4},1},
                                {3,{2,1,5,0},1},
                                {3,{2,1,4,1},1},
                                {3,{2,1,3,2},1},
                                {3,{2,1,2,3},1},
                                {3,{2,1,1,4},1},
                                {3,{2,1,0,5},1},
                                {3,{1,1,6,0},1},
                                {3,{1,1,5,1},1},
                                {3,{1,1,4,2},1},
                                {3,{1,1,3,3},1},
                                {3,{1,1,2,4},1},
                                {3,{1,1,1,5},1},
                                {3,{1,1,0,6},1},
                                {3,{0,1,7,0},1},
                                {3,{0,1,6,1},1},
                                {3,{0,1,5,2},1},
                                {3,{0,1,4,3},1},
                                {3,{0,1,3,4},1},
                                {3,{0,1,2,5},1},
                                {3,{0,1,1,6},1},
                                {3,{0,1,0,7},1},

                                {3,{6,2,0,0},1},
                                {3,{5,2,1,0},1},
                                {3,{5,2,0,1},1},
                                {3,{4,2,2,0},1},
                                {3,{4,2,1,1},1},
                                {3,{4,2,0,2},1},
                                {3,{3,2,3,0},1},
                                {3,{3,2,2,1},1},
                                {3,{3,2,1,2},1},
                                {3,{3,2,0,3},1},
                                {3,{2,2,4,0},1},
                                {3,{2,2,3,1},1},
                                {3,{2,2,2,2},1},
                                {3,{2,2,1,3},1},
                                {3,{2,2,0,4},1},
                                {3,{1,2,5,0},1},
                                {3,{1,2,4,1},1},
                                {3,{1,2,3,2},1},
                                {3,{1,2,2,3},1},
                                {3,{1,2,1,4},1},
                                {3,{1,2,0,5},1},
                                {3,{0,2,6,0},1},
                                {3,{0,2,5,1},1},
                                {3,{0,2,4,2},1},
                                {3,{0,2,3,3},1},
                                {3,{0,2,2,4},1},
                                {3,{0,2,1,5},1},
                                {3,{0,2,0,6},1}};
    ca.setRules(rules);
    ca1.setRules(rules);
    ca2.setRules(rules);
    //ca.printRules();

    // diodes
    vector<vector<int>> grid = {{0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,3,3,0,0,0,0},
                                {2,1,3,3,3,0,3,3,3,3},
                                {0,0,0,0,3,3,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
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