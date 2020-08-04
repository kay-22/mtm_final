#include "Parser.h"

using graph::Parser;
using std::string;
using std::function;

string::const_iterator Parser::findFirstPair(char left_char, char right_char, string::const_iterator& end_it) const
{
    string::const_iterator begin_it;
    bool found_left = false;
    bool found_right = false;

    for (string::const_iterator it = data.begin(); it != data.end(); ++it) {
        if (!found_left && *it == left_char){
            begin_it = it;
            found_left = true;
        }
        if (found_left && *it == right_char) {
            end_it = it;
            found_right = true;
            break;
        }
    }

    if (!found_left || !found_right) {
        begin_it = data.end();
        end_it = data.end();
    }
}

bool Parser::isValid(function<bool(char)> isValidChar = isalnum, 
            SpecialCharacters contains = SpecialCharacters(),
            SpecialCharacters not_contains = SpecialCharacters()) const
{
    for (char ch : data){
        if (!isValid && 
            (contains.empty() || contains.find(ch) != contains.end()) && 
            (not_contains.empty() || not_contains.find(ch) == not_contains.end())) {
                return false;
            }
    }

    return true;
}

const string& Parser::getData() const
{
    return data;
}

bool Parser::operator<(const Parser& other) const
{
    return data < other.data;
}