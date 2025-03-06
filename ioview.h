#ifndef IOVIEW_H
#define IOVIEW_H

#include <QWidget>
#include <QVector>

class QCheckBox;
class QPushButton;
class QSlider;
class QDial;
class QLabel;
class LEDWidget;


class IOView : public QWidget
{
    Q_OBJECT

public:
    explicit IOView(QWidget* parent = nullptr);

    QVector<QCheckBox*> switches;
    QVector<QPushButton*> buttons;
    QVector<LEDWidget*> leds;

    QSlider* slider0;
    QSlider* slider1;
    QDial*   dial0;

signals:
    void buttonKeyChanged(int index, bool state);
    void dial0Changed(int value);

public slots:
    void bindModel(QObject* modelObj);
    void updateLED(int index, bool state);

private slots:
    void onDial0ValueChanged(int value);

private:
    void setupUi();

    QLabel* valueLabel0;
    QLabel* valueLabel1;
    QLabel* valueLabelDial0;
};

#endif // IOVIEW_H
