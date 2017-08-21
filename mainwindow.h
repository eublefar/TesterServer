#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "utils/ioservicethreadcoordinator.h"
#include "utils/measurer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_listeningButton_clicked();
    //tcp UI update slots
    void update_speedTcp(double speed);
    void update_transferedTcp(double bytes);
    void update_totalTimeTcp(const std::chrono::duration<double> time);
    void update_packetSizeTcp(int bytes);
    //udp UI update slots
    void update_speedUdp(double speed);
    void update_transferedUdp(double bytes);
    void update_totalTimeUdp(const std::chrono::duration<double> time);
    void update_packetSizeUdp(int bytes);

private:
    void stop_measure();
    void start_measure();

    Ui::MainWindow *ui;

    IOServiceThreadCoordinator *ioCoordinator;

    Measurer *tcpMeasurer;
    Measurer *udpMeasurer;

    bool started = false;
};

#endif // MAINWINDOW_H
