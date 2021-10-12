#pragma once
#include <iostream>
#include <stdio.h>
//#include <winsock.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

namespace Socket
{
    int port = 8888;
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    const char *message;
    char client_reply[2000];;
    int recv_size;
    int iResult;

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

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(port);

        //Bind
        if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        {
            printf("Bind failed with error code : %d", WSAGetLastError());
        }

        puts("Bind done");

        restartListen:
        //Listen to incoming connections
        listen(s, 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");

        c = sizeof(struct sockaddr_in);
        new_socket = accept(s, (struct sockaddr*)&client, &c);
        if (new_socket == INVALID_SOCKET)
        {
            printf("accept failed with error code : %d", WSAGetLastError());
        }

        puts("Connection accepted");

        //Reply to client
        message = "Hello Client!\n";
        send(new_socket, message, strlen(message), 0);

        do {
            iResult = recv(new_socket, client_reply, sizeof(client_reply), 0);
            if (iResult > 0)
            {
                printf("Bytes received: %d\n", iResult);
                //client_reply[recv_size] = '\0';
                puts(client_reply);
            }
            else if (iResult == 0)
            {
                printf("Connection closed\n");
                goto restartListen;
            }
            else
                printf("recv failed: %d\n", WSAGetLastError());

        } while (iResult > 0);
        
        getchar();

        closesocket(s);
        WSACleanup();
    }

};