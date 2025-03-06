#ifndef SEESAWMODEL_H
#define SEESAWMODEL_H

#include <QString>

class SeesawModel
{
public:
    SeesawModel();

    double reference() const;
    double ball() const;
    double angle() const;
    bool   boing() const;

    void updateFromPacket(const QString &packet);

private:
    int parseSignedHex(const QString &hexStr);

private:
    double m_reference;
    double m_ball;
    double m_angle;
    bool   m_boing;
};

#endif // SEESAWMODEL_H
