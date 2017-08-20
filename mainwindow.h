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
    void on_pushButton_clicked();
    //tcp UI update slots
    void update_SpeedTcp(double speed);
    void update_TransferedTcp(double bytes);
    void update_TotalTimeTcp(const std::chrono::duration<double> time);
    void update_PacketSizeTcp(double bytes);
    //udp UI update slots
    void update_SpeedUdp(double speed);
    void update_TransferedUdp(double bytes);
    void update_TotalTimeUdp(const std::chrono::duration<double> time);
    void update_PacketSizeUdp(double bytes);

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
