#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "server.h"


#define TCP_PORT 5600
#define UDP_PORT 8081
#define BUF_SIZE 1024

void start_server() {
    WSADATA wsaData;
    SOCKET tcp_socket, udp_socket;
    struct sockaddr_in tcp_server_addr, udp_server_addr, client_addr;
    int client_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return;
    }

    // Create TCP socket
    tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_socket == INVALID_SOCKET) {
        printf("Error opening TCP socket\n");
        WSACleanup();
        return;
    }

    // Create UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_socket == INVALID_SOCKET) {
        printf("Error opening UDP socket\n");
        closesocket(tcp_socket);
        WSACleanup();
        return;
    }

    // Initialize TCP server address
    memset(&tcp_server_addr, 0, sizeof(tcp_server_addr));
    tcp_server_addr.sin_family = AF_INET;
    tcp_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcp_server_addr.sin_port = htons(TCP_PORT);

    // Initialize UDP server address
    memset(&udp_server_addr, 0, sizeof(udp_server_addr));
    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    udp_server_addr.sin_port = htons(UDP_PORT);

    // Bind TCP socket
    if (bind(tcp_socket, (struct sockaddr *)&tcp_server_addr, sizeof(tcp_server_addr)) == SOCKET_ERROR) {
        printf("Error on binding TCP\n");
        closesocket(tcp_socket);
        closesocket(udp_socket);
        WSACleanup();
        return;
    }

    // Bind UDP socket
    if (bind(udp_socket, (struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr)) == SOCKET_ERROR) {
        printf("Error on binding UDP\n");
        closesocket(tcp_socket);
        closesocket(udp_socket);
        WSACleanup();
        return;
    }

    // Listen for TCP connections
    listen(tcp_socket, 5);

    printf("Server listening on TCP port %d and UDP port %d\n", TCP_PORT, UDP_PORT);

    while (1) {
        // Accept TCP connection
        SOCKET new_tcp_socket = accept(tcp_socket, (struct sockaddr *)&client_addr, &client_len);
        if (new_tcp_socket == INVALID_SOCKET) {
            printf("Error on accept\n");
            closesocket(tcp_socket);
            closesocket(udp_socket);
            WSACleanup();
            return;
        }

        // Receive data from TCP client
        memset(buffer, 0, BUF_SIZE);
        int bytes_received = recv(new_tcp_socket, buffer, BUF_SIZE, 0);
        if (bytes_received == SOCKET_ERROR) {
            printf("Error reading from TCP socket\n");
            closesocket(new_tcp_socket);
            closesocket(tcp_socket);
            closesocket(udp_socket);
            WSACleanup();
            return;
        }

        printf("Received message from TCP client: %s\n", buffer);

        // Close TCP connection
        closesocket(new_tcp_socket);

        // Send response to UDP client
        sendto(udp_socket, buffer, bytes_received, 0, (struct sockaddr *)&client_addr, client_len);
    }

    // Close sockets
    closesocket(tcp_socket);
    closesocket(udp_socket);

    // Cleanup Winsock
    WSACleanup();
}

int main() {
    start_server();
    return 0;
}
