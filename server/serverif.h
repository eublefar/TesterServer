#ifndef SERVERIF_H
#define SERVERIF_H

#include <vector>
#include <functional>

#include "boost/asio.hpp"

using handler_receive_t = void(const boost::system::error_code& error, int b_received);
using handler_send_t = void(const boost::system::error_code& error, int);
class ServerIf
{
public:

    virtual void setOnReceive (const std::function<handler_receive_t> &value) = 0;
    virtual void setOnSend(const std::function<handler_send_t> &value) = 0;
    virtual void send(std::vector<char> &buffer) = 0;
    virtual void receive(std::vector<char> &buffer) = 0;
};

#endif // SERVERIF_H
