#ifndef VERTICE_NAME
#define VERTICE_NAME

#include "Name.h"

namespace graph
{
    class VerticeName : public Name
    {
    private:
        BracketPattern bracket_pattern;
    protected:
        /**
         * validates the given name.
         * @return true if all the characters are alphanumerical or one of the following
         * characters: '[', ']', and ';'; otherwise, false.
         */
        virtual bool isValidName() const override;
    public:
        explicit VerticeName(const std::string& name);
    };
}

#endif