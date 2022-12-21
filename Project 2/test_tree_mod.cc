// Youssef Elshabasy
// Main file for Part2(c) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree_p2c.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace
{
	/// @brief Reads a file, inserts the data into an AVL tree, and then does multiple calculations for recursion counts, node amount, and finding data.
	/// @tparam TreeType The type of tree to use.
	/// @param db_filename The name of the file to insert data from.
	/// @param seq_filename The sequences to do operations on.
	/// @param a_tree The tree to insert the data into.
	template <typename TreeType>
	void TestTree(const string& db_filename, const string& seq_filename, TreeType& a_tree)
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

		std::cout << "2: " << a_tree.count() << std::endl; // Prints the amount of nodes in the tree.
		std::cout << "3a: " << a_tree.avgDepth() << std::endl; // Prints the average depth of traversal to a node.
		std::cout << "3b: " << a_tree.avgDepth() / a_tree.count() << std::endl; // Prints the average depth of traversal to a node in ratio to amount of nodes in the tree.

		double recursionCount = 0;
		int successCount = 0;
		int sequenceCount = 0;

		std::ifstream seqFile(seq_filename);

		// Read the sequence file and find the sequences in the tree.
		while (seqFile >> dbLine)
		{
			++sequenceCount;
			SequenceMap curr(dbLine, "");
			successCount += a_tree.contains(curr);
			recursionCount += a_tree.findRecursionCount(curr);
		}

		seqFile.close();

		std::cout << "4a: " << successCount << std::endl; // Prints the amount of sequences found in the tree.
		std::cout << "4b: " << recursionCount / sequenceCount << std::endl; // Prints the total amount of recursions to find all nodes in ratio to all the nodes given.

		seqFile.open(seq_filename);

		bool skip = false;
		recursionCount = 0;
		successCount = 0;

		// Reads every other sequence in the file and removes it from the tree.
		while (seqFile >> dbLine)
		{
			if (skip)
			{
				skip = false;
				continue;
			}

			SequenceMap curr(dbLine, "");
			bool contains = a_tree.contains(curr);
			successCount += contains;
			recursionCount += contains ? a_tree.removeRecursionCount(curr) : 0;
			a_tree.remove(curr);
			skip = true;
		}

		std::cout << "5a: " << successCount << std::endl; // Prints the amount of sequences removed from the tree.
		std::cout << "5b: " << recursionCount / successCount << std::endl; // Prints the total amount of recursions to remove all nodes in ratio to the successful removals.
		std::cout << "6a: " << a_tree.count() << std::endl;	// Prints the amount of nodes in the tree.
		std::cout << "6b: " << a_tree.avgDepth() << std::endl; // Prints the average depth of traversal to a node.
		std::cout << "6c: " << a_tree.avgDepth() / a_tree.count() << std::endl; // Prints the average depth of traversal to a node in ratio to amount of nodes in the tree.
	}
}  // namespace

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);
	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
	AvlTree<SequenceMap> a_tree;
	TestTree(db_filename, seq_filename, a_tree);

	return 0;
}
