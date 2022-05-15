#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include <cstdlib>
#include "Cargo.h"
#include"LinkedList.h"
#include"PriQ.h"
#include"LinkedQueue.h"
using std::ifstream;
using namespace std;

//class Cargo;
class Truck
{
private:

	char TruckType;
	int TruckCapacity;
	int TruckMaintenanceTime;
	int TruckSpeed;
	int TruckDeliveryIntervalH;
	int TruckDeliveryIntervalD;
	int TruckNoOfJourneys;
	int TruckID;//truck id
	int DeliveredCargosByTruck;
	PriQ<Cargo*> LoadingCargos; //priority to delivery distance (becomes moving cargos once truck is moving)
	int TruckMoveTimeHour;
	int TruckMoveTimeDay;
	int TruckTotalActiveTimeH;
	int TruckTotalActiveTimeD;//<---- use it in sth
	int TruckUtilization;
	int TimeToComeBackH;
	int TimeToComeBackD;
public:

	Truck();
	Truck(char type, int speed, int capacity, int noOfJourneys, int CheckupTime, int id);
	void setTruckType(char type);
	void setTruckCapacity(int capacity);
	void setTruckMaintenanceTime(int time);
	void setTruckSpeed(int speed);
	/*void setTruckDeliveryInterval(int interval);*/
	void SetNoOfJourneys(int number);
	void SetTruckID(int id);
	void setTruckMoveTime(int h, int d);
	

	char getTruckType()const;
	int getTruckCapacity()const;
	int getTruckMaintenanceTime()const;
	int getTruckSpeed()const;
	int getTruckDeliveryIntervalHours();
	int getTruckDeliveryIntervalDays();
	int getNoOfJourneys()const;
	int getTruckID()const;
	int getNoDeliveredCargosByTruck()const;
	void getTruckMoveTime(int& h, int& d);
	PriQ<Cargo*> getLoadedCargosInTruck() const;
	void getTimeToComeBack(int &hour , int &day);
	Cargo* getLoadedCargosTop();

	void LoadCargos(Cargo* c);
	void UnloadCargo(PriQNode<Cargo*> delivered);
	bool LoadedCargosFull();
	void getDeliveredCargosByTruck();
	void incrementTruckTotalActiveTime();
	void AddJourney();
	double CalculateTruckUtilization();
	friend ostream& operator<<(ostream&output,Truck*t);
	~Truck();

};


