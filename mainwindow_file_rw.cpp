#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FILE - READING AND WRITING
//------------------------------------------------------------------------------------------------------------------------>>
// This is just the Device menu action, and we simply get a file path/name from the user, then pass it to the actual reading function
void MainWindow::actionReadSettingsFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Import Settings from OPZ File"), ".", tr("OPZ files (*.opz)"));

    if (filename == "") return;     // Exit if they cancel
    else readSettingsFromFile(filename, false);

}

// This is the actual reading function, it takes a file path/name as argument. We split this into its own thing because
// we might want to call it distinctly from the menu action, for example, if the application is opened with a command line
// argument (such as we have set to do in Windows when a user double-clicks an .opz file).
//
// Although we go through the trouble of including a DTD in our setting file, QXmlStreamReader doesn't seem to do any
// validation against it whatsoever. I guess it has to be hard-coded instead. For now we just give a message about how
// many vars were imported.
void MainWindow::readSettingsFromFile(QString filename, boolean confirm)
{
    if (filename == "") return;

    // QFile wants separators to be "/", not "\", see http://doc.qt.io/qt-5/qfile.html
    //filename.replace(QString("\\"),QString("/"));     // Use replace, or
    filename = QDir::fromNativeSeparators(filename);    // This built-in function does it
    filename.remove("\n");
    filename = filename.trimmed();

    // Had this happening even after using trimmed sometimes when comming from command line, caused infinite headaches debugging...
    if (filename.left(1) == " ")
        filename = filename.right(filename.length()-1);

    filename = filename.trimmed();                      // Once again for damn good measure

    // Use this to test for errors
    // filename.prepend("\"");
    // filename.append("\"");
    // msgBox(filename, vbOkOnly, "Attempt filename:", vbNoIcon);
    // if (file->exists()) msgBox("File exists",vbOkOnly, "Exists", vbNoIcon);

    // Create a QFile with this path
    QFile* file = new QFile(filename);

    // Error if we can't open it for some reason
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        msgBox(tr("Unable to open file: %1<br><br>%2") .arg(filename).arg(file->errorString()), vbOkOnly, "OPZ Settings File", vbCritical);
        SetStatusLabel("Unable to open file!",slBad);
        return;
    }

    MouseWait();

    xmlReader.setDevice(file);  // Give the xmlReader our file

    QXmlStreamAttributes attributes;
    QString opzSettingsVersion;
    QString errMsg = "";
    uint16_t varID;
    QString varVal;
    int varCount = 0;
    int totalPossibleVars = NUM_STORED_VARS; // How many variables is it possible to import (yes, include the 0 var at the beginning)
    double pctImported = 0;

    // Parse XML until we reach end of it
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        // If token is DTD (document type definition), read it to make sure this is the correct file type
        if (token == QXmlStreamReader::DTD)
        {
            //qDebug()<< xmlReader.dtdName();
        }
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement)
        {
            // If the element is named "opzsettings" we can try to extract the version attribute
            if(xmlReader.name() == "opzsettings")
            {
                attributes = xmlReader.attributes();
                if(attributes.hasAttribute("version"))
                {
                    opzSettingsVersion = attributes.value("version").toString();
                    // qDebug() << opzSettingsVersion;
                    if (opzSettingsVersion != "TCB")
                    {
                        //errMsg = "Wrong settings file type detected";
                    }
                    // For now we don't do anything with this, but we could later
                    // if we decide to implement multiple devices
                    continue;
                }
            }

            // If it's named "vars" we'll go to the next.
            if(xmlReader.name() == "vars")
            {
                continue;
            }

            // If it's named "var" (singular), this is the element we want.
            if(xmlReader.name() == "var")
            {
                // Get the attribute for this var (will be ID)
                // You can have more than one attribute but for now ID is it
                attributes = xmlReader.attributes();
                if(attributes.hasAttribute("id"))
                {
                    varID = attributes.value("id").toInt();
                }
                else
                {
                    varID = -1;
                    // We could throw an error, but for now let's just ignore this element
                }
                // Next element
                xmlReader.readNext();

                // Loop through the elements of var until we hit an EndElement named var
                while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "var"))
                {
                    if(xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if(xmlReader.name() == "value")
                        {
                            xmlReader.readNext();
                            // This elements needs to contain Characters so we know it's actually data
                            if(xmlReader.tokenType() == QXmlStreamReader::Characters)
                            {

                                if (VarArray.contains(varID))  // Don't bother saving any values without a defined ID
                                {                              // It wouldn't hurt anything, but will throw off our count
                                    varVal = xmlReader.text().toString();
                                    VarArray.insert(varID, varVal.toUtf8());
                                    varCount += 1;
                                }
                            }
                        }
                        /*
                        if (xmlReader.name() == "some other name")
                        {
                            // For now we only have values in the XML
                        }
                        */
                    }
                    xmlReader.readNext();
                }
            }
        }
    }

    MouseRestore();

    // Error handling.
    if(xmlReader.hasError())
    {
        msgBox(xmlReader.errorString(), vbOkOnly, "OPZ Settings File", vbCritical);
        SetStatusLabel("Error in file!",slBad);
    }
    // Removes any device() or data from the reader
    xmlReader.clear();
    file->close();

    if (varCount == 0)
    {
        errMsg = "No settings were imported. Please try again with a different file.";
        SetStatusLabel("No settings imported",slBad);
    }
    else
    {
        // We've loaded the setting from the file into our VarArray.
        // Now we need to copy the VarArray to named variables,
        // and then copy the named variables to our controls.
        VarArray_to_Variables();
        Variables_to_Controls();
        if (errMsg != "")
        {
            msgBox(errMsg, vbOkOnly, "OPZ Settings File", vbCritical);
            SetStatusLabel("File import failed!",slBad);
        }
        else
        {
            if (varCount < totalPossibleVars)
            {
                pctImported = ((double)varCount/(double)totalPossibleVars)*100.0;
                SetStatusLabel(QString("Partial settings imported (%1%)").arg(QString::number(pctImported,'f',0)),slGood);
                msgBox(tr("Of %1 settings, only %2 were imported. You may wish to save a new settings file.") .arg(totalPossibleVars).arg(varCount), vbOkOnly, "OPZ Settings File", vbInformation);
            }
            else
            {
                SetStatusLabel(QString("All settings imported (100%)"),slGood);
                if (confirm)
                {
                    msgBox(tr("All settings imported from file:<br><br>%1") .arg(filename), vbOkOnly, "OPZ Settings File", vbInformation);
                }
            }
        }

    }
}
void MainWindow::writeSettingsToFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Settings to OPZ File)"), ".", tr("OPZ files (*.opz)"));

    if (filename == "") return; // Exit if they cancel

    QFile* file = new QFile(filename);
    int varCount = 0;
    // We're actually not using this, so comment it out to avoid compiler warnings
