// Homework 4
// Various sorting algorithms implementations
// Youssef Elshabasy

#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <functional>
using namespace std;

/// @brief Insertion sort algorithm.
/// @tparam TComparable The type of the elements to be sorted.
/// @param a The vector to be sorted.
template <typename TComparable>
void insertionSort(vector<TComparable>& a)
{
    for (int p = 1; p < a.size(); ++p)
    {
        TComparable tmp = std::move(a[p]);

        int j;
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}

/// @brief Internal insertion sort routine for subarrays that is used by quicksort.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
template <typename TComparable, typename TComparator>
void insertionSort(vector<TComparable>& a, int left, int right, TComparator comparator)
{
    for (int p = left + 1; p <= right; ++p)
    {
        TComparable tmp = std::move(a[p]);

        int j;
        for (j = p; j > left && comparator(tmp, a[j - 1]); --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}

/// @brief Shell sort algorithm.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
template <typename TComparable, typename TComparator>
void shellsort(vector<TComparable>& a, TComparator comparator = std::less<TComparable>())
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < a.size(); ++i)
        {
            TComparable tmp = std::move(a[i]);

            int j = i;
            for (; j >= gap && comparator(tmp, a[j - gap]); j -= gap)
                a[j] = std::move(a[j - gap]);
            a[j] = std::move(tmp);
        }
    }
}

/// @brief Internal method for heapsort.
/// @param i The index of an item in the heap.
/// @return The index of the left child.
inline int leftChild(int i)
{
    return 2 * i + 1;
}

/// @brief Internal method for heapsort that is used in deleteMax and buildHeap.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param i The index of an item in the heap.
/// @param n The logical size of the binary heap.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void percDown(vector<TComparable>& a, int i, int n, TComparator comparator)
{
    int child;
    TComparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && comparator(a[child], a[child + 1]))
            ++child;
        if (comparator(tmp, a[child]))
            a[i] = std::move(a[child]);
        else
            break;
    }
    a[i] = std::move(tmp);
}

/// @brief Heap sort algorithm.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void heapsort(vector<TComparable>& a, TComparator comparator = std::less<TComparable>())
{
    for (int i = a.size() / 2 - 1; i >= 0; --i)  /* buildHeap */
        percDown(a, i, a.size(), comparator);
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]);               /* deleteMax */
        percDown(a, 0, j, comparator);
    }
}

/// @brief Internal method that merges two sorted halves of a subarray.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param tmpArray The temporary array.
/// @param leftPos The left-most index of the subarray.
/// @param rightPos The index of the start of the second half.
/// @param rightEnd The right-most index of the subarray.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void merge(vector<TComparable>& a, vector<TComparable>& tmpArray,
    int leftPos, int rightPos, int rightEnd,
    TComparator comparator = std::less<TComparable>{})
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (comparator(a[leftPos], a[rightPos]))
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)    // Copy rest of first half
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)  // Copy rest of right half
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/// @brief Internal method for mergesort to split the array.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param tmpArray The temporary array.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void mergeSort(vector<TComparable>& a,
    vector<TComparable>& tmpArray, int left, int right,
    TComparator comparator = std::less<TComparable>{})
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center, comparator);
        mergeSort(a, tmpArray, center + 1, right, comparator);
        merge(a, tmpArray, left, center + 1, right, comparator);
    }
}

/// @brief Merge sort algorithm.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void mergeSort(vector<TComparable>& a, TComparator comparator = std::less<TComparable>{})
{
    vector<TComparable> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size() - 1, comparator);
}

/// @brief Internal method for quicksort.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @return The median of left, center, and right.
template <typename TComparable, typename TComparator>
const TComparable& median3(vector<TComparable>& a, int left, int right, TComparator comparator)
{
    int center = (left + right) / 2;
    if (comparator(a[center], a[left]))
        std::swap(a[left], a[center]);
    if (comparator(a[right], a[left]))
        std::swap(a[left], a[right]);
    if (comparator(a[right], a[center]))
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

/// @brief Internal method for quicksort.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort(vector<TComparable>& a, int left, int right, TComparator comparator = std::less<TComparable>{})
{
    if (left + 10 <= right)
    {
        const TComparable& pivot = median3(a, left, right, comparator);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (comparator(a[++i], pivot)) { }
            while (comparator(pivot, a[--j])) { }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

        quicksort(a, left, i - 1, comparator);     // Sort small elements
        quicksort(a, i + 1, right, comparator);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right, comparator);
}

/// @brief Internal method for quicksort with middle element as pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort2(vector<TComparable>& a, int left, int right, TComparator comparator = std::less<TComparable>{})
{
    if (left + 10 <= right)
    {
        swap(a[(left + right) / 2], a[right]);
        const TComparable& pivot = a[right];

        // Begin partitioning
        int i = left - 1, j = right;
        for (;;)
        {
            while (comparator(a[++i], pivot)) { }
            while (comparator(pivot, a[--j])) { }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right]);  // Restore pivot

        quicksort2(a, left, i - 1, comparator);     // Sort small elements
        quicksort2(a, i + 1, right, comparator);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right, comparator);
}

