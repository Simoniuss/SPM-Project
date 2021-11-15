#ifndef CA_H
#define CA_H

#include <vector>
#include <map>
#include <string>

/**
*   \brief Implementation of Cellular Automata Frameworks.
*
*   The class ca implements a Cellular Automata Frameworks by providing
*   methods to define grid of CA, define the number of states for each cell
*   and define a set of rules to update the state of each cell.
*
*   The grid is implemented as a vector of vector, the size of the external
*   vector define the number of rows of the grid, the size of internal vector
*   define the number of columns (each internal vector has the same size).
*
*   The states can be defined as set of string, but inside the class they are
*   mapped to int. The empty cell has to be defined as a states.
*
*   The rules are defined as follows (current_state, neighborhood) --> new_state.
*   The neighborhood is a Moore's neighborhood and it's computed summing for each
*   cell the number of states in the neighborhood. The neighborhood is a vector
*   with size of number of states, in which at each position there is how many times
*   the state appears in the neighborhood.
*
*   The execution of the CA is implemented in this class as a sequential execution, but
*   it can be rewrited to implement any other kind of execution.
**/

class ca {

    protected:

        int rows;   /*!< Number of rows of the grid */

        int columns;    /*!< Number of columns of the grid */

        std::vector<std::vector<int>> grid; /*!< Grid of CA. grid.size()=rows, grid[i].size=columns */

        int n_states;   /*!< Number of states */

        std::map<int, std::string> states;  /*!< Map of states (state_tag, state_name) */

        std::map<std::pair<int,std::vector<int>>, int> rules;  /*!< Map of rules ((current_state, neighbors), new_states) */

        int execution_time = 0;     /*!< Contains the last execution time */ 
    
    public:

        /**
        *   The struct Rule implements the definition of a rule.
        **/
        struct Rule {
            int currentState;   /*!< The tag for the current state of a cell */
            // A special vector of neighbors can be defined (0,...,0) that means change the state in any neighbors condition
            std::vector<int> neighbors; /*!< Vector with the number of state in the neighborhood. neighbors.size()=#states */
            int newState;   /*!< The tag for the new state after applying the rule */
        };

        /**
        *   \brief The constructor of the class.
        *   
        *   The constructor of the class to initialize the class. It takes as
        *   parameters the number of rows and the number of columns of the CA.
        *   
        *   \param rows number of rows of the grid
        *   \param columns number of columns of the grid
        **/
        ca(int rows, int columns);

        /**
        *   \brief Default destructor.
        *   
        *   Default destructor (it must be defined to esnure the inheritance).
        **/
        ~ca() {};

        /**
        *   \brief Set the states of CA. 
        *   
        *   Set the states of CA. The states are mapped to sequential tag (int) respecting
        *   the given order. After initializing the states this method can no longer be called.
        *   The number of states is defined by the size of the input vector.
        *   
        *   \param states vector of strings with the name of states
        *   \return 1 if any error occurs, 0 otherwise
        **/
        int setStates(std::vector<std::string> state);

        /**
        *   \brief Set the rules set of the CA. 
        *   
        *   Set the rules set of the CA. If it is called more time, the rules are added to the
        *   current set. It takes an array of Rule struct and set the map of rules for the class.
        *   This method also check if the rule is correctly defined, if the tag of states is possible
        *   and if the rules[i].neighbors is correctly defined. This method cannot be called before
        *   the setting of states.
        *   
        *   \param rules vector of Rule
        *   \return 1 if any error occurs, 0 otherwise
        **/
        int setRules(std::vector<Rule> rules);

        /**
        *   \brief Add a rule to the set of rules. 
        *   
        *   Add one rule to the set of rules checking the correctness of the rule.
        *   If the rule is already defined this method has no effects on the set of rules.
        *   
        *   \param rule rule to add
        *   \return 1 if any error occurs, 0 otherwise
        **/
        int addRule(Rule rule);

        /**
        *   \brief Initialize the CA grid. 
        *   
        *   Initialize the CA grid using the given parameter. This method cannot be called before
        *   the defining of states. It also check if the given grid is well defined, if it respects
        *   the number of rows and columns, and if the states are correct.
        *   
        *   \param grid vector of vector of int that represent the CA grid
        *   \return 1 if any error occurs, 0 otherwise
        **/
        int initializeGrid(std::vector<std::vector<int>> grid);

        /**
        *   \brief Initialize the CA grid randomly. 
        *   
        *   Initialize the CA grid randomly. If the density parameter is defined, the state with tag 0
        *   is considered as the empty state, and the grid is filled with the given density with the
        *   other states. If density>1 it is considered as 1, if density<0 it is considered as 0.
        *   
        *   \param density density of non-empty cells in the grid
        *   \return 1 if any error occurs, 0 otherwise
        **/
        int initializeRandomGrid(float density=0);

        /**
        *   \brief Execute the CA for a given number of steps. 
        *   
        *   Execute the CA for a given number of steps sequentially. The verbose parameter
        *   can be setted to true if you want to view the result of a step after each step. 
        *   If verbose=false it is printed only the grid after all the steps. 
        *   
        *   \param steps the number of steps to execute the CA
        *   \param verbose verbose parameter 
        **/
        virtual void executeCA(int steps, bool verbose=false);

        /**
        *   \brief Print all the states.
        *   
        *   Print the states with the assigned tag. state_name : state_tag
        **/
        void printStates();

        /**
        *   \brief Print all the rules.
        *   
        *   Print all the rules for the current CA. (current_state, neighborhood) --> new_state
        **/
        void printRules();

        /**
        *   \brief Print the current grid.
        *   
        *   Print the current grid.
        **/
        void printGrid();

        /**
        *   \brief Return the last execution time of the CA.
        *   
        *   Return the last execution time of the CA.
        * 
        *   \return the last execution time
        **/
        int getTime();

    protected:
        /**
        *   \brief Get the state of a cell.
        *   
        *   Get the state of a cell in the position (row, col).
        *   
        *   \param row the row of the cell
        *   \param col the column of the cell
        *   \return the state of the cell, -1 if not defined
        **/
        int getCellState(int row, int col);

        /**
        *   \brief Get the (row, col) of a cell by position.
        *   
        *   Get the (row, col) of a cell by position where the position is a number
        *   between 0 and row*columns-1. If the position is not in this range it returns
        *   a pair (-1,-1).
        *   
        *   \param pos position in the grid
        *   \return the pair (row,col), (-1,-1) if not defined
        **/
        std::pair<int,int> getCellByPosition(int pos);

        /**
        *   \brief Sum the states in the Moore's neighborhood for a cell.
        *   
        *   Compute how many neighbor cells for a given cell are in which state. Save it
        *   in a vector and return it. The vector has the size of #states. The vector is empty
        *   if the (row,col) cell doesn't exist.
        *   
        *   \param row the row of the cell
        *   \param col the column of the cell
        *   \return the vector for the neighborhood, or vector with all 0
        **/
        std::vector<int> getNeighborhoodStates(int row, int col);

        /**
        *   \brief Get the state of a cell after update.
        *   
        *   Return the state of the (row,col) cell after update. It checks if any rule match 
        *   with the pattern given by getNeighborhoodStates and return the new state. If 
        *   row/col doesn't exist retrieve error.
        *   
        *   \param row the row of the cell
        *   \param col the column of the cell
        *   \return the new state of the cell, -1 otherwise
        **/
        int getCellUpdate(int row, int col);

};

#endif