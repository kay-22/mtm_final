#ifndef INSTRUCTION_H
#define INSTRUCTION_H


namespace graph
{
    class Instruction 
    //abstruct base class that executes instuctions on a given graph calculator
    {
    public:
        virtual void execute() = 0;
    };
} // namespace graph


#endif // INSTRUCTION_H
