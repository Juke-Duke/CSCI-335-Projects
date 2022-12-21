// Youssef Elshabasy
#include <fstream>
#include <iostream>
#include <string>

#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"
using namespace std;

/// @brief Series of tests to display information about the hash table.
/// @tparam HashTableType The type of hash table to test.
/// @param hash_table The hash table to test (can be linear, quadratic, or double).
/// @param words_filename The filename of input words to construct the hash table.
/// @param query_filename The filename of input words to test the hash table.
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType& hash_table, const string& words_filename, const string& query_filename)
{
    hash_table.MakeEmpty();

    std::string line;
    std::ifstream wordsFile(words_filename);

    size_t elements = 0;
    size_t collisions = 0;

    while (wordsFile >> line)
        elements += hash_table.Insert(line);

    collisions = hash_table.GetTotalCollisions();

    wordsFile.close();

    std::cout << "number_of_elements: " << elements << std::endl;
    std::cout << "size_of_table: " << hash_table.GetCapacity() << std::endl;
    std::cout << "load_factor: " << (double)elements / hash_table.GetCapacity() << std::endl;
    std::cout << "collisions: " << collisions << std::endl;
    std::cout << "avg_collisions: " << (double)collisions / elements << std::endl;

    std::cout << std::endl;

    std::ifstream queryFile(query_filename);

    while (queryFile >> line)
        std::cout << line << " " << (hash_table.Contains(line) ? "Found " : "Not_Found ") << hash_table.GetProbes(line) << std::endl;

    queryFile.close();
}

/// @brief Wrapper function to call the specific testing function for hash table (linear, quadratic, or double).
/// @param argument_count argc as provided in main.
/// @param argument_list argv as provided in main.
/// @return 0 if successful.
int testHashingWrapper(int argument_count, char** argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    }
    else if (param_flag == "quadratic")
    {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    }
    else if (param_flag == "double")
    {
        cout << "r_value: " << R << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetRValue(R);
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    }
    else
    {
        cout << "Unknown tree type " << param_flag
            << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
            << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
            << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
