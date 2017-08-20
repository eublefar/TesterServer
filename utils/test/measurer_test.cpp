#include <QObject>
#include <QtTest/QtTest>

#include "utils/measurer.h"
#include "serverifstub.h"

#include <math.h>
#include <iostream>

class Measurer_test : public QObject
{
    Q_OBJECT
public:
    explicit Measurer_test(QObject *parent = nullptr);
    ~Measurer_test();
signals:

private slots:
    void testMeasurement();
    void testWrongMsgSize();
private:

};


Measurer_test::Measurer_test(QObject *parent) : QObject(parent)
{

}

Measurer_test::~Measurer_test()
{

}

void Measurer_test::testMeasurement()
{
    ServerIfStub* serv = new ServerIfStub(std::chrono::seconds(1));//time it takes to receive stuff
    Measurer m(serv, 15); //msg size 15 on default


    std::string msg("SIZE:25");
    serv->getBuffer()->assign(msg.begin(), msg.end());
    serv->getReceive_handler()(boost::asio::error::message_size, 9); //simulate receive msg smaller than requested
    QCOMPARE(serv->getBuffer()->size(), 25U);
    serv->getBuffer()->assign(25, 'a');
    serv->getReceive_handler()(boost::system::error_code(), 25);//simulate correct message size first time
    double speed = 0.025; //0.025 kbytes per second
    double round_up_speed = round(m.getCurrentSpeed()*1000)/1000;
    QCOMPARE(round_up_speed, speed);
    QCOMPARE(m.getTotalTransfered(), 0.025);
//    QVERIFY(m.getTotalTime() == std::chrono::seconds(2)); // Time is not exactly 2 seconds by the obvious reasons, so no testing here
}

void Measurer_test::testWrongMsgSize()
{
    ServerIfStub* serv = new ServerIfStub(std::chrono::seconds(1));//time it takes to receive stuff
    Measurer m(serv, 15); //msg size 15 on default


    std::string msg("SIZE:25");
    serv->getBuffer()->assign(msg.begin(), msg.end());
    serv->getReceive_handler()(boost::asio::error::message_size, 9); //simulate receive msg smaller than requested

    serv->getBuffer()->assign(277, 'a');
    serv->getReceive_handler()(boost::system::error_code(), 277);//simulate correct message size first time

    QCOMPARE(m.getCurrentSpeed(), 0.);
    QCOMPARE(m.getTotalTransfered(), 0.);
}

QTEST_MAIN(Measurer_test)
#include "measurer_test.moc"

