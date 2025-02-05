# TCP Socket Palindrome Checker using different thread for every user

A client-server application using TCP sockets in C that checks whether a given number is palindrome or not. 
The server handles multiple clients concurrently using threads.

## Features

- TCP Socket implementation
- Multi-threaded server to handle multiple clients
- Palindrome number checking
- Real-time client-server communication

## Prerequisites

- GCC compiler
- POSIX-compliant operating system (Linux/Unix)
- Basic knowledge of terminal/command line


## Compilation Instructions

1. Compile the server:
```bash
gcc server.c -o server -pthread
```

2. Compile the client:
```bash
gcc client.c -o client
```

## Usage

1. First, start the server:
```bash
./server
```
The server will start listening on port 8080.

2. In a different terminal, run the client:
```bash
./client
```

3. When prompted, enter a number to check if it's palindrome.

## Technical Details

### Server (server.c)
- Creates a TCP socket and binds to port 8080
- Listens for incoming client connections
- Creates a new thread for each client connection
- Checks if received number is palindrome
- Sends result back to client
- Supports multiple concurrent clients

### Client (client.c)
- Connects to server on localhost:8080
- Sends a number to server
- Receives and displays the result
- Closes connection after receiving response

## Function Descriptions

### Server-side Functions:
- `isPalindrome(int num)`: Checks if a number is palindrome
- `handle_client(void *arg)`: Thread function to handle client requests
- `main()`: Sets up server socket and accepts connections

### Client-side Functions:
- `main()`: Handles connection to server and user interaction

## Error Handling

The application includes error handling for:
- Socket creation failures
- Connection failures
- Binding errors
- Thread creation issues
- Send/Receive errors

## Limitations

- Only works with integer numbers
- Server runs on localhost (127.0.0.1)
- Fixed port number (8080)
- Maximum client connections limited to 50

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Authors

- Dibakar Patar





## Troubleshooting

1. If "Address already in use" error occurs:
   - Wait for a few minutes and try again
   - Or use a different port number

2. If "Connection refused" error occurs:
   - Ensure server is running
   - Check if firewall is blocking the connection

3. If "Bad file descriptor" error occurs:
   - Ensure proper socket cleanup
   - Check socket initialization

```