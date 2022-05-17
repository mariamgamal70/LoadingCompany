#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include <cstdlib>
//#include"Truck.h"
//#include"LinkedList.h"
//#include"PriQ.h"
//#include"ArrayStack.h"
//#include"LinkedQueue.h"
//#include "Truck.h"
using std::ifstream;
using namespace std;
//class Truck; //---------------------->OPTION1
class Cargo
{
private:

	int LoadTime;
	char CargoType;
	int PreparationTimeDays;
	int PreparationTimeHour;
	int CargoDeliveringCost;
	int DeliveringDistance;
	int CargoID;
	int CargoDeliveryTimeHours;
	int CargoDeliveryTimeDays;
	int WaitTimeHour;
	int WaitTimeDay;
	//Truck* TruckLoadedOn; //OPTION1

public:

	Cargo();
	Cargo(char type, int pd, int ph, int id, int dist, int LT, int cost); //for preparation class
	void setCargoLoadTime(int time);
	void setPreparationTimeDay(int day);
	void setPreparationTimeHour(int hour);
	void setCargoDeliveringCost(int cost);
	void setDeliveringDistance(int distance);
	void setCargoType(char type);
	void SetCargoID(int id);
	void setCargoDeliveryTime(int TruckMoveTimeHour, int TruckMoveTimeDay, int Truckspeed);//OPTION2
	void setCargoWaitTime(int movetimeh,int movetimed);
	//void setTruckLoadedOn(Truck* T);//OPTION1
	//void setCargoDeliveryTime(int& hours, int& days);//-------->get movetime and truckspeed //OPTION1

	char getPreparationTimeDay() const;
	int getPreparationTimeHour()const;
	int getCargoDeliveringCost() const;
	int getDeliveringDistance() const;
	char getCargoType() const;
	int getLoadTime()const;
	int getCargoID() const;
	void getCargoDeliveryTime(int& CDTh, int& CDTd);
	void getCargoWaitTime(int& waittimeh, int& waittimed);

	friend ostream& operator<<(ostream&output,Cargo*c);
	Cargo getCID(int CargoID);
	~Cargo();

};

