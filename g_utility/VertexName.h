#ifndef VERTEX_NAME_H
#define VERTEX_NAME_H

#include "Name.h"

namespace graph
{
    class VertexName : public Name
    {
    protected:
        /**
         * validates the given name.
         * @return true if all the characters are alphanumerical or one of the following
         * characters: '[', ']', and ';'; otherwise, false.
         */
        virtual bool isValidName() const override;
    public:
        explicit VertexName(const std::string& name);
        const BracketPattern bracket_pattern;
    };
}

#endif