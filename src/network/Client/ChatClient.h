#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <boost/asio.hpp>
#include <string>

class ChatClient
{
public:
    ChatClient(boost::asio::io_context &io_context, const std::string &host, unsigned short port);
    void startRead();
    void writeMessages();

private:
    boost::asio::ip::tcp::socket socket_;
};

#endif // CHATCLIENT_H
