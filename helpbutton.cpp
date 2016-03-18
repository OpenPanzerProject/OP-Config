#include "helpbutton.h"

Assistant *HelpButton::assistant;

HelpButton::HelpButton(QWidget *parent) : QPushButton(parent)
{
    QFile file(":/css/helpbutton.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void HelpButton::PassAssistant(Assistant *assRef)
{
    assistant = assRef;
}

void HelpButton::openHelp(const QString &file)
{
    assistant->showDocumentation(file);
}
