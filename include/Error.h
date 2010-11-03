/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#ifndef NEWSOCK_ERROR_H
#define NEWSOCK_ERROR_H

// C++ API headers
#include <string>


namespace NewSock
{
    class Error
    {
    public:
        Error();
        ~Error();
        int GetErrorID() const;
        virtual const char* GetErrorMessage() const;
        virtual const char* what() const;

    private:
        friend class SetError;

        int fErrorID;
        std::string fMessageText;
    };
}

#endif
