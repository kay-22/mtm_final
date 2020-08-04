#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cctype>
#include <functional>
#include <unordered_set>

namespace graph
{
    class Parser
    {
    private:
        const std::string data;
    public:
        typedef std::unordered_set<char> SpecialCharacters;
        Parser(const std::string &data) : data(data) {}

        /**
         * Finds the first mathcing pairs in the parser's data.
         * @param left_char the left character of the pair
         * @param right_char the right character of the pair
         * @param end_it an output iterator to one position after the right_char
         * @return returns an iterator to the left character of the pair. if no pair was found, data.end() is returned
         */
        std::string::const_iterator findFirstPair(char left_char, char right_char, 
            std::string::const_iterator& end_it) const;

        /**
         * Checks if the data is valid under certian criteria.
         * @param isValidChar a bool function whith a char argument that will check each charater in the data. 
         * Alphanumeric by default.
         * @param contains additional characters wich may be allowed
         * @param not_contains additional characters wich are not allowed
         */
        bool isValid(std::function<bool(char)> isValidChar = isalnum, 
            SpecialCharacters contains = SpecialCharacters(),
            SpecialCharacters not_contains = SpecialCharacters()) const;

        const std::string& getData() const;
        bool operator<(const Parser&) const;

        Parser(const Parser&) = default;
        Parser& operator=(const Parser&) = delete;
        ~Parser() = default;
    };

    bool isBracketObject(const Parser&); // (TODO, it's like "[;]", "<,>", "{|}"...)

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
