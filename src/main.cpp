#include <iostream>
#include <boost/asio.hpp>
#include "network/Server/ChatServer.h"
#include "network/Client/ChatClient.h"

void startServer(boost::asio::io_context &io_context, unsigned short port)
{
    ChatServer server(io_context, port);
    io_context.run();
}

void startClient(boost::asio::io_context &io_context, const std::string &host, unsigned short port)
{
    ChatClient client(io_context, host, port);
    io_context.run();
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <server/client> <port> [host]" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    unsigned short port;

    try
    {
        port = static_cast<unsigned short>(std::stoi(argv[2]));
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid port argument: " << argv[2] << std::endl;
        return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Port argument out of range: " << argv[2] << std::endl;
        return 1;
    }

    boost::asio::io_context io_context;

    if (mode == "server")
    {
        std::cout << "[INFO] Starting server on port " << port << std::endl;
        startServer(io_context, port);
    }
    else if (mode == "client")
    {
        if (argc < 4)
        {
            std::cerr << "Usage: " << argv[0] << " client <port> <host>" << std::endl;
            return 1;
        }
        std::string host = argv[3];
        std::cout << "[INFO] Starting client, connecting to " << host << " on port " << port << std::endl;
        startClient(io_context, host, port);
    }
    else
    {
        std::cerr << "Invalid mode: " << mode << std::endl;
        return 1;
    }

    return 0;
}
