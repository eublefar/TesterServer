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

    Measurer* getTcpMeasurer(int port);
    Measurer* getUdpMeasurer(int port);
private:
    IOServiceThreadCoordinator* ioCoordinator_;
};

#endif // MEASURERFACTORY_H
