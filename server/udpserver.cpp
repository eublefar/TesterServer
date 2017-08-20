#include "udpserver.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace boost::asio::ip;

UdpServer::UdpServer(boost::asio::io_service& io_service, unsigned short port):
    socket_(io_service, udp::endpoint(udp::v4(), port)),
    port(port)
{

}

void UdpServer::setOnReceive(const std::function<handler_receive_t> &value)
{
    receive_handler = value;
}

void UdpServer::setOnSend(const std::function<handler_send_t> &value)
{
    send_handler = value;
}

void UdpServer::send(std::vector<char> &buffer)
{
    socket_.async_send_to(boost::asio::buffer(buffer), remote_endpoint_,
                          boost::bind(send_handler,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}

void UdpServer::receive(std::vector<char> &buffer)
{
    socket_.async_receive_from(
      boost::asio::buffer(buffer), remote_endpoint_,
      boost::bind(receive_handler,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}


