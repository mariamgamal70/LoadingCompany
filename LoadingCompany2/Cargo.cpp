#include "Cargo.h"
#include "Truck.h"
#include<iostream>
using namespace std;


Cargo::Cargo()
{
	setCargoType('N');
	setCargoLoadTime(0);
	setCargoDeliveringCost(0);
	setDeliveringDistance(0);
	setPreparationTimeDay(1);
	setPreparationTimeHour(1);
	SetCargoID(0);
	CargoDeliveryTimeHours = 1;
	CargoDeliveryTimeDays = 1;
	WaitTimeHour=1;
	WaitTimeDay=1;
}

Cargo::Cargo(char type, int pd, int ph, int id, int dist, int LT, int cost)
{
	setCargoType(type);
	setPreparationTimeDay(pd);
	setPreparationTimeHour(ph);
	SetCargoID(id);
	setDeliveringDistance(dist);
	setCargoLoadTime(LT);
	setCargoDeliveringCost(cost);
}
void Cargo::setCargoLoadTime(int time)
{
	LoadTime = time;
}

void Cargo::setPreparationTimeDay(int NoOfDays)
{
	PreparationTimeDays = NoOfDays;
}

void Cargo::setPreparationTimeHour(int hour)
{
	PreparationTimeHour = hour;
}

void Cargo::setCargoDeliveringCost(int cost)
{
	CargoDeliveringCost = cost;
}

void Cargo::setDeliveringDistance(int distance)
{
	DeliveringDistance = distance;
}

void Cargo::setCargoType(char type)
{
	CargoType = type;
}

void Cargo::SetCargoID(int id)
{
	CargoID = id;
}
/*void Cargo::setTruckLoadedOn(Truck* T)
{
	TruckLoadedOn =T ;
}*/

char Cargo::getPreparationTimeDay() const
{
	return PreparationTimeDays;
}

int Cargo::getPreparationTimeHour() const
{
	return PreparationTimeHour;
}

int Cargo::getCargoDeliveringCost() const
{
	return CargoDeliveringCost;
}

int Cargo::getDeliveringDistance() const
{
	return DeliveringDistance;
}

char Cargo::getCargoType() const
{
	return CargoType;
}

int Cargo::getLoadTime() const
{
	return LoadTime;
}

int Cargo::getCargoID() const
{
	return CargoID;
}

/*void Cargo::setCargoDeliveryTime(int& hours, int& days)//----------------->OPTION1
{
	int movetimeh, movetimed;
	TruckLoadedOn->getTruckMoveTime(movetimeh, movetimed);
	CargoDeliveryTimeHours = movetimeh + DeliveringDistance / TruckLoadedOn->getTruckSpeed() + PreparationTimeHour; //--->NEEDS MOVE TIME AND TRUCKSPEED , replace preparationtimehour with loadtime
	while (CargoDeliveryTimeHours > 23)
	{
		CargoDeliveryTimeHours = CargoDeliveryTimeHours - 23;
		CargoDeliveryTimeDays = PreparationTimeHour + 1;//--> increment cargo delivery time alone without the need of preparationtimeHour
	}
	hours = CargoDeliveryTimeHours;
	days = CargoDeliveryTimeDays+ movetimed;
}*/

void Cargo::setCargoDeliveryTime(int TruckMoveTimeHour,int TruckMoveTimeDay,int Truckspeed)//-------------->OPTION2
{
	int movetimeh, movetimed;
	CargoDeliveryTimeHours = TruckMoveTimeHour + DeliveringDistance / Truckspeed + LoadTime;
	while (CargoDeliveryTimeHours > 23)
	{
		CargoDeliveryTimeHours = CargoDeliveryTimeHours - 23;
		CargoDeliveryTimeDays ++;
	}
	CargoDeliveryTimeDays = CargoDeliveryTimeDays + TruckMoveTimeDay;
}

void Cargo::setCargoWaitTime(int movetimeh, int movetimed)
{
	WaitTimeHour = (movetimeh+(movetimed*24)) - (PreparationTimeHour+ (PreparationTimeDays*24));
	while (WaitTimeHour > 23)
	{
		WaitTimeHour = WaitTimeHour - 23;
		WaitTimeDay++;
	}
}

void Cargo::getCargoDeliveryTime(int& CDTh, int& CDTd)
{
	CDTh = CargoDeliveryTimeHours;
	CDTd = CargoDeliveryTimeDays;
}

void Cargo::getCargoWaitTime(int& waittimeh, int& waittimed)
{
	waittimeh = WaitTimeHour;
	waittimed = WaitTimeDay;
}

Cargo Cargo::getCID(int CID)
{
	return *this;
}

Cargo::~Cargo()  //any additions?
{

}

ostream& operator<<(ostream& output, Cargo* c)
{
	output << c->getCargoID();
	return output;
}
