#ifndef MEASURERFACTORY_H
#define MEASURERFACTORY_H
#include "boost/asio.hpp"

#include <thread>

#include "measurer.h"
#include "ioservicethreadcoordinator.h"

class MeasurerFactory
{
public:
    MeasurerFactory(IOServiceThreadCoordinator *ioCoordinator);

    Measurer* getTcpMeasurer(uint32_t port);
    Measurer* getUdpMeasurer(uint32_t port);
private:
    IOServiceThreadCoordinator* ioCoordinator_;
};

#endif // MEASURERFACTORY_H
