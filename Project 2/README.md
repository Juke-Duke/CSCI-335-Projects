# Trees

In this assignment, we implement an AVL tree and get to see it self balancing in action, as well as do some computations on the tree to calculate time complexity of certain operations. The data we use to populate the tree are SequenceMap objects, a class that stores a recoginition sequence and all enzymes that associate with it.

## Getting Started

### Importing the header files:
```c++
#include "sequence_map.h"
#include "avl_tree.h"
include "avl_tree_p2c.h"
```

### Compiling the program using a Makefile:
```bash
$ make clean
$ make all
```

### Running the program:
```bash
$ make {query_tree | test_tree | test_tree_p2c}
```
# SequenceMap

## Constructors

### `SequenceMap(const std::string&, const std::string&)`
Initializes a new instance of the SequenceMap class that contains the specified recognition sequence and  a single enzyme acronym to add to it's list of associated enzymes.
```c++
SequenceMap sequenceMap("AT'TAAT", "VspI");
// AT'TAAT is the recognition sequence
// VspI is the enzyme acronym
```

## Operators

### `bool operator<(const SequenceMap&) const`
Returns true if the recognition sequence of the current instance is less than the recognition sequence of the specified SequenceMap object.
```c++
SequenceMap sequenceMap1("AT'TAAT", "VspI");
SequenceMap sequenceMap2("GAGNNNCTC", "TssI");

std::cout << sequenceMap1 < sequenceMap2 << std::endl; // True
```

### `bool operator>(const SequenceMap&) const`
Returns true if the recognition sequence of the current instance is greater than the recognition sequence of the specified SequenceMap object.
```c++
SequenceMap sequenceMap1("AT'TAAT", "VspI");
SequenceMap sequenceMap2("GAGNNNCTC", "TssI");

std::cout << sequenceMap1 > sequenceMap2 << std::endl; // False
```

### `friend std::ostream& operator<<(std::ostream&, const SequenceMap&)`
EC1: Displays all the enzymes associated with this recognition sequence.
```c++
SequenceMap sequenceMap("AT'TAAT", "VspI");

std::cout << sequenceMap << std::endl; // VspI
```

### `friend std::istream& operator>>(std::istream&, SequenceMap&)`
EC1: Creates a new SequenceMap with a given recognition sequence and adds a given enzyme acronym to it's list of enzyme acronyms.
```c++
SequenceMap sequenceMap("AT'TAAT", "VspI");

std::cin >> sequenceMap; // TssI/AT'TAAT// -> SequenceMap("AT'TAAT", "TssI")
```

## Methods

### `void Merge(const SequenceMap&)`
If two SequenceMaps have the same recognition sequence, then the enzyme acronyms of the other SequenceMap are added to this SequenceMap's list of enzyme acronyms.
```c++
SequenceMap sequenceMap1("AT'TAAT", "VspI");
SequenceMap sequenceMap2("AT'TAAT", "PshBI");
sequenceMap1.Merge(sequenceMap2);

std::cout << sequenceMap1 << std::endl; // VspI PshBI
```

# Part 2a.
I implemented a parser to go through the database file presented by the user, and then proceed to insert the SequenceMaps into an AvlTree. I edited `insert` method so that if two SequenceMaps have the same recognition sequence, then the enzyme acronyms of the other SequenceMap are merged into the current SequenceMap's list via the `Merge` method. After all the SequenceMaps are inserted, the user is prompted to enter a recognition sequence, and the program will search for the SequenceMap that contains that recognition sequence. If the SequenceMap is found, then the program will display all the enzymes associated with that recognition sequence. If the SequenceMap is not found, then the program will display a message saying that the recognition sequence was not found.

# Part 2b.
I implemented a parser to go through the database file presented by the user, and then proceed to insert the SequenceMaps into an AvlTree. After all the SequenceMaps are inserted, I display the amount of nodes in the tree using the AvlTree's `count` method, aswell as displaying the average depth of the tree using `avgDepth`. Then, to display the average depth it takes to traverse each node, I displayed the ratio of the average depth to the amount of nodes in the tree. Afterwards, I read through sequences input and display the amount of sequences that were actually found in the tree. I also display the average amount of recursive calls in ratio to the amount of sequences we searched for usig the `findRecursionCount` method. Lastly, I read through the sequences input again, but instead remove every other sequence from the tree. I then display the amount of nodes left in the tree, and the ratio of the amount of total recursive calls in ratio to the nodes that were successfully removed using `removeRecursionCount`. We once again display count, average depth, and average depth to node ratio.

# Part 2c.
I repeated everything done in Part 2b, with the only change being the implementation of the rotation methods. Instead of recursivly calling the single rotations, I just pasted the implementation of the single rotations, swapping in the correct parameters being used.

# EXTRA CREDIT

# EC2

## Question
Show that via AVL single rotations, any binary search tree (with
greater than 3 nodes) T1 can be transformed to another search tree T2 (with
the same items).

## Answer
There are 2 types of single rotations that can be done on an AvlTree. The first is a left rotation, which is done when the right subtree of the root node is taller than the left subtree. The second is a right rotation, which is done when the left subtree of the root node is taller than the right subtree. For the left rotation, the parent of a right child becomes the left child of the right child. For the right rotation, the parent of a left child becomes the right child of the left child. The following diagram shows the transformation of a binary search tree to another search tree via AVL single rotations. These two rotations will result in different binary trees with the same items included.

# EC3

## Question
Give an algorithm to perform this transformation using O(N log N)
rotations on average.

## Answer
A single rotation for a binary search tree can be done in O(log N) on average. Transforming a tree into another tree using single rotations can be done at worst in O(N) time. As the complexity of a single rotation is O(log N), the complexity of transforming a tree into another tree using single rotations is O(N log N).


Youssef Elshabasy - 2022