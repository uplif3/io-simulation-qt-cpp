#include "alarmclockview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QPalette>

#include "segmentdigit.h"
#include "segmentcolon.h"

AlarmclockView::AlarmclockView(QWidget* parent)
    : QWidget(parent),
    hoursTens(nullptr),
    hoursOnes(nullptr),
    colon(nullptr),
    minutesTens(nullptr),
    minutesOnes(nullptr),
    alarmLabel(nullptr),
    beepLabel(nullptr)
{
    setupUi();
}

void AlarmclockView::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(10);

    QLabel* title = new QLabel("Alarm Clock", this);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(title);

    QHBoxLayout* hboxDigits = new QHBoxLayout();
    hboxDigits->setAlignment(Qt::AlignCenter);
    hboxDigits->setSpacing(10);

    hoursTens = new SegmentDigit(this);
    hoursOnes = new SegmentDigit(this);
    colon     = new SegmentColon(this);
    minutesTens = new SegmentDigit(this);
    minutesOnes = new SegmentDigit(this);

    hboxDigits->addWidget(hoursTens);
    hboxDigits->addWidget(hoursOnes);
    hboxDigits->addWidget(colon);
    hboxDigits->addWidget(minutesTens);
    hboxDigits->addWidget(minutesOnes);

    mainLayout->addLayout(hboxDigits);

    QHBoxLayout* hboxStatus = new QHBoxLayout();
    hboxStatus->setAlignment(Qt::AlignCenter);
    hboxStatus->setSpacing(20);

    alarmLabel = new QLabel("ALARM", this);
    alarmLabel->setStyleSheet("color: red; font-weight: bold;");
    beepLabel = new QLabel("BEEP", this);
    beepLabel->setStyleSheet("color: orange; font-weight: bold;");

    hboxStatus->addWidget(alarmLabel);
    hboxStatus->addWidget(beepLabel);

    mainLayout->addLayout(hboxStatus);

    setLayout(mainLayout);
}
