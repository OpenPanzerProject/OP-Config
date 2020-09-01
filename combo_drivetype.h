#ifndef COMBO_DRIVETYPE_H
#define COMBO_DRIVETYPE_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

enum MotorCategory
{   mcDrive,
    mcTurretRotation,
    mcTurretElevation
};

class DriveTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit DriveTypeComboBox(QWidget *parent = 0);
    void setCategory(MotorCategory mc);
//    QStringList driveTypeList() const;
//    int currentDriveType() const;

    // These return the enum code or label
    int getCode(QString label);
    QString getLabel(int code);
    Drive_t getCurrentDriveType(void);
    boolean isSerial();                     // Does the currently-selected drive type require serial communication
    boolean isOnboard();                    // Is the currently-selected drive type the on-board motors?
    boolean isOnboard_CD();                 // Onboard drivers C & D, only for select hardware
    boolean isRCOutput();                   // Is the currently-selected drive type an RC output (SERVO_ESC or SERVO_PAN)?
    boolean isESC();                        // Is the currently-selected drive type an ESC (SERVO_ESC)?

signals:
    void currentDriveTypeChanged(QString);      // Custom signal to tell us the new Drive type in String format
    void currentDriveTypeChanged(QByteArray);   // Custom signal to tell us the new Drive type, converting the enum to a ByteArray (used to save into data array)
    void currentDriveTypeChanged(Drive_t);      // here we pass back an actual drive type

public slots:
    //void insertDriveType(const QString& newlabel);    // For user-entered fields, we won't need this
    void setCurrentDriveType(const Drive_t& driveType);
    void setCurrentDriveType(int driveTypeCode);

private slots:
    void emitCurrentDriveTypeChanged();                 // We will connect this slot to the built-in index changed, and emit our custom signals

private:


protected:
    int m_nextDriveTypeCode;
};

#endif // DRIVETYPECOMBOBOX_H
