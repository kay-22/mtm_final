#ifndef NAME_H
#define NAME_H

#include <string>
#include <cctype>
#include <unordered_set>

#include <g_except.h>
#include "Parser.h"

namespace graph
{
    /**
     * wrapper class for string that represents a name with some conventional constraints
     */
    class Name
    {
    protected:
        Parser name; 

        /**
         * should validate a character under a decided criteria.
         * @return true if the character is valid; otherwise, false.
         */
        //virtual bool isValidCharacter(char) const = 0;

        /**
         * should validate a string as a possible name string. Each character of the string  
         * could be validated with isValidCharacter.
         * @return true if the string is a valid name string; otherwise, false.
         */
        virtual bool isValidName() const = 0;

    public:
        explicit Name(const std::string& name) :name(name) {}
        Name(const Name&) = default;
        Name& operator=(const Name&) = default;
        bool operator<(const Name&) const;
        virtual ~Name() = default;
        const std::string& toString();
    };
}

#endif