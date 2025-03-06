#ifndef SERIALSERVICE_H
#define SERIALSERVICE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>

class QSerialPort;

class SerialService : public QObject
{
    Q_OBJECT
public:
    explicit SerialService(QObject* parent = nullptr);
    ~SerialService();

    QStringList listComPorts() const;

    Q_INVOKABLE bool connectPort(const QString &portName, int baudRate = 9600);

    Q_INVOKABLE void disconnectPort();

    void write(const QString &message);

    bool isOpen() const;

signals:
    void connected();
    void disconnected();

    void dataReceived(const QString &line);

private slots:
    void onReadyRead();

private:
    QSerialPort *m_serialPort;
    bool m_isConnected;

    QByteArray m_readBuffer;
};

#endif // SERIALSERVICE_H
