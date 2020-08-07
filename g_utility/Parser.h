#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cctype>
#include <functional>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <memory>
#include <algorithm>

#include "../g_calc/Instruction.h"

namespace graph
{
    struct BracketPattern;

    class Parser
    {
    private:
        std::vector<std::string> data;
        std::string current_word;
    public:
        typedef std::unordered_set<char> SpecialCharacters;
        static const SpecialCharacters NO_ADDITIONAL;

        Parser(const std::string &current_word = std::string("")) : current_word(current_word) {}
        Parser(const std::ifstream& data_stram);

        /**
         * Finds the first mathcing pairs in the parser's current_word.
         * @param left_char the left character of the pair
         * @param right_char the right character of the pair
         * @param end_it an output iterator to one position after the right_char
         * @return returns an iterator to the left character of the pair. if no pair was found, current_word.end() is returned
         */
        std::string::const_iterator findFirstPair(char left_char, char right_char, 
            std::string::const_iterator& end_it) const;

        /**
         * Checks if the current_word is valid under certian criteria.
         * @param isValidChar a bool function whith a char argument that will check each charater in the current_word. 
         * Alphanumeric by default.
         * @param contains additional characters wich may be allowed. Use Parser::NO_ADDITIONAL if there is no need.
         * @param not_contains additional characters wich are not allowed. Use Parser::NO_ADDITIONAL if there is no need
         */
        bool isValid(std::function<bool(char)> isValidChar = isalnum, 
            const SpecialCharacters& contains = NO_ADDITIONAL,
            const SpecialCharacters& not_contains = NO_ADDITIONAL) const;
        
        /**
         * Checks if the current_word is a matching squence of a given bracket pattern 
         * (e.g. "[;]" and "{{}}{|}" are valid sequences, and "<.>.>" and "[];" are not)
         */
        bool isMatchingSequence(const BracketPattern&) const;
        std::vector<std::shared_ptr<Instruction>> makeInstructions() const;

        const std::string& getCurrentWord() const;

        bool operator<(const Parser&) const;

        Parser(const Parser&) = default;
        Parser& operator=(const Parser&) = default;
        ~Parser() = default;
    };

    struct BracketPattern
    {
        char left;
        char right;
        char delimiter;

        BracketPattern(char left, char right, char delimiter = 0) : left(left), right(right), delimiter(delimiter) {}
        Parser::SpecialCharacters toSpecialCharacters() const;
    };
    
    
} // namespace graph


#endif // PARSER_H
