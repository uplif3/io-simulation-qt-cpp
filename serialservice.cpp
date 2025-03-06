#include "serialservice.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

SerialService::SerialService(QObject *parent)
    : QObject(parent),
    m_serialPort(nullptr),
    m_isConnected(false)
{
}

SerialService::~SerialService()
{
    disconnectPort();
}

QStringList SerialService::listComPorts() const
{
    QStringList result;
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        result << info.portName();
    }
    return result;
}

bool SerialService::connectPort(const QString &portName, int baudRate)
{
    disconnectPort();

    m_serialPort = new QSerialPort(this);
    m_serialPort->setPortName(portName);
    m_serialPort->setBaudRate(baudRate);

    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "SerialService: Konnte Port" << portName
                 << "nicht öffnen! Error:"
                 << m_serialPort->errorString();
        delete m_serialPort;
        m_serialPort = nullptr;
        m_isConnected = false;
        return false;
    }

    m_isConnected = true;
    qDebug() << "SerialService: Port" << portName
             << "mit Baud" << baudRate << "geöffnet.";

    connect(m_serialPort, &QSerialPort::readyRead,
            this, &SerialService::onReadyRead);

    emit connected();
    return true;
}

void SerialService::disconnectPort()
{
    if (m_serialPort) {
        if (m_serialPort->isOpen()) {
            m_serialPort->close();
            qDebug() << "SerialService: Port geschlossen.";
        }
        m_serialPort->deleteLater();
        m_serialPort = nullptr;
    }

    bool wasConnected = m_isConnected;
    m_isConnected = false;

    if (wasConnected) {
        emit disconnected();
    }
}

void SerialService::write(const QString &message)
{
    if (m_serialPort && m_serialPort->isOpen()) {
        QByteArray data = message.toUtf8() + "\n";
        qint64 written = m_serialPort->write(data);
        if (written == -1) {
            qDebug() << "SerialService: Fehler beim Senden:"
                     << m_serialPort->errorString();
        }
    } else {
        qDebug() << "SerialService: Port nicht offen, kann nicht senden!";
    }
}

bool SerialService::isOpen() const
{
    return (m_serialPort && m_serialPort->isOpen());
}


void SerialService::onReadyRead()
{
    if (!m_serialPort) return;

    m_readBuffer.append(m_serialPort->readAll());

    int index = 0;
    while ((index = m_readBuffer.indexOf('\n')) >= 0) {
        QByteArray line = m_readBuffer.left(index);
        m_readBuffer.remove(0, index + 1);

        QString lineStr = QString::fromUtf8(line).trimmed();
        if (!lineStr.isEmpty()) {
            emit dataReceived(lineStr);
        }
    }
}
