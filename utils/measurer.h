#ifndef MEASURER_H
#define MEASURER_H
#include <QObject>

#include "server/serverif.h"

#include <mutex>

enum Status
{
    NOT_CONNECTED,
    WAITING,
    LISTENING
};

class Measurer : public QObject
{
    Q_OBJECT
public:
    Measurer(ServerIf *server, int msg_size = 15);
    virtual ~Measurer() {}
    std::chrono::duration<double> getTotalTime();
    double getTotalTransfered();
    double getCurrentSpeed();

    int getMsg_size() const;

    std::vector<char> getBuffer();

signals:
    void update_speed(const double speed);
    void update_totalTransfered(const double transfered);
    void update_totalTime(const std::chrono::duration<double> time);
    void update_msgSize(const int size);

private:
    void receiveHandlerSetSize(const boost::system::error_code& error, int b_received);
    void receiveHandlerMeasure(const boost::system::error_code& error, unsigned int b_received);
    void sendHandlerMeasure(const boost::system::error_code& error, int b_sent);

    std::unique_ptr<ServerIf> server;
    int msg_size_;

    std::mutex data_mutex;
        double total_transfered = 0;
        double current_speed = 0;
        std::chrono::duration<double> total_time;
        std::vector<char> buffer;
    std::chrono::time_point<std::chrono::system_clock> transfer_start;

};

#endif // MEASURER_H
