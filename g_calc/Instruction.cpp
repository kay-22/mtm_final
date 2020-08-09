#include "Instruction.h"

using std::map;
using std::set;
using std::list;
using std::string;
using std::ostream;
using std::endl;
using graph::Instruction;
using graph::Declaration;
using graph::Quit;
using graph::Reset;
using graph::Delete;
using graph::Print;
using graph::Save;
using graph::Load;
using graph::Empty;
using graph::BracketPattern;
using graph::Parser;
using graph::Graph;
using graph::makeGraph;
using graph::BadCommandExpression;
using graph::UndefinedVariableException;
using graph::OperatorExceptoin;

const BracketPattern Instruction::EXPRESSION_BRACKET('(',')');
const map<Instruction::keyword, string> Instruction::KEYWORDS = {
                                                                    {PRINT, "print"}, 
                                                                    {DELETE, "delete"},
                                                                    {RESET, "reset"}, 
                                                                    {QUIT, "quit"}, 
                                                                    {SAVE, "save"}, 
                                                                    {LOAD, "load"}
                                                                };

//static string openExpression(const string& expression);
//static bool isExpressionExists(const string& expression);
//static bool isEnclosedExpression(const string& expression);
static Graph evaluateExpression(const string& expression, const std::set<Graph>& who_set);

Instruction::code Declaration::execute(set<Graph>& who_set, ostream& out)  
{
    Graph rvalue_graph(data.at(0));// make constatns for placeholders
    if (data.at(1).empty()) {
        throw BadCommandExpression(string("did you mean ") + data.at(0) + DECLARATION_CHAR + data.at(2) + string("?"));
    }
    
    const Graph& lvalue_graph = evaluateExpression(data.at(2), who_set);

    if (who_set.find(rvalue_graph) != who_set.end()) {
        who_set.erase(rvalue_graph);
    } 
    who_set.insert(lvalue_graph);

    return okCode;
}

Instruction::code Print::execute(set<Graph>& who_set, ostream& out)
{
    Parser parser(data.back());
    parser.openExpression();

    // if (parser.getCurrentWord().empty()){ //openExpression should throw if empty
    //     throw 
    // }
    
    const Graph& graph = evaluateExpression(parser.getCurrentWord(), who_set);

    out << graph << endl;

    return okCode;
}
Instruction::code Delete::execute(set<Graph>& who_set, ostream& out) 
{
    
    Parser parser(data.back());
    parser.openExpression();
    Graph graph(parser.getCurrentWord());

    if (who_set.find(graph) == who_set.end()) {
        throw UndefinedVariableException("'" + parser.getCurrentWord() + "'");
    }
    who_set.erase(graph);

    return okCode;
}
Instruction::code Reset::execute(set<Graph>& who_set, ostream& out) 
{
    if (!data.back().empty()) {
        throw BadCommandExpression("'reset' does not take any arguments");
    }
    who_set.clear();
    return okCode;
}
Instruction::code Quit::execute(set<Graph>& who_set, ostream& out)
{
    if (!data.back().empty()) {
        throw BadCommandExpression("'quit' does not take any arguments");
    }
    return quitCode;
}
Instruction::code Save::execute(set<Graph>& who_set, ostream& out) {return okCode;}
Instruction::code Load::execute(set<Graph>& who_set, ostream& out) {return okCode;}
Instruction::code Empty::execute(set<Graph>& who_set, ostream& out) 
{
    return okCode;
}


Graph evaluateExpression(const string& expression, const set<Graph>& who_set)
{
    Parser parser(expression);
    list<string> expression_data = parser.getExpressionData(); //change to queue<strint>
    Graph result_graph;    

    if (expression_data.size() == 1) {

        if (expression_data.front().front() == Instruction::EXPRESSION_BRACKET.left) {
            return evaluateExpression(expression, who_set); // open parentheses 
        }

        if (expression_data.front().front() == Parser::GRAPH_BRACKET.left) {
            return makeGraph(expression); //graph literal
        }
        else if (parser.isGraphOperator()) {
            throw OperatorExceptoin("operator " + parser.getCurrentWord() + " expected variable");
        }

        Graph graph(expression);
        if (who_set.find(graph) == who_set.end()) {
            throw UndefinedVariableException("'" + expression + "'");
        }
        
        return graph;
    }


    int complement_counter;
    string complemet_op;
    complemet_op.push_back(Graph::OperationCharacters::COMPLEMENT);
    while (!expression_data.empty() && expression_data.front() == complemet_op) {
        expression_data.pop_front();
        complement_counter++;
    }

    if (expression_data.empty()) {
        throw OperatorExceptoin("operator '!' expected variable");
    }

    
    Graph current_graph = evaluateExpression(expression_data.front(), who_set);
    expression_data.pop_front();
    
    //make operators += != and so
    result_graph = (complement_counter%2)? current_graph : !current_graph;

    if (expression_data.empty()) {
        return result_graph;
    }

    if (expression_data.size() == 1) {
        throw OperatorExceptoin("expected binary operator");
    }

    char Operator = expression_data.front().front();
    //check isoperator? or just rely on swith
    expression_data.pop_front();
    current_graph = evaluateExpression(expression_data.front(), who_set);

    switch (Operator)
    {
        case Graph::OperationCharacters::UNION:
            result_graph = result_graph + current_graph; //+=
            break;
        
        case Graph::OperationCharacters::INTERSECTION:
            result_graph = result_graph ^ current_graph; //+=
            break;
        
        case Graph::OperationCharacters::PRODUCT:
            result_graph = result_graph * current_graph; //+=
            break;
        
        case Graph::OperationCharacters::DIFFERENCE:
            result_graph = result_graph + current_graph; //+=
            break;
        
        default:
            throw OperatorExceptoin("expected binary operator");
            break;
    }

    string next_expression(result_graph.makeLiteral());
    
    while (!expression_data.empty()) {
        next_expression += expression_data.front();
        expression_data.pop_front();
    }

    return evaluateExpression(next_expression, who_set);
}

// Graph Instruction::evaluateSimpleExpression(const string& expression, const set<Graph>& who_set) 
// {
//     if (isalnum(expression.front() )
// }