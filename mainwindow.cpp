#include<math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/measurerfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listeningButton_clicked()
{
    if(started)
    {
        stop_measure();
    }
    else
    {
        start_measure();
    }
    started = !started;
}

void MainWindow::stop_measure()
{
    delete ioCoordinator;
    ioCoordinator = nullptr;
    delete tcpMeasurer;
    tcpMeasurer = nullptr;
    delete udpMeasurer;
    udpMeasurer = nullptr;
    ui->statusLabel_tcp->setText("Not Connected");
    ui->statusLabel_udp->setText("Not Connected");
    ui->listeningButton->setText("Start Listening");
}

void MainWindow::start_measure()
{
    ioCoordinator = new IOServiceThreadCoordinator();
    MeasurerFactory f(ioCoordinator);
    tcpMeasurer = f.getTcpMeasurer(ui->portEdit->text().toUInt());

    QObject::connect(tcpMeasurer, SIGNAL(update_speed(double)),
                     this, SLOT(update_speedTcp(double)));
    QObject::connect(tcpMeasurer, SIGNAL(update_totalTransfered(double)),
                     this, SLOT(update_transferedTcp(double)));
    QObject::connect(tcpMeasurer, SIGNAL(update_totalTime(std::chrono::duration<double>)),
                     this, SLOT(update_totalTimeTcp(std::chrono::duration<double>)));
    QObject::connect(tcpMeasurer, SIGNAL(update_msgSize(int)),
                     this, SLOT(update_packetSizeTcp(int)));

    udpMeasurer = f.getUdpMeasurer(ui->portEdit->text().toUInt());

    QObject::connect(udpMeasurer, SIGNAL(update_speed(double)),
                     this, SLOT(update_speedUdp(double)));
    QObject::connect(udpMeasurer, SIGNAL(update_totalTransfered(double)),
                     this, SLOT(update_transferedUdp(double)));
    QObject::connect(udpMeasurer, SIGNAL(update_totalTime(std::chrono::duration<double>)),
                     this, SLOT(update_totalTimeUdp(std::chrono::duration<double>)));
    QObject::connect(udpMeasurer, SIGNAL(update_msgSize(int)),
                     this, SLOT(update_packetSizeUdp(int)));
    QFont font = ui->statusLabel_tcp->font();
    ui->statusLabel_tcp->setText("Live");
    ui->statusLabel_udp->setText("Live");
    ui->listeningButton->setText("Stop Listening");
}

void MainWindow::update_speedTcp(double speed)
{
    ui->speedEdit_tcp->setText(QString::number(speed));
}

void MainWindow::update_transferedTcp(double bytes)
{
    ui->totalEdit_tcp->setText(QString::number(bytes));
}

void MainWindow::update_totalTimeTcp(const std::chrono::duration<double> time)
{
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count();
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count();
    ui->timeEdit_tcp->setText(QString::number(minutes)
                              .append(":")
                              .append(QString::number(seconds)));
}

void MainWindow::update_packetSizeTcp(int bytes)
{
    ui->packetSizeEdit_tcp->setText(QString::number(bytes));
}

void MainWindow::update_speedUdp(double speed)
{
    ui->speedEdit_udp->setText(QString::number(speed));
}

void MainWindow::update_transferedUdp(double bytes)
{
    ui->totalEdit_udp->setText(QString::number(bytes));
}

void MainWindow::update_totalTimeUdp(const std::chrono::duration<double> time)
{
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count();
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count();
    ui->timeEdit_udp->setText(QString::number(minutes)
                              .append(":")
                              .append(QString::number(seconds)));
}

void MainWindow::update_packetSizeUdp(int bytes)
{
    ui->packetSizeEdit_udp->setText(QString::number(bytes));
}