//    int totalPossibleVars = NUM_STORED_VARS; // How many variables is it possible to export (yes, include the 0 var at the beginning)
//    double pctExported = 0;

    // Error if we can't open it for some reason
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        msgBox(tr("Unable to open file: %1") .arg(filename), vbOkOnly, "OPZ Settings File", vbCritical);
        SetStatusLabel("Unable to open file!",slBad);
        return;
    }

    MouseWait();

    // Before we can write our settings to a file, we need to make sure VarArray is updated with the current values from the form
    Controls_to_Variables();    // This puts the control values into our named variables
    Variables_to_VarArray();    // This copies our named variables into the VarArray

    QXmlStreamWriter xmlWriter(file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    // Set our custom document type definition
    QString DTD;
    DTD =  "<!DOCTYPE opzsettings [\n";
    DTD += "<!ELEMENT opzsettings (vars)>\n";
    DTD += "<!ELEMENT vars (var+)>\n";      // + meaning var must occur at least once but can also occur many times (it should)
    DTD += "<!ELEMENT var (value)>\n";
    DTD += "<!ELEMENT value (#PCDATA)>\n";
    DTD += "<!ATTLIST opzsettings version CDATA #REQUIRED>\n";
    DTD += "<!ATTLIST var id CDATA #REQUIRED>\n";
    DTD += "]>\n";

    xmlWriter.writeDTD(DTD);

    xmlWriter.writeStartElement("opzsettings"); // These are case-sensitive, so whatever you do here, use the same case in the read
    xmlWriter.writeAttribute("version", "TCB"); // Some day if we have multiple devices we will want to change the version
        xmlWriter.writeStartElement("vars");
        QMapIterator<uint16_t, QByteArray> i(VarArray); // We can iterate through a QMap using this notation
        while (i.hasNext())
        {
            i.next();   // Yes, it will still start on the first item
            xmlWriter.writeStartElement("var");
                xmlWriter.writeAttribute("id", QString::number(i.key()));
                    xmlWriter.writeTextElement("value", i.value());
                        // writeTextElement is a convenience function equal to the following three statements:
                        //xmlWriter.writeStartElement("value");
                        //xmlWriter.writeCharacters(i.value());
                        //xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
            varCount += 1;
        }
        xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file->close();

    //pctExported = ((double)varCount/(double)totalPossibleVars)*100.0;
    SetStatusLabel(QString("File saved"), slNeutral); //.arg(QString::number(pctImported,'f',0)),slGood); -- no need, we will always write 100%

    MouseRestore();
}
