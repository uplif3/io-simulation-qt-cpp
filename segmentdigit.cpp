#include "segmentdigit.h"
#include <QPainter>
#include <QColor>
#include <QPaintEvent>

SegmentDigit::SegmentDigit(QWidget* parent)
    : QWidget(parent),
    m_digit("0")
{
    setFixedSize(60, 100);
}

void SegmentDigit::setDigit(const QString &digit)
{
    if (m_digit == digit)
        return;

    m_digit = digit;
    update();
}

QString SegmentDigit::digit() const
{
    return m_digit;
}

void SegmentDigit::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    bool segAOn = false;
    bool segBOn = false;
    bool segCOn = false;
    bool segDOn = false;
    bool segEOn = false;
    bool segFOn = false;
    bool segGOn = false;

    const QString d = m_digit;
    if      (d == "0") { segAOn=true; segBOn=true; segCOn=true; segDOn=true; segEOn=true; segFOn=true; }
    else if (d == "1") { segBOn=true; segCOn=true; }
    else if (d == "2") { segAOn=true; segBOn=true; segDOn=true; segEOn=true; segGOn=true; }
    else if (d == "3") { segAOn=true; segBOn=true; segCOn=true; segDOn=true; segGOn=true; }
    else if (d == "4") { segBOn=true; segCOn=true; segFOn=true; segGOn=true; }
    else if (d == "5") { segAOn=true; segCOn=true; segDOn=true; segFOn=true; segGOn=true; }
    else if (d == "6") { segAOn=true; segCOn=true; segDOn=true; segEOn=true; segFOn=true; segGOn=true; }
    else if (d == "7") { segAOn=true; segBOn=true; segCOn=true; }
    else if (d == "8") { segAOn=true; segBOn=true; segCOn=true; segDOn=true; segEOn=true; segFOn=true; segGOn=true; }
    else if (d == "9") { segAOn=true; segBOn=true; segCOn=true; segDOn=true; segFOn=true; segGOn=true; }


    QColor colorOn("red");
    QColor colorOff("gray");

    // Segment A = oben
    painter.fillRect(5, 0, 50, 8, segAOn ? colorOn : colorOff);
    // Segment B = oben rechts
    painter.fillRect(55, 8, 8, 40, segBOn ? colorOn : colorOff);
    // Segment C = unten rechts
    painter.fillRect(55, 52, 8, 40, segCOn ? colorOn : colorOff);
    // Segment D = unten
    painter.fillRect(5, 92, 50, 8, segDOn ? colorOn : colorOff);
    // Segment E = unten links
    painter.fillRect(0, 52, 8, 40, segEOn ? colorOn : colorOff);
    // Segment F = oben links
    painter.fillRect(0, 8, 8, 40, segFOn ? colorOn : colorOff);
    // Segment G = Mitte
    painter.fillRect(5, 46, 50, 8, segGOn ? colorOn : colorOff);
}
