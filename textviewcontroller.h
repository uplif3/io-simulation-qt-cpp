#ifndef TEXTVIEWCONTROLLER_H
#define TEXTVIEWCONTROLLER_H

#include <QObject>
#include <QString>

class TextView;


class TextViewController : public QObject
{
    Q_OBJECT
public:
    explicit TextViewController(TextView* view, QObject* parent = nullptr);

    void handleIncomingData(const QString &data);

private slots:
    void clearLog();
    void toggleSync();

private:
    void connectSignals();

    TextView* m_view;
    bool m_autoScroll;
};

#endif // TEXTVIEWCONTROLLER_H
