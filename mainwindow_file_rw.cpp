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
    QString opzSettingsMod = "OLD";         // Old OPZ files won't even have this attribute so we set it to a default value
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
            if (xmlReader.name() == "opzsettings")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == QLatin1String("version"))
                    {
                        opzSettingsVersion = attr.value().toString();
                        //qDebug() << opzSettingsVersion;
                        // For now we don't do anything with this, but we could later
                        // if we decide to implement multiple devices
                    }

                    if (attr.name().toString() == QLatin1String("mod"))
                    {
                        opzSettingsMod = attr.value().toString();
                        //qDebug() << opzSettingsMod;
                        // We use the mod attribute to distinguish the new aux channel nomenclature
                        // for Trigger IDs that went into effect after 0.92.22
                    }
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
        msgBox(errMsg, vbOkOnly, "OPZ Settings File", vbCritical);
        SetStatusLabel("No settings imported",slBad);
        return;
    }
    else if (opzSettingsVersion != "TCB")
    {
        errMsg = "Wrong settings file type detected";
        msgBox(errMsg, vbOkOnly, "OPZ Settings File", vbCritical);
        SetStatusLabel("No settings imported",slBad);
        return;
    }
    else
    {
        // We've loaded the setting from the file into our VarArray.

        if (opzSettingsMod == "OLD")    // "OLD" is the default value, new files should have a mod value of "NewAux"
        {
            // This is an old (0.92.22 and earlier) OPZ setting file. We need to convert the digital aux channel
            // Trigger IDs to the new position nomenclature
            ConvertOldAuxChannels();
        }

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

void MainWindow::ConvertOldAuxChannels()
{
uint16_t triggerID;
uint16_t newTriggerID;
uint8_t channelNumber;
uint8_t triggerAction;
uint8_t numPositions;

// All versions of TCB firmware up to 0.92.22 used a version of Trigger ID construction for digital aux channels incompatible with
// future versions. The earlier construct gave every aux channel 5 possible positions, even if in fact it was only defined by the user
// as having 2 or 3 positions. But internally, behind the scenes, a 3 position switch would have 5 positions of which only positions
// 1, 3 and 5 were ever active. Likewise for a 2 position switch only positions 1 and 5 would activate. This had a single convenience:
// Regardless of the number of used positions, the incoming radio pulse would always be 1500 uS for position 3 for example. However
// the disadvantages to this approach were legion, and finally we have changed to the more logical arrangement whereby a 3 position
// switch has 3 positions of 1, 2, and 3, and an N-position switch has N positions numbered from 1 to N.

// What needs to be correced are old Trigger IDs, an example might be 4035, under the old nomenclature this would indicate a trigger
// when Aux Channel 4, defined as a 3-position switch, was found to be in position 3 (but the Trigger ID labels position 3 as "5").
// This Trigger ID would need to be changed to 4033 instead (3-positions, 3rd position)

    int startVal = FUNCTION_TRIGGERS_START_ID;          // 1411 - defined in op_eeprom_varinfo.h
    for (int i=0; i<(MAX_FUNCTION_TRIGGERS*2); i+=2)    // Increment by 2 because each function trigger has a Trigger ID first and then a Function, we only want Trigger ID here
    {
        triggerID = VarArray.value(startVal + i).toUInt();
        if (triggerID >= trigger_id_multiplier_auxchannel && triggerID < trigger_id_adhoc_start)    // Is this an aux channel trigger
        {
            channelNumber = FT_TableModel->getAuxChannelNumberFromTriggerID(triggerID);
            numPositions = FT_TableModel->getNumPositionsFromTriggerID(triggerID);
            triggerAction = FT_TableModel->getTriggerActionFromTriggerID(triggerID);
            if (triggerAction > 0)  // Meaning, not variable but digital
            {
                // Here we correct the trigger action. There are actually only two cases that need to be changed
                switch (triggerAction)
                {
                    case 3: triggerAction = 2;              break;      // Position 3 of a 3 position switch converts to position 2
                    case 5: triggerAction = numPositions;   break;      // Position 5 (of any position switch) converts to the maximum number of positions
                }
                // Technically position 3 could also have been from a 5-position switch in which case it shouldn't be changed. However
                // we never enabled the 5-position option so we don't have to worry about it.

                // Construct a new, corrected Trigger ID
                newTriggerID = (channelNumber * trigger_id_multiplier_auxchannel);
                newTriggerID += (numPositions * switch_pos_multiplier) + triggerAction;
                // qDebug() << "Channel " << channelNumber << " Trigger ID " << VarArray.value(startVal + i).toUInt() << " (" << newTriggerID << ") Positions: " << numPositions << " Pos: " << triggerAction;

                // Update the VarArray
                VarArray.insert(startVal + i, QByteArray::number(newTriggerID));
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
    DTD += "<!ATTLIST opzsettings mod CDATA #IMPLIED>\n";  // IMPLIED means "optional", opz files from 0.92.22 and prior won't have it
    DTD += "<!ATTLIST var id CDATA #REQUIRED>\n";
    DTD += "]>\n";

    xmlWriter.writeDTD(DTD);

    xmlWriter.writeStartElement("opzsettings"); // These are case-sensitive, so whatever you do here, use the same case in the read
    xmlWriter.writeAttribute("version", "TCB"); // Some day if we have multiple devices we will want to change the version
    xmlWriter.writeAttribute("mod","NewAux");   // This flag indicates the OPZ file is using the new aux channel position nomenclature
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
