#include "combo_drivetype.h"

DriveTypeComboBox::DriveTypeComboBox(QWidget *parent) :	QComboBox(parent), m_nextDriveTypeCode(-1){}

void DriveTypeComboBox::setCategory(MotorCategory mc)
{
    /* generate the default options with associated values */

    // We'll give the servo option slightly different labels depending on category.
    // They will all accept standard servo signals and be plugged into a servo channel on the board,
    // but for drive motors you would probably be using an RC ESC, for turret elevation it will be a literal servo
    // Of course you can use a literal servo for drive motors and an RC ESC for elevation if you want.
    switch (mc)
    {
        case mcDrive:
            insertItem(count(), "RC Output", SERVO_ESC);
            insertItem(count(), "Built-in Driver", ONBOARD);
            break;

        case mcTurretRotation:
            insertItem(count(), "RC Output", SERVO_ESC);
            insertItem(count(), "Servo - Pan Effect", SERVO_PAN);
            insertItem(count(), "Built-in Driver (Motor A)", ONBOARD);
            break;

        case mcTurretElevation:
            insertItem(count(), "RC Output", SERVO_ESC);
            insertItem(count(), "Servo - Pan Effect", SERVO_PAN);
            insertItem(count(), "Built-in Driver (Motor B)", ONBOARD);
            break;
    }

    insertItem(count(), "OP Scout Serial ESC", OP_SCOUT);
    insertItem(count(), "Sabertooth Serial ESC", SABERTOOTH);
    insertItem(count(), "Pololu Serial ESC", POLOLU);

    // So that it shows up last -
    if (mc == mcTurretRotation || mc == mcTurretElevation)
    {
        insertItem(count(), "Detached", DRIVE_DETACHED);
    }

    // Create our own custom signal
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(emitCurrentDriveTypeChanged()));
}

void DriveTypeComboBox::emitCurrentDriveTypeChanged()
{   // Whenever index changes, we emit the current drive type in both QByteArray and QString format.
    emit currentDriveTypeChanged(this->currentData().toByteArray());
    emit currentDriveTypeChanged(this->currentText());
    emit currentDriveTypeChanged(static_cast<Drive_t>(this->currentData().toUInt()));
}

// We can programmatically set the combo box to a value by passing it directly the enum code
void DriveTypeComboBox::setCurrentDriveType(int driveTypeCode)
{
    this->setCurrentIndex(this->findData(driveTypeCode));
}

// We can programmatically set the combo box to a value by passing it a Drive_t enum member name
void DriveTypeComboBox::setCurrentDriveType(const Drive_t& driveType)
{
    this->setCurrentIndex(this->findData(driveType));

}

// Returns the current index by string name
int DriveTypeComboBox::getCode(QString label)
{
    return this->findText(label);
}

// Returns the current index by enum code
QString DriveTypeComboBox::getLabel(int code)
{
    return this->itemText(this->findData(code));
}

// This returns the current actual Drive_t
Drive_t DriveTypeComboBox::getCurrentDriveType(void)
{
    return Drive_t(this->currentData().toInt());
}

boolean DriveTypeComboBox::isSerial()
{
    switch(this->getCurrentDriveType())
    {
        case POLOLU:
        case SABERTOOTH:
        case OP_SCOUT:
            return true;
            break;

        default:
            return false;
    }
}

boolean DriveTypeComboBox::isOnboard()
{
    if (this->getCurrentDriveType() == ONBOARD) return true;
    else return false;
}

boolean DriveTypeComboBox::isRCOutput()
{
    if (this->getCurrentDriveType() == SERVO_ESC || this->getCurrentDriveType() == SERVO_PAN) return true;
    else return false;
}

boolean DriveTypeComboBox::isESC()
{   // Same as above, but this doesn't include the pan servo option (which in fact shouldn't ever be an ESC)
    if (this->getCurrentDriveType() == SERVO_ESC) return true;
    else return false;
}

/* For user-entered items, we won't need this
void DriveTypeComboBox::insertDriveType(const QString& newlabel)
{
    insertItem(0, newlabel, m_nextDriveTypeCode--);
}
*/
