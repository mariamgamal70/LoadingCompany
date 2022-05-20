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
	int SumNormalCargos,SumSpecialCargos,SumVIPCargos;
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
	LinkedQueue<Truck*> NormalTrucksUnderCheckup; //each truck has its own check up time
	LinkedQueue<Truck*> SpecialTrucksUnderCheckup;
	LinkedQueue<Truck*> VIPTrucksUnderCheckup;

	//available but loading (to set calculations in it)
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
	//LinkedQueue <Cargo*> NormalDeliveredCargos;
	//LinkedQueue <Cargo*> SpecialDeliveredCargos;
	//LinkedQueue <Cargo*> VIPDeliveredCargos;
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
	int count;
	char EventType;
	char CargoType;
	int EventTimeHours, EventTimeDays;
	int CargoID, CargoDist, CargoLoadTime, CargoCost;
	int CargoExtraMoney;
	UIclass* ui;
	int noOfPromotedCargos,noOfAutoPCargos;
	int SumTruckActiveTimeH,SumTruckActiveTimeD;
	int SumWaitTimeH, SumWaitTimeD;
	int SumUtilization;
	int sumspecialloadtime;
	int sumnormalloadtime;
	int sumviploadtime;

public:
	CompanyClass();
	CompanyClass(UIclass* uii);
	void FileLoading();
	void RemoveCargo(int id);
	void PromoteCargo(int id);
	//void AutoPromote(int id);  Class responsibility?
	//double setpriorityequation(int pH, int pD, int DD, int CC);

	void AddToNormalCargos(Cargo* C);
	void AddToSpecialCargos(Cargo* C);
	void AddToVIPCargos(Cargo* C, double priority);
	void AddToAppropriateList(Cargo* C);
	void AddTruckToCheckup(Truck* T);
	void AssignCargoToTruck(); // uncomment stuff if MoveTruckFromEmptyToLoading is finished
	void AddToDeliveredCargos();
	void LoadingToMovingTrucks();
	void MoveTruckFromEmptyToLoading(Truck* T);
	void MoveTruckFromLoadingToMoving(Truck* T);
	void MoveTruckFromCheckupToAvailable(Truck* T);
	//-----------------GETTERS----------------------//	
	
	//double getCargoAvgTime();
	int getTotalNumberOfCargos();			//called at the end of simulation 
	int getTotalNumberOfTrucks();			//called at the end of simulation 
	int getCurrentTimeHour();
	int getCurrentTimeDay();
	int getNumberOfNormalTrucks();			//called at the end of simulation 
	int getNumberOfspecialTrucks();			//called at the end of simulation 
	int getNumberOfVipTrucks();				//called at the end of simulation 

	//----------------PRINTS------------------------//
	void printWNormalCargos();
	void printWspecialCargos();
	void printWvipCargos();

	/*void printLnormalTrucks();
	void printLspecialTrucks();
	void printLVIPTrucks();*/

	void printCheckupNormal();
	void printCheckupSpecial();
	void printCheckupVIP();

	void printEmptyNormalTrucks();
	void printEmptySpecialTrucks();
	void printEmptyVIPTrucks();

	/*void printNormalDeliveredCargos();
	void printSpecialDeliveredCargos();
	void printVIPDeliveredCargos();*/
	//void printDeliveredCargos();

	//void printE
	void printcheckuptruck();
	void printwaitingcargos();
	void SimulatorFunction();
	void printloadingtrucks();
	void printmovingcargos();
	void printavailtrucks();
	void printdeliveredcargo();
	//-------------------OUTPUT FILE CALCULATIONS----------------//
	void calcCargoAvgWaitTime(int& h, int& d);	//called at the end of simulation 
	int calcAutoPromotedCargos();				//called at the end of simulation 
	double calcAvgActiveTime();					//called at the end of simulation 
	double calcAvgUtilization();				//called at the end of simulation 

	~CompanyClass();
};