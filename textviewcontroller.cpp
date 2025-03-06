#include "textviewcontroller.h"
#include "textview.h"

#include <QPushButton>
#include <QDebug>
#include <QTextEdit>

TextViewController::TextViewController(TextView* view, QObject* parent)
    : QObject(parent),
    m_view(view),
    m_autoScroll(true)
{
    connectSignals();
}

void TextViewController::connectSignals()
{
    connect(m_view->btnClear, &QPushButton::clicked,
            this, &TextViewController::clearLog);

    connect(m_view->btnSync, &QPushButton::clicked,
            this, &TextViewController::toggleSync);
}

void TextViewController::clearLog()
{
    m_view->logTextArea->clear();
}

void TextViewController::toggleSync()
{
    m_autoScroll = !m_autoScroll;
    m_view->setAutoScroll(m_autoScroll);

    if (m_autoScroll) {
        m_view->btnSync->setText("Unsync");
        m_view->scrollToBottom();
    } else {
        m_view->btnSync->setText("Sync");
    }
}

void TextViewController::handleIncomingData(const QString &data)
{
    m_view->appendLog(data);
}
