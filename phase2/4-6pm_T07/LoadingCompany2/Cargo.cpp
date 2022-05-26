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
	CargoDeliveryTimeHours = 0;
	CargoDeliveryTimeDays = 0;
	WaitTimeHour=0;
	WaitTimeDay=0;
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

void Cargo::setCargoDeliveryTime(int TruckMoveTimeHour, int TruckMoveTimeDay, int Truckspeed)
{
	int movingtimehours = DeliveringDistance / Truckspeed;
	int movingtimedays = 1;
	while (movingtimehours > 23)
	{
		movingtimehours = movingtimehours - 23;
		movingtimedays++;
	}
	CargoDeliveryTimeHours = TruckMoveTimeHour + movingtimehours + LoadTime;
	CargoDeliveryTimeDays = movingtimedays + TruckMoveTimeDay;
	while (CargoDeliveryTimeHours > 23)
	{
		CargoDeliveryTimeHours = CargoDeliveryTimeHours - 23;
		CargoDeliveryTimeDays++;
	}
}

void Cargo::setCargoWaitTime(int movetimeh, int movetimed)
{
	WaitTimeDay = 0;
	WaitTimeHour = (movetimeh+(movetimed*24)) - (PreparationTimeHour+ (PreparationTimeDays*24));
	while (WaitTimeHour > 23)
	{
		WaitTimeHour = WaitTimeHour - 23;
		WaitTimeDay++;
	}
}

void Cargo::setTruckLoadedOn(int tid)
{
	TID = tid;
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

int Cargo::getTruckLoadedOn()
{
	return TID;
}

Cargo Cargo::getCID(int CID)
{
	return *this;
}

Cargo::~Cargo()
{

}

ostream& operator<<(ostream& output, Cargo* c)
{
	output << c->getCargoID();
	return output;
}
