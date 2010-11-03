/*
 * <Copyright Year Your name, optional@email>
 *
 * Copyright 2010 Adam Chyła, adam.chyla@gmail.com
 * All rights reserved. Distributed under the terms of the GNU Lesser General Public License v3.0.
 */

/*
 * DGRAM talker example
 * 
 * Usage:
 * example5 listener_port
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

        Sock soket(PF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in myAddr;
        memset(&myAddr, 0, sizeof(myAddr));
        myAddr.sin_addr.s_addr = htonl(INADDR_ANY); // localhost
        myAddr.sin_port = htons(port);
        myAddr.sin_family = PF_INET;


        struct sockaddr_in theirAddr;
        memset(&theirAddr, 0, sizeof(theirAddr));

        while (true)
        {
            try
            {
                std::string tmp;
                while (std::getline(std::cin, tmp))
                {
                    soket.SendTo(tmp.c_str(), tmp.length(), 0,
                            reinterpret_cast<sockaddr*>(&myAddr), sizeof(sockaddr_in));
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
