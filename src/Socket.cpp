/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#include "../include/Socket.h"

namespace NewSock
{
    Sock::Sock(int sockFD)
    {
        Init();

        if (sockFD)
            fSockFD = sockFD;
        else
            fSockFD = -1;
    }

    Sock::Sock(int domain, int type, int protocol, Throw fThrow)
    {
        Init();

        fSockFD = socket(domain, type, protocol);

        if (fThrow)
            if (fSockFD == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Socket(int domain, int type, int protocol)");
                throw Error;
            }
    }


    Sock::Sock(Sock &fSock)
    {
        Init();

        fSockFD = fSock.GetSockFD();
        fBufLength = fSock.GetBufLength();

        for (register int i = 0; i < fBufLength; i++)
            fBuf[i] = fSock.GetBuf()[i];
    }


    Sock::~Sock()
    {
        if (fSockFD != -1)
            close(fSockFD);
    }


    int Sock::Accept(struct sockaddr *addr, Throw fThrow)
    {
        unsigned int fTheirSockaddrSize = sizeof(*addr);

        int fResult = accept(fSockFD,
                            addr,
                            reinterpret_cast<socklen_t*>(&fTheirSockaddrSize));

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Accept(struct sockaddr *addr)");
                throw Error;
            }

        return fResult;
    }


    int Sock::Bind(struct sockaddr *my_addr, Throw fThrow)
    {
        int fResult = bind(fSockFD, my_addr, sizeof(*my_addr));

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Bind(struct sockaddr *my_addr)");
                throw Error;
            }

        return fResult;
    }


    int Sock::Close(Throw fThrow)
    {
        int fResult = close(fSockFD);

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Close()");
                throw Error;
            }

        if (fResult)
            fSockFD = -1;

        return fResult;
    }


    int Sock::Connect(struct sockaddr *serv_addr, Throw fThrow)
    {
        int fResult = connect(fSockFD, serv_addr, sizeof(*serv_addr));

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Connect(struct sockaddr *serv_addr)");
                throw Error;
            }

        return fResult;
    }


    const char *Sock::GetBuf() const
    {
        return reinterpret_cast<const char*>(fBuf);
    }


    int Sock::GetBufLength() const
    {
        return fBufLength;
    }


    int Sock::GetSockFD() const
    {
        return fSockFD;
    }


    int Sock::Listen(int backlog, Throw fThrow)
    {
        int fResult = listen(fSockFD, backlog);

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Listen(int backlog)");
                throw Error;
            }

        return fResult;
    }


    int Sock::Recv(unsigned int flags, Throw fThrow)
    {
        return Recv(fBuf, BufSize, flags);
    }


    int Sock::Recv(void *buf, int len, unsigned int flags, Throw fThrow)
    {
        fBufLength = recv(fSockFD, buf, len, flags);

        if (fThrow)
            switch (fBufLength)
            {
                case -1:
                {
                    SetError Error;
                    Error.SetErrorMessageByErrorID(errno,
                                "Recv(void *buf, int len, unsigned int flags)");
                    throw Error;
                    break;
                }

                case 0:
                {
                    SetError Error;
                    Error.SetErrorMessageByErrorID(errno, "Connection lost");
                    throw Error;
                    break;
                }
            }

        return fBufLength;
    }

    
    int Sock::RecvFrom(unsigned int flags,
                    struct sockaddr *from, socklen_t *fromlen, Throw fThrow)
    {
        fBufLength = RecvFrom(fBuf, BufSize, flags, from, fromlen, fThrow);

        if (fThrow)
            if (fBufLength == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "RecvFrom(unsigned int flags, \
    struct sockaddr *from, socklen_t *fromlen)");
                throw Error;
            }

        return fBufLength;
    }


    int Sock::RecvFrom(void *buf, int len, unsigned int flags,
                    struct sockaddr *from, socklen_t *fromlen, Throw fThrow)
    {
        int fResult = recvfrom(fSockFD, buf, len, flags, from, fromlen);

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "RecvFrom(void *buf, int len, \
    unsigned int flags,\
    struct sockaddr *from, int *fromlen)");
                throw Error;
            }

        return fResult;
    }

    
    int Sock::Send(const void *msg, int len, int flags, Throw fThrow) const
    {
        int fResult = send(fSockFD, msg, len, flags);

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Send(const void *msg, int len, int flags)");
                throw Error;
            }

        return fResult;
    }


    int Sock::SendTo(const void *msg, int len, int flags,
                    const struct sockaddr *to, int tolen, Throw fThrow)
    {
        int fResult = sendto(fSockFD, msg, len, flags, to, tolen);

        if (fThrow)
            if (fResult == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "SendTo(const void *msg, int len, \
    int flags, const struct sockaddr *to, int tolen)");
                throw Error;
            }

        return fResult;
    }


    int Sock::Shutdown(int how, Throw fThrow)
    {
        return shutdown(fSockFD, how);
    }


    int Sock::Socket(int domain, int type, int protocol, Throw fThrow)
    {
        fSockFD = socket(domain, type, protocol);

        if (fThrow)
            if (fSockFD == False)
            {
                SetError Error;
                Error.SetErrorMessageByErrorID(errno, "Socket(int domain, int type, int protocol)");
                throw Error;
            }

        return fSockFD;
    }


    Sock &Sock::operator<<(const std::string &fMessage)
    {
        Send(fMessage.c_str(), fMessage.length());

        return *this;
    }


    Sock &Sock::operator<<(int fNumber)
    {
        std::stringstream fStream;
        fStream << fNumber;

        std::string fMessage;
        fStream >> fMessage;

        Send(fMessage.c_str(), fMessage.length());

        return *this;
    }


    int Sock::operator>>(std::string &fMessage)
    {
        register int fResult = Recv();
        fMessage = "";

        for (register int i = 0; i < fBufLength; i++)
            fMessage += fBuf[i];

        return fResult;
    }


    const float Sock::NewSockLibVersion() const
    {
        const float NewSockLibVERSION = 1.0;

        return NewSockLibVERSION;
    }


    void Sock::Init()
    {
        fBufLength = 0;

        fBuf = new char[BufSize];
        memset(fBuf, 0, BufSize);
    }
}
