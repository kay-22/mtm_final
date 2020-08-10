#include "Instruction.h"

using std::map;
using std::set;
using std::queue;
using std::string;
using std::ostream;
using std::ifstream;
using std::ios_base;
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
using graph::Who;
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
                                                                    {LOAD, "load"},
                                                                    {WHO, "who"}
                                                                };

//static string openExpression(const string& expression);
//static bool isExpressionExists(const string& expression);
//static bool isEnclosedExpression(const string& expression);
static Graph evaluateExpression(const string& expression, const std::set<Graph>& who_set);
static bool handleComplement(queue<string>& expression_data);

Instruction::code Declaration::execute(set<Graph>& who_set, ostream& out)  
{
    Graph graph(data.at(0));// make constatns for placeholders
    if (data.at(1).empty()) {
        throw BadCommandExpression(string("did you mean ") + data.at(0) + DECLARATION_CHAR + data.at(2) + string("?"));
    }
    
    graph = evaluateExpression(data.at(2), who_set);

    if (who_set.find(graph) != who_set.end()) {
        who_set.erase(graph); //finds graph with the same name, but data can be different
    } 
    who_set.insert(graph);

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
Instruction::code Save::execute(set<Graph>& who_set, ostream& out) 
{
    Graph graph(data.at(1));
    const auto& who_it = who_set.find(graph);
    if (who_it == who_set.end()) {
        //throw graph does not exist
    }
    graph = *who_it;

    set<Edge> edges = graph.getEdgesSet();
    unsigned int num_vertices = graph.size();
    unsigned int num_edges = edges.size();

    outfile.write((const char*)&num_vertices, sizeof(unsigned int));
    outfile.write((const char*)&num_edges, sizeof(unsigned int));

    for (const auto& vertex_datum : graph){
        string vertex_name(vertex_datum.first.getName());
        unsigned int vertex_name_length = vertex_name.size();
        outfile.write((const char*)&vertex_name_length, sizeof(unsigned int));
        outfile.write(&vertex_name[0], vertex_name_length);
    }

    for (const Edge& edge : edges){
        string vertex_from_name(edge.first.getName());
        unsigned int vertex_name_length = vertex_from_name.size();
        outfile.write((const char*)&vertex_name_length, sizeof(unsigned int)); //make function for this
        outfile.write(&vertex_from_name[0], vertex_name_length);
        
        string vertex_to_name(edge.first.getName());
        vertex_name_length = vertex_to_name.size();
        outfile.write((const char*)&vertex_name_length, sizeof(unsigned int));
        outfile.write(&vertex_to_name[0], vertex_name_length);
    }

    return okCode;
}
Instruction::code Load::execute(set<Graph>& who_set, ostream& out) 
{//actually should return bad operator

    Graph result;
    string filename = data.back();
    ifstream infile(filename, ios_base::binary);
    if(!infile) {
        //throw
    }

    unsigned int num_vertices = 0;
    unsigned int num_edges= 0;
    infile.read((char*)&num_vertices, sizeof(unsigned int));
    infile.read((char*)&num_edges, sizeof(unsigned int));

    for (int i = 0; i< num_vertices; ++i) {
        unsigned int vertex_name_lenght = 0;
        infile.read((char*)&num_edges, sizeof(unsigned int));//make function for this
        
        string vertex_name(vertex_name_lenght, 0);
        infile.read(&vertex_name[0], sizeof(unsigned int));

        result.addVertex(Vertex(vertex_name));
    }

    for (int i = 0; i < num_edges; ++i) {
        unsigned int vertex_name_lenght = 0;

        infile.read((char*)&num_edges, sizeof(unsigned int));
        string vertex_from_name(vertex_name_lenght, 0);
        infile.read(&vertex_from_name[0], sizeof(unsigned int));        

        infile.read((char*)&num_edges, sizeof(unsigned int));
        string vertex_to_name(vertex_name_lenght, 0);
        infile.read(&vertex_to_name[0], sizeof(unsigned int));

        Vertex vertex_from(vertex_from_name);
        Vertex vertex_to(vertex_to_name);

        result.addEdge(makeEdge(vertex_from, vertex_to));
    }

    return result;
    return okCode;
}
Instruction::code Empty::execute(set<Graph>& who_set, ostream& out) 
{
    return okCode;
}

Instruction::code Who::execute(set<Graph>& who_set, ostream& out) 
{
    if (!data.back().empty()) {
        throw BadCommandExpression("'who' does not take any arguments");
    }

    for (const Graph& graph : who_set) {
        out << graph.getName() << endl;
    }
    return okCode;
}


Graph evaluateExpression(const string& expression, const set<Graph>& who_set)
{
    Parser parser(expression);
    queue<string> expression_data = parser.getExpressionData(); //change to queue<strint>
    Graph result_graph;    

    if (expression_data.size() == 1) {

        if (expression_data.front().front() == Instruction::EXPRESSION_BRACKET.left) {
            return evaluateExpression(expression_data.back(), who_set); // getExpressionData opens parentheses 
        }

        if (expression_data.front().front() == Parser::GRAPH_BRACKET.left) {
            return makeGraph(expression_data.back()); //graph literal
        }
        else if (parser.isGraphOperator()) {
            throw OperatorExceptoin("operator " + parser.getCurrentWord() + " expected variable");
        }

        Graph graph(expression_data.back());

        const set<Graph>::iterator& who_it = who_set.find(graph);
        if (who_it == who_set.end()) {
            throw UndefinedVariableException("'" + expression_data.back() + "'");
        }

        graph = *who_it;
        
        return graph;
    }

    
    bool is_complement = handleComplement(expression_data);

    if (expression_data.empty()) {
        throw OperatorExceptoin("operator '!' expected variable");
    }

    
    Graph current_graph = evaluateExpression(expression_data.front(), who_set);
    expression_data.pop();
    
    //make operators += != and so
    result_graph = (is_complement)? current_graph : !current_graph;

    if (expression_data.empty()) {
        return result_graph;
    }

    if (expression_data.size() == 1) {
        throw OperatorExceptoin("expected binary operator before '" + expression_data.back() + "'");
    }

    char Operator = expression_data.front().front();
    //check isoperator? or just rely on swith
    expression_data.pop();
    is_complement = handleComplement(expression_data);
    
    current_graph = evaluateExpression(expression_data.front(), who_set);
    current_graph = (is_complement)? current_graph : !current_graph;

    switch (Operator)
    {
        case Graph::OperationCharacters::UNION:
            result_graph = result_graph + current_graph; //+= need to make
            break;
        
        case Graph::OperationCharacters::INTERSECTION:
            result_graph = result_graph ^ current_graph; //^=
            break;
        
        case Graph::OperationCharacters::PRODUCT:
            result_graph = result_graph * current_graph; //*=
            break;
        
        case Graph::OperationCharacters::DIFFERENCE:
            result_graph = result_graph - current_graph; //-=
            break;
        
        default:
            throw OperatorExceptoin("expected binary operator before '" + expression_data.back() + "'");
            break;
    }
    expression_data.pop();

    string next_expression(result_graph.makeLiteral());
    
    while (!expression_data.empty()) {
        next_expression += expression_data.front();
        expression_data.pop();
    }

    return evaluateExpression(next_expression, who_set);
}

bool handleComplement(queue<string>& expression_data)
{
    int complement_counter;
    string complemet_op;
    complemet_op.push_back(Graph::OperationCharacters::COMPLEMENT);
    while (!expression_data.empty() && expression_data.front() == complemet_op) {
        expression_data.pop();
        complement_counter++;
    }

    return complement_counter%2 == 0;
}
// Graph Instruction::evaluateSimpleExpression(const string& expression, const set<Graph>& who_set) 
// {
//     if (isalnum(expression.front() )
// }