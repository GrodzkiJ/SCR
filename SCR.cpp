#include "SCR.h"
#include <iostream>
#include <windows.h>

#include <QDebug>
#include <QStringList>

using namespace std;

CRC16Modbus::CRC16Modbus(const QByteArray src):
    crcTable{0}
{
    il=1;
    czas=0;
    initCRC16Table();

    if (!src.isNull()) {
        calculateCRC16(src);
    }
}

void CRC16Modbus::initCRC16Table()
{
    const quint16 polynomial = 0xA001;

    quint32 index, j;
    quint16 crc, c;

    for (index = 0; index < arrayCRCTableLength; ++index) {

        crc = 0;
        c = index;

        for (j = 0; j < 8; ++j) {
            if ( ( crc ^ c ) & 0x0001 )
                crc = ( crc >> 1 ) ^ polynomial;
            else
                crc =   crc >> 1;

            c = c >> 1;
        }

        crcTable[index] = crc;
    }
}

QStringList CRC16Modbus::CRC16Table() const
{

    const quint8 columns = 15;
    int counter = 0;
    bool flag = true;

    QStringList strList;

    for (int currentColumn = 0; currentColumn < columns && flag; ++currentColumn) {
        QDebug deb = qDebug();
        for (int col = 0; flag; ++col) {
            QByteArray src = QByteArray::number(crcTable[counter++], 16).toUpper();

#ifdef QT_DEBUG
            deb << QString(src) << "	";
#endif
            strList << QString(src);

            if (counter >= arrayCRCTableLength)
                flag = false;
        }
    }

    return strList;
}

void CRC16Modbus::calculateCRC16(const QByteArray src)
{
    DWORD t1, t2;

    t1=GetTickCount();

    for(int i=0;i<il;i++)
    {

#ifdef QT_DEBUG
    qDebug("Numbers byte arrey: %d", src.length()); // 5 numbers
#endif

    quint16 crc16Modbus = 0xFFFF; // pay attention to initialization

    for (int index = 0; index < src.length(); ++index)
    {
        crc16Modbus = updateCRC16(crc16Modbus, (quint8)src[index]);

#ifdef QT_DEBUG
        qDebug() << QString("Command Byte %1 = %2 (%3)\n").
                    arg(index).
                    arg(QString::number((quint8)src.at(index), 16)).
                    arg(QString::number(src.at(index), 10));
#endif
    }

    long dec1 = crc16Modbus & 0xFF;
    QString hex1 = QString::number(dec1, 16).toUpper();

#ifdef QT_DEBUG
    qDebug() << QString("CRC 1 = %1 (%3)").arg(hex1).arg(dec1);
#endif
    result = QByteArray::fromHex(hex1.toLatin1());

    long dec2 = (crc16Modbus >> 8) & 0xFF;
    QString hex2 = QString::number(dec2, 16).toUpper();

#ifdef QT_DEBUG
    qDebug() << QString("CRC 2 = %1 (%3)").arg(hex2).arg(dec2);
#endif
    result += QByteArray::fromHex(hex2.toLatin1());
    reverse(result.begin(), result.end());
}
    t2=GetTickCount() - t1;

    czas=t2;
}

quint16 CRC16Modbus::updateCRC16(quint16 crc, const quint8 c)
{

    quint16 short_c = 0x00FF & c;
    quint16 tmp = crc ^ short_c;

    crc = ( crc >> 8 ) ^ crcTable[tmp & 0xFF];

    return crc;
}

QByteArray CRC16Modbus::CRC16Data() const
{
    return result;
}

void CRC16Modbus::setCRC16(const QByteArray src)
{
    if (!src.isNull()) {
        calculateCRC16(src);
    }
}

