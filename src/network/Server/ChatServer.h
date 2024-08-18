#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <boost/asio.hpp>
#include <vector>
#include <memory>

using boost::asio::ip::tcp;

class ChatServer
{
public:
    ChatServer(boost::asio::io_context &io_context, short port);

private:
    void startAccept();
    void startRead(std::shared_ptr<tcp::socket> socket);
    void broadcastMessage(const std::string &message);

    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<tcp::socket>> connections_;
};

#endif // CHAT_SERVER_H
