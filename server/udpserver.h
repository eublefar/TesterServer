#ifndef UDPSERVER_H
#define UDPSERVER_H
#include "serverif.h"

#include "boost/asio.hpp"

#include <functional>
#include <vector>


class UdpServer : public ServerIf
{
public:
    UdpServer(boost::asio::io_service& io_service, unsigned short port);
    virtual void setOnReceive (const std::function<handler_receive_t> &value);
    virtual void setOnSend(const std::function<handler_send_t> &value);
    virtual void send(std::vector<char> &buffer);
    virtual void receive(std::vector<char> &buffer);
private:
    std::function<handler_receive_t> receive_handler;
    std::function<handler_send_t> send_handler;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    unsigned short port;
};

#endif // UDPSERVER_H
