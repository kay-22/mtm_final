#ifndef GRAPH_NAME
#define GRAPH_NAME

#include "VerticeName.h"

namespace graph
{
    class AlphanumericName : public VerticeName
    {
    protected:
        /**
         * validates the given character.
         * @return true if the character is alphanumerical 
         */
        virtual bool isValidCharacter(char) override;
    public:
        AlphanumericName(const std::string& name) : VerticeName(name, SpecialCharacters()) {}
    };
} // namespace graph


#endif