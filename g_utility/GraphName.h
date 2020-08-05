#ifndef GRAPH_NAME
#define GRAPH_NAME

#include "Name.h"

namespace graph
{
    class GraphName : public Name
    {
    protected:
        /**
         * @return true if all characters are alphanumerical 
         */
        virtual bool isValidName() const override;
    public:
        explicit GraphName(const std::string& name);
    };
} // namespace graph


#endif