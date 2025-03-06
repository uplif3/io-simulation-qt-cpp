#ifndef ALARMCLOCKVIEW_H
#define ALARMCLOCKVIEW_H

#include <QWidget>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;


class SegmentDigit;
class SegmentColon;


class AlarmclockView : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmclockView(QWidget* parent = nullptr);

    SegmentDigit* hoursTens;
    SegmentDigit* hoursOnes;
    SegmentColon* colon;
    SegmentDigit* minutesTens;
    SegmentDigit* minutesOnes;

    QLabel* alarmLabel;
    QLabel* beepLabel;

private:
    void setupUi();
};

#endif // ALARMCLOCKVIEW_H
