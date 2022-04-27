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
void Cargo::setTruckLoadedOn(Truck* T)
{
	TruckLoadedOn =T ;
}

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

void Cargo::getCargoDeliveryTime(int& hours, int& days)
{
	int movetimeh, movetimed;
	TruckLoadedOn->getTruckMoveTime(movetimeh, movetimed);
	CargoDeliveryTimeHours = movetimeh + DeliveringDistance / TruckLoadedOn->getTruckSpeed() + PreparationTimeHour; //--------------------->NEEDS MOVE TIME AND TRUCKSPEED
	while (CargoDeliveryTimeHours > 24)
	{
		CargoDeliveryTimeHours = CargoDeliveryTimeHours - 24;
		CargoDeliveryTimeDays = PreparationTimeHour + 1;
	}
	hours = CargoDeliveryTimeHours;
	days = CargoDeliveryTimeDays+ movetimed;
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
	output << c->getCargoID()<<","<<" ";
	return output;
}
