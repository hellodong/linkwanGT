#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

    void on_testButton_clicked();

    void receiveInfo();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    void SerialPortInit();
};
#endif // MAINWINDOW_H
