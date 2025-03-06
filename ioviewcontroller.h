#ifndef IOVIEWCONTROLLER_H
#define IOVIEWCONTROLLER_H

#include <QObject>
#include <QString>

class IOView;
class IOModel;
class SerialService;


class IOViewController : public QObject
{
    Q_OBJECT
public:
    explicit IOViewController(IOView* view,
                              IOModel* model,
                              SerialService* serialService = nullptr,
                              QObject* parent = nullptr);


    void handleIncomingData(const QString &hexData);
    void setButtonKey(int index, bool state);

    void sendSwitches();
    void sendButtons();
    void sendScale0();
    void sendScale1();

private slots:
    void setupBindings();

    void setSwitch(int index, int state);
    void toggleButton(int index);
    void setScale0(int value);
    void setScale1(int value);

private:
    IOView*       m_view;
    IOModel*      m_model;
    SerialService* m_serialService;

};

#endif // IOVIEWCONTROLLER_H
