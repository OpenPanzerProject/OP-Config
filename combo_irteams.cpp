#include "combo_irteams.h"

IRTeamsComboBox::IRTeamsComboBox(QWidget *parent) : QComboBox(parent) {}

void IRTeamsComboBox::SetupNone()
{
    this->clear();
    this->insertItem(0, "No Team", IR_TEAM_NONE);
}

void IRTeamsComboBox::SetupFOVTeams()
{
    // We skip value 1, instead we set Team 1 to 0 (IR_TEAM_NONE) and then
    // go directly to Team 2.
    this->clear();
    this->insertItem(0, "Team 1 (free for all)", IR_TEAM_NONE);
    this->insertItem(count(), "Team 2", IR_TEAM_FOV_2);
    this->insertItem(count(), "Team 3", IR_TEAM_FOV_3);
    this->insertItem(count(), "Team 4", IR_TEAM_FOV_4);
}

