#pragma once
#include "PreparationEvent.h"
#include "Event.h"
#include "CompanyClass.h"
#include "Cargo.h"
PreparationEvent::PreparationEvent()
{
	CargoCost = 0;
	LoadTime = 0;
	DeliveryDistance = 0;
	CargoType = 'N';
}
PreparationEvent::PreparationEvent(char CargoT, int EventTimeHours, int EventTimeDays, int CargoID, int CargoDist, int LoadTimeHours, int Cost)
{
	SetCost(Cost);
	SetLoadtime(LoadTimeHours);
	SetDeliveryDist(CargoDist);
	SetCargotype(CargoT);
	SetHours(EventTimeHours);
	SetDays(EventTimeDays);
	SetID(CargoID);

}


int PreparationEvent::GetCargoCost() const
{
	return CargoCost;
}
int PreparationEvent::GetLoadTime() const
{
	return LoadTime;
}
int PreparationEvent::GetDeliveryDistance() const
{
	return DeliveryDistance;
}
char PreparationEvent::GetCargoType() const
{
	return CargoType;
}

void PreparationEvent::SetCost(int Cost)
{
	CargoCost = Cost;
}

void PreparationEvent::SetLoadtime(int Loadt)
{
	LoadTime = Loadt;
}

void PreparationEvent::SetDeliveryDist(int Distance)
{
	DeliveryDistance = Distance;
}

void PreparationEvent::SetCargotype(char t)
{
	CargoType = t;
}

void PreparationEvent::Execute()
{
	char Type = GetCargoType();
	int PrepD = GetDays();
	int PrepH = GetHours();
	int id = GetSelectedId();
	int dist = GetDeliveryDistance();
	int LoadT = GetLoadTime();
	int cost = GetCargoCost();
	Cargo* CargoReady = new Cargo(Type, PrepD, PrepH, id, dist, LoadT, cost);
	EventExecuted->AddToAppropriateList(CargoReady);

}
PreparationEvent::~PreparationEvent()
{
}








/*void PreparationEvent::SetDIST(Cargo c, int d)
{
	c.setDeliveringDistance(d);
}
void PreparationEvent::SetCost(Cargo c, int co)
{
	c.setCargoDeliveringCost(co);
}
void PreparationEvent::SetLT(Cargo c, int lt)
{
	c.setCargoLoadTime(lt);
}
int PreparationEvent::GetCost(Cargo c )
{
	return(c.getCargoDeliveringCost());
}
int PreparationEvent::GetLT(Cargo c )
{
	return(c.getLoadTime()); //ADD LOAD START AND END TIMES
}

int PreparationEvent::GetDist(Cargo c)
{
	return(c.getDeliveringDistance());
}
*/


/*Cargo Preparation::GetCargo(Cargo c, )
{
	return c;
} */
/* void PreparationEvent::SetCargoOfExecute(Cargo c, char type, int lt, int dc, int dd, int td, int th)
{
	c.setCargoType(type);
	c.setCargoLoadTime(lt);
	c.setCargoDeliveringCost(dc);
	c.setDeliveringDistance(dd);
	c.setPreparationTimeDay(td);
	c.setPreparationTimeHour(th);
}*/

/*void PreparationEvent::Execute(LinkedQueue<Cargo> Lspecial, LinkedQueue<Cargo> Lnormal, LinkedQueue<Cargo> Lvip, char type, int lt, int dc, int dd, int td, int th)
{
	Cargo c;
	c.setCargoType(type);
	c.setCargoLoadTime(lt);
	c.setCargoDeliveringCost(dc);
	c.setDeliveringDistance(dd);
	c.setPreparationTimeDay(td);
	c.setPreparationTimeHour(th);
	if (type == 'N')
	{
		Lnormal.enqueue(c);
	}
	if (type == 'S')
	{
		Lspecial.enqueue(c);
	}
	if (type == 'V')
	{
		Lvip.enqueue(c);
	}


	return c;
}*/