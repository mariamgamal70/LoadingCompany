#include "Event.h"

Event::Event()
{
	//Hours = 1;
	//Days = 1;
	//SelectedId = 0;
	//EventExecuted = nullptr;
}

Event::Event(int EventTimeHours, int EventTimeDays, int sid,CompanyClass*c)
{
	Hours = EventTimeHours;
	Days = EventTimeDays;
	SelectedId = sid;
	EventExecuted = c;
}

void Event::SetHours(int h)
{
	Hours = h;
}

void Event::SetDays(int d)
{
	Days = d;
}

void Event::SetID(int id)
{
	SelectedId = id;
}

void Event::SetComapnyptr(CompanyClass* c)
{
	EventExecuted = c;
}

int Event::GetHours() const
{
	return Hours;
}

int Event::GetDays() const
{
	return Days;
}
int Event::GetSelectedId() const
{
	return SelectedId;
}

Event::~Event()
{
}