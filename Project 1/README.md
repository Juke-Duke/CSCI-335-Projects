# Points2D\<TNumber\>

A class that represents a strongly typed sequence of 2D points, which subsequently are represented as `[x, y]` arrays. Provides methods to create, combine, and display these sequence of points.

## Getting Started

### Importing the header file:
```c++
#include "Points2D.h"
```

### Compiling the program using a Makefile:
```bash
$ make clean
$ make all
```

### Running the program:
```bash
$ ./{program_name}
```
**You can also input files as arguments for the istream to read from (see also [Input Overload](#friend-stdistream-operatorstdistream-points2d-noexcept)):**
```bash
$ ./{program_name} < {input_file}
```

## Constructors

### `Points2D() noexcept`
Initializes a new instance of the Points2D class that is empty and has the default initial size of 0.
```c++
Points2D<int> points; // Creates an empty Points2D<int> instance with size 0.
```

### `Points2D(const Points2D&) noexcept`
Initializes a new instance of the Points2D class that contains elements deep copied from another Points2D class instance.
```c++
Points2D<double> points1;
Points2D<double> points2(points1); // Copy constructor gets called here
```

### `Points2D(Points2D&&) noexcept`
Initializes a new instance of the Points2D class that contains elements from an rvalue reference.
```c++
Points2D<double> points1;
Points2D<double> points2(std::move(points1)); // Move constructor gets called here
```

### `Points2D(const std::array<TNumber, 2>&) noexcept`
Initializes a new instance of the Points2D class that contains one point from a single std::array of two elements.
```c++
std::array<int, 2> point = { 1, 2 };
Points2D<int> points(point); // Array constructor gets called here (1, 2)
```

## Assignments

### `Points2D& operator=(const Points2D&) noexcept`
Assigns the current instance to a deep copy of another Points2D class instance.
```c++
Points2D<double> points1;
Points2D<double> points2;
points2 = points1; // Copy assignment operator gets called here
```

### `Points2D& operator=(Points2D&&) noexcept`
Assigns the current instance to an rvalue reference.
```c++
Points2D<double> points1;
Points2D<double> points2;
points2 = std::move(points1); // Move assignment operator gets called here
```

## Accessors

### `size_t size() const noexcept`
Gets the number of points in the current instance.
```c++
Points2D<int> points1;
std::cout << points1.size() << std::endl; // Displays 0

std::array<double, 2> point = { 1.5, 2.7 };
Points2D<double> points2(point);
std::cout << points2.size() << std::endl; // Displays 1

Points2D<double> points3;
std::cin >> points3; // 3 2.5 7.2 1.1 4.3 5.6 9.9 -> (2.5, 7.2) (1.1, 4.3) (5.6, 9.9)
std::cout << points3.size() << std::endl; // Displays 3
```

### `const std::array<TNumber, 2>& operator[](int) const`
Gets the point at the specified index, can not be used to modify the point or its components.
```c++
std::array<int, 2> point = { 5, 8 };
Points2D<int> points(point);
std::cout << points[0][0] << std::endl; // Displays 5
std::cout << points[0][1] << std::endl; // Displays 8

std::array<int, 2> point2 = { 1, 2 };
points[0] = point2; // Error: cannot modify the point due to a const reference
points[0][0] = 10; // Error: lvalue must be modifiable
point2 = points[0]; // Will set point2 to { 5, 8 }
```

## Operators

### `friend Points2D& operator+(const Points2D&, const Points2D&) noexcept`
Adds two Points2D class instances together by concatenating their points, and returns a new Points2D class instance.
```c++
Points2D<int> points1;
Points2D<int> points2;

std::cin >> points1; // 2 16 2 5 3 -> (16, 2) (5, 3)
std::cin >> points2; // 3 2 8 9 1 12 2 -> (2, 8) (9, 1) (12, 2)

Points2D<int> points3 = points1 + points2; // (18, 10) (14, 4) (12, 2)
```
> **Note** Only Points2D class instances with the same template type can be added together.

### `friend std::ostream& operator<<(std::ostream&, const Points2D&) noexcept`
Outputs the sequence of points in the current instance to display.
```c++
std::array<int, 2> point1 = { 1, 2 };
Points2D<int> points1(point1);

Points2D<int> points2(point2);
std::cin >> points2; // 3 5 8 1 2 3 4 -> (5, 8) (1, 2) (3, 4)

std::cout << points1 << std::endl; // Displays (1, 2)
std::cout << points2 << std::endl; // Displays (5, 8), (1, 2), (3, 4)
```

### `friend std::istream& operator>>(std::istream&, Points2D&) noexcept`
Inputs a sequence of points from the user and stores them in the current instance.
```c++
Points2D<int> points1;
std::cin >> points1; // 3 5 8 14 6 2 1 -> (5, 8) (14, 6) (2, 1)

Points2D<double> points2;
std::cin >> points2; // 2 1.5 2.7 3.1 4.2 -> (1.5, 2.7) (3.1, 4.2)
```
> **Note** You must follow the format of the input, otherwise the program will not work as expected.
> - The first input is the number of points to be inputted, in this case being the size of the Points2D class instance.
> - The next following inputs are the x and y components of the points, with every two inputs being a point, everything separated by a space.
> - The number of inputs must be equal to the size of the Points2D class instance multiplied by 2.
>
> ex. <br>
> ```bash
> $ 3 5 8 14 6 2 1
> ```
> This should be read as `(5, 8) (14, 6) (2, 1)` and will be stored in the Points2D class instance while setting its size to 3. <br>
> ex. <br>
> ```bash
> $ 2 1.5
> ```
> This will result in an error since the given size is 2, but only one input was given. <br>

## Destructor

### `~Points2D() noexcept`
Destroys the current instance of the Points2D class and frees up the memory used to store the points.
```c++
Points2D<int> points;

// Will call the destructor once points goes out of scope and is not referenced anymore
```

Youssef Elshabasy - 2022
