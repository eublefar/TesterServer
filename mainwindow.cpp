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

void MainWindow::on_pushButton_clicked()
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

}

void MainWindow::start_measure()
{

}

void MainWindow::update_SpeedTcp(double speed)
{

}

void MainWindow::update_TransferedTcp(double bytes)
{

}

void MainWindow::update_TotalTimeTcp(const std::chrono::duration<double> time)
{

}

void MainWindow::update_PacketSizeTcp(double bytes)
{

}

void MainWindow::update_SpeedUdp(double speed)
{

}

void MainWindow::update_TransferedUdp(double bytes)
{

}

void MainWindow::update_TotalTimeUdp(const std::chrono::duration<double> time)
{

}

void MainWindow::update_PacketSizeUdp(double bytes)
{

}


