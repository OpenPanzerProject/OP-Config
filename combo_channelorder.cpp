#include "combo_channelorder.h"

ChannelOrderComboBox::ChannelOrderComboBox(QWidget *parent) : QComboBox(parent), _priorChannel()
{
    // If either the text or index has changed, emit our custom signal
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(channelNumberChangedSlot(QString)));
    connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(channelNumberChangedSlot(QString)));
}

void ChannelOrderComboBox::channelNumberChangedSlot(const QString &newChannel)
{
    // Send out a signal with the old value, the new value, and a pointer to this box
    emit channelNumberChanged(_priorChannel, newChannel, this);
    // Overload currentIndexChanged too, and pass a reference to the combo box with it
    //emit currentIndexChanged(this->currentIndex(), this);
    // Now save the new channel as our old channel for next time
    _priorChannel = newChannel;
}


void ChannelOrderComboBox::setup(boolean isAux)
{
    // Aux channels get "N/A" in index 0.
    if (isAux)
    {
        this->insertItem(0, "N/A");
        _isAux = true;
    }
    else
    {
        _isAux = false;
    }

    // Otherwise all channels gets 1-MAX_NUM_CHANNELS in the remaining positions
    for(int i = 1; i <= COUNT_OP_CHANNELS; i++)
    {
        this->insertItem(i, QString::number(i));
    }
}

boolean ChannelOrderComboBox::isAux(void)
{
    return _isAux;
}
