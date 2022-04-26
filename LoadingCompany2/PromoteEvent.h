#pragma once
#include "Event.h"
class PromoteEvent :public Event
{
    int CargoExtraCost;

public:
    PromoteEvent();
    PromoteEvent(int EventTimeHours = 1, int EventTimeDays = 1, int CargoID = 0, int CargoExtraMoney = 0);
    void Execute(); //calls setter of type of cargo c
    //void IsLetter(char ch);
    void SetExtraMoney(int extra);
    ~PromoteEvent();
};

