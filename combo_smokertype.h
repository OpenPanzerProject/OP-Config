#ifndef SMOKERTYPECOMBOBOX_H
#define SMOKERTYPECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class SmokerTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SmokerTypeComboBox(QWidget *parent = 0);
    // These return the enum code or label
    int getCode(QString label);
    QString getLabel(int code);
    Smoker_t getCurrentSmokerType(void);


signals:
    void currentSmokerTypeChanged(QString);      // Custom signal to tell us the new Smoker type in String format
    void currentSmokerTypeChanged(QByteArray);   // Custom signal to tell us the new Smoker type, converting the enum to a ByteArray (used to save into data array)
    void currentSmokerTypeChanged(Smoker_t);      // here we pass back an actual smoker type

public slots:
    void setCurrentSmokerType(const Smoker_t& smokerType);
    void setCurrentSmokerType(int smokerTypeCode);

private slots:
    void emitSmokerTypeChanged();        // We will connect this slot to the built-in index changed, and emit our custom signals

private:


};

#endif // SMOKERTYPECOMBOBOX_H


