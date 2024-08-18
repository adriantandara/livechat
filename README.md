# ChatApp

ChatApp is a simple chat application that enables communication between a server and clients using Boost.Asio for networking. This guide explains how to build and use the application on Linux.

## Requirements

- Linux (recent distribution, e.g., Ubuntu 20.04 or later)
- [Boost C++ Libraries](https://www.boost.org/) (especially Boost.Asio)
- [CMake](https://cmake.org/)
- [GCC](https://gcc.gnu.org/) or another compatible C++ compiler

## Installation

### 1. Clone the Repository

Clone the project from GitHub (replace the URL with the correct one for your project):

```bash
git clone https://github.com/username/ChatApp.git
cd ChatApp
```

---

### 2. Install Dependencies

Ensure you have Boost and CMake installed. You can install Boost using your distribution’s package manager. For example, on Ubuntu:

```bash
sudo apt update
sudo apt install libboost-all-dev cmake g++ make
```

---

### 3. Build the Project

Build the project using CMake and make:

```bash
mkdir build
cd build
cmake ..
make
```

---

## Usage

### Starting the Server

To start the server, use the command:

```bash
./ChatSystem server <port>
```

---

Replace `<port>` with the port you want the server to listen on (e.g., 25655).

### Starting the Client

To start the client and connect to the server, use the command:

```bash
./ChatSystem client <host> <port>
```

---

Replace `<host>` with the IP address or domain name of the server and `<port>` with the port the server is listening on (e.g., 25655).

## Examples

### Starting a Server on Port 25655

```bash
./ChatSystem server 25655
```

---

### Starting a Client Connecting to `trwix.go.ro` on Port 25655

```bash
./ChatSystem client trwix.go.ro 25655
```

---

## Contributing

If you would like to contribute to the project, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-new-feature`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-new-feature`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
