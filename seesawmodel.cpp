#include "seesawmodel.h"
#include <QDebug>

SeesawModel::SeesawModel()
    : m_reference(0.0),
    m_ball(0.0),
    m_angle(0.0),
    m_boing(false)
{
}

double SeesawModel::reference() const { return m_reference; }
double SeesawModel::ball() const      { return m_ball; }
double SeesawModel::angle() const     { return m_angle; }
bool   SeesawModel::boing() const     { return m_boing; }

void SeesawModel::updateFromPacket(const QString &packet)
{

    if (packet.size() < 13) {
        qDebug() << "SeesawModel: Packet too short:" << packet;
        return;
    }

    QString refHex   = packet.mid(0, 4);
    QString ballHex  = packet.mid(4, 4);
    QString angleHex = packet.mid(8, 4);
    QChar   boingChar= packet.at(12);

    int rawReference = parseSignedHex(refHex);
    int rawBall      = parseSignedHex(ballHex);
    int rawAngle     = parseSignedHex(angleHex);

    m_reference = rawReference / 50000.0;
    m_ball      = rawBall      / 50000.0;
    m_angle     = rawAngle     / 2000.0;
    m_boing     = (boingChar == QLatin1Char('t'));
}

int SeesawModel::parseSignedHex(const QString &hexStr)
{
    bool ok = false;
    int num = hexStr.toInt(&ok, 16);
    if (!ok) {
        return 0;
    }

    if ((num & 0x8000) != 0) {
        num -= 0x10000;
    }
    return num;
}
