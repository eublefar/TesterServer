#include "tcpserver.h"

#include "boost/asio.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace boost::asio::ip;

TcpServer::TcpServer(boost::asio::io_service& io_service, unsigned short port):
    acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
    socket_(io_service),
    port(port)
{
    acceptor_.async_accept(socket_,
        boost::bind(&TcpServer::handleAccept, this,
          boost::asio::placeholders::error));
}

void TcpServer::setOnReceive(const std::function<handler_receive_t> &value)
{
    receive_handler = value;
}

void TcpServer::setOnSend(const std::function<handler_send_t> &value)
{
    send_handler = value;
}

void TcpServer::send(std::vector<char> &buffer)
{
    boost::asio::async_write(socket_, boost::asio::buffer(buffer),
        boost::bind(send_handler,
                    boost::asio::placeholders::error(),
                    boost::asio::placeholders::bytes_transferred()));
}

void TcpServer::receive(std::vector<char> &buffer)
{
    boost::asio::async_read(socket_, boost::asio::buffer(buffer),
        boost::bind(receive_handler,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void TcpServer::handleAccept(const boost::system::error_code &error)
{

}

