#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <graph/Graph.h>

namespace graph
{
    class Instruction 
    //abstruct base class that executes instuctions on a given graph calculator
    {
    protected:
        std::vector<std::string> data;
        
        //Graph evaluateExpression(const string& expression, const std::set<Graph>& who_set);
        //Graph evaluateSimpleExpression(const string& expression, const std::set<Graph>& who_set);
        
    public:
        Instruction(std::vector<std::string> data) : data(data) {}
        enum code{quitCode, okCode};
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) = 0;
        virtual ~Instruction() = default;
        
        enum keyword {PRINT, DELETE, RESET, QUIT, SAVE, LOAD};
        static const std::map<keyword, std::string> KEYWORDS;
        static const BracketPattern EXPRESSION_BRACKET;
    };

    class Declaration : public Instruction
    {
    public:
        Declaration(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Declaration() = default;

        static const char DECLARATION_CHAR;
    };

    class Delete : public Instruction
    {
    public:
        Delete(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Delete() = default;
    };

    class Reset : public Instruction
    {
    public:
        Reset(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Reset() = default;
    };

    class Quit : public Instruction
    {
    public:
        Quit(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Quit() = default;
    };

    class Print : public Instruction
    {
    public:
        Print(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Print() = default;
    };

    class Save : public Instruction
    {
    public:
        Save(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Save() = default;
    };
      
    class Load : public Instruction
    {
    public:
        Load(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Load() = default;
    };

    class Empty : public Instruction
    {
    public:
        Empty() : Instruction(std::vector<std::string>()) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Empty() = default;
    };

} // namespace graph


#endif // INSTRUCTION_H
