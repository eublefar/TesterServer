#include "ioservicethreadcoordinator.h"

IOServiceThreadCoordinator::IOServiceThreadCoordinator(uint8_t pThreadNumber)
{
    for(int i=0;i<pThreadNumber;++i)
    {
        workers.push_back(std::unique_ptr<std::thread>(new std::thread([&]{while(!terminate)io_service.run();})));
    }
}

IOServiceThreadCoordinator::~IOServiceThreadCoordinator()
{
    terminate = true;
    for(auto &worker : workers)
    {
        worker->join();
    }
}

boost::asio::io_service &IOServiceThreadCoordinator::getIOService()
{
    return io_service;
}
