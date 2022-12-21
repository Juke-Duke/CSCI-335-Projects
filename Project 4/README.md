
# Sorting

In this assignment, we implement multiple sorting algorithms, including quicksort, mergesort, and heapsor, shellsort, and some others, but we use the first 4 and time them to compare runtimes.

## Getting Started

### Importing the header file:
```c++
#include "Sort.h"
```

### Compiling the program using a Makefile:
```bash
$ make clean
$ make all
```

### Running the Time Tests
```bash
$ ./test_sorting_algorithms <random | sorted_small_to_large | sorted_large_to_small> {number of elements} <less | greater>
```

### Assignment

The program will take a user input for a vector and will run multiple sorting algorithms on it. The program will then output the runtime of each algorithm.
After doing multiple tests, it would seem quicksort, as the name implies, has the usual best average running time, However, when inputting a sorted vector, it's runtime increases dratically, making it slower than other sorting algorithms. This is due to the fact that quicksort is a divide and conquer algorithm, and when the vector is already sorted, it will have to divide the vector into 1 element vectors, which is the worst case scenario for quicksort. This is why quicksort is not the best sorting algorithm for a sorted vector and is worse case O(N<sup>2</sup>).

Youssef Elshabasy 2022
