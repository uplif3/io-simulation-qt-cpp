#include "iomodel.h"
#include <QDebug>

IOModel::IOModel(QObject* parent)
    : QObject(parent),
    m_leds(NUM_LEDS, false),
    m_switches(NUM_SWITCHES, false),
    m_buttons(NUM_BUTTONS, false),
    m_scale0(0),
    m_scale1(0)
{
}

void IOModel::setLedsFromHex(const QString &hexVal)
{
    qDebug() << "Change LEDS!!!!";
    bool ok = false;
    int val = hexVal.toInt(&ok, 16);
    if (!ok) {
        qDebug() << "Invalid LED hex value:" << hexVal;
        return;
    }

    for (int i = 0; i < NUM_LEDS; i++) {
        bool newState = ((val >> i) & 1) == 1;
        if (m_leds[i] != newState) {
            m_leds[i] = newState;
            emit ledChanged(i, newState);
        }
    }
    qDebug() << "LEDs:" << QString::number(val, 2).rightJustified(8, '0');
}

void IOModel::setSwitchesFromHex(const QString &hexVal)
{
    bool ok = false;
    int val = hexVal.toInt(&ok, 16);
    if (!ok) {
        qDebug() << "Invalid Switches hex value:" << hexVal;
        return;
    }

    for (int i = 0; i < NUM_SWITCHES; i++) {
        m_switches[i] = ((val >> i) & 1) == 1;
    }
}

void IOModel::setButtonsFromHex(const QString &hexVal)
{
    bool ok = false;
    int val = hexVal.toInt(&ok, 16);
    if (!ok) {
        qDebug() << "Invalid Buttons hex value:" << hexVal;
        return;
    }

    for (int i = 0; i < NUM_BUTTONS; i++) {
        m_buttons[i] = ((val >> i) & 1) == 1;
    }
}

QString IOModel::getButtonsAsHex() const
{
    int val = 0;
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (m_buttons[i]) {
            val |= (1 << i);
        }
    }
    QString res = QString("%1").arg(val, 2, 16, QLatin1Char('0'));
    qDebug() << "Buttons:" << res;
    return res;
}

QString IOModel::getSwitchesAsHex() const
{
    int val = 0;
    for (int i = 0; i < NUM_SWITCHES; i++) {
        if (m_switches[i]) {
            val |= (1 << i);
        }
    }
    return QString("%1").arg(val, 2, 16, QLatin1Char('0'));
}

QString IOModel::getScale0AsHex() const
{
    QString res = QString("%1").arg(m_scale0, 4, 16, QLatin1Char('0'));
    qDebug() << "Scale0:" << res;
    return res;
}

QString IOModel::getScale1AsHex() const
{
    return QString("%1").arg(m_scale1, 4, 16, QLatin1Char('0'));
}
