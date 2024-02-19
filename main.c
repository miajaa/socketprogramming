#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Function prototypes
void start_server();
void start_client();

int main() {
    // Initialize the server
    printf("Starting the server...\n");
    start_server();

    // Give some time for the server to start
    Sleep(2000);

    // Initialize the client
    printf("Starting the client...\n");
    start_client();

    return 0;
}
