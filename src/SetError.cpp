/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#include "../include/SetError.h"


namespace NewSock
{
    SetError::SetError(const char* messageText)
    {
        if (messageText)
            fMessageText = messageText;
    }


    SetError::SetError(std::string &messageText)
    {
        if (!messageText.empty())
            fMessageText = messageText;
    }


    int SetError::SetErrorMessage(const char* messageText)
    {
        if (messageText)
        {
            fMessageText = messageText;
            return True;
        }
        else
            return False;
    }


    void SetError::SetErrorID(int errorID)
    {
        fErrorID = errorID;
    }


    void SetError::SetErrorMessageByErrorID(int errorID, const char* messageText)
    {
        if (messageText)
        {
            fMessageText = messageText;
            fMessageText += ": ";
            fMessageText += strerror(errorID);
        }
        else
            fMessageText == strerror(errorID);

        fErrorID = errorID;
    }
}
