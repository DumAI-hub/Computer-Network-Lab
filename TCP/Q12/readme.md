
# Byte Stuffing Client-Server Implementation

This project implements a client-server application that demonstrates byte stuffing protocol in network communication using C. The implementation uses TCP sockets for reliable communication between client and server.

## Prerequisites

- GCC compiler
- Linux/Unix environment
- Basic understanding of socket programming

## Files

- `client.c`: Implementation of the client side
- `server.c`: Implementation of the server side

## Compilation

To compile the programs, use GCC:

```bash
# Compile server
gcc server.c -o server

# Compile client
gcc client.c -o client
```

## Usage

1. First, start the server:
```bash
./server
```

2. Then, in a different terminal, start the client:
```bash
./client
```

3. Enter data when prompted by the client

## How It Works

### Byte Stuffing Process

1. **Client Side:**
   - Takes input data from user
   - Performs byte stuffing by adding '$' at the beginning and end
   - Doubles up any '$' characters in the original data
   - Sends stuffed data to server

2. **Server Side:**
   - Receives stuffed data
   - Performs byte destuffing
   - Sends back the destuffed data
   - Displays both stuffed and original frames

## Protocol

- Flag character: '$'
- Port: 8080
- Maximum buffer size: 1024 bytes

## Error Handling

The implementation includes error handling for:
- Socket creation
- Connection establishment
- Binding
- Sending/Receiving data
- Memory allocation

## Author

Dibakar Patar

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues and enhancement requests.