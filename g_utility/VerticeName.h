#ifndef VERTICE_NAME
#define VERTICE_NAME

#include "Name.h"

namespace graph
{
    class VerticeName : public Name
    {
    protected:
        /**
         * validates the given character.
         * @return true if the character is alphanumerical or one of the following
         * characters: '[', ']', and ';'; otherwise, false.
         */
        virtual bool isValidCharacter(char) override;
    public:
        explicit VerticeName(const std::string& name) : Name(name, {'[', ']', ';'}) {}
    };
}

#endif