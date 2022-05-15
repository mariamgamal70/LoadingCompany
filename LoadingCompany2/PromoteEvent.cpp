#include "PromoteEvent.h"
#include"Event.h"
#include "CompanyClass.h"
PromoteEvent::PromoteEvent()
{
	Hours = 1;
	Days = 1;
	SelectedId = 0;
	EventExecuted = nullptr;
	CargoExtraCost = 0;
}

PromoteEvent::~PromoteEvent()
{
}

PromoteEvent::PromoteEvent(int EventTimeHours, int EventTimeDays, int CargoID, int CargoExtraMoney)
{
	Hours = EventTimeHours;
	Days = EventTimeDays;
	SelectedId = CargoID;
	CargoExtraCost = CargoExtraMoney;
}

void PromoteEvent::Execute(CompanyClass*Event_Executed)
{
	Event_Executed->PromoteCargo(SelectedId);
}

void PromoteEvent::SetExtraMoney(int extra)
{
	CargoExtraCost = extra;
}


int PromoteEvent::GetExtraMoney() const
{
	return CargoExtraCost;
}
