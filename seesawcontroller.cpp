#include "seesawcontroller.h"
#include "seesawmodel.h"
#include "seesawview.h"
#include "seesawcanvas.h"
#include "seesawgraphcanvas.h"

SeesawController::SeesawController(SeesawModel* model,
                                   SeesawView* view,
                                   QObject* parent)
    : QObject(parent),
    m_model(model),
    m_view(view)
{
    updateView();
}

void SeesawController::handleIncomingData(const QString &data)
{
    m_model->updateFromPacket(data);
    updateView();
}

void SeesawController::updateView()
{
    m_view->seesawCanvas->setData(
        m_model->reference(),
        m_model->ball(),
        m_model->angle(),
        m_model->boing()
        );
    m_view->graphCanvas->updateGraphData(
        m_model->reference(),
        m_model->ball(),
        m_model->angle()
        );
}
