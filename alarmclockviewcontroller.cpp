#include "alarmclockviewcontroller.h"
#include "alarmclockview.h"
#include "alarmclockmodel.h"
#include "segmentcolon.h"
#include "segmentdigit.h"
#include "QLabel"


AlarmclockViewController::AlarmclockViewController(AlarmclockView* view,
                                                   AlarmclockModel* model,
                                                   QObject* parent)
    : QObject(parent),
    m_view(view),
    m_model(model)
{
    updateView();
}

void AlarmclockViewController::setHexString(const QString &hexStr)
{
    m_model->setHexString(hexStr);
    updateView();
}

void AlarmclockViewController::handleIncomingData(const QString &data)
{
    setHexString(data);
}

void AlarmclockViewController::updateView()
{

    m_view->hoursTens->setDigit(m_model->hoursTens());
    m_view->hoursOnes->setDigit(m_model->hoursOnes());
    m_view->minutesTens->setDigit(m_model->minutesTens());
    m_view->minutesOnes->setDigit(m_model->minutesOnes());

    m_view->colon->setIsOn(m_model->colonOn());

    m_view->alarmLabel->setVisible(m_model->alarmActive());
    m_view->beepLabel->setVisible(m_model->beepActive());
}
