#ifndef SEGMENTCOLON_H
#define SEGMENTCOLON_H

#include <QWidget>


class SegmentColon : public QWidget
{
    Q_OBJECT
public:
    explicit SegmentColon(QWidget* parent = nullptr);

    void setIsOn(bool on);
    bool isOn() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool m_isOn;
};

#endif // SEGMENTCOLON_H
