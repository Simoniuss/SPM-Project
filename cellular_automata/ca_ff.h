#ifndef CA_FF_H
#define CA_FF_H

#include <vector>
#include "ca.h"

/**
*   \brief Implementation of Cellular Automata Frameworks parallelized with FastFlow.
*
*   The class ca_ff inherits from the class ca all the methods to build a CA
*   and re-implement the method executeCA using ff parallelization. In particular
*   this implementation uses ff/parallel_for to get parallel execution.
*
*   \see ca.h
*   \see ff/parallel_for.hpp
**/

class ca_ff: public ca {

    private:
        std::vector<std::vector<int>> copyGrid;     /*!< Grid used for the parallel execution */ 

    public:

        /**
        *   \brief The constructor of the class.
        *   
        *   The constructor of the class to initialize the class. It takes as
        *   parameters the number of rows and the number of columns of the CA
        *   and build an object of type ca.
        *
        *   \see ca.h
        *   
        *   \param rows number of rows of the grid
        *   \param columns number of columns of the grid
        **/
        ca_ff(int rows, int columns);

        /**
        *   \brief Execute the CA for a given number of steps, with some degree of parallelization. 
        *   
        *   Execute the CA for a given number of steps using a given parallel degree. The verbose 
        *   parameter can be setted to true if you want to view the result of a step after each step. 
        *   If verbose=false it is printed only the grid after all the steps.
        *   
        *   \param steps the number of steps to execute the CA
        *   \param parDegree parallel degree
        *   \param verbose verbose parameter 
        **/
        void executeCA(int steps, int parDegree=1, bool verbose=false);

};


#endif