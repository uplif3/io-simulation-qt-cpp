#ifndef SEESAWVIEW_H
#define SEESAWVIEW_H

#include <QWidget>

class SeesawCanvas;
class SeesawGraphCanvas;

class SeesawView : public QWidget
{
    Q_OBJECT
public:
    explicit SeesawView(QWidget* parent = nullptr);

    SeesawCanvas* seesawCanvas;
    SeesawGraphCanvas* graphCanvas;

private:
    void setupUi();
};

#endif // SEESAWVIEW_H
