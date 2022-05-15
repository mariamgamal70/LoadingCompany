#pragma once
#include"Cargo.h"
class CompanyClass;

class Event
{
protected:
	int Hours ;
	int Days ;
	int SelectedId ;

public:
	Event();

	Event(int EventTimeHours, int EventTimeDays, int sid);  //removed Companyptr from Event class Data members

	void SetHours(int h);
	void SetDays(int d);
	void SetID(int id);
	//void SetCompanyptr(CompanyClass*c);

	int GetHours() const;
	int GetDays() const;
	int GetSelectedId() const;

	virtual void Execute(CompanyClass*Event_Executed) = 0;

	~Event();
};

