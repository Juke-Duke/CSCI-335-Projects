// Youssef Elshabasy
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include "double_hashing.h"
using namespace std;

/// @brief Creates and fills double hashing hash table with all words from
/// @param dictionary_file The file containing the dictionary
/// @return The hash table containing the dictionary
HashTableDouble<string> MakeDictionary(const string& dictionary_file)
{
  HashTableDouble<string> dictionary_hash;
  dictionary_hash.SetRValue(89);
  ifstream dictionaryFile(dictionary_file);
  string line;

  while (dictionaryFile >> line)
  {
    dictionary_hash.Insert(line);
  }

  return dictionary_hash;
}

/// @brief Checks if a word is in the dictionary and will offer alternatives if not with 3 techniques
/// @param dictionary The dictionary hash table
/// @param document_file The file containing the document
void SpellChecker(HashTableDouble<string>& dictionary, const string& document_file)
{
  ifstream documentFile(document_file);
  string line;
  string word = "";
  vector<string> words;

  while (documentFile >> line)
  {
    for (auto& c : line)
    {
      if (c != ' ')
      {
        word += tolower(c);
      }
      else if (word != "")
      {
        if (!isalpha(word[0]) && !isdigit(word[0]))
          word = word.substr(1);
        if (!isalpha(word[word.size() - 1]) && !isdigit(word[word.size() - 1]))
          word.pop_back();

        words.push_back(word);
        word.clear();
      }
    }

    if (!word.empty())
    {
      if (!isalpha(word[0]) && !isdigit(word[0]))
        word = word.substr(1);
      if (!isalpha(word[word.size() - 1]) && !isdigit(word[word.size() - 1]))
        word.pop_back();

      words.push_back(word);
    }
    word.clear();
  }

  for (auto& word : words)
  {
    if (dictionary.Contains(word))
      cout << word << " is CORRECT" << endl;
    else
    {
      cout << word << " is INCORRECT" << endl;

      // Case A: Adding one character in any possible position
      for (size_t i = 0; i < word.size() + 1; ++i)
      {
        for (int j = 0; j < 26; ++j)
        {
          string temp = word;
          temp.insert(i, 1, 'a' + j);
          if (dictionary.Contains(temp))
            cout << "** " << word << " -> " << temp << " ** case A" << endl;
        }
      }

      // Case B: Removing one character
      for (size_t i = 0; i < word.size(); ++i)
      {
        string temp = word;
        temp.erase(i, 1);
        if (dictionary.Contains(temp))
          cout << "** " << word << " -> " << temp << " ** case B" << endl;
      }

      // Case C: Swapping two adjacent characters
      for (size_t i = 0; i < word.size() - 1; ++i)
      {
        string temp = word;
        swap(temp[i], temp[i + 1]);
        if (dictionary.Contains(temp))
          cout << "** " << word << " -> " << temp << " ** case C" << endl;
      }
    }
  }

  documentFile.close();
}

/// @brief Wrapper function for spell checker
/// @param argument_count The number of arguments
/// @param argument_list The list of arguments
/// @return 0 if successful.
int testSpellingWrapper(int argument_count, char** argument_list)
{
  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  // Call functions implementing the assignment requirements.
  HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
  SpellChecker(dictionary, document_filename);

  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}
