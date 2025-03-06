#ifndef ALARMCLOCKMODEL_H
#define ALARMCLOCKMODEL_H

#include <QString>
#include <QHash>

class AlarmclockModel
{
public:
    AlarmclockModel();

    void setHexString(const QString &hexData);
    void clearProperties();

    QString hoursTens() const      { return m_hoursTens; }
    QString hoursOnes() const      { return m_hoursOnes; }
    QString minutesTens() const    { return m_minutesTens; }
    QString minutesOnes() const    { return m_minutesOnes; }

    bool alarmActive() const       { return m_alarmActive; }
    bool beepActive() const        { return m_beepActive; }
    bool colonOn() const           { return m_colonOn; }

private:
    QString decodeDigit(int b);

private:
    QString m_hoursTens;
    QString m_hoursOnes;
    QString m_minutesTens;
    QString m_minutesOnes;

    bool m_alarmActive;
    bool m_beepActive;
    bool m_colonOn;

    QHash<QString, QString> m_segMap;
};

#endif // ALARMCLOCKMODEL_H
