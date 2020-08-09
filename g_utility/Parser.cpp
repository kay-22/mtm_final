#include "Parser.h"
#include <g_calc/Instruction.h>

using graph::Parser;
using graph::BracketPattern;
using graph::Instruction;
using graph::Declaration;
using graph::Quit;
using graph::Reset;
using graph::Delete;
using graph::Print;
using graph::Save;
using graph::Load;
using graph::Empty;
using graph::Who;
using graph::MatchingSequenceParserException;
using graph::GraphLiteralParserException;
using graph::EmptyExpressionException;
using std::string;
using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;
using std::function;
using std::find;
using std::istream;
using std::istringstream;
using std::getline;
using std::reverse;

static bool containsChar(const Parser::SpecialCharacters&, char);
static bool containsChar(const string::const_iterator& begin, const string::const_iterator& end, char ch);
static vector<string> split(const string& data, char delimiter = ' ');
static vector<string> split(const string& data, BracketPattern bracket_pattern);
static shared_ptr<Instruction> makeDeclaration(const string& target_string, string instruction_data);
static shared_ptr<Instruction> makeCommand(const string& command_string, string instruction_data);
static vector<string> makeCommandData(const string& command_string, string instruction_data);
static void trimSideSpaces(std::string& string);
Parser::Parser(istream& input, bool read_one_line) : data(), current_word()
{
    bool read_next = true;
    for (string line; read_next && getline(input, line);) {
        const string& cref_line = line;
        data.push_back(cref_line);

        if(read_one_line){
            read_next = false;
        }
    }
    //reverse(data.begin(), data.end());
    //current_word = data.back();
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
bool Parser::isKeyWord() const
{
    for (auto key_it = Instruction::KEYWORDS.begin(); key_it != Instruction::KEYWORDS.end(); ++key_it) {
        if (key_it->second == current_word) {
            return true;
        }
    }

    return false;
}
const string& Parser::getCurrentWord() const
{
    return current_word;
}

// void Parser::next()
// {
//     if (!data.empty()) {
//         data.pop_back();
//         if (!data.empty()) {
//             current_word = data.back();
//         }
//     }
// }

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

vector<shared_ptr<Instruction>> Parser::makeInstructions()
{
    vector<shared_ptr<Instruction>> result;
    vector<string> instruction_data;
    if (data.empty()) {
        result.push_back(make_shared<Empty>());
        return result;
    }
    
    for (string instruction_string : data) {
        current_word = "";
        trimSideSpaces(instruction_string);

        if (instruction_string.empty()) {
            result.push_back(make_shared<Empty>());
            break;
        }

        for(char ch : instruction_string) {
            if (isspace(ch) || 
                ch == Declaration::DECLARATION_CHAR || 
                ch == Instruction::EXPRESSION_BRACKET.left) {
                break;
            }
            current_word += ch;
        }

        shared_ptr<Instruction> instruction;
        if (isKeyWord()) {
            instruction = makeCommand(current_word, instruction_string);
        }
        else {
            instruction = makeDeclaration(current_word, instruction_string);
        }
        result.push_back(instruction);
    }

    return result;
}

bool Parser::isEnclosedExpression() const
{
    
    if (current_word.empty()) {
        return false;
    }

    string::const_iterator right_it;
    string::const_iterator left_it = findFirstPair(Instruction::EXPRESSION_BRACKET, right_it);

    return  left_it == current_word.begin() && 
            right_it == current_word.end();
}

bool Parser::isExpressionExists() const
{
    if (current_word.empty()) {
        return false;
    }

    string::const_iterator right_it;
    string::const_iterator left_it = findFirstPair(Instruction::EXPRESSION_BRACKET, right_it);

    return  left_it != current_word.end();
}

void Parser::openExpression() 
{
    if (!isEnclosedExpression()) {
        //throw expression not properly enclosed with ()
        throw MatchingSequenceParserException(string("please check for matching ") + 
                                              Instruction::EXPRESSION_BRACKET.left + 
                                              Instruction::EXPRESSION_BRACKET.right);
    }

    current_word = string(current_word.begin()+1, current_word.end()-1);
    trimSideSpaces(current_word); //maybe make this function not static
}

queue<string> Parser::getExpressionData()
{
    if (current_word.empty()) {
        throw EmptyExpressionException("please enter a valid expression");
    }
    if(!isMatchingSequence(Instruction::EXPRESSION_BRACKET)) {
        throw MatchingSequenceParserException(string("please check for matching ") + 
                                              Instruction::EXPRESSION_BRACKET.left + 
                                              Instruction::EXPRESSION_BRACKET.right);
        
    }
    
    if (isEnclosedExpression()) {
        openExpression();
    }

    if (isValid(isspace)) {
        throw EmptyExpressionException("please make sure all brackets enclose a valid expression");
    }

    SpecialCharacters operations_characters(Graph::OperationCharacters::toSpecialChars());
    string temp_word;
    string delimiter;
    queue<string> result;
    char current_ch = 0;
    string back_up = current_word;

    while (!current_word.empty()) {
        current_ch = current_word.front();
        if (containsChar(operations_characters, current_ch)) {
            if (!temp_word.empty()) {
                trimSideSpaces(temp_word);
                result.push(temp_word);
            }
            delimiter.push_back(current_ch);
            result.push(delimiter);
            delimiter.pop_back();

            current_word.erase(0,1);
            trimSideSpaces(current_word);
            temp_word = "";
            continue;
        }
        else if (current_ch == Instruction::EXPRESSION_BRACKET.left) {
            getExpressionDataAux(temp_word, result, Instruction::EXPRESSION_BRACKET);
            continue;
        }
        else if (current_ch == GRAPH_BRACKET.left) {
                if (!isMatchingSequence(GRAPH_BRACKET)) {
                    throw MatchingSequenceParserException(string("please check for matching ") + 
                                                                 GRAPH_BRACKET.left + 
                                                                 GRAPH_BRACKET.right);
                }   
            getExpressionDataAux(temp_word, result, GRAPH_BRACKET);
            continue;
        }
        temp_word += current_ch;
        current_word.erase(0,1);
        //trimSideSpaces(current_word);
    }

    if (!temp_word.empty()) {
        result.push(temp_word);
    }

    current_word = back_up;

    return result;
}

void Parser::getExpressionDataAux(string& temp_word, queue<string>& result, const BracketPattern& bracket_pattern) 
{

    if (!temp_word.empty()) {
        trimSideSpaces(temp_word);
        result.push(temp_word);
    }
    temp_word = popFirstPair(bracket_pattern);
    result.push(temp_word);
    temp_word = "";
}
string Parser::popFirstPair(const BracketPattern& bracket_pattern)
{
    string::const_iterator right_it;
    string::const_iterator left_it = findFirstPair(bracket_pattern, right_it);
    
    string result(left_it, right_it);
    current_word.erase(left_it,right_it);
    trimSideSpaces(current_word);

    return result;
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
    while (containsChar(temp_parser.current_word.begin(), temp_parser.current_word.end(), EDGE_BRACKET.right)) { //maybe change to !=stringnpos
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

bool Parser::isGraphOperator() const
{
    if (current_word.size() != 1)
    {
        return false;
    }

    return containsChar(Graph::OperationCharacters::toSpecialChars(), current_word.back());
}

Parser::GraphLiteralData Parser::decomposeGraphLiteral()
{
    GraphVerticesData vertices_data;
    GraphEdgesData edges_data;

    if (!isGraphLiteral()) {
        throw GraphLiteralParserException("'" + current_word + "' is not a valid graph literal.");
    }

    if (isValid(isspace, GRAPH_BRACKET.toSpecialCharacters())) {
        return makeGraphLiteralData(vertices_data, edges_data); //empty graph
    }
    string::const_iterator graph_delim_it = find(current_word.begin(), current_word.end(), GRAPH_BRACKET.delimiter);
    
    string vertices_data_string(current_word.cbegin()+1, graph_delim_it);

    if (graph_delim_it == current_word.end()) {
        if (isMatchingSequence(BracketPattern(EDGE_BRACKET.left,EDGE_BRACKET.right)) &&
             current_word.find(EDGE_BRACKET.left) != string::npos) {
            throw GraphLiteralParserException("please write all edges after '|' ");
        }
        vertices_data_string.pop_back();
        vertices_data = split(vertices_data_string, OBJECT_DELIMITER);

        return makeGraphLiteralData(vertices_data, edges_data); //empty edge list without delimiter
    }
    vertices_data = split(vertices_data_string, OBJECT_DELIMITER);
    
    string temp_edges_data_string(graph_delim_it+1, current_word.cend()-1);
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

    if(data.back() == delimiter) {
        data_vector.push_back("");
    }

    return data_vector;
}

vector<string> split(const string& data, BracketPattern bracket_pattern)
{
    vector<string> data_vector;
    bracket_pattern.delimiter = 0; // ignore delimiter
    Parser current_parser_data(data);
    if(!current_parser_data.isMatchingSequence(bracket_pattern)) {
        throw MatchingSequenceParserException(string("please check for matching ") + bracket_pattern.left + bracket_pattern.right);
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

shared_ptr<Instruction> makeDeclaration(const string& target_string, string instruction_data)
{
    vector<string> declaration_data;

    declaration_data.push_back(target_string);

    if (target_string.size() < instruction_data.size()){
        instruction_data.erase(0, target_string.size());
        trimSideSpaces(instruction_data);

        if(instruction_data.empty() || instruction_data.front() !=  Declaration::DECLARATION_CHAR) {
            declaration_data.push_back("");
            declaration_data.push_back("");
        }
        else {
            declaration_data.push_back(string("") + Declaration::DECLARATION_CHAR);
            
            instruction_data.erase(0, 1);
            trimSideSpaces(instruction_data);

            declaration_data.push_back(instruction_data);
        }
    }
    else {
        declaration_data.push_back("");
        declaration_data.push_back("");
    }
    Declaration d(declaration_data);
    //d.execute()
    return make_shared<Declaration>(declaration_data);
}

shared_ptr<Instruction> makeCommand(const string& command_string, string instruction_data)
{
    const vector<string>& command_data = makeCommandData(command_string, instruction_data);
    shared_ptr<Instruction> command;
    
    if (command_string == Instruction::KEYWORDS.at(Instruction::QUIT)) {
        command = make_shared<Quit>(command_data);
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::RESET)) {
        command = make_shared<Reset>(command_data);
        
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::DELETE)) {
        command = make_shared<Delete>(command_data);
        
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::PRINT)) {
        command = make_shared<Print>(command_data);
        
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::SAVE)) {
        command = make_shared<Save>(command_data);
        
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::LOAD)) {
        command = make_shared<Load>(command_data);
        
    }

    else if (command_string == Instruction::KEYWORDS.at(Instruction::WHO)) {
        command = make_shared<Who>(command_data);
        
    }

    return command;
}

vector<string> makeCommandData(const string& command_string, string instruction_data)
{
    vector<string> result;
    
    result.push_back(command_string);
    if (command_string.size() < instruction_data.size()){
        instruction_data.erase(0, command_string.size());
        trimSideSpaces(instruction_data);
        
        result.push_back(instruction_data);
    }
    else {
        result.push_back("");
    }

    return result;
}