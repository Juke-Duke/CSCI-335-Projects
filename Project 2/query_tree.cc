// Youssef Elshabasy
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace
{

	/// @brief Reads a file, inserts the data into an AVL tree, and then reads input to display all enzymes of a given recognition sequence, else will display Not Found.
	/// @tparam TreeType The type of tree to use.
	/// @param db_filename The name of the file to insert data from.
	/// @param a_tree The tree to insert the data into.
	template <typename TreeType>
	void QueryTree(const std::string& db_filename, TreeType& a_tree)
	{
		std::ifstream dbFile(db_filename);
		std::string dbLine;

		// Skip the first 10 lines of the file.
		for (int i = 0; i < 10; ++i)
			std::getline(dbFile, dbLine);

		// Read the database file and insert SequenceMaps into the tree.
		while (dbFile >> dbLine)
		{
			std::string enzymeAcronym;
			std::string recognitionSequence;

			// Parse the enzyme acronym and recognition sequence from the line.
			for (size_t i = 0; i < dbLine.size() - 1; ++i)
			{
				if (dbLine[i] == '/' && dbLine[i + 1] == '/')
				{
					SequenceMap newSequenceMap(recognitionSequence, enzymeAcronym);
					a_tree.insert(newSequenceMap);
				}
				else if (dbLine[i] != '/')
					recognitionSequence += dbLine[i];
				else
				{
					if (enzymeAcronym.empty())
						enzymeAcronym = recognitionSequence;
					else
					{
						SequenceMap temp(recognitionSequence, enzymeAcronym);
						a_tree.insert(temp);
					}

					recognitionSequence.clear();
				}
			}
		}

		dbFile.close();

		std::string recognitionSequence;

		// Read in the recognition sequence(s) from the user.
		while (std::cin >> recognitionSequence)
		{
			SequenceMap target(recognitionSequence, "");

			const SequenceMap* result = a_tree.find(target);

			if (result != nullptr)
				std::cout << *result << std::endl;
			else
				std::cout << "Not Found" << std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
		return 0;
	}
	const std::string db_filename(argv[1]);

	cout << "Input filename is " << db_filename << endl;
	AvlTree<SequenceMap> a_tree;
	QueryTree(db_filename, a_tree);

	return 0;
}
