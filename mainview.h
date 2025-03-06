#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QStringList>
#include "textview.h"
#include "textviewcontroller.h"

class QToolBar;
class QLabel;
class QComboBox;
class QPushButton;
class QStatusBar;

class QWidget;
class QVBoxLayout;
class QGridLayout;
class TextView;


class MainView : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = nullptr);

    void setPortList(const QStringList &ports);
    QString currentPort() const;

    void showStatus(const QString &text, int timeout = 0);

    void setLeftViews(const QList<QWidget*> &views);
    void setRightViews(const QList<QWidget*> &views);

    TextViewController* logController() const { return m_logController; }
    TextViewController* debugController() const { return m_debugController; }

signals:
    void connectRequested();
    void disconnectRequested();

private:
    void initUI();

private:
    QToolBar*    m_toolBar;
    QLabel*      m_portLabel;
    QComboBox*   m_comboPorts;
    QPushButton* m_btnConnect;
    QPushButton* m_btnDisconnect;
    QStatusBar*  m_statusBar;

    QWidget*     m_centralWidget;
    QGridLayout* m_grid;

    QWidget*     m_leftContainer;
    QVBoxLayout* m_leftLayout;

    QWidget*     m_rightContainer;
    QVBoxLayout* m_rightLayout;

    TextView*    m_logView;
    TextView*    m_debugView;
    TextViewController* m_logController;
    TextViewController* m_debugController;
};

#endif // MAINVIEW_H
