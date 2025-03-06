#ifndef SEESAWCONTROLLER_H
#define SEESAWCONTROLLER_H

#include <QObject>
#include <QString>

class SeesawModel;
class SeesawView;


class SeesawController : public QObject
{
    Q_OBJECT
public:
    explicit SeesawController(SeesawModel* model,
                              SeesawView* view,
                              QObject* parent = nullptr);

    void handleIncomingData(const QString &data);

private:
    void updateView();

private:
    SeesawModel* m_model;
    SeesawView*  m_view;
};

#endif // SEESAWCONTROLLER_H
