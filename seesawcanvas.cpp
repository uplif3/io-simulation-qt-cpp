#include "seesawcanvas.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QPolygonF>
#include <QPointF>
#include <QPalette>
#include <cmath>

SeesawCanvas::SeesawCanvas(int width, int height, QWidget* parent)
    : QWidget(parent),
    m_reference(0.0),
    m_ball(0.0),
    m_angle(0.0),
    m_boing(false)
{
    setFixedSize(width, height);
}

void SeesawCanvas::setData(double reference, double ball, double angle, bool boing)
{
    m_reference = reference;
    m_ball      = ball;
    m_angle     = angle;
    m_boing     = boing;
    update();
}

void SeesawCanvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int canvasWidth  = width();
    const int canvasHeight = height();

    QColor bgColor = palette().window().color();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(bgColor));
    painter.drawRect(0, 0, canvasWidth, canvasHeight);

    QColor colorStand(0x60, 0x60, 0x60);   // Grau
    QColor colorRamp(0x00, 0x4D, 0xE6);    // Blau
    QColor colorBall(0xF0, 0xF0, 0xF0);    // Hellgrau
    QColor colorRef(0xFC, 0xF8, 0x00);     // Gelb
    QColor colorBoingOn(0xCC, 0x00, 0x00); // Rot
    QColor colorBoingOff(0x60, 0x60, 0x60);// Grau

    double marginBottom = 10.0;
    double baseX        = canvasWidth / 2.0;
    double baseY        = canvasHeight - marginBottom;

    double seesawWidth  = 420.0;
    double standWidth   = 36.0;
    double standHeight  = 70.0;
    double rBall        = 9.0;
    double markerWidth  = 6.0;
    double markerHeight = 11.0;

    // --- STAND ---
    double sp1x = baseX - standWidth / 2.0;
    double sp1y = baseY;
    double sp2x = baseX;
    double sp2y = baseY - standHeight;
    double sp3x = baseX + standWidth / 2.0;
    double sp3y = baseY;

    QPolygonF standPolygon;
    standPolygon << QPointF(sp1x, sp1y)
                 << QPointF(sp2x, sp2y)
                 << QPointF(sp3x, sp3y);

    painter.setBrush(colorStand);
    painter.drawPolygon(standPolygon);

    // --- REFERENCE-Marker ---
    double markerRawX = (m_reference / 0.6) * ((seesawWidth / 2.0) - 1.5 * rBall);
    double markerRawY = 180.0 - 1.0;

    double m1x = baseX + (markerRawX - markerWidth);
    double m1y = baseY - markerRawY;
    double m2x = baseX + (markerRawX + markerWidth);
    double m2y = baseY - markerRawY;
    double m3x = baseX + markerRawX;
    double m3y = baseY - (markerRawY - markerHeight);

    QPolygonF refPolygon;
    refPolygon << QPointF(m1x, m1y)
               << QPointF(m2x, m2y)
               << QPointF(m3x, m3y);

    painter.setBrush(colorRef);
    painter.drawPolygon(refPolygon);

    // --- WIPPE ---
    double angleRad = m_angle * M_PI / 180.0;
    double seesawHalfW = seesawWidth / 2.0;
    double seesawPivotY = 90.0;
    double yOffset = std::tan(angleRad) * seesawHalfW;
    double yLeft   = seesawPivotY + yOffset;
    double yRight  = seesawPivotY - yOffset;

    double rampP1x = baseX - seesawHalfW;
    double rampP1y = baseY - yLeft;
    double rampP2x = baseX + seesawHalfW;
    double rampP2y = baseY - yRight;

    QPen penRamp(colorRamp, 3.0);
    painter.setPen(penRamp);
    painter.drawLine(rampP1x, rampP1y, rampP2x, rampP2y);

    // --- BALL ---
    double ballX = (m_ball / 0.6) * seesawHalfW;
    double ballY = seesawPivotY - std::tan(angleRad) * ballX + rBall;

    double ballCenterX = baseX + ballX;
    double ballCenterY = baseY - ballY;

    painter.setPen(Qt::NoPen);
    painter.setBrush(colorBall);
    painter.drawEllipse(QPointF(ballCenterX, ballCenterY), rBall, rBall);

    // --- BOING! ---
    QColor boingColor = m_boing ? colorBoingOn : colorBoingOff;
    painter.setPen(boingColor);
    painter.setFont(QFont("Verdana", 14));

    double textX = baseX - seesawWidth / 2.0 - 40.0;
    double textY = baseY - 10.0;

    painter.drawText(QPointF(textX, textY), QString("Boing!"));
}
