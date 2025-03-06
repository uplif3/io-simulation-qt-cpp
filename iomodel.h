#ifndef IOMODEL_H
#define IOMODEL_H

#include <QObject>
#include <QVector>

class IOModel : public QObject
{
    Q_OBJECT

public:
    static const int NUM_LEDS     = 8;
    static const int NUM_SWITCHES = 8;
    static const int NUM_BUTTONS  = 4;

    explicit IOModel(QObject* parent = nullptr);


    void setLedsFromHex(const QString &hexVal);

    void setSwitchesFromHex(const QString &hexVal);
    void setButtonsFromHex(const QString &hexVal);

    QString getButtonsAsHex() const;
    QString getSwitchesAsHex() const;
    QString getScale0AsHex() const;
    QString getScale1AsHex() const;


    bool led(int i) const        { return m_leds[i]; }
    bool sw(int i) const         { return m_switches[i]; }
    bool button(int i) const     { return m_buttons[i]; }

    void setLed(int i, bool on)  { m_leds[i] = on; }
    void setSwitch(int i, bool on) { m_switches[i] = on; }
    void setButton(int i, bool on) { m_buttons[i] = on; }

    int scale0() const           { return m_scale0; }
    int scale1() const           { return m_scale1; }

    void setScale0(int value)    { m_scale0 = value; }
    void setScale1(int value)    { m_scale1 = value; }

signals:
    void ledChanged(int index, bool state);

private:
    QVector<bool> m_leds;
    QVector<bool> m_switches;
    QVector<bool> m_buttons;

    int m_scale0;
    int m_scale1;
};

#endif // IOMODEL_H
