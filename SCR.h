#ifndef SCR_H
#define SCR_H

#include <QString>
#include <QByteArray>


class CRC16Modbus
{   
    enum {arrayCRCTableLength = 256};

    QByteArray result;
    quint16 crcTable[arrayCRCTableLength]; //< test

    void initCRC16Table();

    quint16 updateCRC16(quint16 crc, const quint8 c);

public:

    int il, czas;

    void calculateCRC16(const QByteArray src = 0);

    CRC16Modbus(const QByteArray src = 0);

    QStringList CRC16Table() const;

    QByteArray CRC16Data() const;

    void setCRC16(const QByteArray src = 0);
};


#endif // SCR_H
