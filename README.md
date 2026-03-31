# Basic C++ HTTP Server

A minimal, single-threaded HTTP server written in C++ using POSIX sockets. This project serves as a foundational learning exercise in network programming, demonstrating the basic lifecycle of a TCP connection and the fundamentals of the HTTP protocol.

## Overview

Currently, this project implements a simple blocking loop that performs the following steps:

1. Creates a TCP socket.
2. Binds the socket to port `9999`.
3. Listens for incoming client connections.
4. Accepts connections one at a time.
5. Reads the incoming raw HTTP request into a buffer.
6. Responds with a hardcoded `HTTP/1.1 200 OK` status and a basic text payload.

## Prerequisites

- A C++ compiler (e.g., `g++` or `clang++`)
- A POSIX-compliant environment (Linux, macOS, WSL, etc.)

## Getting Started

### Build

Compile the source code from your terminal:

```bash
g++ main.cpp -o server
```

### Run

Execute the compiled binary to start the server:

```bash
./server
```

### Test

Once the server is running, you can test it by opening a new terminal window and using `curl`:

```bash
curl -i http://localhost:9999
```

Alternatively, open your web browser and navigate to `http://localhost:9999`. You should see the response `"Helooo"` in your browser, and the terminal running your server will print the raw HTTP request headers it received from the client.

## Future Roadmap

This is the first iteration of an ongoing learning project. Planned future enhancements include:

- Building a proper HTTP request parser to handle different methods (`GET`, `POST`, etc.) and headers.
- Transitioning from a blocking architecture to an asynchronous, non-blocking model using `epoll`.