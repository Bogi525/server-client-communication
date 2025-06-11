
# Client-Server Communication

A basic synchronous TCP client-server application in C++ using the standalone Asio library. 
Developed as a personal project to learn fundamental socket programming concepts, client authentication, message exchange, and port-forwarding.

#
This project implements a **single-client-at-a-time server** that supports user registration, login, and message exchange.
The client connects, registers or logs in, sends messages, and receives acknowledgments from the server.

## Features:

- TCP socket communication with synchronous blocking calls
- User registration and login functionality
- Client-server message exchange with server acknowledgments
- Handles one client connection at a time

## Technologies:
- C++
- Standalone Asio
- GNU Make
- Developed in Visual Studio Code on Windows 11
