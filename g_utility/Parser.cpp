#include "Parser.h"
#include <g_calc/Instruction.h>

using graph::Parser;
using graph::BracketPattern;
using graph::Instruction;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using std::function;
using std::find;
using std::ifstream;
using std::istringstream;
using std::getline;
using std::reverse;

static bool containsChar(const Parser::SpecialCharacters&, char);
static bool containsChar(const string::const_iterator& begin, const string::const_iterator& end, char ch);
static vector<string> split(const string& data, char delimiter = ' ');
static vector<string> split(const string& data, const BracketPattern& bracket_pattern);
static void trimSideSpaces(string& string);

Parser::Parser(const ifstream& input) : data(), current_word()
{

}

const Parser::SpecialCharacters Parser::NO_ADDITIONAL; //default constructor is called
const BracketPattern Parser::GRAPH_BRACKET('{', '}', '|');
const BracketPattern Parser::EDGE_BRACKET('<', '>', ',');
const BracketPattern Parser::VERTEX_BRACKET('[', ']', ';');
const char Parser::OBJECT_DELIMITER = ',';

string::const_iterator Parser::findFirstPair(char left_char, char right_char, string::const_iterator& right_it) const
{
    string::const_iterator left_it;
    bool found_left = false;
    // for (string::const_iterator it = current_word.begin(); it != current_word.end(); ++it) {
    //     if (!found_left && *it == left_char){
    //         begin_it = it;
    //         found_left = true;
    //     }
    //     else if (found_left && *it == right_char) {
    //         right_it = it+1;
    //         found_right = true;
    //         break;
    //     }
    // }

    if (!isMatchingSequence(BracketPattern(left_char, right_char))) {
        right_it = current_word.end();
        return current_word.end();
    }

    int count = 0;
    for (string::const_iterator it = current_word.begin(); it != current_word.end(); ++it) {
        if (*it == left_char) {
            count++;
            if (!found_left) {
                found_left = true;
            }
        }
        else if (*it == right_char) {
            count--;
            right_it = it+1;
        }
        if (found_left && count == 0) {
            break;
        }
    }

    left_it = find(current_word.begin(), current_word.end(), left_char);

    // if (!found_left || !found_right) {
    //     begin_it = current_word.end();
    //     right_it = current_word.end();
    // }

    return left_it;
}

string::const_iterator Parser::findFirstPair(const BracketPattern& bracket_pattern, 
    string::const_iterator& right_it) const
{
    return findFirstPair(bracket_pattern.left, bracket_pattern.right, right_it);
}

string::const_iterator Parser::findFirstPair(string::const_iterator first_it, string::const_iterator last_it,
    const BracketPattern& bracket_pattern, 
    string::const_iterator& right_it) const
{
    string temp_word(first_it, last_it);
    string::const_iterator temp_right_it;;
    string::const_iterator temp_left_it = Parser(temp_word).findFirstPair(bracket_pattern.left,
                                                                          bracket_pattern.right, 
                                                                          temp_right_it);

    if (temp_left_it == temp_word.end()) {
        right_it = current_word.end();
        return current_word.end();
    }
    int left_distance = temp_left_it - temp_word.begin();
    int right_distance = temp_word.end() - temp_right_it;

    right_it = last_it - right_distance;
    return first_it + left_distance;
                                                                    
}

bool Parser::isValid(function<bool(char)> isValidChar, 
    const SpecialCharacters& contains,
    const SpecialCharacters& not_contains) const
{
    for (char ch : current_word){
        if ((!isValidChar(ch) && (contains.empty() || !containsChar(contains, ch))) ||
            (!not_contains.empty() && containsChar(not_contains, ch))) {
                return false;
            }
    }

    return true;
}

bool Parser::isValid(string::const_iterator first_it, string::const_iterator last_it, 
    function<bool(char)> isValidChar, 
    const SpecialCharacters& contains,
    const SpecialCharacters& not_contains) const
{
    return Parser(string(first_it, last_it)).isValid(isValidChar, contains, not_contains);
}

const string& Parser::getCurrentWord() const
{
    return current_word;
}

