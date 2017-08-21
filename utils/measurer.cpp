#include "measurer.h"


Measurer::Measurer(ServerIf *pServer, int pMsg_size):
    server(pServer),
    msg_size_(pMsg_size)
{
    buffer.resize(pMsg_size, '\0');
    pServer->setOnReceive(std::bind(&Measurer::receiveHandlerSetSize,this,
                                    std::placeholders::_1, std::placeholders::_2));
    pServer->receive(buffer);
}

void Measurer::receiveHandlerSetSize(const boost::system::error_code &error, int b_received)
{
    if (!error || error == boost::asio::error::message_size)
    {
        if(strstr(buffer.data(), "SIZE") && (b_received > 5))
        {
            int new_size = atoi(buffer.data()+5);
            msg_size_ = new_size;
            buffer.resize(new_size, '\0');
            server->setOnReceive(std::bind(&Measurer::receiveHandlerMeasure,this,
                                            std::placeholders::_1, std::placeholders::_2));
            transfer_start = std::chrono::system_clock::now();
            emit update_msgSize(msg_size_);
        }
        else
        {
            std::string s{"Wrong Size"};
            std::vector<char> msg;
            msg.assign(s.begin(), s.end());
            server->send(msg);
        }
    }
    server->receive(buffer);
}

void Measurer::receiveHandlerMeasure(const boost::system::error_code &error, unsigned int b_received)
{
    if (!error && b_received == msg_size_)
    {
        std::chrono::duration<double> transfer_time = std::chrono::system_clock::now() - transfer_start;
        data_mutex.lock();
            total_transfered+=((double)b_received)/1000;
            total_time += transfer_time;
            current_speed = ((double)b_received)/(transfer_time.count()* 1000);
            emit update_speed(current_speed);
            emit update_totalTransfered(total_transfered);
            emit update_totalTime(total_time);
        data_mutex.unlock();
        transfer_start = std::chrono::system_clock::now();
    }
    server->receive(buffer);
}

void Measurer::sendHandlerMeasure(const boost::system::error_code &error, int b_sent)
{

}

std::vector<char> Measurer::getBuffer()
{
    std::lock_guard<std::mutex> guard(this->data_mutex);
    return buffer;
}

int Measurer::getMsg_size() const
{
    return msg_size_;
}


std::chrono::duration<double> Measurer::getTotalTime()
{
    std::lock_guard<std::mutex> guard(this->data_mutex);
    return total_time;
}

double Measurer::getTotalTransfered()
{
    std::lock_guard<std::mutex> guard(this->data_mutex);
    return total_transfered;
}

double Measurer::getCurrentSpeed()
{
    std::lock_guard<std::mutex> guard(this->data_mutex);
    return current_speed;
}

