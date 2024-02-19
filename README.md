### Socket programming

This C program implements a simple client-server application using sockets. This code is made to work on Windows, although with small fixes to the code it is runnable on Unix too.
- The client sends a message to the server over TCP protocol, and the server responds to the client's message using UDP protocol.
- The client __(client.c)__ creates a TCP socket, connects to the server, sends a message, and then closes the TCP connection. It utilizes Winsock library functions for socket creation, connection, and data transmission.
- The server __(server.c)__ creates both TCP and UDP sockets, binds them to specific ports, and listens for incoming connections. When a TCP client connects, it receives a message, closes the TCP connection, and sends a response to the client     using UDP protocol. It also uses Winsock functions for socket operations.
- Both files include appropriate error handling mechanisms and comments explaining the purpose of each code segment. Additionally, the necessary networking functions and structures from the Winsock library are utilized to establish and manage network connections.

## To run the client-server application on Windows, follow these steps:

# Compile the Code:

- Open Command Prompt (cmd).
- Navigate to the directory containing your C source code files (client.c and server.c).
- Compile both client.c and server.c files separately using GCC compiler with the following commands:
```
gcc -o client.exe client.c -lws2_32
gcc -o server.exe server.c -lws2_32
```
This will generate client.exe and server.exe executables.

# Run the Server:

- In Command Prompt, navigate to the directory containing server.exe.
- Run the server executable with command:
```
server.exe
```
- The server should start listening for incoming connections on TCP port 5600 and UDP port 8081.

# Run the Client:

- Open another instance of Command Prompt.
- Navigate to the directory containing client.exe.
- Run the client with command:
```
client.exe
```
- The client will connect to the server, send a message over TCP, and receive a response over UDP.

# Verify the Communication:

- Check the Command Prompt windows for any output messages from the server and client, confirming the successful communication.
- Optional: Adjust IP Addresses and Ports:
  - If needed, modify the IP addresses and ports in the code files (client.c and server.c) to match your network configuration.