string Parser::onlyChars(const SpecialCharacters& special_characters) const
{
    string temp_word = current_word;
    function<bool(char)> predicate = [&special_characters](char ch) {
                                        return !containsChar(special_characters,ch);
                                     };
    string::const_iterator new_end = std::remove_if(temp_word.begin(), temp_word.end(), predicate);
    temp_word.erase(new_end, temp_word.end());

    return temp_word;
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
    string only_pattern = onlyChars(bracket_pattern.toSpecialCharacters());
    if (only_pattern.empty()){
        return true; // empty sequence
    }
    
    int count = 0;
    for (char ch : only_pattern)
    {
        if (ch == bracket_pattern.left) {
            count++;
        }
        else if (ch == bracket_pattern.right) {
            count--;
        }
        else /* ch == bracke_pattern.delimiter*/ {
            if (count < 1) {
                return false; //found delimiter not in brackets
            }
        }

        if (count < 0) {
            return false; //found right-bracket before left-bracket
        }
    }

    if (count != 0) {
        return false; //found left-bracket without right-brackt
    }

    // Parser current_parser(temp_word);
    // string& current_data = current_parser.current_word;
    // string::const_iterator right_it;
    // string::const_iterator left_it = current_parser.findFirstPair(bracket_pattern.left, 
    //                                                                 bracket_pattern.right, right_it);
                                                                    
    // while (!current_data.empty()) {
    //     if (left_it == current_data.end()) {
    //         return false; //didn't find pair
    //     }
    //     if(left_it != current_data.begin()) {
    //         return false; //delimiter or right bracket found before first left-bracket
    //     }
    //     if (right_it-left_it-1 == 0 || !containsChar(left_it+1, right_it, bracket_pattern.left)) {
    //         current_data.erase(left_it, right_it); //nothing or only delimiters between pairs 
    //         if (current_data.empty()) {
    //             return true;
    //         }
    //     }
    //     else {    
    //         //at least one left-bracket between pair
    //         string::const_iterator other_left = find(left_it+1,right_it, bracket_pattern.left); 
    //         current_data.erase(right_it-1);
    //         current_data.erase(left_it, other_left);
    //     }

    //     current_parser = Parser(current_data);
    //     left_it = current_parser.findFirstPair(bracket_pattern.left, bracket_pattern.right, right_it);
    // }
    
    return true;
}

bool Parser::isMatchingSequence(string::const_iterator first_it, string::const_iterator last_it,
    const BracketPattern& bracket_pattern) const
{
    return Parser(string(first_it, last_it)).isMatchingSequence(bracket_pattern);
}

bool Parser::isGraphLiteral() const 
{
    string only_graph_pattern = onlyChars(GRAPH_BRACKET.toSpecialCharacters());

    if (only_graph_pattern == string("{}")) {
        return true; //no edge list (doesn't check vertices names)
    }
    if (only_graph_pattern != string("{|}")) {
        return false;
    }
    
    string::const_iterator right_it;
    string::const_iterator left_it = findFirstPair(GRAPH_BRACKET.delimiter, GRAPH_BRACKET.right, right_it);

    //string only_edge_pattern = onlyChars(EDGE_BRACKET.toSpecialCharacters());

    // Parser current_data(string(left_it, right_it));
    // left_it = current_data.current_word.begin();
    // right_it = current_data.current_word.end();

    BracketPattern edge_bracket(EDGE_BRACKET.left, EDGE_BRACKET.right); //no delimiter
    //function<bool(char)> myisspace = [](char ch){return ch==' ';};
    //[](char ch){return ch==' ';});
    if (right_it-left_it-1 == 0 || isValid(left_it+1, right_it-1, isspace)){
        return true; //empty edge list
    }
    if (!isMatchingSequence(left_it, right_it, edge_bracket) || !containsChar(left_it, right_it, EDGE_BRACKET.right)) {
        return false;//edge list is not a matching sequence, nor edges where found.
    }
    // string::const_iterator current_right_it;
    // string::const_iterator current_left_it = current_data.findFirstPair(edge_bracket, current_right_it);
    Parser temp_parser(string(left_it+1, right_it-1));

    string::const_iterator new_end = std::remove_if(temp_parser.current_word.begin(), 
                                                    temp_parser.current_word.end(),
                                                    isspace);
    temp_parser.current_word.erase(new_end, temp_parser.current_word.end());
    //at least one edge
    int edge_counter = 0;
    while (containsChar(temp_parser.current_word.begin(), temp_parser.current_word.end(), EDGE_BRACKET.right)) {
        left_it = temp_parser.findFirstPair(edge_bracket, right_it);
        temp_parser.current_word.erase(left_it, right_it);
        edge_counter++;
    }


    if (!temp_parser.current_word.empty() &&
        !temp_parser.isValid([](char ch) {return ch==OBJECT_DELIMITER;})) {
        return false;//found something between '|' and '}' other than an edge or ','
    }

    if (edge_counter-1 > int(temp_parser.getCurrentWord().size())) {
        return false; // not enough ',' between edges
    }
//     BracketPattern edge_bracket(EDGE_BRACKET.left, EDGE_BRACKET.right); //without delimiter

//     string::const_iterator right_it;
//     string::const_iterator left_it = findFirstPair(current_word.begin()+1, current_word.end(), GRAPH_BRACKET, right_it); // not sure if right iterators are returend
//     if (left_it != current_word.end()) {
//         return false; //found '{' in the middle
//     }

//     left_it = findFirstPair(GRAPH_BRACKET, right_it);
//     if (left_it != current_word.begin() || right_it != current_word.end()) {
//         return false;// found '}' in the middle, or didn't find pair at all.
//     }

//     left_it = findFirstPair(GRAPH_BRACKET.delimiter, GRAPH_BRACKET.delimiter, right_it);
//     if (left_it != current_word.end()) {
//         return false; //too many delimiters
//     }

//     function<bool(char)> myisspace = [](char ch){return ch==' ';};

//     left_it = findFirstPair(GRAPH_BRACKET.delimiter, GRAPH_BRACKET.right, right_it);
//     if (right_it-left_it-1 == 0 || isValid(left_it+1, right_it-1, myisspace)){
//         return true; //empty edge list
//     }
//     if (isMatchingSequence(left_it, right_it, edge_bracket)) {
//         return false; // edge list is not a matching sequence (didn't check delimiter)
//     }

//     left_it = findFirstPair(left_it, right_it, edge_bracket, right_it);
//     if (left_it == current_word.end()) {
//         return false; // found something like {a,b|$%#$#%#$%}
//     }

//     //edge list is not empty
//     left_it = findFirstPair(GRAPH_BRACKET.delimiter, edge_bracket.left, right_it);
//     if (right_it-left_it-1 > 0 && !isValid(left_it+1, right_it-1, myisspace)) {
//         return false; // found something between '|' and first '<'
//     }
//     BracketPattern flipped_edge_bracket(edge_bracket.right, edge_bracket.left);

//     left_it = findFirstPair(left_it+1, current_word.end(), flipped_edge_bracket, right_it);
//     while (left_it != current_word.end()) {
//         if (!isValid(myisspace, SpecialCharacters({','}))) {
//             return false;// found something between edges other than ','
//         }
//         left_it = findFirstPair(left_it+1, current_word.end(), flipped_edge_bracket, right_it);
//     }

return true;
}

