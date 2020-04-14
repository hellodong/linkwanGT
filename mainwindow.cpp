#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort;
    SerialPortInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial;
}

void MainWindow::SerialPortInit()
{
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        QSerialPort serial;
        serial.setPort(info);
        qDebug() << serial.portName();
        ui->comboBox->addItem(serial.portName());
    }
}


void MainWindow::on_comboBox_activated(int index)
{
        qDebug("combo Box %d \n", index);

}

void MainWindow::on_pushButton_clicked(bool checked)
{
    qDebug() << checked;

    QString serialName(ui->comboBox->currentText());
    if (serialName.isEmpty()){
        return;
    }
    if (serial->isOpen()){
        return;
    }
    serial->setPortName(serialName);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setParity(QSerialPort::)
}
