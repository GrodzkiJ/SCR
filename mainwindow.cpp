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

    // Tworzy walidator, aby odfiltrować wszystkie dane wejściowe oprócz szesnastkowego kodu bajtowego.
    // Zakres wprowadzania to liczby od 0 do 9 i litery alfabetu łacińskiego od A do F,
    // wielkie i małe litery.

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

    //Obliczanie sumy kontrolnej obiektu crc16. Jako argument wysyłamy tutaj zestaw bajtów w
    //formacie szesnastkowym i uważamy, że jest to tablica bajtów.

    CRC16Modbus crc16(QByteArray::fromHex(ui->lineEditByteCode->text().toLocal8Bit()));

    crc16.il=c;

    crc16.calculateCRC16(QByteArray::fromHex(ui->lineEditByteCode->text().toLocal8Bit()));

    int i=crc16.czas;

    QString s=QString::number(i);

    ui->lineEditCzas->setText(s);

    //Otrzymujemy wynik obliczeń jako tablicę bajtów w QByteArray.

    ui->lineEditOutputCRC->setText(crc16.CRC16Data().toHex().toUpper());
}

