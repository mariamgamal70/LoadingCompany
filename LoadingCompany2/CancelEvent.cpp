#include "CancelEvent.h"
#include "Event.h"
#include"CompanyClass.h"
/*CancelEvent::CancelEvent()
{
}
*/


CancelEvent::CancelEvent(int EventTimeHours, int EventTimeDays, int CargoID)
{
	Hours = EventTimeHours;
	Days = EventTimeDays;
	SelectedId = CargoID;
}

void CancelEvent::Execute()
{

	EventExecuted->RemoveCargo(SelectedId);
}



CancelEvent::~CancelEvent()
{

}

/*void CancelEvent::IsLetter(char x) NO NEED
{
}

void CancelEvent::CancelIDNormal(Cargo c)  NO NEED
{
}
*/