#ifndef GC_FILE_NAME_H
#define GC_FILE_NAME_H

#include "Name.h"

namespace graph
{
    class GCFileName : public Name
    {
    protected:
        /**
         * @return false if at lease one character is '/' or char(0) ; otherwise, true.
         */
        virtual bool isValidName() const override;
    public:
        explicit GCFileName(const std::string& name);
    };
}

#endif