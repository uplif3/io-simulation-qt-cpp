#include "ledwidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPaintEvent>

LEDWidget::LEDWidget(int radius, QWidget* parent) : QWidget(parent),
    m_isOn(false),
    m_radius(radius)
{
    setFixedSize(m_radius * 2, m_radius * 2);
}

void LEDWidget::setOn(bool state)
{
    if (m_isOn == state)
        return;

    m_isOn = state;
    update();
}

bool LEDWidget::isOn() const
{
    return m_isOn;
}

void LEDWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.eraseRect(rect());

    QPen pen(Qt::black, 1);
    painter.setPen(pen);

    QColor fillColor = m_isOn ? QColor("green") : QColor("darkgreen");
    painter.setBrush(QBrush(fillColor));

    painter.drawEllipse(0, 0, width(), height());

    if (m_isOn) {
        QColor glowColor(50, 255, 50, 128); // Halbtransparent
        painter.setBrush(QBrush(glowColor));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(m_radius * 0.2, m_radius * 0.2, m_radius * 1.6, m_radius * 1.6);
    }
}
