#ifndef SEESAWCANVAS_H
#define SEESAWCANVAS_H

#include <QWidget>

class SeesawCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit SeesawCanvas(int width = 600, int height = 300, QWidget* parent = nullptr);

    void setData(double reference, double ball, double angle, bool boing);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    double m_reference;
    double m_ball;
    double m_angle;
    bool   m_boing;
};

#endif // SEESAWCANVAS_H
