#ifndef NAME_H
#define NAME_H

#include <string>
#include <cctype>
#include <unordered_set>

namespace graph
{
    /**
     * wrapper class for string that represents a name with some conventional constraints
     */
    class Name
    {
    public:
        typedef std::unordered_set<char> SpecialCharacters;
        explicit Name(const std::string& name, const SpecialCharacters& special_chars = SpecialCharacters());
        Name(const Name&) = default;
        Name& operator=(const Name&) = default;
        bool operator<(const Name&);
        virtual ~Name() = default;
        const std::string& toString();
        
    protected:
        std::string name;
        SpecialCharacters special_chars;

        /**
         * should validate a character under a decided constraint.
         * @return true if the character is valid; otherwise, false.
         */
        virtual bool isValidCharacter(char) = 0;

        /**
         * validates a string as a possible name string. Each character of the string is 
         * validated with isValidCharacter.
         * @return true if the string is a valid name string; otherwise, false.
         */
        virtual bool isValidNameString(const std::string&);
    };
}

#endif