#ifndef MEASURER_H
#define MEASURER_H
#include <QObject>

#include "server/serverif.h"

#include <mutex>

class Measurer : QObject
{
    Q_OBJECT
public:
    Measurer(ServerIf *server, uint32_t msg_size = 15);
    virtual ~Measurer() {}
    std::chrono::duration<double> getTotalTime();
    double getTotalTransfered();
    double getCurrentSpeed();

    uint32_t getMsg_size() const;

    std::vector<char> getBuffer() const;

signals:
    void updateSpeed(const double speed);
    void updateTotalTransfered(const double transfered);
    void updateTotalTime(const std::chrono::duration<double> time);
    void updateMsgSize(const uint32_t size);

private:
    void receiveHandlerSetSize(const boost::system::error_code& error, int b_received);
    void receiveHandlerMeasure(const boost::system::error_code& error, unsigned int b_received);
    void sendHandlerMeasure(const boost::system::error_code& error, int b_sent);

    std::unique_ptr<ServerIf> server;
    uint32_t msg_size_;

    std::mutex data_mutex;
        double total_transfered = 0;
        double current_speed = 0;
        std::chrono::duration<double> total_time;
        std::vector<char> buffer;
    std::chrono::time_point<std::chrono::system_clock> transfer_start;

};

#endif // MEASURER_H
