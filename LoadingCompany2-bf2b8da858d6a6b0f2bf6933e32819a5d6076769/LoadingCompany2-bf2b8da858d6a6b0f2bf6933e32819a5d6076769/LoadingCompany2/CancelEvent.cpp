#include "CancelEvent.h"
#include "Event.h"
#include"CompanyClass.h"
/*CancelEvent::CancelEvent()
{
}*/

CancelEvent::CancelEvent(int EventTimeHours, int EventTimeDays, int CargoID)
{
	Hours = EventTimeHours;
	Days = EventTimeDays;
	SelectedId = CargoID;
}

void CancelEvent::Execute(CompanyClass*Event_Executed) 
{

	Event_Executed->RemoveCargo(SelectedId);
}

CancelEvent::~CancelEvent()
{

}
