#pragma once
#include "PreparationEvent.h"
#include "Event.h"
#include "CompanyClass.h"
#include "Cargo.h"
#include <iostream>
using namespace std;
PreparationEvent::PreparationEvent()
{
	Hours = 1;
	Days = 1;
	SelectedId = 0;
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
	EventExecuted = new CompanyClass;
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

void PreparationEvent::Execute(CompanyClass*Event_Executed)
{
	char Type = GetCargoType();
	int PrepD = GetDays();
	int PrepH = GetHours();
	int id = GetSelectedId();
	int dist = GetDeliveryDistance();
	int LoadT = GetLoadTime();
	int cost = GetCargoCost();
	CargoReady=new Cargo(Type, PrepD,PrepH, id, dist, LoadT, cost);
	Event_Executed->AddToAppropriateList(CargoReady);
}

PreparationEvent::~PreparationEvent()
{
}
