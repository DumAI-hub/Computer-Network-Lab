## Overview
This problem requires to implement a distributed system consisting of two servers and a client that work together to analyze numbers.
The system determines if a number is even/odd and checks for prime numbers using different servers.

## Components

### 1. Client
- Connects to Server 1 to send a number
- Listens for responses from both servers
- Handles both even and odd number cases
- Port: 4002 (for receiving Server 2 responses)

### 2. Server 1
- Primary server that receives numbers from clients
- Checks if numbers are even or odd
- Handles even numbers directly
- Forwards odd numbers to Server 2
- Port: 4000

### 3. Server 2
- Secondary server that performs prime number checking
- Receives odd numbers from Server 1
- Sends results directly to the client
- Port: 4001


## Technical Requirements
- Linux/Unix operating system
- GCC compiler
- Basic networking capabilities

## Compilation Instructions
```bash
# Compile Server 1
gcc server1.c -o server1

# Compile Server 2
gcc server2.c -o server2

# Compile Client
gcc client.c -o client
```

## Running the System
1. Start Server 2:
```bash
./server2
```

2. Start Server 1:
```bash
./server1
```

3. Start Client:
```bash
./client
```

## Usage
1. Run all components in the order mentioned above
2. Enter a number when prompted by the client
3. System will process the number and return results:
   - If even: Response comes from Server 1
   - If odd: Response comes from both Server 1 and Server 2 (prime check)

## Communication Flow
1. Client → Server 1: Sends number
2. Server 1: 
   - If even: Responds directly to client
   - If odd: Forwards to Server 2
3. Server 2 (for odd numbers):
   - Checks if number is prime
   - Sends result directly to client

## Port Configuration
- Server 1: PORT 4000
- Server 2: PORT 4001
- Client Listening Port: 4002

## Error Handling
- Socket creation failures
- Connection errors
- Send/Receive failures
- Invalid input handling

## Limitations
- Handles one client at a time
- Numbers must be integers
- Local host implementation (127.0.0.1)

## Author
Dibakar Patar

## Notes
- Ensure all ports (4000, 4001, 4002) are available
- Run on localhost for testing
- Close all programs properly to free up ports
```