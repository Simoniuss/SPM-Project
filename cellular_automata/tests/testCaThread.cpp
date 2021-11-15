#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "ca_thread.h"

using namespace std;

int main () {
  cout << "Test Game of Life " << endl;
  ca_thread ca(10,10);


  cout << "***************************************************************"<< endl;
  cout << "TEST STATES"<< endl;
  vector<string> states = {"dead", "live"};
  int res = ca.setStates(states);
  cout << "Set states: " << res << endl;


  cout << "***************************************************************"<< endl;
  cout << "TEST RULES"<< endl;
  vector<ca_thread::Rule> rules = { {1,{8,0},0},
                         {1,{7,1},0},
                         {1,{4,4},0},
                         {1,{3,5},0},
                         {1,{2,6},0},
                         {1,{1,7},0},
                         {1,{0,8},0},
                         {0,{5,3},1} };
  res = ca.setRules(rules);
  cout << "Set rules: " << res << endl;
  ca.printRules();



  cout << "***************************************************************"<< endl;
  cout << "TEST GRID"<< endl;
  vector<vector<int>> grid = { {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,1,0,0,0,0,0},
                                {0,0,0,1,1,0,0,0,0,0},
                                {0,0,0,0,0,1,1,0,0,0},
                                {0,0,0,0,0,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0},
                                {0,1,0,1,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0} };
  res = ca.initializeGrid(grid);
  cout << "Initialize grid: " << res << endl;
  ca.printGrid();

  //res = ca.initializeRandomGrid(0);
  //cout << "Initialize random grid: " << res << endl;
  //ca.printGrid();

  // Test executeCA()
  cout << "***************************************************************"<< endl;
  cout << "TEST EXECUTE"<< endl;
  ca.printRules();
  ca.printGrid();
  ca.executeCA(10,20);
  cout << "***************************************************************"<< endl;

  return 0;
}