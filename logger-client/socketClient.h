#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
//#include <winsock.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
/*
create a socket.
bind* - this is probably be unnecessary because you're the client, not the server.
connect to a server.
send/recv - repeat until we have or receive data
shutdown to end read/write.
close to releases data.
*/
namespace client
{
    const char* ipAddress = "127.0.0.1";
    int port = 8888;
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    const char* message;
    char server_reply[2000];
    int recv_size;

    void close()
    {
        closesocket(s);
        WSACleanup();
    }
    
    bool sendMessage(std::string msg)
    {
        const char* cMsg = msg.c_str();
        if (send(s, cMsg, strlen(cMsg), 0))
        {
            return true;
        }
        return false;
    }

    bool init()
    {
        printf("\nInitialising Winsock...");
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return 1;
        }

        printf("Initialised.\n");

        //Create a socket
        if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d", WSAGetLastError());
        }

        printf("Socket created.\n");

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ipAddress);
        server.sin_port = htons(port);

        while (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
        {
            puts("connection error");
            return false;
        }

        puts("connected");

        //Receive a reply from the server
        if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
        {
            puts("recv failed");
        }

        puts("Reply received\n");

        //Add a NULL terminating character to make it a proper string before printing
        server_reply[recv_size] = '\0';
        puts(server_reply);

        message = "Hello server.";
        send(s, message, strlen(message), 0);

        return true;
    }

}