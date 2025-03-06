#include "seesawview.h"
#include <QVBoxLayout>

#include "seesawcanvas.h"
#include "seesawgraphcanvas.h"

SeesawView::SeesawView(QWidget* parent)
    : QWidget(parent),
    seesawCanvas(nullptr),
    graphCanvas(nullptr)
{
    setupUi();
}

void SeesawView::setupUi()
{
    seesawCanvas = new SeesawCanvas(600, 300, this);
    graphCanvas  = new SeesawGraphCanvas(600, 150, this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(10);
    layout->addWidget(seesawCanvas);
    layout->addWidget(graphCanvas);

    setLayout(layout);
}
