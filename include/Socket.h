/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

#ifndef NEWSOCK_H
#define NEWSOCK_H

#include "Const.h"
#include "SetError.h"

// C++ API headers
#include <cerrno>
#include <cstring>
#include <sstream>
#include <string>

// POSIX API headers
#if defined(linux)
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// MS Windows API headers
#elif defined(_WIN32)
#include <winsock.h>

#else
#error ERROR: Unsupported system.
#endif

namespace NewSock
{
    enum Throw
    {
        SockNoThrow = 0,
        SockThrow = 1
    };

    class Sock
    {
    public:
        Sock(int sockFD = -1);
        Sock(int domain, int type, int protocol, Throw fThrow = SockThrow);
        Sock(Sock &fSock);
        ~Sock();

        virtual int Accept(struct sockaddr *addr, Throw fThrow = SockThrow);
        virtual int Bind(struct sockaddr *my_addr, Throw fThrow = SockThrow);
        virtual int Close(Throw fThrow = SockThrow);
        virtual int Connect(struct sockaddr *serv_addr, Throw fThrow = SockThrow);
        virtual const char *GetBuf() const;
        virtual int GetBufLength() const;
        virtual int GetSockFD() const;
        virtual int Listen(int backlog, Throw fThrow = SockThrow);
        virtual int Recv(unsigned int flags = 0, Throw fThrow = SockThrow);
        virtual int Recv(void *buf, int len, unsigned int flags, Throw fThrow = SockThrow);
        virtual int RecvFrom(unsigned int flags,
                            struct sockaddr *from, socklen_t *fromlen, Throw fThrow = SockThrow);
        virtual int RecvFrom(void *buf, int len, unsigned int flags,
                            struct sockaddr *from, socklen_t *fromle, Throw fThrow = SockThrow);
        virtual int Send(const void *msg, int len, int flags = 0, Throw fThrow = SockThrow) const;
        virtual int SendTo(const void *msg, int len, int flags,
                            const struct sockaddr *to, int tolen, Throw fThrow = SockThrow);
        virtual int Shutdown(int how, Throw fThrow = SockThrow);
        virtual int Socket(int domain, int type, int protocol, Throw fThrow = SockThrow);

        virtual Sock &operator<<(const std::string &fMessage);
        virtual Sock &operator<<(int fNumber);

        virtual int operator>>(std::string &fMessage);

        const float NewSockLibVersion() const;

    private:
        void Init();

        int fSockFD;
        int fBufLength;
        char *fBuf;
    };
}

#endif
