# Bit-Stuffing UDP Client-Server Implementation

## Overview
This project demonstrates the bit-stuffing technique using a UDP client-server architecture. The implementation includes bit stuffing at the client side and bit destuffing at the server side.

## Data Flow Diagram
```
[Client]                                 [Server]
   |                                        |
   |--- Input Bit Sequence                  |
   |    (e.g., "111111111")                |
   |                                        |
   |--- Perform Bit Stuffing               |
   |    (Insert 0 after five 1s)           |
   |    ("1111101111")                     |
   |                                        |
   |-------- Send Stuffed Data ------->    |
   |                                        |
   |                                        |--- Receive Stuffed Data
   |                                        |
   |                                        |--- Perform Bit Destuffing
   |                                        |    (Remove stuffed 0s)
   |                                        |
   |                                        |--- Display Original Data
```

## Components

### 1. Client (client.c)
- Creates UDP socket
- Gets bit sequence input from user
- Performs bit stuffing
- Sends stuffed data to server

### 2. Server (server.c)
- Creates UDP socket
- Listens for incoming data
- Performs bit destuffing
- Displays original message

## Technical Details

### Bit Stuffing Rules
- A '0' is inserted after five consecutive '1's
- Used to prevent data patterns from being mistaken for control information

### Protocol
- UDP (User Datagram Protocol)
- Port: 8080
- Maximum message length: 1024 bytes

## Implementation Flow

### Client Side:
1. Socket Creation
2. Get user input (bit sequence)
3. Bit stuffing process
4. Send data to server
5. Close socket

### Server Side:
1. Socket Creation
2. Bind to port
3. Wait for data
4. Receive stuffed data
5. Perform destuffing
6. Display results
7. Close socket

## How to Compile and Run

### Compilation
```bash
# Compile server
gcc server.c -o server

# Compile client
gcc client.c -o client
```

### Execution
```bash
# Terminal 1 - Run server
./server

# Terminal 2 - Run client
./client
```

## Example Usage

```bash
# Server Terminal
$ ./server
Server running... waiting for data...
Received stuffed data: 1111101111
After destuffing: 111111111

# Client Terminal
$ ./client
Enter the bit sequence (0s and 1s): 111111111
After bit stuffing: 1111101111
Data sent to server.
```

## Function Descriptions

### Client Functions
- `bitStuffing(char *input, char *output)`
  - Input: Original bit sequence
  - Output: Stuffed bit sequence
  - Process: Inserts 0 after five consecutive 1s

### Server Functions
- `bitDestuffing(char *stuffedData, char *destuffedData)`
  - Input: Stuffed bit sequence
  - Output: Original bit sequence
  - Process: Removes stuffed 0s

## Error Handling
- Socket creation failure
- Binding failure
- Invalid input handling

## System Requirements
- Linux/Unix-based operating system
- GCC compiler
- Basic networking support

## Limitations
- Only handles binary input (0s and 1s)
- Maximum message length of 1024 bytes
- No error correction mechanisms
- Basic implementation without advanced features

## Future Enhancements
1. Add error checking for input validation
2. Implement acknowledgment mechanism
3. Add support for larger message sizes
4. Include error correction capabilities
5. Add GUI interface