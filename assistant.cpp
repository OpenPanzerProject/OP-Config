/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QByteArray>
#include <QtCore/QDir>
#include <QtCore/QLibraryInfo>
#include <QtCore/QProcess>

#include <QtWidgets/QMessageBox>

#include "assistant.h"

Assistant::Assistant() : proc(0) {}


Assistant::~Assistant()
{
    if (proc && proc->state() == QProcess::Running) {
        proc->terminate();
        proc->waitForFinished(3000);
    }
    delete proc;
}

void Assistant::showDocumentation(const QString &page)
{
    if (!startAssistant())
        return;

    QByteArray ba("SetSource ");
    ba.append("qthelp://openpanzer.desktop.help/docs/");    // From .qhcp file: Namespace then virtual folder
    ba.append(page.toLatin1());
    ba.append(";syncContents;");    // Add a syncContents command
    proc->write(ba + '\n');
}

bool Assistant::startAssistant()
{
    if (!proc)
        proc = new QProcess();

    if (proc->state() != QProcess::Running) {
        // This line came with the sample code. It seems to load Assistant from the Qt install directory.
            //QString app = QLibraryInfo::location(QLibraryInfo::BinariesPath) + QDir::separator();
        // That is fine during testing, but in deployment we should instead create an Assistant folder
        // in our application directory with its own files.
        QString app = "";
        #if !defined(Q_OS_MAC)
            app += QLatin1String("assistant");
        #else
            app += QLatin1String("Assistant.app/Contents/MacOS/Assistant");
        #endif

        // THIS IS WHERE YOU SET THE PATH TO THE QHC.
        // I find that trying to use a relative path from the location of assistant.exe doesn't work, instead I need to specify
        // the full path. I have these files placed in apppath/assistant/help_files/ and I used applicationDirPath() to get
        // the application path since we won't know in advance where the user is going to put it.
        QStringList args;
        args << QLatin1String("-collectionFile")
             << QApplication::applicationDirPath()
              + QLatin1String("/help_files/opconfighelp.qhc")
             << QLatin1String("-enableRemoteControl");
        proc->start(app, args);

        if (!proc->waitForStarted()) {
            QMessageBox::critical(0, QObject::tr("OP Config"),
                QObject::tr("Unable to launch Qt Assistant (%1)").arg(app));
            return false;
        }
        else
        {
            // Process is running, now let's do a few other small things:
            QByteArray ba;
            ba.append("hide bookmarks;");   // Hide the bookmarks, though user can always show it again if they want
            ba.append("hide index;");       // We haven't created an index (not the same as contents). So again, hide.
            ba.append("expandToc -1;");     // Expand the table of contents completely - this is really very helpful (-1 means complete)
            ba.append("syncContents;");     // Even better, we now "click" the sync contents button so the user can see where they are at.
            proc->write(ba);
        }
    }
    return true;
}

