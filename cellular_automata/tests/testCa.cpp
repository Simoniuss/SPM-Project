#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "ca.h"

using namespace std;

int main () {
  cout << "Test Game of Life " << endl;
  ca ca(10,10);

  // Test setStates(), printStates()
  cout << "***************************************************************"<< endl;
  cout << "TEST STATES"<< endl;
  vector<string> states = {"dead", "live"};
  int res = ca.setStates(states);
  cout << "Set states: " << res << endl;
  res = ca.setStates(states);
  cout << "Try to set states again: " << res << endl;
  ca.printStates();
  cout << "***************************************************************"<< endl;

  // Test setRules(), printRules(), addRules()
  // {currentState, {deadCell, liveCell}, newState}. 0-->dead, 1-->live.
  cout << "***************************************************************"<< endl;
  cout << "TEST RULES"<< endl;
  vector<ca::Rule> rules = { {1,{8,0},0},
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

  rules = { {1,{8,0},0},
            {0,{6,2},0} };
  res = ca.setRules(rules);
  cout << "Set new rules: " << res << endl;
  ca.printRules();

  rules = { {5,{7,1},0},
            {0,{6,2,3},0} };
  res = ca.setRules(rules);
  cout << "Set wrong rules: " << res << endl;
  ca.printRules();

  class ca ca1(20,20);
  rules = { {1,{8,0},0},
            {0,{6,2},0} };
  res = ca1.setRules(rules);
  cout << "Set rules with empty state: " << res << endl;

  ca::Rule r = {0,{6,2},0};
  res = ca1.addRule(r);
  cout << "Add rule with empty state: " << res << endl;

  r = {0,{3,5},1};
  res = ca.addRule(r);
  cout << "Add rule: " << res << endl;
  ca.printRules();
  cout << "***************************************************************"<< endl;

  // Test initializeGrid(), initializeRandomGrid()
  cout << "***************************************************************"<< endl;
  cout << "TEST GRID"<< endl;
  vector<vector<int>> grid = { {1,0,0,0,0,0,1,0,0,0},
                               {0,1,0,0,0,0,0,0,1,0},
                               {0,0,0,0,1,0,0,1,0,0},
                               {0,1,0,1,0,0,0,0,0,0},
                               {0,0,0,1,0,0,0,0,1,0},
                               {0,1,0,0,0,0,0,1,0,0},
                               {0,0,0,0,0,1,0,1,0,0},
                               {0,0,0,1,0,0,0,0,0,0},
                               {0,0,1,0,0,0,1,0,1,0},
                               {0,1,0,0,1,0,0,0,1,0} };
  res = ca.initializeGrid(grid);
  cout << "Initialize grid: " << res << endl;
  ca.printGrid();

  res = ca1.initializeGrid(grid);
  cout << "Initialize grid with empty state: " << res << endl;

  vector<vector<int>> grid1 = { {1,0,0,0,0,0,1,0,0,0},
                               {0,1,0,0,0,0,0,0,1,0},
                               {0,0,0,0,1,0,0,1,0,0},
                               {0,1,0,1,0,0,0,0,0,0},
                               {0,0,0,1,0,0,0,0,1,0},
                               {0,1,0,0,0,4,0,1,0,0},
                               {0,0,0,0,0,1,0,1,0,0},
                               {0,0,1,0,0,0,1,0,1,0},
                               {0,0,1,0,0,0,1,0,1,0},
                               {0,1,0,0,1,0,0,0,1,0} };
  res = ca.initializeGrid(grid1);
  cout << "Initialize grid with error: " << res << endl;

  res = ca.initializeRandomGrid(0);
  cout << "Initialize random grid: " << res << endl;
  ca.printGrid();

  res = ca.initializeRandomGrid(0.5);
  cout << "Initialize random grid with density: " << res << endl;
  ca.printGrid();
  cout << "***************************************************************"<< endl;

  // Test getCellState(), getCellByPosition(), getNeighborhoodStates(), updateCell()
  cout << "***************************************************************"<< endl;
  cout << "TEST GET"<< endl;

  ca.printGrid();
  res = ca.getCellState(10,10);
  cout << "Get cell state: " << res << endl;

  ca.printGrid();
  pair<int,int> p = ca.getCellByPosition(23);
  cout << "Get cell position: r:" << p.first << " c:" << p.second << endl;

  ca.printGrid();
  vector<int> neigh = ca.getNeighborhoodStates(0,0);
  cout << "Get neighborhood sum: 0:" << neigh[0] << " 1:" << neigh[1] << endl;

  ca.printRules();
  ca.printGrid();
  res = ca.getCellUpdate(0,0);
  ca.printGrid();
  cout << "Update cell state: " << res << endl;
  cout << "***************************************************************"<< endl;

  // Test executeCA()
  cout << "***************************************************************"<< endl;
  cout << "TEST EXECUTE"<< endl;
  ca.printRules();
  ca.printGrid();
  ca.executeCA(10);
  cout << "***************************************************************"<< endl;

  return 0;
}