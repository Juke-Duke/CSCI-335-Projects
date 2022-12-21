# Hashing

In this assignment, we implement three different hashing algorithms: linear probing, quadratic probing, and double hashing. This program will also compare the performance of these three algorithms, and show statistics, such as the number of collisions, the number of probes, and the load factor.

## Getting Started

### Importing the header files:
```c++
#include "linear_probing.h"
#include "quadratic_probing.h"
#include "double_hashing.h"
```

### Compiling the program using a Makefile:
```bash
$ make clean
$ make all
```

### Running the program:
```bash
$ make {linear_probing | quadratic_probing | double_hashing}
```

# Linear Probing

Linear probing is a collision resolution technique in hashing. When a collision occurs, the probing function searches for the next free slot in the hash table and inserts the item in that slot. If the slot is taken, the probing function continues to search for the next free slot, as the name implies, linearly.

# Quadratic Probing

Quadratic probing is another collision resolution technique in hashing, where the probing function searches for the next free slot in the hash table by using a quadratic function. If a slot if taken, then the first probe will be at the next slot, then the next probe will be at 2<sup>2</sup> slots away, then 3<sup>2</sup> slots away, and so on.

# Double Hashing

For double hashing, the probing function is a hash function itself. In this implementation, the user is allowed to provide their own "R value", a number in which will be used for the computation in the hash function. The next probe is decided by the hash function.

# Performance Comparison

Based on the results of the `create_and_test_hash.cc` program, it is shown that the linear probing algorithim has the most amount of collisions and probes, followed by quadratic probing, then with the least amount, double hashing. This is expected as with linear probing, it would take much longer to find an empty slot as it is linearly searching for the next empty slot. Quadratic is faster as the searches are more spread out, making the likelihood of finding an empty slot higher. Double hashing is the fastest as it is using a hash function to find the next empty slot, making the likelihood of finding an empty slot even higher and more unique.