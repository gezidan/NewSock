/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#ifndef NEWSOCK_SETERROR_H
#define NEWSOCK_SETERROR_H

#include "Const.h"
#include "Error.h"

// C++ API headers
#include <cstring>
#include <string>


namespace NewSock
{
    class SetError : public Error
    {
    public:
        SetError(const char* messageText = NULL);
        SetError(std::string &messageText);
        virtual int SetErrorMessage(const char* messageText);
        virtual void SetErrorID(int errorID);
        virtual void SetErrorMessageByErrorID(int errorID = 0, const char* messageText = NULL);
    };
}

#endif
