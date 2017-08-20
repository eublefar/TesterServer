#ifndef IOSERVICETHREADCOORDINATOR_H
#define IOSERVICETHREADCOORDINATOR_H
#include "boost/asio.hpp"

#include <thread>
#include <vector>
class IOServiceThreadCoordinator
{
public:
    IOServiceThreadCoordinator(uint8_t pThreadNumber = std::thread::hardware_concurrency());
    ~IOServiceThreadCoordinator();
    boost::asio::io_service& getIOService();
private:
    std::vector<std::unique_ptr<std::thread>> workers;
    boost::asio::io_service io_service;
    bool terminate = false;
};

#endif // IOSERVICETHREADCOORDINATOR_H
