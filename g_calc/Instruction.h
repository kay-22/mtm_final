#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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
    public:
        Instruction(std::vector<std::string> data) : data(data) {}
        enum code{quitCode, okCode};
        virtual code execute(std::set<Graph>& who_set) = 0;
        virtual ~Instruction() = default;
        
        enum keyword {PRINT, DELETE, RESET, QUIT, SAVE, LOAD};
        static const std::map<keyword, std::string> KEYWORDS;
    };

    class Declaration : public Instruction
    {
    public:
        Declaration(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Declaration() = default;

        static const char DECLARATION_CHAR;
    };

    class Delete : public Instruction
    {
    public:
        Delete(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Delete() = default;
    };

    class Reset : public Instruction
    {
    public:
        Reset(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Reset() = default;
    };

    class Quit : public Instruction
    {
    public:
        Quit(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Quit() = default;
    };

    class Print : public Instruction
    {
    public:
        Print(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Print() = default;
    };

    class Save : public Instruction
    {
    public:
        Save(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Save() = default;
    };
      
    class Load : public Instruction
    {
    public:
        Load(std::vector<std::string> data) : Instruction(data) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Load() = default;
    };

    class Empty : public Instruction
    {
    public:
        Empty() : Instruction(std::vector<std::string>()) {}
        virtual code execute(std::set<Graph>& who_set) override;
        virtual ~Empty() = default;
    };
    // class Command : public Instruction
    // {
    // protected:
    //     std::string keyword;
    // public:
    //     Command(const std::string& keyword) : keyword(keyword) {}
    
    // };

    // class Delete : public Command
    // {
    //     Graph target;
    // public:
    //     Delete(std::set<Graph>& who_set, const Graph& target) 
    //     : Command(std::string("delete")) , target(target) {}
        
    //     virtual code execute() override;
    // };

    // class Reset : public Command
    // {
    // public:
    //     Reset(std::set<Graph>& who_set) : Command(std::string("reset")) {}
    //     virtual code execute() override;
    // };    
    
    // class Quit : public Command
    // {
    // public:
    //     Quit() : Command(std::string("quit")) {}
    //     virtual code execute() override;
    // };

    // class Print : public Command
    // {
    // private:
    //     std::string expression;
    // public:
    //     Print(const std::string& expression) : Command(std::string("print")), expression(expression) {}
    //     virtual code execute() override;
    // };

    // class Save : public Command
    // {
    // private:
    //     Graph target;
    //     std::string filename;
    // public:
    //     Save(const Graph& target, std::string filename) : 
    //         Command(std::string("save")), target(target), filename(filename) {}
    //     virtual code execute() override;
    // };

    // class Declaration : public Instruction
    // {

    // };

} // namespace graph


#endif // INSTRUCTION_H
