#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "client.h"

#define PORT_TCP 5600
#define PORT_UDP 8081
#define SERVER_IP "127.0.0.1"

int main() {
    // Initialize the client
    printf("Starting the client...\n");
    start_client();

    return 0;
}

void start_client() {
    WSADATA wsaData;
    SOCKET sockfd_tcp = INVALID_SOCKET;
    struct sockaddr_in serv_addr_tcp;

    // Initialize Winsock
    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        printf("WSAStartup failed with error: %d\n", wsResult);
        return;
    }

    // Create TCP socket
    sockfd_tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd_tcp == INVALID_SOCKET) {
        printf("Error opening TCP socket: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Initialize server address structure
    memset(&serv_addr_tcp, 0, sizeof(serv_addr_tcp));
    serv_addr_tcp.sin_family = AF_INET;
    serv_addr_tcp.sin_port = htons(PORT_TCP);
    serv_addr_tcp.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (serv_addr_tcp.sin_addr.s_addr == INADDR_NONE) {
        printf("Invalid TCP address: %s\n", SERVER_IP);
        closesocket(sockfd_tcp);
        WSACleanup();
        return;
    }

    // Connect to the server using TCP
    if (connect(sockfd_tcp, (struct sockaddr*)&serv_addr_tcp, sizeof(serv_addr_tcp)) == SOCKET_ERROR) {
        printf("Error connecting to TCP server: %d\n", WSAGetLastError());
        closesocket(sockfd_tcp);
        WSACleanup();
        return;
    }

    // Send message to server
    char message[] = "Hello, server!";
    int bytes_sent = send(sockfd_tcp, message, strlen(message), 0);
    if (bytes_sent == SOCKET_ERROR) {
        printf("Error sending message to TCP server: %d\n", WSAGetLastError());
        closesocket(sockfd_tcp);
        WSACleanup();
        return;
    }

    printf("Message sent to TCP server: %s\n", message);

    // Close TCP socket
    closesocket(sockfd_tcp);

    // Cleanup Winsock
    WSACleanup();
}
