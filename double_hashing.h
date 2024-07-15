// Farhin Bhuiyan
#ifndef DOUBLE_HASHING_H // Include guard to prevent multiple inclusions of this header file
#define DOUBLE_HASHING_H

#include <vector>         // Include vector for dynamic array
#include <algorithm>      // Include algorithm for standard algorithms
#include <functional>     // Include functional for hash functions
#include "common.h"       // Include common functions and definitions

// Double hashing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  // Enum to define the state of each entry in the hash table
  enum EntryType { ACTIVE, EMPTY, DELETED };

  // Constructor to initialize the hash table with a given size and R value
  explicit HashTableDouble(size_t size = 101, int r = 89)
    : array_(NextPrime(size)), R_(r) { // Initialize array with next prime number >= size and set R value
    MakeEmpty(); // Initialize the table to empty state
  }

  // Check if an element is in the hash table and count the number of probes
  bool Contains(const HashedObj & x, int &probes) const {
    size_t current_pos = FindPos(x, probes);
    return IsActive(current_pos);
  }

  // Insert an element into the hash table
  bool Insert(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos)) // Element already exists
      return false;
    array_[current_pos].element_ = x; // Insert the element
    array_[current_pos].info_ = ACTIVE; // Mark as active
    if (++current_size_ > array_.size() / 2) // Check load factor
      Rehash(); // Rehash if necessary
    return true;
  }

  // Insert an element into the hash table using move semantics
  bool Insert(HashedObj && x) {
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos)) // Element already exists
      return false;
    array_[current_pos] = std::move(x); // Insert the element
    array_[current_pos].info_ = ACTIVE; // Mark as active
    if (++current_size_ > array_.size() / 2) // Check load factor
      Rehash(); // Rehash if necessary
    return true;
  }

  // Remove an element from the hash table
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos)) // Element does not exist
      return false;
    array_[current_pos].info_ = DELETED; // Mark as deleted
    return true;
  }

  // Make the hash table empty
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY; // Mark all entries as empty
  }

  // Get the current number of elements in the hash table
  size_t Size() const {
    return current_size_;
  }

  // Get the size of the hash table
  size_t TableSize() const {
    return array_.size();
  }

  // Get the number of collisions that have occurred
  size_t NumCollisions() const {
    return num_collisions_;
  }

 private:
  // Structure to represent each entry in the hash table
  struct HashEntry {
    HashedObj element_; // The element stored
    EntryType info_; // The state of the entry

    // Constructors for HashEntry
    HashEntry(const HashedObj & e = HashedObj{}, EntryType i = EMPTY)
      : element_{ e }, info_{ i } {}

    HashEntry(HashedObj && e, EntryType i = EMPTY)
      : element_{ std::move(e) }, info_{ i } {}
  };

  std::vector<HashEntry> array_; // The array of hash entries
  size_t current_size_; // Current number of elements in the hash table
  mutable size_t num_collisions_ = 0; // Number of collisions (mutable to allow modification in const functions)
  int R_;  // The R value used in double hashing.

  // Check if a position in the hash table is active
  bool IsActive(size_t current_pos) const {
    return array_[current_pos].info_ == ACTIVE;
  }

  // Find the position of an element in the hash table and count probes
  size_t FindPos(const HashedObj & x, int &probes) const {
    size_t current_pos = InternalHash(x); // Primary hash
    size_t offset = R_ - (InternalHash2(x) % R_); // Secondary hash
    probes = 1; // Start with one probe

    // Double hashing: find the position or an empty slot
    while (array_[current_pos].info_ != EMPTY &&
           array_[current_pos].element_ != x) {
      current_pos += offset; // Compute ith probe
      probes++; // Increment the number of probes
      num_collisions_++; // Increment the number of collisions
      if (current_pos >= array_.size())
        current_pos -= array_.size(); // Wrap around if necessary
    }
    return current_pos;
  }

  // Find the position of an element in the hash table without counting probes
  size_t FindPos(const HashedObj & x) const {
    int probes = 0;
    return FindPos(x, probes);
  }

  // Rehash the hash table when the load factor is too high
  void Rehash() {
    std::vector<HashEntry> old_array = array_; // Copy the old array

    // Create a new double-sized, empty table
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY; // Mark all entries as empty

    // Copy the old entries into the new table
    current_size_ = 0;
    num_collisions_ = 0;
    for (auto & entry : old_array)
      if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
  }

  // Primary hash function to calculate the position of an element
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf; // Use the standard hash function
    return hf(x) % array_.size(); // Modulo the size of the array
  }

  // Secondary hash function to calculate the offset for double hashing
  size_t InternalHash2(const HashedObj & x) const {
    static std::hash<HashedObj> hf; // Use the standard hash function
    return hf(x); // Return the hash value
  }
};

#endif  // DOUBLE_HASHING_H

