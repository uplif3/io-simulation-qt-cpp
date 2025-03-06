#include "seesawgraphcanvas.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPaintEvent>
#include <cmath>          // Für isnan() (C++17: std::isnan()), etc.
#include <limits>         // Für std::numeric_limits<double>::quiet_NaN()

SeesawGraphCanvas::SeesawGraphCanvas(int width, int height, QWidget* parent)
    : QWidget(parent),
    m_graphWidth(width),
    m_graphHeight(height),
    m_referenceData(GRAPH_MAX_POINTS, std::numeric_limits<double>::quiet_NaN()),
    m_ballData(GRAPH_MAX_POINTS, std::numeric_limits<double>::quiet_NaN()),
    m_angleData(GRAPH_MAX_POINTS, std::numeric_limits<double>::quiet_NaN()),
    m_currentIndex(0),
    m_count(0)
{
    setFixedSize(m_graphWidth, m_graphHeight);
}

void SeesawGraphCanvas::updateGraphData(double reference, double ball, double angle)
{
    double refScaled   = (reference / 0.6) * (m_graphHeight / 2.0);
    double ballScaled  = (ball      / 0.6) * (m_graphHeight / 2.0);
    double angleScaled = (angle     / 15.0) * (m_graphHeight / 2.0);

    m_referenceData[m_currentIndex] = refScaled;
    m_ballData[m_currentIndex]      = ballScaled;
    m_angleData[m_currentIndex]     = angleScaled;

    m_currentIndex++;
    if (m_currentIndex >= GRAPH_MAX_POINTS) {
        m_currentIndex = 0;
    }

    if (m_count < GRAPH_MAX_POINTS) {
        m_count++;
    }

    update();
}

void SeesawGraphCanvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    double baseX = 10.0;
    double baseY = 10.0;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(baseX, baseY, m_graphWidth, m_graphHeight);

    QPen gridPen(QColor(0x40, 0x40, 0x40), 1);
    painter.setPen(gridPen);

    for (int x = 0; x <= m_graphWidth; x += 50) {
        painter.drawLine(baseX + x, baseY, baseX + x, baseY + m_graphHeight);
    }

    for (int y = 0; y <= m_graphHeight; y += 30) {
        painter.drawLine(baseX, baseY + y, baseX + m_graphWidth, baseY + y);
    }

    QColor refColor(0xFC, 0xF8, 0x00);
    QColor ballColor(0xF0, 0xF0, 0xF0);
    QColor angleColor(0x00, 0x4D, 0xE6);

    double xStep;
    if (GRAPH_MAX_POINTS > 1) {
        xStep = static_cast<double>(m_graphWidth) / (GRAPH_MAX_POINTS - 1);
    } else {
        xStep = static_cast<double>(m_graphWidth);
    }

    drawRingCurve(painter, m_referenceData, refColor,   xStep, baseX, baseY);
    drawRingCurve(painter, m_ballData,      ballColor,  xStep, baseX, baseY);
    drawRingCurve(painter, m_angleData,     angleColor, xStep, baseX, baseY);

    painter.setPen(QPen(QColor("orange"), 1));
    double cursorX = baseX + m_currentIndex * xStep;
    painter.drawLine(cursorX, baseY, cursorX, baseY + m_graphHeight);

    painter.end();
}

void SeesawGraphCanvas::drawRingCurve(QPainter& painter,
                                      const std::vector<double>& dataList,
                                      const QColor& color,
                                      double xStep,
                                      double baseX,
                                      double baseY)
{
    QPen pen(color, 2);
    painter.setPen(pen);

    int lastIndex = m_count - 1;
    for (int i = 0; i < lastIndex; ++i) {
        int i2 = i + 1;
        if (i2 == m_currentIndex) {
            continue;
        }

        double y1 = dataList[i];
        double y2 = dataList[i2];

        if (std::isnan(y1) || std::isnan(y2)) {
            continue;
        }

        double x1 = baseX + i  * xStep;
        double x2 = baseX + i2 * xStep;
        double midY = baseY + m_graphHeight / 2.0;

        painter.drawLine(x1, midY - y1, x2, midY - y2);
    }
}
