/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

/*
 * SOCK_STREAM listener and talker example
 *
 * Usage:
 * example3 port
 */

#include "../include/Error.h"
#include "../include/Socket.h"

// C++ API headers
#include <cstring>
#include <iostream>
#include <sstream>

// POSIX API headers
#include <arpa/inet.h>
#include <sys/types.h>


using NewSock::Sock;
using NewSock::Error;


int main(int argc, char **argv)
{
    try
    {
        int port = 8010;

        if (argc > 1)
        {
            std::stringstream stream(argv[1]);
            stream >> port;

            if (port <= 0)
                port = 8010;

            std::cerr << "Port: " << port << '\n';
        }

        Sock soket(PF_INET, SOCK_STREAM, 0);

        struct sockaddr_in myAddr;
        memset(&myAddr, 0, sizeof(myAddr));
        myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        myAddr.sin_port = htons(port);
        myAddr.sin_family = PF_INET;

        soket.Bind(reinterpret_cast<struct sockaddr*>(&myAddr));
        soket.Listen(20);


        struct sockaddr_in theirAddr;
        memset(&theirAddr, 0, sizeof(theirAddr));

        while (true)
        {
            try
            {
                Sock soket2(soket.Accept(reinterpret_cast<struct sockaddr*>(&theirAddr)));
                std::string line;

                while (soket2 >> line)
                {
                    std::cout << soket2.GetBufLength() << ": ";

                    std::cout << line;

                    if (line == "exit\r\n") // telnet /r/n
                        return 0;

                    soket2 << "=> " << line;
                }
            }
            catch (Error &fError)
            {
                if (fError.GetErrorID() != NewSock::True)
                    throw fError;
            }
        }
    }
    catch (Error &fError)
    {
        std::cout << "ErrorID: " << fError.GetErrorID() << "\nError message: "
                << fError.what() << '\n';
    }
    catch (std::exception &ex)
    {
        std::cout << "Exception: " << ex.what() << '\n';
    }

    return 0;
}
