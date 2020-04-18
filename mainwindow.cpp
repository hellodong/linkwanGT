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
    ui->textBrowser->setReadOnly(true);
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
        ui->combox->addItem(serial.portName());
    }
}

void MainWindow::receiveInfo()
{
        QByteArray info = serial->readAll();
        ui->textBrowser->insertPlainText(info);
}

void MainWindow::on_comboBox_activated(int index)
{

}

void MainWindow::on_testButton_clicked()
{
    QString serialName(ui->combox->currentText());
    if (serialName.isEmpty()){
        qDebug()<<"No Serial Name";
        return;
    }
    if (serial->isOpen()){
        qDebug()<<"Serial("<<serialName<<") is Openend";
        return;
    }
    serial->setPortName(serialName);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QSerialPort::ReadWrite)){
         qDebug()<<"Serial("<<serialName<<") Open";
         ui->textBrowser->append("Serial Open");
         connect(serial,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
    }else{
        qDebug()<<"Serial("<<serialName<<") Open failed";
        ui->textBrowser->append("Serial Open Failed");
    }
}
