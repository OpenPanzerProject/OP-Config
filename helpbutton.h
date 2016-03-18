#ifndef HELPBUTTON_H
#define HELPBUTTON_H

#include <QObject>
#include <QPushButton>
#include <assistant.h>
#include <QFile>

class HelpButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HelpButton(QWidget *parent = 0);
    void PassAssistant(Assistant *assRef);
    void openHelp(const QString &file);

signals:

public slots:

private:
    // QT Assistant
    // ---------------------------------------------------------------------------------------------------->>
    static Assistant *assistant;
};

#endif // HELPBUTTON_H

