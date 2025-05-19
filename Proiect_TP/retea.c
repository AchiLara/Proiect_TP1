#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "retea.h"


int initWinsock() 
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2,2), &wsa) == 0;
}

int pornesteServer(const char* port) 
{
    if (!initWinsock()) return -1;
    
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET) return -1;

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(port));

    if (bind(serverSock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) 
    {
        closesocket(serverSock);
        return -1;
    }

    listen(serverSock, 1);

    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    SOCKET clientSock = accept(serverSock, (struct sockaddr*)&client, &c);
    closesocket(serverSock);
    return clientSock;
}

int conecteazaLaServer(const char* ip, const char* port) 
{
    if (!initWinsock()) return -1;
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return -1;

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) 
    {
        closesocket(sock);
        return -1;
    }

    return sock;
}

int trimiteMutare(int sockfd, int linie, int coloana) {
    int mutare[2] = {linie, coloana};
    return send(sockfd, (char*)mutare, sizeof(mutare), 0) > 0;
}

int primesteMutare(int sockfd, int* linie, int* coloana) 
{
    int mutare[2];
    int bytes = recv(sockfd, (char*)mutare, sizeof(mutare), 0);
    if (bytes <= 0) return 0;
    *linie = mutare[0];
    *coloana = mutare[1];
    return 1;
}

void inchideSocket(int sockfd) 
{
    closesocket(sockfd);
    WSACleanup();
}