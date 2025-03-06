#ifndef ALARMCLOCKVIEWCONTROLLER_H
#define ALARMCLOCKVIEWCONTROLLER_H

#include <QObject>
#include <QString>

class AlarmclockView;
class AlarmclockModel;

class AlarmclockViewController : public QObject
{
    Q_OBJECT
public:
    explicit AlarmclockViewController(AlarmclockView* view,
                                      AlarmclockModel* model,
                                      QObject* parent = nullptr);

    void setHexString(const QString &hexStr);
    void handleIncomingData(const QString &data);

private:
    void updateView();

private:
    AlarmclockView*  m_view;
    AlarmclockModel* m_model;
};

#endif // ALARMCLOCKVIEWCONTROLLER_H
