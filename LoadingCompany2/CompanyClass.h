#pragma once

#include <fstream>
#include <iostream>
//-------------------------//
#include "LinkedQueue.h"
#include "PriQ.h"
#include "CargoLinkedList.h"
//-------------------------//
#include "Truck.h"
#include"Cargo.h"
//-------------------------//
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include"PromoteEvent.h"
#include"UIclass.h"
class Event;
class CompanyClass
{
	int Hour;
	int Day;
	int TotalNumberOfTrucks;
	int SumNormalCargos;
	int SumSpecialCargos;
	int SumVIPCargos;
	int SumCargos;
	int CargoAvgTime;
	int SumAllloadTime;
	double VIPCargoPriority;
	//------------------------event list----------------------------------------------
	LinkedQueue <Event*> Eventlist;
	//------------------------intial Truck lists ==empty truck list-------------------
	//available but empty 
	LinkedQueue<Truck*> NormalTruckQueue;
	LinkedQueue<Truck*> SpecialTruckQueue;
	LinkedQueue <Truck*> VIPTruckQueue;

	//-----------------------------related trucks list---------------------------------
	//not available trucks
	PriQ<Truck*> MovingTrucks;
	LinkedQueue<Truck*> NormalTrucksUnderCheckup; //each truck has its own check up time
	LinkedQueue<Truck*> SpecialTrucksUnderCheckup;
	LinkedQueue<Truck*> VIPTrucksUnderCheckup;

	//available but loading
	LinkedQueue<Truck*> LoadingNormalTrucks;
	LinkedQueue<Truck*> LoadingSpecialTrucks;
	LinkedQueue<Truck*> LoadingVIPTrucks;
	//----------------------------initial cargo list------------------------------------
		//waiting to be loaded 
	CargoLinkedList NormalCargos; // to apply cancellation and promotion on it easier
	LinkedQueue<Cargo*> SpecialCargos;
	PriQ<Cargo*> VIPCargoPriQueue;
	//----------------------------cargo related lists-----------------------------------
			//PriQ<Cargo*> MovingCargos;//priority to the least delivery time
	LinkedQueue <Cargo*> DeliveredCargos;
	//---------------------------for file loading function------------------------------
	int nN, nS, nV;
	int Ns, Ss, Vs;
	int Nc, Sc, Vc;
	int Nj, Sj, Vj;
	char N, S, V;
	int NoOfJourneys, NCheckupTime, VCheckupTime, SCheckupTime;
	int AutoPDays, MaxWaitHours;

	int NoOfEvents;
	int count = 0;
	char EventType;
	char CargoType;
	int EventTimeHours, EventTimeDays;
	int CargoID, CargoDist, CargoLoadTime, CargoCost;
	int CargoExtraMoney;
    UIclass* ui;


public:
	CompanyClass();
	CompanyClass(UIclass* uii);
	void FileLoading();
	void RemoveCargo(int id);
	void PromoteCargo(int id);

	void AddToAppropriateList(Cargo* C);
	void AddTruckToCheckup(Truck* T);
	void MoveTruckFromEmptyToLoading(Truck* T);
	void MoveTruckFromLoadingToMoving(Truck* T);
	//-----------------GETTERS----------------------//	
	double getCargoAvgTime();
	int getTotalNumberOfCargos();
	int getTotalNumberOfTrucks();
	int getCurrentTimeHour();
	int getCurrentTimeDay();
	/*LinkedList<Cargo*> getNormalCargos(); // to apply cancellation and promotion on it easier
	LinkedQueue<Cargo*> getSpecialCargos();
	PriQ<Cargo*> getVIPCargos();
	LinkedQueue<Truck*> getLoadingNormalTrucks();
	LinkedQueue<Truck*>getLoadingSpecialTrucks();
	LinkedQueue<Truck*> getLoadingVIPTrucks();
	LinkedQueue<Truck*> getNormalTrucksUnderCheckup(); //each truck has its own check up time
	LinkedQueue<Truck*> getSpecialTrucksUnderCheckup();
	LinkedQueue<Truck*> getVIPTrucksUnderCheckup();
	LinkedQueue<Cargo*> getDeliveredCargos();*/


	void printWNormalCargos();
	void printWspecialCargos();
	void printWvipCargos();

	void printLnormalTrucks();
	void printLspecialTrucks();
	void printLVIPTrucks();

	void printCheckupNormal();
	void printCheckupSpecial();
	void printCheckupVIP();

	void printEmptyNormalTrucks();
	void printEmptySpecialTrucks();
	void printEmptyVIPTrucks();

	//void printE
	void printcheckuptruck();
	void printwaitingcargos();
	void SimulatorFunction();

	~CompanyClass();
};