#pragma once
#include"Cargo.h"
class CompanyClass;

class Event
{
protected:
	int Hours ;
	int Days ;
	int SelectedId ;
	CompanyClass* EventExecuted;
	//char CargoType;

public:
	Event();

	Event(int EventTimeHours, int EventTimeDays, int sid,CompanyClass*c);

	void SetHours(int h);
	void SetDays(int d);
	void SetID(int id);
	void SetComapnyptr(CompanyClass*c);

	int GetHours() const;
	int GetDays() const;
	int GetSelectedId() const;

	//ComapnyClass*GetCompanyptr() const;

	virtual void Execute() = 0;


	~Event();
	//int GetID(Cargo c);
	//char GetCargoType(Cargo c);
	//int GetEventTime(int& EventTimeDays); // type of hour:min to be changed
	  /*void IsLetter( char ch, Cargo c);*/
};

