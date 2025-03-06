#ifndef SEGMENTDIGIT_H
#define SEGMENTDIGIT_H

#include <QWidget>
#include <QString>

class SegmentDigit : public QWidget
{
    Q_OBJECT
public:
    explicit SegmentDigit(QWidget* parent = nullptr);

    void setDigit(const QString &digit);
    QString digit() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_digit;
};

#endif // SEGMENTDIGIT_H
