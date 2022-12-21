#pragma once

#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

class SequenceMap
{
private:
    std::string recognitionSequence;
    std::vector<std::string> enzymeAcronyms;

public:
    /// @brief Initializes a new instance of the SequenceMap class that contains the specified recognition sequence and  a single enzyme acronym to add to it's list of associated enzymes.
    /// @param recognitionSequence The recognition sequence.
    /// @param enzymeAcronym The enzyme acronym that is associated with the recognition sequence.
    SequenceMap(const std::string& recognitionSequence, const std::string& enzymeAcronym)
        : recognitionSequence(recognitionSequence)
    {
        enzymeAcronyms.push_back(enzymeAcronym);
    }

    /// @brief Less than recognition sequence comparison overload.
    /// @param rhs The other SequenceMap to compare to.
    /// @return True if the recognition sequence of this SequenceMap is less than the recognition sequence of the other SequenceMap.
    bool operator<(const SequenceMap& rhs) const
    {
        return recognitionSequence < rhs.recognitionSequence;
    }

    /// @brief Greater than recognition sequence comparison overload.
    /// @param rhs The other SequenceMap to compare to.
    /// @return True if the recognition sequence of this SequenceMap is greater than the recognition sequence of the other SequenceMap.
    bool operator>(const SequenceMap& rhs) const
    {
        return recognitionSequence > rhs.recognitionSequence;
    }

    /// @brief Displays all the enzymes associated with this recognition sequence.
    /// @param out The output stream to display the enzymes to.
    /// @param sequenceMap The SequenceMap to display the enzymes of.
    /// @return The enzymes associated with this recognition sequence.
    friend std::ostream& operator<<(std::ostream& out, const SequenceMap& sequenceMap)
    {
        for (auto& enzymeAcronym : sequenceMap.enzymeAcronyms)
            out << enzymeAcronym << " ";

        return out;
    }

    /// @brief Creates a new SequenceMap with a given recognition sequence and adds a given enzyme acronym to it's list of enzyme acronyms.
    /// @param in The input stream to read the recognition sequence and enzyme acronym from.
    /// @param sequenceMap The SequenceMap to create.
    /// @return The SequenceMap with the given recognition sequence and enzyme acronym.
    friend std::istream& operator>>(std::istream& in, SequenceMap& sequenceMap)
    {
        std::string line;
        std::string enzymeAcronym;
        std::string recognitionSequence;

        std::getline(in, line);
        enzymeAcronym = line.substr(0, line.find('/'));
        line = line.substr(line.find('/') + 1);
        recognitionSequence = line.substr(0, line.find('/'));

        sequenceMap.recognitionSequence = recognitionSequence;
        sequenceMap.enzymeAcronyms.clear();
        sequenceMap.enzymeAcronyms.push_back(enzymeAcronym);

        return in;
    }

    /// @brief If two SequenceMaps have the same recognition sequence, then the enzyme acronyms of the other SequenceMap are added to this SequenceMap's list of enzyme acronyms.
    /// @param otherSequence The other SequenceMap to merge with this SequenceMap.
    void Merge(const SequenceMap& otherSequence)
    {
        if (recognitionSequence == otherSequence.recognitionSequence)
            for (auto& enzymeAcronym : otherSequence.enzymeAcronyms)
                if (std::find(enzymeAcronyms.begin(), enzymeAcronyms.end(), enzymeAcronym) == enzymeAcronyms.end())
                    enzymeAcronyms.push_back(enzymeAcronym);
    }
};