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
	int LoadedCargoFurthestDistance;
public:

	Truck();
	Truck(char type, int speed, int capacity, int noOfJourneys, int CheckupTime, int id);
	void setTruckType(char type);
	void setTruckCapacity(int capacity);
	void setTruckMaintenanceTime(int time);//adjust---------------------------------->
	void setTruckSpeed(int speed);
	void SetNoOfJourneys(int number);
	void SetTruckID(int id);
	void setTruckMoveTime(int h, int d);
	void setCargosLoadedFurthestDistance(int dist);
	void setTimeToComeBack(); //should be set and make another getter

	char getTruckType()const;
	int getTruckCapacity()const;
	int getTruckMaintenanceTime()const;
	int getTruckSpeed()const;
	void getTruckDeliveryInterval(int& hours, int& days);
	int getNoOfJourneys()const;
	int getTruckID()const;
	int getNoDeliveredCargosByTruck()const;
	void getTruckMoveTime(int& h, int& d);
	void getTimeToComeBack(int& hour, int& day);
	PriQ<Cargo*> getLoadedCargosInTruck() const;
	Cargo* getLoadedCargosTop();
	int getLoadedCargoFurthestDistance();
	int getSumUnloadTimeCargos();
	double getTruckUtilization();
	char getCargoLoadedType();

	void LoadCargos(Cargo* c);
	void UnloadCargo(PriQNode<Cargo*>& delivered);
	bool LoadedCargosFull();
	//bool LoadedCargosEmpty(); //yara might need it 
	void getDeliveredCargosByTruck();
	void incrementTruckTotalActiveTime();
	void AddJourney();
	void CalculateTruckUtilization(int simh, int simd);//called at the end of simulation 
	friend ostream& operator<<(ostream& output, Truck* t);
	~Truck();

};

