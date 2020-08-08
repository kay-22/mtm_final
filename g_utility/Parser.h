#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cctype>
#include <functional>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>

#include <g_except/ParserException.h>

//#include <g_calc/Instruction.h>

namespace graph
{
    class Instruction;
    struct BracketPattern;

    class Parser
    {
    private:
        std::vector<std::string> data;
        std::string current_word;
        void getExpressionDataAux(std::string&, std::vector<std::string>&, const BracketPattern&);
    public:
        typedef std::unordered_set<char> SpecialCharacters;
        static const SpecialCharacters NO_ADDITIONAL;
        static const BracketPattern GRAPH_BRACKET;
        static const BracketPattern EDGE_BRACKET;
        static const BracketPattern VERTEX_BRACKET;
        static const char OBJECT_DELIMITER;

        Parser(const std::string &current_word = std::string("")) : current_word(current_word) {}
        Parser(std::ifstream& data_stram);

        /**
         * Finds the first mathcing pairs in the parser's current_word.
         * @param left_char the left character of the pair
         * @param right_char the right character of the pair
         * @param right_it an output iterator to one position after the right_char
         * @return returns an iterator to the left character of the pair. if no pair was found, current_word.end() is returned
         */
        std::string::const_iterator findFirstPair(char left_char, char right_char, 
            std::string::const_iterator& right_it) const;
        /**
         * Finds the first mathcing pairs in the parser's current_word.
         * @param bracket_pattern the pattern dedides the right and the left character of the pair appropriately
         * @param right_it an output iterator to one position after the right_char
         * @return returns an iterator to the left character of the pair. if no pair was found, current_word.end() is returned
         */
        std::string::const_iterator findFirstPair(const BracketPattern& bracket_pattern, 
            std::string::const_iterator& right_it) const;

        /** Finds the first mathcing pairs in a sub word of the current_word.
         * @param bracket_pattern the pattern dedides the right and the left character of the pair appropriately
         * @param right_it an output iterator to one position after the right_char
         * @return returns an iterator to the left character of the pair. if no pair was found, current_word.end() is returned
         */
        std::string::const_iterator findFirstPair(std::string::const_iterator first_it, 
            std::string::const_iterator last_it,
            const BracketPattern& bracket_pattern, 
            std::string::const_iterator& right_it) const;

        std::string popFirstPair(const BracketPattern& BracketPattern);
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
         * Checks a sub word of the current_word is valid under certian criteria.
         * @param isValidChar a bool function whith a char argument that will check each charater in the current_word. 
         * Alphanumeric by default.
         * @param contains additional characters wich may be allowed. Use Parser::NO_ADDITIONAL if there is no need.
         * @param not_contains additional characters wich are not allowed. Use Parser::NO_ADDITIONAL if there is no need
         */
        bool isValid(std::string::const_iterator first_it, std::string::const_iterator last_it, 
            std::function<bool(char)> isValidChar = isalnum, 
            const SpecialCharacters& contains = NO_ADDITIONAL,
            const SpecialCharacters& not_contains = NO_ADDITIONAL) const;
        
        /**
         * Checks if the current_word is a matching squence of a given bracket pattern 
         * (e.g. "[;]" and "{{}}{|}" are valid sequences, and "<.>.>" and "[];" are not)
         */
        bool isMatchingSequence(const BracketPattern&) const;
        /**
         * Checks a sub string of the current_word is a matching squence of a given bracket pattern 
         * (e.g. "[;]" and "{{}}{|}" are valid sequences, and "<.>.>" and "[];" are not)
         */
        bool isMatchingSequence(std::string::const_iterator first_it, std::string::const_iterator last_it,
            const BracketPattern& bracket_pattern) const;

        //checks if the current word has a pattern of {,,|<,>,,} doesn't check the names
        bool isGraphLiteral() const;
        //typedef std::pair<std::vector<std::string>, std::vector<std::pair<std::string, std::string>>> GraphLiteralData; //good lord in heavens
        typedef std::vector<std::string> GraphVerticesData;
        typedef std::vector<std::pair<std::string, std::string>> GraphEdgesData;
        typedef std::pair<GraphVerticesData, GraphEdgesData> GraphLiteralData;
        GraphLiteralData decomposeGraphLiteral();

        std::vector<std::shared_ptr<Instruction>> makeInstructions();
        
        
        //check if the calculator expression is  ('expression') without additional expressions
        bool isEnclosedExpression() const;
        //checks if there is at least one ('expression'). doesn't have to be enclosed.
        bool isExpressionExists() const;
        //removes outer brackets from expression
        void openExpression();
        std::vector<std::string> getExpressionData();

        std::string onlyChars(const SpecialCharacters&) const;
        const std::string& getCurrentWord() const;

        static void trimSideSpaces(std::string& string);
        
        // advance current word to the next one in the data
        void next();

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
    
    Parser::GraphLiteralData makeGraphLiteralData(const Parser::GraphVerticesData&, const Parser::GraphEdgesData&);
    //Parser::GraphEdgesData makeGraphEdgesData(const std::string& from_vertex_data, const std::string& to_vertex_data);
    
} // namespace graph


#endif // PARSER_H
