// Homework 4
// Testing Sorting Algorithms and timing them
// Youssef Elshabasy

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

/// @brief Validates the vector is sorted using the given comparator.
/// @tparam Comparable The type of the elements in the vector.
/// @tparam Comparator The type of the comparator.
/// @param input The vector to validate.
/// @param comparator The comparator to use.
/// @return True if the vector is sorted, false otherwise.
template <typename TComparable, typename TComparator>
bool VerifyOrder(const vector<TComparable>& input, TComparator comparator)
{
  for (size_t i = 0; i < input.size() - 1; ++i)
    if (!comparator(input[i], input[i + 1]))
      return false;

  return true;
}

/// @brief Computes the duration two time points.
/// @param start_time The start time.
/// @param end_time The end time.
/// @return The duration between the two time points.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time,
  chrono::high_resolution_clock::time_point end_time)
{
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

template <typename TComparable, typename TComparator>
void TimeHeapSort(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  HeapSort(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Heapsort\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeMergeSort(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  MergeSort(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Mergesort\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeQuickSort(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  QuickSort(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Quicksort\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeQuickSortMiddle(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  QuickSort(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Median of Three\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeQuickSort2(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  QuickSort2(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Middle\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeQuickSort3(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  QuickSort3(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "First\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

template <typename TComparable, typename TComparator>
void TimeShellSort(vector<TComparable> input, TComparator comparator)
{
  const auto begin_time = chrono::high_resolution_clock::now();
  ShellSort(input, comparator);
  const auto end_time = chrono::high_resolution_clock::now();
  cout << "Shellsort\n" << ComputeDuration(begin_time, end_time) << " ns" << endl;
  cout << "Verified: " << VerifyOrder(input, comparator) << endl;
}

/// @brief Generates a vector of random integers.
/// @param size_of_vector The size of the vector to generate.
/// @return A vector of random integers.
vector<int> GenerateRandomVector(size_t size_of_vector)
{
  vector<int> random_vector;

  for (size_t i = 0; i < size_of_vector; ++i)
    random_vector.push_back(rand());

  return random_vector;
}

/// @brief Generates a vector of sorted integers.
/// @param size_of_vector The size of the vector to generate.
/// @param smaller_to_larger If true, the vector will be sorted from smallest to largest.
/// @return A vector of sorted integers.
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger)
{
  vector<int> sorted_vector;
  for (size_t i = 1; i <= size_of_vector; ++i)
  {
    if (smaller_to_larger)
      sorted_vector.push_back(i);
    else
      sorted_vector.push_back(size_of_vector - i + 1);
  }

  return sorted_vector;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char** argv)
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small")
  {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0)
  {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater")
  {
    cout << "Invalid comparison type" << endl;
    return;
  }

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl << endl;
  vector<int> input_vector;
  if (input_type == "random")
    input_vector = GenerateRandomVector(input_size);
  else if (input_type == "sorted_small_to_large")
    input_vector = GenerateSortedVector(input_size, true);
  else if (input_type == "sorted_large_to_small")
    input_vector = GenerateSortedVector(input_size, false);

  if (comparison_type == "less")
  {
    TimeHeapSort(input_vector, less<int>{});
    cout << endl;
    TimeMergeSort(input_vector, less<int>{});
    cout << endl;
    TimeQuickSort(input_vector, less<int>{});
    cout << endl;
    cout << "Testing Quicksort Pivot Implementations" << endl;
    cout << endl;
    TimeQuickSortMiddle(input_vector, less<int>{});
    cout << endl;
    TimeQuickSort2(input_vector, less<int>{});
    cout << endl;
    TimeQuickSort3(input_vector, less<int>{});
    cout << endl;
    TimeShellSort(input_vector, less<int>{});
  }
  else
  {
    TimeHeapSort(input_vector, greater<int>{});
    cout << endl;
    TimeMergeSort(input_vector, greater<int>{});
    cout << endl;
    TimeQuickSort(input_vector, greater<int>{});
    cout << endl;
    cout << "Testing Quicksort Pivot Implementations" << endl;
    cout << endl;
    TimeQuickSortMiddle(input_vector, greater<int>{});
    cout << endl;
    TimeQuickSort2(input_vector, greater<int>{});
    cout << endl;
    TimeQuickSort3(input_vector, greater<int>{});
    cout << endl;
    TimeShellSort(input_vector, greater<int>{});
  }
}

int main(int argc, char** argv)
{
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  testSortingWrapper(argc, argv);

  return 0;
}
