#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <windows.h>

#include "SCR.h"

#include <QRegExp>
#include <QtCore/QtEndian>
#include <QShortcut>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp HEXregExp("[A-Fa-f0-9]{0,}");

    ui->lineEditByteCode->setValidator(new QRegExpValidator(HEXregExp, this));

    connect(ui->lineEditByteCode, SIGNAL(returnPressed()),
            this, SLOT(on_calculatePushButton_clicked()));

    connect(ui->lineEditIloscPowtorzen, SIGNAL(returnPressed()),
            this, SLOT(on_calculatePushButton_clicked()));

    connect(ui->lineEditCzas, SIGNAL(returnPressed()),
            this, SLOT(on_calculatePushButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditByteCode_textChanged(const QString &arg1)
{
    ui->lineEditByteCode->setText(arg1.toUpper());
}

void MainWindow::on_lineEditIloscPowtorzen_textChanged(const QString &arg1)
{
    ui->lineEditByteCode->setText(arg1.toUpper());
}

void MainWindow::on_pushButton_clicked()
{
    int c = ui->lineEditIloscPowtorzen->text().toInt();

    CRC16Modbus crc16(QByteArray::fromHex(ui->lineEditByteCode->text().toLocal8Bit()));

    crc16.il=c;

    crc16.calculateCRC16(QByteArray::fromHex(ui->lineEditByteCode->text().toLocal8Bit()));

    int i=crc16.czas;

    QString s=QString::number(i);

    ui->lineEditCzas->setText(s);

    ui->lineEditOutputCRC->setText(crc16.CRC16Data().toHex().toUpper());
}

