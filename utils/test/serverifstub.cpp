#include "serverifstub.h"

ServerIfStub::ServerIfStub()
{

}


void ServerIfStub::setOnReceive(const std::function<handler_receive_t> &value)
{
}

void ServerIfStub::setOnSend(const std::function<handler_send_t> &value)
{
}

void ServerIfStub::send(std::vector<char> &buffer)
{
}

void ServerIfStub::receive(std::vector<char> &buffer)
{
}

std::chrono::duration<double> ServerIfStub::getTime_to_wait() const
{
    return time_to_wait;
}

void ServerIfStub::setTime_to_wait(const std::chrono::duration<double> &value)
{
    time_to_wait = value;
}

std::chrono::duration<double> ServerIfStub::getTime_to_wait() const
{
    return time_to_wait;
}

void ServerIfStub::setTime_to_wait(const std::chrono::duration<double> &value)
{
    time_to_wait = value;
}

boost::system::error_code ServerIfStub::getError() const
{
    return error;
}

void ServerIfStub::setError(const boost::system::error_code &value)
{
    error = value;
}

uint32_t ServerIfStub::getBytes_received() const
{
    return bytes_received;
}

void ServerIfStub::setBytes_received(const uint32_t &value)
{
    bytes_received = value;
}

std::chrono::duration<double> ServerIfStub::getTime_to_wait() const
{
    return time_to_wait;
}

void ServerIfStub::setTime_to_wait(const std::chrono::duration<double> &value)
{
    time_to_wait = value;
}

std::function<handler_receive_t> ServerIfStub::getReceive_handler() const
{
    return receive_handler;
}

std::function<handler_send_t> ServerIfStub::getSend_handler() const
{
    return send_handler;
}

void ServerIfStub::setBuffer(std::vector<char> *value)
{
    buffer = value;
}

std::vector<char> &ServerIfStub::getBuffer() const
{
    return buffer;
}
