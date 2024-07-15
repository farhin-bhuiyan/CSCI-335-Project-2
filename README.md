# Spell Checker Project

## Project Overview

This project implements a spell checker using various hashing techniques: linear probing, quadratic probing, and double hashing. The spell checker reads a document, checks each word against a dictionary, and identifies misspelled words. It also provides possible corrections for each misspelled word by applying the following rules:

1. Adding one character in any possible position.
2. Removing one character from the word.
3. Swapping adjacent characters in the word.

## Project Structure

The project consists of the following files:

### 1. `create_and_test_hash.cc`

This file contains the main driver code to test different hashing techniques (linear probing, quadratic probing, and double hashing). It reads a list of words to construct the hash table and a list of query words to test the hash table. The output includes the number of elements, table size, load factor, number of collisions, and average number of collisions.

#### Key Functions:

- `TestFunctionForHashTable`: Tests the hash table with the given words and query files and prints the results.
- `testHashingWrapper`: Wrapper function to handle command-line arguments and call the appropriate hash table test function.

### 2. `spell_check.cc`

This file contains the implementation of the spell checker using double hashing. It reads a dictionary file to construct the hash table and a document file to spell-check.

#### Key Functions:

- `MakeDictionary`: Creates and fills a hash table with all words from the dictionary file.
- `AddOneChar`, `RemoveOneChar`, `SwapAdjacentChars`: Generate possible corrections for misspelled words.
- `SpellChecker`: Checks each word in the document file against the dictionary and prints the results.
- `testSpellingWrapper`: Wrapper function to handle command-line arguments and call the spell checker functions.

### 3. `quadratic_probing.h`

This file implements the quadratic probing hash table. It includes methods for inserting, removing, and checking the existence of elements in the hash table.

### 4. `linear_probing.h`

This file implements the linear probing hash table. It includes methods for inserting, removing, and checking the existence of elements in the hash table.

### 5. `double_hashing.h`

This file implements the double hashing hash table. It includes methods for inserting, removing, and checking the existence of elements in the hash table.

### 6. `common.h`

This file includes common functions and definitions shared between different hash table implementations, such as `IsPrime` and `NextPrime`.

## Running the Project

### Prerequisites

- A C++ compiler that supports C++11 or later (e.g., `g++`).

### Compilation

1. **Compile the hashing test program:**

   ```sh
   g++ -std=c++11 -o create_and_test_hash create_and_test_hash.cc
