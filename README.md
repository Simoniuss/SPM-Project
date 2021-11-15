# SPM Project
Project implementation for the course of Parallel and Distributed System at the University of Pisa 2020-2021. The project consists in the multi-threaded implementation of a Cellular Automata framework.


 ##  Table of Contents
 * [Introduction](#introduction)
 * [Installation](#installation)
 * [Usage](#usage)
 * [Test](#test)


 ## Introduction
 The implementation of this framework allows to define a grid of a Cellular Automata with its own rules considering a 8-neighbours cell for the update of each state. The framework is implemented in 3 different ways:
 1. Sequential
 2. Parallel with standard thread implementation
 3. Parallel using [FastFlow](https://github.com/fastflow/fastflow)

### 1. ca.h
It implements the sequential algorithm for the execution of the Cellular Automata. It also implements the the framework to define the grid, the states and the rules of the CA.

### 2. ca_thread.h
In this implemnetations the execution of the Cellular Automata is parallelized using the C++ standard library with thread.

### 3. ca_ff.h
The last implementation uses FastFlow library to execute in parallel the CA.

More details about the project and about the results achieved using different implementations can be found in _Report_. 


 ## Installation
```
$ git clone https://github.com/Simoniuss/SPM-Project
$ cd SPM-Project/cellular_automata
$ make
```

## Usage
```
./game_of_life rows columns steps pardegree
```
It execute #_steps_ for a grid _rows_*_columns_ with a parallel degree = _pardegree_

## Test
The implementation can be tested to obtain how the performances change with different parameters.
```
./avg_time.sh number_executions rows columns steps pardegree
```
The script takes the average time between _number_executions_ executions of the algorithm.