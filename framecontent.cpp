#include "framecontent.h"

FrameContent::FrameContent(QWidget *parent) : QFrame(parent)
{
    QFile file(":/css/contentframe.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }

}

