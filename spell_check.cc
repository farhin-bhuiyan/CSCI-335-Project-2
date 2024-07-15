// Farhin Bhuiyan
// spell_check.cc: A simple spell checker.

#include <fstream>          // Include file stream for file operations
#include <iostream>         // Include input-output stream for console operations
#include <string>           // Include string for string operations
#include <unordered_set>    // Include unordered_set for storing unique corrections
#include <vector>           // Include vector for dynamic arrays
#include <algorithm>        // Include algorithm for standard algorithms
#include <cctype>           // Include cctype for character handling functions

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h" // Include double hashing implementation
using namespace std;

// Helper function to remove punctuation and convert to lowercase
string CleanWord(const string &word) {
  string cleaned_word;
  for (char ch : word) {
    if (isalpha(ch)) { // Check if character is alphabetic
      cleaned_word += tolower(ch); // Convert to lowercase and add to cleaned_word
    }
  }
  return cleaned_word; // Return the cleaned word
}

// Creates and fills double hashing hash table with all words from dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash; // Create a hash table for the dictionary
  ifstream infile(dictionary_file); // Open the dictionary file
  string word;
  while (infile >> word) { // Read each word from the dictionary file
    dictionary_hash.Insert(CleanWord(word)); // Insert cleaned word into the hash table
  }
  return dictionary_hash; // Return the populated hash table
}

// Generate possible corrections by adding one character
vector<string> AddOneChar(const string &word) {
  vector<string> corrections; // Vector to store possible corrections
  for (size_t i = 0; i <= word.size(); ++i) {
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      string corrected_word = word;
      corrected_word.insert(corrected_word.begin() + i, ch); // Insert a character at each position
      corrections.push_back(corrected_word); // Add to corrections vector
    }
  }
  return corrections; // Return all possible corrections
}

// Generate possible corrections by removing one character
vector<string> RemoveOneChar(const string &word) {
  vector<string> corrections; // Vector to store possible corrections
  for (size_t i = 0; i < word.size(); ++i) {
    string corrected_word = word;
    corrected_word.erase(corrected_word.begin() + i); // Remove a character from each position
    corrections.push_back(corrected_word); // Add to corrections vector
  }
  return corrections; // Return all possible corrections
}

// Generate possible corrections by swapping adjacent characters
vector<string> SwapAdjacentChars(const string &word) {
  vector<string> corrections; // Vector to store possible corrections
  for (size_t i = 0; i < word.size() - 1; ++i) {
    string corrected_word = word;
    swap(corrected_word[i], corrected_word[i + 1]); // Swap adjacent characters
    corrections.push_back(corrected_word); // Add to corrections vector
  }
  return corrections; // Return all possible corrections
}

// For each word in the document_file, it checks the 3 cases for a word being misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {
  ifstream infile(document_file); // Open the document file
  string word;
  while (infile >> word) { // Read each word from the document file
    string cleaned_word = CleanWord(word); // Clean the word by removing punctuation and converting to lowercase
    int probes = 0; // Variable to count the number of probes
    if (dictionary.Contains(cleaned_word, probes)) { // Check if the cleaned word is in the dictionary
      cout << cleaned_word << " is CORRECT" << endl; // Print if the word is correct
    } else {
      cout << cleaned_word << " is INCORRECT" << endl; // Print if the word is incorrect
      auto add_corrections = AddOneChar(cleaned_word); // Generate corrections by adding one character
      auto remove_corrections = RemoveOneChar(cleaned_word); // Generate corrections by removing one character
      auto swap_corrections = SwapAdjacentChars(cleaned_word); // Generate corrections by swapping adjacent characters
      unordered_set<string> all_corrections(add_corrections.begin(), add_corrections.end()); // Store all corrections in an unordered set
      all_corrections.insert(remove_corrections.begin(), remove_corrections.end()); // Add remove corrections to the set
      all_corrections.insert(swap_corrections.begin(), swap_corrections.end()); // Add swap corrections to the set
      for (const string &correction : all_corrections) { // Check each correction
        if (dictionary.Contains(correction, probes)) { // If correction is in the dictionary
          if (find(add_corrections.begin(), add_corrections.end(), correction) != add_corrections.end()) {
            cout << "** " << cleaned_word << " -> " << correction << " ** case A" << endl; // Print case A correction
          } else if (find(remove_corrections.begin(), remove_corrections.end(), correction) != remove_corrections.end()) {
            cout << "** " << cleaned_word << " -> " << correction << " ** case B" << endl; // Print case B correction
          } else if (find(swap_corrections.begin(), swap_corrections.end(), correction) != swap_corrections.end()) {
            cout << "** " << cleaned_word << " -> " << correction << " ** case C" << endl; // Print case C correction
          }
        }
      }
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: same as argv in main.
// Implements the functionality by calling appropriate functions with the provided arguments
int testSpellingWrapper(int argument_count, char** argument_list) {
  const string document_filename(argument_list[1]); // Get the document file name from arguments
  const string dictionary_filename(argument_list[2]); // Get the dictionary file name from arguments

  // Call functions implementing the assignment requirements.
  HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename); // Create and populate the dictionary hash table
  SpellChecker(dictionary, document_filename); // Check the spelling in the document file

  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) { // Check if the number of arguments is correct
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl; // Print usage instructions if the number of arguments is incorrect
    return 0;
  }
  
  testSpellingWrapper(argc, argv); // Call the wrapper function with the provided arguments
  
  return 0;
}



