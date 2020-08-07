#ifndef EXPRESSION_H
#define EXPRESSION_H

namespace graph
{
    class Expression
    {
    public:
        virtual void evaluate(const Expression&) = 0;
    };
} // namespace graph


#endif // EXPRESSION_H