/// @brief Internal method for quicksort with first element as pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort3(vector<TComparable>& a, int left, int right, TComparator comparator = std::less<TComparable>{})
{
    if (left + 10 <= right)
    {
        swap(a[left], a[right]);
        const TComparable& pivot = a[right];

        // Begin partitioning
        int i = left - 1, j = right;
        for (;;)
        {
            while (comparator(a[++i], pivot)) { }
            while (--j >= 0 && comparator(pivot, a[j])) { }

            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right]);  // Restore pivot

        quicksort3(a, left, i - 1, comparator);     // Sort small elements
        quicksort3(a, i + 1, right, comparator);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right, comparator);
}

/// @brief Quick sort algorithm with median-of-three pivot selection.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort(vector<TComparable>& a, TComparator comparator = std::less<TComparable>{})
{
    quicksort(a, 0, a.size() - 1, comparator);
}

/// @brief Quicksort algorithm with middle element as pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort2(vector<TComparable>& a, TComparator comparator = std::less<TComparable>{})
{
    quicksort2(a, 0, a.size() - 1, comparator);
}

/// @brief Quicksort algorithm with first element as pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void quicksort3(vector<TComparable>& a, TComparator comparator = std::less<TComparable>{})
{
    quicksort3(a, 0, a.size() - 1, comparator);
}

/// @brief Internal method for quick selection.
/// @tparam TComparable The type of the elements to be sorted.
/// @param a The vector to be sorted.
/// @param left The left-most index of the subarray.
/// @param right The right-most index of the subarray.
/// @param k The desired rank (1 is minimum) in the entire array.
template <typename TComparable>
void quickSelect(vector<TComparable>& a, int left, int right, int k)
{
    if (left + 10 <= right)
    {
        const TComparable& pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (a[++i] < pivot) { }
            while (pivot < a[--j]) { }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

        // Recurse; only this part changes
        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}

/// @brief Quick selection algorithm.
/// @tparam TComparable The type of the elements to be sorted.
/// @param a The vector to be sorted.
/// @param k The desired rank (1 is minimum) in the entire array.
template <typename TComparable>
void quickSelect(vector<TComparable>& a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}

template <typename TComparable>
void SORT(vector<TComparable>& items)
{
    if (items.size() > 1)
    {
        vector<TComparable> smaller;
        vector<TComparable> same;
        vector<TComparable> larger;

        auto chosenItem = items[items.size() / 2];

        for (auto& i : items)
        {
            if (i < chosenItem)
                smaller.push_back(std::move(i));
            else if (chosenItem < i)
                larger.push_back(std::move(i));
            else
                same.push_back(std::move(i));
        }

        SORT(smaller);     // Recursive call!
        SORT(larger);      // Recursive call!

        std::move(begin(smaller), end(smaller), begin(items));
        std::move(begin(same), end(same), begin(items) + smaller.size());
        std::move(begin(larger), end(larger), end(items) - larger.size());

        /*
                items.clear( );
                items.insert( end( items ), begin( smaller ), end( smaller ) );
                items.insert( end( items ), begin( same ), end( same ) );
                items.insert( end( items ), begin( larger ), end( larger ) );
        */
    }
}

/// @brief The more public version of insertion sort. It requires a pair of iteratorsand a comparison function object.
/// @tparam RandomIterator The type of the iterator.
/// @tparam TComparator The type of the comparator.
/// @param begin The begin iterator.
/// @param end The end iterator.
/// @param comparator The comparator.
template <typename RandomIterator, typename TComparator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end,
    TComparator comparator)
{
    if (begin == end)
        return;

    RandomIterator j;

    for (RandomIterator p = begin + 1; p != end; ++p)
    {
        auto tmp = std::move(*p);
        for (j = p; j != begin && comparator(tmp, *(j - 1)); --j)
            *j = std::move(*(j - 1));
        *j = std::move(tmp);
    }
}

/// @brief The The two-parameter version calls the three parameter version, using C++11 decltype
/// @tparam RandomIterator The type of the iterator.
/// @param begin The begin iterator.
/// @param end The end iterator.
template <typename RandomIterator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end)
{
    insertionSort(begin, end, less<decltype(*begin)>{ });
}

/// @brief Heapsort with a comparator.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void HeapSort(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    heapsort(a, comparator);
}

/// @brief Mergesort with a comparator.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void MergeSort(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    mergeSort(a, comparator);
}

/// @brief Quicksort with a comparator.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void QuickSort(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    quicksort(a, comparator);
}

/// @brief Quicksort with a comparator and the middle element as the pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void QuickSort2(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    quicksort2(a, comparator);
}

/// @brief Quicksort with a comparator and the first element as the pivot.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void QuickSort3(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    quicksort3(a, comparator);
}

/// @brief Shellsort with a comparator.
/// @tparam TComparable The type of the elements to be sorted.
/// @tparam TComparator The type of the comparator.
/// @param a The vector to be sorted.
/// @param comparator The comparator.
template <typename TComparable, typename TComparator>
void ShellSort(vector<TComparable>& a, TComparator comparator)
{
    if (a.empty())
    {
        cout << "Invalid size" << endl;
        return;
    }

    shellsort(a, comparator);
}

#endif  // SORT_H
