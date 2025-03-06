#include "ioviewcontroller.h"
#include "ioview.h"
#include "iomodel.h"
#include "serialservice.h"

#include <QCheckBox>
#include <QPushButton>
#include <QSlider>
#include <QDial>
#include <QDebug>

IOViewController::IOViewController(IOView* view,
                                   IOModel* model,
                                   SerialService* serialService,
                                   QObject* parent)
    : QObject(parent),
    m_view(view),
    m_model(model),
    m_serialService(serialService)
{
    setupBindings();
}

void IOViewController::setupBindings()
{
    for (int i = 0; i < m_view->switches.size(); i++) {
        QCheckBox* chk = m_view->switches[i];

        connect(chk, &QCheckBox::stateChanged, this, [this, i](int state){
            setSwitch(i, state);
        });
    }

    for (int i = 0; i < m_view->buttons.size(); i++) {
        QPushButton* btn = m_view->buttons[i];
        connect(btn, &QPushButton::clicked, this, [this, i](bool /*checked*/){
            toggleButton(i);
        });
    }

    connect(m_view->slider0, &QSlider::valueChanged, this, [this](int value){
        setScale0(value);
    });

    connect(m_view->slider1, &QSlider::valueChanged, this, [this](int value){
        setScale1(value);
    });

    connect(m_view, &IOView::dial0Changed, this, &IOViewController::setScale0);

    connect(m_view, &IOView::buttonKeyChanged, this, &IOViewController::setButtonKey);
}

void IOViewController::setSwitch(int index, int state)
{
    bool on = (state == 2); // Qt::Checked == 2
    m_model->setSwitch(index, on);
    sendSwitches();
}

void IOViewController::toggleButton(int index)
{
    bool current = m_model->button(index);
    m_model->setButton(index, !current);
    sendButtons();
}

void IOViewController::setScale0(int value)
{
    m_model->setScale0(value);
    sendScale0();
}

void IOViewController::setScale1(int value)
{
    m_model->setScale1(value);
    sendScale1();
}

void IOViewController::setButtonKey(int index, bool state)
{
    m_model->setButton(index, state);
    sendButtons();
}

void IOViewController::sendSwitches()
{
    QString hexVal = m_model->getSwitchesAsHex();
    QString message = QString("d01") + hexVal;
    qDebug() << "Sending switches:" << message;
    if (m_serialService) {
        m_serialService->write(message);
    }
}

void IOViewController::sendButtons()
{
    QString hexVal = m_model->getButtonsAsHex();
    QString message = QString("d02") + hexVal;
    qDebug() << "Sending buttons:" << message;
    if (m_serialService) {
        m_serialService->write(message);
    }
}

void IOViewController::sendScale0()
{
    QString hexVal = m_model->getScale0AsHex();
    QString message = QString("d0a") + hexVal;
    qDebug() << "Sending scale0:" << message;
    if (m_serialService) {
        m_serialService->write(message);
    }
}

void IOViewController::sendScale1()
{
    QString hexVal = m_model->getScale1AsHex();
    QString message = QString("d0b") + hexVal;
    qDebug() << "Sending scale1:" << message;
    if (m_serialService) {
        m_serialService->write(message);
    }
}

void IOViewController::handleIncomingData(const QString &hexData)
{
    m_model->setLedsFromHex(hexData);
}
