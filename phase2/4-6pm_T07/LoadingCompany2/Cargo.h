#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include <cstdlib>

using std::ifstream;
using namespace std;

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
	int TID;

public:

	Cargo();
	Cargo(char type, int pd, int ph, int id, int dist, int LT, int cost); 
	void setCargoLoadTime(int time);
	void setPreparationTimeDay(int day);
	void setPreparationTimeHour(int hour);
	void setCargoDeliveringCost(int cost);
	void setDeliveringDistance(int distance);
	void setCargoType(char type);
	void SetCargoID(int id);
	void setCargoDeliveryTime(int TruckMoveTimeHour, int TruckMoveTimeDay, int Truckspeed);
	void setCargoWaitTime(int movetimeh,int movetimed);
	void setTruckLoadedOn(int tid);

	char getPreparationTimeDay() const;
	int getPreparationTimeHour()const;
	int getCargoDeliveringCost() const;
	int getDeliveringDistance() const;
	char getCargoType() const;
	int getLoadTime()const;
	int getCargoID() const;
	void getCargoDeliveryTime(int& CDTh, int& CDTd);
	void getCargoWaitTime(int& waittimeh, int& waittimed);
	int getTruckLoadedOn();

	friend ostream& operator<<(ostream&output,Cargo*c);
	Cargo getCID(int CargoID);
	~Cargo();

};

