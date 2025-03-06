#ifndef SEESAWGRAPHCANVAS_H
#define SEESAWGRAPHCANVAS_H

#include <QWidget>
#include <vector>

class SeesawGraphCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit SeesawGraphCanvas(int width = 600, int height = 150, QWidget* parent = nullptr);

    void updateGraphData(double reference, double ball, double angle);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawRingCurve(QPainter& painter,
                       const std::vector<double>& dataList,
                       const QColor& color,
                       double xStep,
                       double baseX,
                       double baseY);

private:
    int m_graphWidth;
    int m_graphHeight;

    static const int GRAPH_MAX_POINTS = 200;

    std::vector<double> m_referenceData;
    std::vector<double> m_ballData;
    std::vector<double> m_angleData;

    int m_currentIndex;
    int m_count;
};

#endif // SEESAWGRAPHCANVAS_H
