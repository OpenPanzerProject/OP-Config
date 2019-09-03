#ifndef RECOILSERVOPRESETCOMBOBOX_H
#define RECOILSERVOPRESETCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class RecoilServoPresetComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit RecoilServoPresetComboBox(QWidget *parent = 0);

    // These return the enum code or label
    int getCode(QString label);
    QString getLabel(int code);
    Smoker_t getCurrentRecoilPreset(void);

signals:
    void currentRecoilPresetChanged(QString);      // Custom signal to tell us the new recoil preset in String format
    void currentRecoilPresetChanged(QByteArray);   // Custom signal to tell us the new recoil preset, converting the enum to a ByteArray (used to save into data array)
    void currentRecoilPresetChanged(RecoilPreset); // Here we pass back an actual recoil preset type

public slots:
    void setCurrentRecoilPreset(const RecoilPreset& rs);
    void setCurrentRecoilPreset(int recoilPresetNum);

private slots:
    void emitRecoilServoPresetChanged();           // We will connect this slot to the built-in index changed, and emit our custom signals

private:



};


#endif // RECOILSERVOPRESETCOMBOBOX_H

