#ifndef SERVERIFMOCK_H
#define SERVERIFMOCK_H
#include "server/serverif.h"
#include <chrono>
#include <thread>
class ServerIfStub : public ServerIf
{
public:
    ServerIfStub(std::chrono::duration<double> time_to_wait = std::chrono::seconds(2)):
          time_to_wait(time_to_wait)
    {
    }


    // ServerIf interface
public:
    virtual void setOnReceive(const std::function<handler_receive_t> &value){receive_handler=value;}
    virtual void setOnSend(const std::function<handler_send_t> &value){send_handler =value;}

    virtual void send(std::vector<char> &buffer)
    {

    }
    virtual void receive(std::vector<char> &buffer)
    {
        this->buffer = &buffer;
        std::this_thread::sleep_for(time_to_wait);
    }


    std::chrono::duration<double> getTime_to_wait() const{return time_to_wait;}
    void setTime_to_wait(const std::chrono::duration<double> &value){time_to_wait = value;}

    std::function<handler_receive_t> getReceive_handler() const{return receive_handler;}

    std::function<handler_send_t> getSend_handler() const{return send_handler;}

    std::vector<char> *getBuffer() const{return buffer;}

private:

    std::function<handler_receive_t> receive_handler;
    std::function<handler_send_t> send_handler;

    std::chrono::duration<double> time_to_wait;

    std::vector<char> *buffer;


};

#endif // SERVERIFMOCK_H
