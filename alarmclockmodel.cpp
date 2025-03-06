#include "alarmclockmodel.h"
#include <QDebug>

AlarmclockModel::AlarmclockModel()
    : m_hoursTens("0"),
    m_hoursOnes("0"),
    m_minutesTens("0"),
    m_minutesOnes("0"),
    m_alarmActive(false),
    m_beepActive(false),
    m_colonOn(false)
{
    m_segMap.insert("3f", "0");
    m_segMap.insert("06", "1");
    m_segMap.insert("5b", "2");
    m_segMap.insert("4f", "3");
    m_segMap.insert("66", "4");
    m_segMap.insert("6d", "5");
    m_segMap.insert("7d", "6");
    m_segMap.insert("07", "7");
    m_segMap.insert("7f", "8");
    m_segMap.insert("6f", "9");
}

void AlarmclockModel::setHexString(const QString &hexData)
{
    if (hexData.size() < 8) {
        clearProperties();
        return;
    }

    bool ok = false;
    int b3 = hexData.mid(0, 2).toInt(&ok, 16);
    if (!ok) { clearProperties(); return; }
    int b2 = hexData.mid(2, 2).toInt(&ok, 16);
    if (!ok) { clearProperties(); return; }
    int b1 = hexData.mid(4, 2).toInt(&ok, 16);
    if (!ok) { clearProperties(); return; }
    int b0 = hexData.mid(6, 2).toInt(&ok, 16);
    if (!ok) { clearProperties(); return; }

    m_hoursTens   = decodeDigit(b3);
    m_hoursOnes   = decodeDigit(b2);
    m_minutesTens = decodeDigit(b1);
    m_minutesOnes = decodeDigit(b0);

    m_alarmActive = (b2 & 0x80) != 0;
    m_beepActive  = (b0 & 0x80) != 0;
    m_colonOn     = (b1 & 0x80) != 0;
}

void AlarmclockModel::clearProperties()
{
    m_hoursTens = " ";
    m_hoursOnes = " ";
    m_minutesTens = " ";
    m_minutesOnes = " ";
    m_alarmActive = false;
    m_beepActive  = false;
    m_colonOn     = false;
}

QString AlarmclockModel::decodeDigit(int b)
{
    int value = (b & 0x7F);
    QString hexStr = QString("%1").arg(value, 2, 16, QLatin1Char('0'));
    hexStr = hexStr.toLower();
    if (m_segMap.contains(hexStr)) {
        return m_segMap.value(hexStr);
    } else {
        return "?";
    }
}
