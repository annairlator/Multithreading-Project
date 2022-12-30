# Multithreading-Project
# Demonstration of Concurrency Control Methods

This project demonstrates three major approaches for controlling access to a shared resource between multiple concurrent processes:

* Peterson's Algorithm
* Test and Set
* Fetch and Add

## Prerequisite Software

* g++
* make

## Building

To build using make, run the following command while in the same directory as ```makefile```:
```
make
```

## Running

Once built using the above steps, the project can be executed as follows while in the same directory as ```makefile```:
```
./Project2.0.exe <method> <number of concurrent processes>
```
Where method is:
* 0 for Peterson's algorithm
* 1 for Test and Set
* 2 for Fetch and Add
