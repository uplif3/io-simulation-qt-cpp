#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QWidget>
#include <QString>

class QTextEdit;
class QPushButton;


class TextView : public QWidget
{
    Q_OBJECT
public:
    explicit TextView(QWidget* parent = nullptr);

    void scrollToBottom();
    void appendLog(const QString &text);

    bool autoScroll() const;
    void setAutoScroll(bool value);

    QPushButton* btnSync;
    QPushButton* btnClear;
    QTextEdit*   logTextArea;

private:
    void setupUi();

    bool m_autoScroll;
};

#endif // TEXTVIEW_H
