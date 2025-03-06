#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QString>
#include <QKeyEvent>

class SerialService;
class MainView;

class IOModel;
class IOView;
class IOViewController;

class AlarmclockModel;
class AlarmclockView;
class AlarmclockViewController;

class SeesawModel;
class SeesawView;
class SeesawController;

class TextView;
class TextViewController;


class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);
    ~MainController();

    void showMainWindow();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    bool handleGlobalKeyPress(QKeyEvent* keyEvent);
    bool handleGlobalKeyRelease(QKeyEvent* keyEvent);

private slots:
    void onConnect();
    void onDisconnect();
    void onDataReceived(const QString &data);

private:
    SerialService* m_serialService;

    MainView* m_mainView;

    IOModel* m_ioModel;
    IOView* m_ioView;
    IOViewController* m_ioController;

    AlarmclockModel* m_alarmclockModel;
    AlarmclockView* m_alarmclockView;
    AlarmclockViewController* m_alarmclockController;

    SeesawModel* m_seesawModel;
    SeesawView* m_seesawView;
    SeesawController* m_seesawController;

    TextView*         m_logView;
    TextViewController* m_logController;

    TextView*         m_debugView;
    TextViewController* m_debugController;
};

#endif // MAINCONTROLLER_H
