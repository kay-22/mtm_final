#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
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
        enum code{QUIT};
        virtual code execute(std::set<Graph>& who_set) = 0;
        virtual ~Instruction() = default;
    };

    class Declaration : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
    };

    class Delete : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
    };

    class Reset : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
    };

    class Quit : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
    };

    class Print : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
    };

    class Save : public Instruction
    {
    public:
        virtual code execute(std::set<Graph>& who_set) override;
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
