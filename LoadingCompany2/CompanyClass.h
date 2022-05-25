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
	int sumfinalnorm, sumfinalspec, sumfinalvip;
	int SumCargos;
	//int CargoAvgTime;
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
	LinkedQueue<Truck*> NormalTrucksUnderCheckup;
	LinkedQueue<Truck*> SpecialTrucksUnderCheckup;
	LinkedQueue<Truck*> VIPTrucksUnderCheckup;

	//available but loading (to set calculations in it)
	PriQ<Truck*> LoadingTrucks;
	//----------------------------initial cargo list------------------------------------
	//waiting to be loaded 
	CargoLinkedList NormalCargos; // to apply cancellation and promotion on it easier
	LinkedQueue<Cargo*> SpecialCargos;
	PriQ<Cargo*> VIPCargoPriQueue;
	//----------------------------cargo related lists-----------------------------------
	//PriQ<Cargo*> MovingCargos;//priority to the least delivery time
	LinkedQueue <Cargo*> DeliveredCargos;
	//---------------------------for file loading function------------------------------
	int nN, nS, nV; //number
	int Ns, Ss, Vs; //speed
	int Nc, Sc, Vc; //capacity
	//int Nj, Sj, Vj; 
	char N, S, V;
	int NoOfJourneys, NCheckupTime, VCheckupTime, SCheckupTime;
	int AutoPDays, MaxWaitHours;
	int NoOfEvents;
	int count;
	char EventType;
	char CargoType;
	int EventTimeHours, EventTimeDays;
	int CargoID, CargoDist, CargoLoadTime, CargoCost;
	int CargoExtraMoney;
	UIclass* ui;
	int noOfAutoPCargos;
	int SumTruckActiveTimeH, SumTruckActiveTimeD;
	int SumWaitTimeH, SumWaitTimeD;
	int SumUtilization;
	int sumspecialloadtime;
	int sumnormalloadtime;
	int sumviploadtime;
	int countDelivered;

public:
	CompanyClass();
	CompanyClass(UIclass* uii);
	void FileLoading();
	void OutputFile();
	void RemoveCargo(int id);
	void PromoteCargo(int id);
	void ExecuteEvents();
	bool checkfunction();
	//void AutoPromote(int id);  Class responsibility?
	//double setpriorityequation(int pH, int pD, int DD, int CC);

	void AddToNormalCargos(Cargo* C);
	void AddToSpecialCargos(Cargo* C);
	void AddToVIPCargos(Cargo* C, double priority);
	void AddToAppropriateList(Cargo* C);
	
	void AssignSpecialCargos();
	void AssignNormalCargos();
	void AssignVIPcargos();
	void AssignCargoToTruck();
	//void AddToDeliveredCargos();

	void MoveTruckFromEmptyToLoading(Truck*& T, int TLD, PriQ<Cargo*>loadingcargos);
	void MoveTruckFromLoadingToMoving();
	void MoveTruckFromMovingToCheckup_or_Available(Truck*truck_finishedjourney);
	void MoveTruckFromCheckupToAvailable();
	void MoveCargosFrom_Moving_to_Delivered();
	//-----------------GETTERS----------------------//	

	//double getCargoAvgTime();
	int getTotalNumberOfCargos();			//called at the end of simulation 
	int getTotalNumberOfTrucks();			//called at the end of simulation 
	int getCurrentTimeHour();
	int getCurrentTimeDay();
	int getNumberOfNormalTrucks();			//called at the end of simulation 
	int getNumberOfspecialTrucks();			//called at the end of simulation 
	int getNumberOfVipTrucks();				//called at the end of simulation 
	int getnumfinalnorm();
	int getnumfinalspec();
	int getnumfinalvip();
	int getautopromnum();
	int getNumberOfMovingCargos();
	Cargo* dequeueDeliveredCargo();
	//----------------PRINTS------------------------//
	//void printHeadLine();
	void printWNormalCargos();
	void printWspecialCargos();
	void printWvipCargos();

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
	void printloadingtrucks();
	void printmovingcargos();
	void printavailtrucks();
	void printdeliveredcargo();

	void dequeueLoadingTruck(Truck* deq);
	void dequeueMovingTruck(Truck* deq);
	//-------------------OUTPUT FILE CALCULATIONS----------------//
	void calcCargoAvgWaitTime(int& h, int& d);	//called at the end of simulation 
	int calcAutoPromotedCargos();				//called at the end of simulation 
	double calcAvgActiveTime();					//called at the end of simulation 
	double calcAvgUtilization();				//called at the end of simulation 
	
	~CompanyClass();
};