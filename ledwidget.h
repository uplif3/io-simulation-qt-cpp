#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

class LEDWidget : public QWidget
{
    Q_OBJECT
public:
    LEDWidget(int radius = 20, QWidget* parent = nullptr);
    void setOn(bool state);
    bool isOn() const;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    bool m_isOn;
    int m_radius;
};

#endif // LEDWIDGET_H
