#include "ChatServer.h"
#include <iostream>

ChatServer::ChatServer(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    startAccept();
}

void ChatServer::startAccept()
{
    auto new_connection = std::make_shared<tcp::socket>(acceptor_.get_executor());
    acceptor_.async_accept(*new_connection,
                           [this, new_connection](boost::system::error_code ec)
                           {
                               if (!ec)
                               {
                                   std::string client_ip = new_connection->remote_endpoint().address().to_string();
                                   std::cout << "[INFO] " << client_ip << " client has connected to your server." << std::endl;
                                   connections_.push_back(new_connection);
                                   startRead(new_connection);
                               }
                               startAccept();
                           });
}

void ChatServer::startRead(std::shared_ptr<tcp::socket> socket)
{
    auto buffer = std::make_shared<std::vector<char>>(1024);
    socket->async_read_some(boost::asio::buffer(*buffer),
                            [this, socket, buffer](boost::system::error_code ec, std::size_t length)
                            {
                                if (!ec)
                                {
                                    std::string message(buffer->begin(), buffer->begin() + length);
                                    std::string client_ip = socket->remote_endpoint().address().to_string();
                                    std::cout << "[" << client_ip << "] [CHAT]: " << message << std::endl;
                                    broadcastMessage(message); // Send message to all clients
                                    startRead(socket);
                                }
                                else
                                {
                                    std::string client_ip = socket->remote_endpoint().address().to_string();
                                    auto it = std::find(connections_.begin(), connections_.end(), socket);
                                    if (it != connections_.end())
                                    {
                                        connections_.erase(it);
                                        std::cout << "[INFO] " << client_ip << " [CLIENT] disconnected." << std::endl;
                                    }
                                }
                            });
}

void ChatServer::broadcastMessage(const std::string &message)
{
    for (auto &socket : connections_)
    {
        boost::asio::async_write(*socket, boost::asio::buffer(message),
                                 [](boost::system::error_code ec, std::size_t /*length*/)
                                 {
                                     if (ec)
                                     {
                                         std::cerr << "[ERROR] Failed to send message." << std::endl;
                                     }
                                 });
    }
}
