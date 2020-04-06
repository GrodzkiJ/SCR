#ifndef SCR_H
#define SCR_H

#include <QString>
#include <QByteArray>

//Klasa akceptująca bajty przez konstruktor i / lub bajty metody
//setCRC16() wykonuje dla nich obliczenie sumy kontrolnej.
class CRC16Modbus
{   
    enum {arrayCRCTableLength = 256};

    QByteArray result;
    quint16 crcTable[arrayCRCTableLength]; //Metoda CRC16Modbus::initCRC16Table tworzy tabelę CRC-16.

    void initCRC16Table();

    quint16 updateCRC16(quint16 crc, const quint8 c);

public:

    int il, czas;

    void calculateCRC16(const QByteArray src = 0);

    //CRC16Modbus::calculateCRC16 obliczenie sumy kontrolnej CRC16.
    //Wynik jest zapisywany w wewnętrznej tablicy, którą można uzyskać, wywołując metodę CRC16Data ().
    //src - bajty źródłowe do obliczeń.

    CRC16Modbus(const QByteArray src = 0);

    //CRC16ModBus Konstruktor oblicza sumę kontrolną CRC-16 z otrzymanej tablicy bajtów.

    QStringList CRC16Table() const;

    //CRC16Modbus::CRC16Table drukuje tabelę na konsoli, jeśli włączony jest tryb debugowania.
    //Zwraca tabelę jako tablicę wierszy QString. Tabela jako zestaw wierszy.

    QByteArray CRC16Data() const;

    //CRC16Modbus::CRC16Data metoda zwraca wynik obliczeń sumy kontrolnej. Zwraca wynik jako tablicę bajtów QByteArray.


    void setCRC16(const QByteArray src = 0);

    //CRC16Modbus::setCRC16 metoda zapisuje i przelicza nowe dane, jeśli obiekt został już utworzony. Src nowa tablica danych.


    ~CRC16Modbus();
};


#endif // SCR_H
