#include "mainview.h"

#include "textview.h"
#include <QToolBar>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QWidget>


MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , m_toolBar(nullptr)
    , m_portLabel(nullptr)
    , m_comboPorts(nullptr)
    , m_btnConnect(nullptr)
    , m_btnDisconnect(nullptr)
    , m_statusBar(nullptr)
    , m_centralWidget(nullptr)
    , m_grid(nullptr)
    , m_leftContainer(nullptr)
    , m_leftLayout(nullptr)
    , m_rightContainer(nullptr)
    , m_rightLayout(nullptr)
    , m_logView(nullptr)
    , m_debugView(nullptr)
{
    setWindowTitle("GUI mit Serial & Log Service");
    initUI();
}

void MainView::initUI()
{
    // Toolbar
    m_toolBar = new QToolBar("Haupt-Toolbar", this);
    addToolBar(m_toolBar);

    m_portLabel = new QLabel("COM-Port: ");
    m_comboPorts = new QComboBox();
    m_btnConnect = new QPushButton("Verbinden");
    m_btnDisconnect = new QPushButton("Trennen");

    m_toolBar->addWidget(m_portLabel);
    m_toolBar->addWidget(m_comboPorts);
    m_toolBar->addWidget(m_btnConnect);
    m_toolBar->addWidget(m_btnDisconnect);

    // Zentral-Widget
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_grid = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_grid);

    // Linker Container (VBox)
    m_leftContainer = new QWidget(m_centralWidget);
    m_leftLayout = new QVBoxLayout(m_leftContainer);
    m_leftLayout->setContentsMargins(0,0,0,0);
    m_leftLayout->setSpacing(5);

    m_grid->addWidget(m_leftContainer, 0, 0, 2, 1);

    // Rechter Container (VBox)
    m_rightContainer = new QWidget(m_centralWidget);
    m_rightLayout = new QVBoxLayout(m_rightContainer);
    m_rightLayout->setContentsMargins(0,0,0,0);
    m_rightLayout->setSpacing(5);


    m_rightContainer->setLayout(m_rightLayout);
    m_grid->addWidget(m_rightContainer, 0, 1, 2, 1);

    m_grid->setRowStretch(0, 1);
    m_grid->setRowStretch(1, 1);
    m_grid->setColumnStretch(0, 1);
    m_grid->setColumnStretch(1, 2);

    // Status Bar
    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    connect(m_btnConnect, &QPushButton::clicked, this, [this]{
        emit connectRequested();
    });
    connect(m_btnDisconnect, &QPushButton::clicked, this, [this]{
        emit disconnectRequested();
    });
}

void MainView::setPortList(const QStringList &ports)
{
    m_comboPorts->clear();
    m_comboPorts->addItems(ports);
}

QString MainView::currentPort() const
{
    return m_comboPorts->currentText();
}

void MainView::showStatus(const QString &text, int timeout)
{
    m_statusBar->showMessage(text, timeout);
}

void MainView::setLeftViews(const QList<QWidget*> &views)
{
    QLayoutItem* child;
    while ((child = m_leftLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->setParent(nullptr);
        }
        delete child;
    }

    for (QWidget* view : views) {
        m_leftLayout->addWidget(view);
        m_leftLayout->setStretchFactor(view, 1);
    }

    m_leftContainer->update();
}

void MainView::setRightViews(const QList<QWidget*> &views)
{
    QLayoutItem* child;
    while ((child = m_rightLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->setParent(nullptr);
        }
        delete child;
    }

    for (QWidget* view : views) {
        m_rightLayout->addWidget(view);
        m_rightLayout->setStretchFactor(view, 1);
    }

    m_rightContainer->update();
}

