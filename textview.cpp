#include "textview.h"

#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>

TextView::TextView(QWidget *parent)
    : QWidget(parent),
    btnSync(nullptr),
    btnClear(nullptr),
    logTextArea(nullptr),
    m_autoScroll(true)
{
    setupUi();
}

void TextView::setupUi()
{
    logTextArea = new QTextEdit(this);
    logTextArea->setReadOnly(true);
    logTextArea->setLineWrapMode(QTextEdit::WidgetWidth);

    btnSync = new QPushButton("Unsync", this);
    btnClear = new QPushButton("Clear", this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(logTextArea);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->setAlignment(Qt::AlignLeft);
    buttonLayout->addWidget(btnSync);
    buttonLayout->addWidget(btnClear);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void TextView::scrollToBottom()
{
    QScrollBar* scrollbar = logTextArea->verticalScrollBar();
    if (scrollbar) {
        scrollbar->setValue(scrollbar->maximum());
    }
}

void TextView::appendLog(const QString &text)
{
    logTextArea->append(text);
    if (m_autoScroll) {
        scrollToBottom();
    }
}

bool TextView::autoScroll() const
{
    return m_autoScroll;
}

void TextView::setAutoScroll(bool value)
{
    m_autoScroll = value;
}
