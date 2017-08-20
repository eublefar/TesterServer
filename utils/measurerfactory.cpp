#include "measurerfactory.h"
#include "measurer.h"
#include "server/tcpserver.h"
#include "server/udpserver.h"

MeasurerFactory::MeasurerFactory(IOServiceThreadCoordinator *ioCoordinator):
    ioCoordinator_(ioCoordinator)
{

}

Measurer* MeasurerFactory::getTcpMeasurer(uint32_t port)
{
    ServerIf* tcpServer = new TcpServer(ioCoordinator_->getIOService(), port);
    return new Measurer(tcpServer);
}

Measurer* MeasurerFactory::getUdpMeasurer(uint32_t port)
{
    ServerIf* udpServer = new UdpServer(ioCoordinator_->getIOService(), port);
    return new Measurer(udpServer);
}
