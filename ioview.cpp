#include "ioview.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QSlider>
#include <QDial>
#include <QLabel>

#include "ledwidget.h"


IOView::IOView(QWidget* parent)
    : QWidget(parent),
    slider0(nullptr),
    slider1(nullptr),
    dial0(nullptr),
    valueLabel0(nullptr),
    valueLabel1(nullptr),
    valueLabelDial0(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
    setupUi();
}

void IOView::setupUi()
{
    QGridLayout* grid = new QGridLayout(this);
    grid->setHorizontalSpacing(5);
    grid->setVerticalSpacing(5);
    this->setLayout(grid);

    QLabel* label_leds = new QLabel("LEDs:", this);
    grid->addWidget(label_leds, 0, 0);

    QWidget* ledContainer = new QWidget(this);
    QHBoxLayout* ledLayout = new QHBoxLayout(ledContainer);
    ledLayout->setSpacing(5);
    ledContainer->setLayout(ledLayout);
    grid->addWidget(ledContainer, 0, 1);

    for (int i = 0; i < 8; i++) {
        LEDWidget* led = new LEDWidget(10, ledContainer);
        leds.insert(0, led);
        ledLayout->addWidget(led);

        QLabel* lbl = new QLabel(QString("LED %1").arg(7 - i), ledContainer);
        ledLayout->addWidget(lbl);
    }

    QLabel* label_switches = new QLabel("Switches:", this);
    grid->addWidget(label_switches, 1, 0);

    QWidget* switchContainer = new QWidget(this);
    QHBoxLayout* switchLayout = new QHBoxLayout(switchContainer);
    switchLayout->setSpacing(5);

    for (int i = 0; i < 8; i++) {
        QCheckBox* chk = new QCheckBox(QString("SW %1").arg(7 - i), switchContainer);
        switches.insert(0, chk);
        switchLayout->addWidget(chk);
    }
    switchContainer->setLayout(switchLayout);
    grid->addWidget(switchContainer, 1, 1);

    QLabel* label_buttons = new QLabel("Buttons:", this);
    grid->addWidget(label_buttons, 2, 0);

    QWidget* buttonContainer = new QWidget(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setSpacing(5);

    for (int i = 0; i < 4; i++) {
        QPushButton* btn = new QPushButton(QString("BTN %1").arg(3 - i), buttonContainer);
        buttons.insert(0, btn);
        buttonLayout->addWidget(btn);
    }
    buttonContainer->setLayout(buttonLayout);
    grid->addWidget(buttonContainer, 2, 1);

    QLabel* label_scale0 = new QLabel("Scale0:", this);
    grid->addWidget(label_scale0, 3, 0);

    slider0 = new QSlider(Qt::Horizontal, this);
    slider0->setMinimum(0);
    slider0->setMaximum(1023);
    slider0->setTickInterval(256);
    slider0->setTickPosition(QSlider::TicksBelow);
    grid->addWidget(slider0, 3, 1);

    valueLabel0 = new QLabel("0", this);
    grid->addWidget(valueLabel0, 3, 2);

    connect(slider0, &QSlider::valueChanged, this, [this](int value){
        valueLabel0->setText(QString::number(value));
    });

    QLabel* label_scale1 = new QLabel("Scale1:", this);
    grid->addWidget(label_scale1, 4, 0);

    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setMinimum(0);
    slider1->setMaximum(1023);
    slider1->setTickInterval(256);
    slider1->setTickPosition(QSlider::TicksBelow);
    grid->addWidget(slider1, 4, 1);

    valueLabel1 = new QLabel("0", this);
    grid->addWidget(valueLabel1, 4, 2);

    connect(slider1, &QSlider::valueChanged, this, [this](int value){
        valueLabel1->setText(QString::number(value));
    });

    QLabel* label_dial0 = new QLabel("Dial Scale0:", this);
    grid->addWidget(label_dial0, 5, 0);

    dial0 = new QDial(this);
    dial0->setMinimum(0);
    dial0->setMaximum(1023);
    dial0->setNotchesVisible(true);
    grid->addWidget(dial0, 5, 1);

    valueLabelDial0 = new QLabel("0", this);
    grid->addWidget(valueLabelDial0, 5, 2);

    connect(dial0, &QDial::valueChanged, this, &IOView::onDial0ValueChanged);
}

void IOView::onDial0ValueChanged(int value)
{
    valueLabelDial0->setText(QString::number(value));

    emit dial0Changed(value);
}


void IOView::bindModel(QObject* modelObj)
{
    connect(modelObj, SIGNAL(ledChanged(int,bool)),
            this, SLOT(updateLED(int,bool)));
}

void IOView::updateLED(int index, bool state)
{
    if (index >= 0 && index < leds.size()) {
        leds[index]->setOn(state);
    }
}
