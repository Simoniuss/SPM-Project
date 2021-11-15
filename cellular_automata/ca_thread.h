#ifndef CA_THREAD_H
#define CA_THREAD_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "ca.h"

/**
*   \brief Implementation of Cellular Automata Frameworks using parallelization.
*
*   The class ca_thread inherits from the class ca all the methods to build a CA
*   and re-implement the method executeCA using standard library parallelization.
*   The parallelization is done using thread and implementing a barrier between each
*   step to synchronize all threads.
*
*   \see ca.h
**/

class ca_thread: public ca {

    private:
        std::mutex barrier_mtx;   /*!< Mutex used for the implementation of barrier */
        std::condition_variable barrier_cv;   /*!< Condition variable used for the implementation of barrier */
        int init_counter;   /*!< Initialization of barrier counter */
        std::atomic<int> counter;   /*!< Atomic barrier counter */
        std::vector<std::vector<int>> copyGrid;     /*!< Grid used for the parallel execution */
        std::mutex copyGrid_mtx;   /*!< Mutex used to synchronize write on the copyGrid */ 

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
        ca_thread(int rows, int columns);

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

    private:

        /**
        *   \brief Thread definition to update a chunk of grid. 
        *   
        *   Update a chunk of grid for given number of steps. After each step the 
        *   function wait on a barrier and before restart the barrier swap the computed
        *   values with the original grid. Update-->copyGrid, read-->grid.
        *   
        *   \param steps the number of steps to execute the CA
        *   \param range chunksize
        *   \param verbose verbose parameter
        **/
        void updateChunk(int steps, std::pair<int,int> range, bool verbose);

        /**
        *   \brief Barrier implementation for updateChunk. 
        *   
        *   Implement a barrier that put on wait threads until all the threads had completed
        *   a step. When all threads had completed the step, call barrierComplete() function.
        *
        *   \see updateChunk
        *   \see barrierComplete
        *   
        *   \param step current step
        *   \param verbose verbose parameter
        **/
        void barrierWait(int step, bool verbose);

        /**
        *   \brief Function called to restart barrier and notify waiting threads. 
        *   
        *   Function called to restart barrier and notify waiting threads. Before
        *   notifying threads save the results of copyGrid in grid.
        *   
        *   \see barrierWait
        *
        *   \param step current step
        *   \param verbose verbose parameter
        **/
        void barrierComplete(int step, bool verbose);

};


#endif