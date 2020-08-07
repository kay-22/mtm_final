#include "Parser.h"

using graph::Parser;
using graph::BracketPattern;
using graph::Instruction;
using std::string;
using std::vector;
using std::shared_ptr;
using std::function;
using std::find;
using std::ifstream;

static bool containsChar(const Parser::SpecialCharacters&, char);
static bool containsChar(const string::const_iterator& begin, const string::const_iterator& end, char ch);

Parser::Parser(const ifstream& input) : data(), current_word()
{

}

const Parser::SpecialCharacters Parser::NO_ADDITIONAL; //default constructor is called

string::const_iterator Parser::findFirstPair(char left_char, char right_char, string::const_iterator& end_it) const
{
    string::const_iterator begin_it;
    bool found_left = false;
    bool found_right = false;

    for (string::const_iterator it = current_word.begin(); it != current_word.end(); ++it) {
        if (!found_left && *it == left_char){
            begin_it = it;
            found_left = true;
        }
        if (found_left && *it == right_char) {
            end_it = it+1;
            found_right = true;
            break;
        }
    }

    if (!found_left || !found_right) {
        begin_it = current_word.end();
        end_it = current_word.end();
    }

    return begin_it;
}

bool Parser::isValid(function<bool(char)> isValidChar, 
    const SpecialCharacters& contains,
    const SpecialCharacters& not_contains) const
{
    for (char ch : current_word){
        if ((!isValidChar(ch) && (!contains.empty() && !containsChar(contains, ch))) ||
            (!not_contains.empty() && containsChar(not_contains, ch))) {
                return false;
            }
    }

    return true;
}

const string& Parser::getCurrentWord() const
{
    return current_word;
}

vector<shared_ptr<Instruction>> Parser::makeInstructions() const
{
    return vector<shared_ptr<Instruction>>();
}

bool Parser::operator<(const Parser& other) const
{
    return current_word < other.current_word;
}

bool Parser::isMatchingSequence(const BracketPattern& bracket_pattern) const
{
    string temp_word = current_word;
    function<bool(char)> predicate = [&bracket_pattern](char ch) {
                                        return !containsChar(bracket_pattern.toSpecialCharacters(),ch);
                                     };
    string::const_iterator new_end = std::remove_if(temp_word.begin(), temp_word.end(), predicate);
    temp_word.erase(new_end, temp_word.end());

    if (temp_word.empty()){
        return true; // empty sequence
    }
    
    Parser current_parser(temp_word);
    string& current_data = current_parser.current_word;
    string::const_iterator right_it;
    string::const_iterator left_it = current_parser.findFirstPair(bracket_pattern.left, 
                                                                    bracket_pattern.right, right_it);
                                                                    
    while (!current_data.empty()) {
        if (left_it == current_data.end()) {
            return false; //didn't find pair
        }
        if(left_it != current_data.begin()) {
            return false; //delimiter or right bracket found before first left-bracket
        }
        if (right_it-left_it-1 == 0 || !containsChar(left_it+1, right_it, bracket_pattern.left)) {
            current_data.erase(left_it, right_it); //nothing or only delimiters between pairs 
            if (current_data.empty()) {
                return true;
            }
        }
        else {    
            //at least one left-bracket between pair
            string::const_iterator other_left = find(left_it+1,right_it, bracket_pattern.left); 
            current_data.erase(right_it-1);
            current_data.erase(left_it, other_left);
        }

        current_parser = Parser(current_data);
        left_it = current_parser.findFirstPair(bracket_pattern.left, bracket_pattern.right, right_it);
    }
    
    return true;
}

Parser::SpecialCharacters BracketPattern::toSpecialCharacters() const
{
    return Parser::SpecialCharacters({left, right, delimiter});
}

bool containsChar(const Parser::SpecialCharacters& special_chars, char ch)
{
    return special_chars.find(ch) != special_chars.end();
}

bool containsChar(const string::const_iterator& begin, const string::const_iterator& end, char ch)
{
    for (string::const_iterator it = begin; it != end; ++it) {
        if (*it == ch) {
            return true;
        }
    }

    return false;
}