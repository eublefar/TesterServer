#include "measurerfactory.h"
#include "measurer.h"
#include "server/tcpserver.h"
#include "server/udpserver.h"

MeasurerFactory::MeasurerFactory(IOServiceThreadCoordinator *ioCoordinator):
    ioCoordinator_(ioCoordinator)
{

}

Measurer* MeasurerFactory::getTcpMeasurer(int port)
{
    ServerIf* tcpServer = new TcpServer(ioCoordinator_->getIOService(), port);
    return new Measurer(tcpServer);
}

Measurer* MeasurerFactory::getUdpMeasurer(int port)
{
    ServerIf* udpServer = new UdpServer(ioCoordinator_->getIOService(), port);
    return new Measurer(udpServer);
}
