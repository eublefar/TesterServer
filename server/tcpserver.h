#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "serverif.h"

#include "boost/asio.hpp"

#include <functional>
#include <vector>
using namespace boost::asio::ip;

class TcpServer : public ServerIf
{
public:
    TcpServer(boost::asio::io_service& io_service, unsigned short port);
    virtual void setOnReceive (const std::function<handler_receive_t> &value);
    virtual void setOnSend(const std::function<handler_send_t> &value);
    virtual void send(std::vector<char> &buffer);
    virtual void receive(std::vector<char> &buffer);
private:
    void handleAccept(const boost::system::error_code& error);

    std::function<handler_receive_t> receive_handler;
    std::function<handler_send_t> send_handler;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    unsigned short port;
};

#endif // TCPSERVER_H
