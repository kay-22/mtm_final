#ifndef GRAPH_NAME
#define GRAPH_NAME

#include "Name.h"

namespace graph
{
    class GraphName : public Name
    {
    protected:
        /**
         * validates the given character.
         * @return true if the character is alphanumerical 
         */
        virtual bool isValidCharacter(char) override;
    public:
        GraphName(const std::string& name) : Name(name) {}
    };
} // namespace graph


#endif