Parser::GraphLiteralData Parser::decomposeGraphLiteral()
{
    GraphVerticesData vertices_data;
    GraphEdgesData edges_data;

    if (!isGraphLiteral()) {
        //throw
        //std::cout <<" oh";
    }

    string::const_iterator graph_delim_it = find(current_word.begin(), current_word.end(), GRAPH_BRACKET.delimiter);
    
    string vertices_data_string(current_word.cbegin()+1, graph_delim_it);
    vertices_data = split(vertices_data_string, OBJECT_DELIMITER);
    
    string temp_edges_data_string(graph_delim_it, current_word.cend());
    vector<string> temp_edges_data = split(temp_edges_data_string, EDGE_BRACKET);

    for (string edge_datum : temp_edges_data) {
        size_t edge_delim_pos = edge_datum.find(EDGE_BRACKET.delimiter);
        string vertex_from(edge_datum.substr(1, edge_delim_pos-1)); //must ignore the '<' and ','
        string vertex_to(edge_datum.substr(edge_delim_pos + 1, edge_datum.size()-1 - edge_delim_pos-1)); //must ignore ',' and '>'

        trimSideSpaces(vertex_from);
        trimSideSpaces(vertex_to);

        edges_data.push_back(make_pair(vertex_from, vertex_to));
    }

    return makeGraphLiteralData(vertices_data, edges_data);
}

Parser::SpecialCharacters BracketPattern::toSpecialCharacters() const
{
    return Parser::SpecialCharacters({left, right, delimiter});
}
Parser::GraphLiteralData graph::makeGraphLiteralData(const Parser::GraphVerticesData& vertices_data, 
                                                     const Parser::GraphEdgesData& edges_data)
{
    return make_pair(vertices_data, edges_data);
}

bool containsChar(const Parser::SpecialCharacters& special_chars, char ch)
{
    return special_chars.find(ch) != special_chars.end();
}

bool containsChar(const string::const_iterator& begin, const string::const_iterator& end, char ch)
{
    string::const_iterator it = find(begin, end, ch);
    // for (string::const_iterator it = begin; it != end; ++it) {
    //     if (*it == ch) {
    //         return true;
    //     }
    // }

    return it != end;
}

vector<string> split(const string& data, char delimiter)
{
    vector<string> data_vector;
    istringstream data_input(data);
    for (string datum_string; getline(data_input, datum_string, delimiter);){
        if (!isspace(delimiter)) {
            trimSideSpaces(datum_string);
        }
        data_vector.push_back(datum_string);
    }

    return data_vector;
}

vector<string> split(const string& data, const BracketPattern& bracket_pattern)
{
    vector<string> data_vector;

    Parser current_parser_data(data);
    if(!current_parser_data.isMatchingSequence(bracket_pattern)) {
        //throw
    }

    string current_data(data);
    while (current_data.find(bracket_pattern.left) != string::npos) {
        string::const_iterator right_it;
        string::const_iterator left_it = current_parser_data.findFirstPair(bracket_pattern, right_it);
        
        data_vector.push_back(string(left_it,right_it));

        size_t right_pos = right_it - current_parser_data.getCurrentWord().begin();
        size_t left_pos = left_it - current_parser_data.getCurrentWord().begin();
        size_t count = right_pos - left_pos;

        current_data.erase(left_pos, count);
        current_parser_data = Parser(current_data);
    }
    return data_vector;   
}

void trimSideSpaces(string& string)
{
    size_t count = 0;
    for (char ch : string){
        if (!isspace(ch)) {
            break;
        }
        count++;
    }
    string.erase(0,count);

    while(!string.empty() && isspace(string.back())) {
        string.pop_back();
    }
}