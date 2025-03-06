#include "maincontroller.h"
#include "mainview.h"

#include "serialservice.h"
#include "iomodel.h"
#include "ioview.h"
#include "ioviewcontroller.h"
#include "alarmclockmodel.h"
#include "alarmclockview.h"
#include "alarmclockviewcontroller.h"
#include "seesawmodel.h"
#include "seesawview.h"
#include "seesawcontroller.h"
#include "textview.h"
#include "textviewcontroller.h"

#include <QDateTime>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

MainController::MainController(QObject* parent)
    : QObject(parent)
{
    m_serialService = new SerialService();

    m_mainView = new MainView();

    m_ioModel = new IOModel();
    m_ioView  = new IOView();
    m_ioView->bindModel(m_ioModel);
    m_ioController = new IOViewController(m_ioView, m_ioModel, m_serialService);

    m_alarmclockModel = new AlarmclockModel();
    m_alarmclockView  = new AlarmclockView();
    m_alarmclockController = new AlarmclockViewController(m_alarmclockView, m_alarmclockModel);

    m_seesawModel = new SeesawModel();
    m_seesawView  = new SeesawView();
    m_seesawController = new SeesawController(m_seesawModel, m_seesawView);

    m_logView = new TextView();
    m_logController = new TextViewController(m_logView, this);

    m_debugView      = new TextView();
    m_debugController= new TextViewController(m_debugView, this);

    m_mainView->setLeftViews({m_ioView});
    m_mainView->setRightViews({m_logView, m_debugView});

    QStringList ports = m_serialService->listComPorts();
    m_mainView->setPortList(ports);

    connect(m_mainView, &MainView::connectRequested, this, &MainController::onConnect);
    connect(m_mainView, &MainView::disconnectRequested, this, &MainController::onDisconnect);

    connect(m_serialService, &SerialService::connected, [this]{
        m_mainView->showStatus("Verbunden", 3000);
    });
    connect(m_serialService, &SerialService::disconnected, [this]{
        m_mainView->showStatus("Getrennt", 3000);
    });
    connect(m_serialService, &SerialService::dataReceived,
            this, &MainController::onDataReceived);
}

MainController::~MainController()
{
    delete m_seesawController;
    delete m_seesawView;
    delete m_seesawModel;

    delete m_alarmclockController;
    delete m_alarmclockView;
    delete m_alarmclockModel;

    delete m_ioController;
    delete m_ioView;
    delete m_ioModel;

    delete m_mainView;
    delete m_serialService;
}

void MainController::showMainWindow()
{
    m_mainView->resize(800, 600);
    m_mainView->show();
    m_mainView->activateWindow();
    m_mainView->raise();
}

void MainController::onConnect()
{
    QString portName = m_mainView->currentPort();
    if (!portName.isEmpty()) {
        m_serialService->connectPort(portName);
    } else {
        m_mainView->showStatus("Kein Port ausgewählt!", 2000);
    }
}

void MainController::onDisconnect()
{
    m_serialService->disconnectPort();
}

void MainController::onDataReceived(const QString &data)
{

    if (data.startsWith("dL")) {
        m_logController->handleIncomingData(data.mid(2));
    } else if (data.startsWith("dS")) {
        if (data.startsWith("dS0")) {
            m_mainView->setLeftViews({m_ioView});
        } else if (data.startsWith("dS1")) {
            m_mainView->setLeftViews({m_alarmclockView, m_ioView});
        } else if (data.startsWith("dS2")) {
            m_mainView->setLeftViews({m_seesawView, m_ioView});
        }
    }
    else if (data.startsWith("d0")) {
        m_ioController->handleIncomingData(data.mid(2));
    }
    else if (data.startsWith("d1")) {
        m_alarmclockController->handleIncomingData(data.mid(2));
    }
    else if (data.startsWith("d2")) {
        m_seesawController->handleIncomingData(data.mid(2));
    }
    else if (data.startsWith("?")) {
        if (data.startsWith("?T")) {
            QString currentTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
            m_serialService->write(QString("dT") + currentTime);
        }
        else if (data.startsWith("?01")){
            m_ioController->sendSwitches();
        }
        else if (data.startsWith("?02")){
            m_ioController->sendButtons();
        }
        else if (data.startsWith("?0a")){
            m_ioController->sendScale0();
        }
        else if (data.startsWith("?0b")){
            m_ioController->sendScale0();
        }
    } else {
        m_debugController->handleIncomingData(data.mid(2));
    }
}

bool MainController::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        return handleGlobalKeyPress(keyEvent);
    }
    else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        return handleGlobalKeyRelease(keyEvent);
    }
    return false;
}

bool MainController::handleGlobalKeyPress(QKeyEvent* keyEvent)
{
    if (keyEvent->isAutoRepeat()) {
        return false;
    }

    int key = keyEvent->key();
    switch (key) {
    case Qt::Key_1:
        m_ioController->setButtonKey(3, true);
        return true;
    case Qt::Key_2:
        m_ioController->setButtonKey(2, true);
        return true;
    case Qt::Key_3:
        m_ioController->setButtonKey(1, true);
        return true;
    case Qt::Key_4:
        m_ioController->setButtonKey(0, true);
        return true;
    default:
        return false;
    }
}

bool MainController::handleGlobalKeyRelease(QKeyEvent* keyEvent)
{
    if (keyEvent->isAutoRepeat()) {
        return false;
    }

    int key = keyEvent->key();
    switch (key) {
    case Qt::Key_1:
        m_ioController->setButtonKey(3, false);
        return true;
    case Qt::Key_2:
        m_ioController->setButtonKey(2, false);
        return true;
    case Qt::Key_3:
        m_ioController->setButtonKey(1, false);
        return true;
    case Qt::Key_4:
        m_ioController->setButtonKey(0, false);
        return true;
    default:
        return false;
    }
}
