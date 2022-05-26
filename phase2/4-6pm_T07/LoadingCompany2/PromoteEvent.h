#pragma once
#include<iostream>
#include"Event.h"
using namespace std;
class PromoteEvent :public Event
{
private:
	int CargoExtraCost;
public:
	PromoteEvent();
	PromoteEvent(int EventTimeHours = 1, int EventTimeDays = 1, int CargoID = 0, int CargoExtraMoney = 0);

	void Execute(CompanyClass*Event_Executed); //calls setter of type of cargo c->beforee
	void SetExtraMoney(int extra);
	int GetExtraMoney() const;

	~PromoteEvent();
};

