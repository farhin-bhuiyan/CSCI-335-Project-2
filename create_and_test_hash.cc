// Farhin Bhuiyan
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

using namespace std;

// You can add more functions here

// Template function to test the hash table with words and queries
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    // Open the words file
    ifstream words_file(words_filename);
    // Open the query file
    ifstream query_file(query_filename);

    // Check if both files are successfully opened
    if (!words_file.is_open() || !query_file.is_open()) {
        cerr << "Unable to open file" << endl; // Print error message if files can't be opened
        return; // Exit the function if files can't be opened
    }

    string word;
    // Insert words from the words file into the hash table
    while (words_file >> word) {
        hash_table.Insert(word);
    }

    // Get the number of elements in the hash table
    size_t num_elements = hash_table.Size();
    // Get the size of the hash table
    size_t table_size = hash_table.TableSize();
    // Calculate the load factor
    float load_factor = static_cast<float>(num_elements) / table_size;
    // Get the number of collisions
    size_t num_collisions = hash_table.NumCollisions();
    // Calculate the average number of collisions
    float avg_collisions = static_cast<float>(num_collisions) / num_elements;

    // Print the results
    cout << "number_of_elements: " << num_elements << endl;
    cout << "size_of_table: " << table_size << endl;
    cout << "load_factor: " << fixed << setprecision(6) << load_factor << endl;
    cout << "collisions: " << num_collisions << endl;
    cout << "avg_collisions: " << fixed << setprecision(6) << avg_collisions << endl;
    cout << endl;

    // Check each word in the query file and print whether it is found and the number of probes
    while (query_file >> word) {
        int probes = 0;
        bool found = hash_table.Contains(word, probes);
        cout << word << " " << (found ? "Found " : "Not_Found ") << probes << endl;
    }
}

// Wrapper function to handle command-line arguments and call the appropriate hash table test function
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]); // Get the words file name from arguments
    const string query_filename(argument_list[2]); // Get the query file name from arguments
    const string param_flag(argument_list[3]);     // Get the flag indicating the type of hashing

    int R = 89; // Default R value for double hashing
    if (argument_count == 5) {
        const string rvalue(argument_list[4]); // Get the R value from arguments if provided
        R = stoi(rvalue); // Convert R value to an integer
    }

    // Choose the type of hash table based on the flag
    if (param_flag == "linear") {
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } else if (param_flag == "quadratic") {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    } else if (param_flag == "double") {
        cout << "r_value: " << R << endl;
        HashTableDouble<string> double_probing_table(101, R); // Create hash table with specified size and R value
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } else {
        cout << "Unknown hash type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
int main(int argc, char **argv) {
    if (argc != 4 && argc != 5) { // Check if the number of arguments is correct
        // Print usage instructions if the number of arguments is incorrect
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv); // Call the wrapper function with the provided arguments
    return 0;
}





