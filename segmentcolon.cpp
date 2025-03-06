#include "segmentcolon.h"
#include <QPainter>
#include <QColor>
#include <QPaintEvent>

SegmentColon::SegmentColon(QWidget* parent)
    : QWidget(parent),
    m_isOn(false)
{
    setFixedSize(10, 100);
}

void SegmentColon::setIsOn(bool on)
{
    if (m_isOn == on)
        return;

    m_isOn = on;
    update();
}

bool SegmentColon::isOn() const
{
    return m_isOn;
}

void SegmentColon::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor color = m_isOn ? QColor("red") : QColor("dimgray");

    painter.setBrush(color);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(1, 16, 8, 8);
    painter.drawEllipse(1, 60, 8, 8);
}
