#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace
{
  /// @brief Internal method to return a prime number at least as large as n.
  /// @param n The number to test for primality or to use as a starting point.
  /// @return The next prime number.
  bool IsPrime(size_t n)
  {
    if (n == 2 || n == 3)
      return true;

    if (n == 1 || n % 2 == 0)
      return false;

    for (int i = 3; i * i <= n; i += 2)
      if (n % i == 0)
        return false;

    return true;
  }

  /// @brief Internal method to return a prime number at least as large as n.
  /// @param n The number to test for primality or to use as a starting point.
  /// @return The next prime number.
  int NextPrime(size_t n)
  {
    if (n % 2 == 0)
      ++n;

    while (!IsPrime(n))
      n += 2;

    return n;
  }
}  // namespace


/// @brief Quadratic probing implementation for a hash table.
/// @tparam HashedObj The type of object to store in the hash table indexed by a hash.
template <typename HashedObj>
class HashTable
{
public:
  enum EntryType { ACTIVE, EMPTY, DELETED };

  /// @brief Construct a hash table with a given size.
  /// @param size The size of the hash table, defaults to 101.
  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
  {
    MakeEmpty();
  }

  /// @brief Determine if the hash table contains a given object.
  /// @param x The object to search for.
  /// @return True if the object is in the hash table, false otherwise.
  bool Contains(const HashedObj& x)
  {
    return IsActive(FindPos(x));
  }

  /// @brief Get the current capacity of the hash table.
  /// @return The number of slots in the hash table.
  size_t GetCapacity() const
  {
    return array_.size();
  }

  /// @brief Clears the hash table.
  void MakeEmpty()
  {
    current_size_ = 0;
    for (auto& entry : array_)
      entry.info_ = EMPTY;
  }

  /// @brief Insert a new object into the hash table.
  /// @param x The object to insert.
  /// @return True if the object was inserted, false if the object already exists.
  bool Insert(const HashedObj& x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }

  /// @brief Insert a new object into the hash table.
  /// @param x The rvalue object to insert.
  /// @return True if the object was inserted, false if the object already exists.
  bool Insert(HashedObj&& x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  /// @brief Get the total amount of collisions of this hash table.
  /// @return The total number of collisions
  size_t GetTotalCollisions() const
  {
    return totalCollisions;
  }

  /// @brief Get the amount of probes for a search.
  /// @return The number of probes for a search.
  size_t GetProbes(const HashedObj& x) const
  {
    size_t probes = 1;
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x)
    {
      ++probes;
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
        current_pos -= array_.size();
    }

    return probes;
  }

  /// @brief Remove an object from the hash table.
  /// @param x The object to remove.
  /// @return True if the object was removed, false if the object was not found.
  bool Remove(const HashedObj& x)
  {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

private:
  struct HashEntry
  {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
      : element_{ e }, info_{ i }
    { }

    HashEntry(HashedObj&& e, EntryType i = EMPTY)
      : element_{ std::move(e) }, info_{ i }
    { }
  };

  std::vector<HashEntry> array_;
  size_t current_size_;
  size_t totalCollisions = 0;

  /// @brief Checks to see if the current position is active.
  /// @param current_pos The current position in the hash table.
  /// @return True if the current position is active, false otherwise.
  bool IsActive(size_t current_pos) const
  {
    return array_[current_pos].info_ == ACTIVE;
  }

  /// @brief Finds the position of an object in the hash table.
  /// @param x The object to find the position of.
  /// @return The position of the object in the hash table.
  size_t FindPos(const HashedObj& x)
  {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x)
    {
      ++totalCollisions;
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
        current_pos -= array_.size();
    }
    return current_pos;
  }

  /// @brief Will resize the hash table to the next prime number.
  void Rehash()
  {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto& entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto& entry : old_array)
      if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
  }

  /// @brief Hash function for the hash table.
  /// @param x The object to hash.
  /// @return The hash value of the object.
  size_t InternalHash(const HashedObj& x) const
  {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
};

#endif  // QUADRATIC_PROBING_H