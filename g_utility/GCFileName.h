#ifndef GC_FILE_NAME
#define GC_FILE_NAME

#include "Name.h"

namespace graph
{
    class GCFileName : public Name
    {
    protected:
        /**
         * validates the given character.
         * @return false if the character is '/' or '\0'; otherwise, true.
         */
        virtual bool isValidCharacter(char) override;
    public:
        explicit GCFileName(const std::string& name) : Name(name, {'/', char(0)}) {}
    };
}

#endif