#include "Event.h"
#include "PreparationEvent.h"
#include "PromoteEvent.h"
#include "CancelEvent.h"
#include "CompanyClass.h"

Event::Event()
{
	Hours = 1;
	Days = 1;
	SelectedId = 0;
	EventExecuted = nullptr;
	 
	//?Cargo c;  
}

/*void Event::IsLetter(char ch, Cargo c)
{
	if (ch == 'R')
	{
		//ask for LinkedQueue<Cargo> Lspecial, LinkedQueue<Cargo> Lnormal, LinkedQueue<Cargo> Lvip, char type, int lt, int dc, int dd, int td, int th
		PreparationEvent p;
		p.Execute(c);//put LinkedQueue<Cargo> Lspecial, LinkedQueue<Cargo> Lnormal, LinkedQueue<Cargo> Lvip, char type, int lt, int dc, int dd, int td, int th
	}
	if (ch == 'X')
	{
		CancelEvent ca;
		ca.Execute(c);
	}
	if (ch == 'P')
	{
		PromoteEvent p;
		p.Execute(c);
	}
}
char Event::GetCargoType(Cargo c)
{
	return(c.getCargoType());
}

int Event::GetEventTime(int& EventTimeDays)
{
	return(Hours);
}

 int  Event::GetID(Cargo c)
{
	return(c.getCID());
}

*/
/*Event::Event()
{
	Hours = 1;
	Days = 1;
	SelectedId = 0;
}*/



Event::Event(int EventTimeHours, int EventTimeDays, int sid)
{
	Hours = EventTimeHours;
	Days = EventTimeDays;
	SelectedId = sid;
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
void Execute()
{

}
Event::~Event()
{

}
