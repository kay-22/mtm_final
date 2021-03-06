#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

//#include <iostream> // remove

#include "../graph/Graph.h"
#include "../g_except/InstructionException.h"

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
        Instruction(const std::vector<std::string>& data) : data(data) {}
        enum code{quitCode, okCode};
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) = 0;
        virtual ~Instruction() = default;
        
        enum keyword {PRINT, DELETE, RESET, QUIT, SAVE, LOAD, WHO, HELP};
        static const std::map<keyword, std::string> KEYWORDS;
        static const BracketPattern EXPRESSION_BRACKET;
    };

    class Declaration : public Instruction
    {
    public:
        Declaration(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Declaration() = default;

        static const char DECLARATION_CHAR = '=';
    };

    class Delete : public Instruction
    {
    public:
        Delete(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Delete() = default;
    };

    class Reset : public Instruction
    {
    public:
        Reset(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Reset() = default;
    };

    class Quit : public Instruction
    {
    public:
        Quit(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Quit() = default;
    };

    class Print : public Instruction
    {
    public:
        Print(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Print() = default;
    };

    class Save : public Instruction
    {
    public:
        Save(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Save() = default;
    };
      
    class Load : public Instruction
    {
    public:
        Load(const std::vector<std::string>& data) : Instruction(data) {}
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

    class Who : public Instruction
    {
    public:
        Who(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Who() = default;
    };

    
    class Help : public Instruction
    {
    public:
        Help(const std::vector<std::string>& data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set, std::ostream& out) override;
        virtual ~Help() = default;
    };


} // namespace graph


#endif // INSTRUCTION_H
