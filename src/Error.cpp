/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#include "../include/Error.h"


namespace NewSock
{
    Error::Error()
    {
        fErrorID = 0;
    }


    Error::~Error()
    {
    }


    int Error::GetErrorID() const
    {
        return fErrorID;
    }


    const char* Error::GetErrorMessage() const
    {
        return fMessageText.c_str();
    }


    const char* Error::what() const
    {
        return fMessageText.c_str();
    }
}
