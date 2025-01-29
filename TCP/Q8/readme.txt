# File Copy Server-Client Application

## Description
This application implements a client-server architecture using TCP sockets to copy files. The server accepts file copy requests from clients and creates/copies files as requested. The client can specify both source and destination filenames for the copy operation.

## Features
- TCP socket-based communication
- Binary file support
- Error handling for file operations
- Real-time status updates
- Support for multiple client connections (sequential)

## Prerequisites
- Linux/Unix operating system
- GCC compiler
- Basic knowledge of terminal operations



2. Compile the programs:
```bash
make
# or manually:
gcc server.c -o server
gcc client.c -o client
```

## Usage

### Starting the Server
```bash
./server
```
The server will start listening on port 4000.

### Running the Client
```bash
./client
```
Follow the prompts to:
1. Enter source filename
2. Enter destination filename

## Program Flow
1. Server starts and listens for connections
2. Client connects to server
3. Client sends source and destination filenames
4. Server verifies source file existence
5. Server creates/opens destination file
6. Server copies file contents
7. Server sends completion status
8. Client displays status messages


## Error Handling
The application handles various error scenarios:
- Source file not found
- Unable to create destination file
- Connection failures
- File operation errors

## Example Usage
```bash
# Terminal 1 (Server)
$ ./server
Server listening on port 4000...

# Terminal 2 (Client)
$ ./client
Enter source filename: input.txt
Enter destination filename: output.txt
Server: File copy started
Server: File copy completed
```


## Compilation
```bash

# Manual compilation
gcc -o server server.c
gcc -o client client.c
```

# Manual cleanup
rm server client
```

## Dependencies
- Standard C libraries
- POSIX socket API
- Unix/Linux system calls

## Common Issues
1. Permission Denied
   - Solution: Check file permissions
   
2. Address Already in Use
   - Solution: Change port or wait for timeout

3. Connection Refused
   - Solution: Ensure server is running

## Author
[Your Name]