#include "ChatClient.h"
#include <iostream>
#include <thread>

ChatClient::ChatClient(boost::asio::io_context &io_context, const std::string &host, unsigned short port)
    : socket_(io_context)
{
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    boost::asio::connect(socket_, endpoints);
    std::cout << "[INFO] Connected to server at " << host << " on port " << port << std::endl;
    startRead();
    std::thread([this]()
                { writeMessages(); })
        .detach();
}

void ChatClient::startRead()
{
    auto buffer = std::make_shared<std::vector<char>>(1024);
    socket_.async_read_some(boost::asio::buffer(*buffer),
                            [this, buffer](boost::system::error_code ec, std::size_t length)
                            {
                                if (!ec)
                                {
                                    std::string message(buffer->begin(), buffer->begin() + length);
                                    startRead();
                                }
                                else
                                {
                                    std::cerr << "[ERROR] Disconnected from server." << std::endl;
                                }
                            });
}

void ChatClient::writeMessages()
{
    std::string message;
    while (std::getline(std::cin, message))
    {
        boost::asio::async_write(socket_, boost::asio::buffer(message + "\n"),
                                 [](boost::system::error_code ec, std::size_t /*length*/)
                                 {
                                     if (ec)
                                     {
                                         std::cerr << "[ERROR] Failed to send message." << std::endl;
                                     }
                                 });
    }
}
