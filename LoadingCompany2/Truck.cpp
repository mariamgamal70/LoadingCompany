#include "Truck.h"
#include"PriQ.h"
#include "Cargo.h"
Truck::Truck()
{
	TruckID++;
	setTruckType('N');
	setTruckCapacity(0);
	setTruckMaintenanceTime(0);
	setTruckSpeed(0);
	SetNoOfJourneys(0);
	TruckID = 0;
	DeliveredCargosByTruck = 0;
	setTruckMoveTime(0, 0);
	TruckTotalActiveTimeH=0;
	TruckTotalActiveTimeD=0;
	TruckUtilization = 0;
	TruckDeliveryIntervalH = 0;
	TruckDeliveryIntervalD = 0;
}

Truck::Truck(char type, int speed, int capacity, int noOfJourneys, int CheckupTime, int id)
{
	setTruckType(type);
	setTruckSpeed(speed);
	setTruckCapacity(capacity);
	SetNoOfJourneys(noOfJourneys);
	setTruckMaintenanceTime(CheckupTime);
	SetTruckID(id);
}

void Truck::setTruckType(char type)
{
	TruckType = type;
}

void Truck::setTruckCapacity(int capacity)
{
	TruckCapacity = capacity;
}

void Truck::setTruckMaintenanceTime(int time)
{
	TruckMaintenanceTime = time;
}

void Truck::setTruckSpeed(int speed)
{
	TruckSpeed = speed;
}

void Truck::SetNoOfJourneys(int number)
{
	TruckNoOfJourneys = number;
}
void Truck::SetTruckID(int id)
{
	TruckID = id;
}
void Truck::getDeliveredCargosByTruck()
{
	DeliveredCargosByTruck= TruckCapacity* TruckNoOfJourneys;
}

void Truck::incrementTruckTotalActiveTime()
{
	TruckTotalActiveTimeH++;
	while (TruckTotalActiveTimeH > 23)
	{
		TruckTotalActiveTimeH = TruckTotalActiveTimeH - 23;
		TruckTotalActiveTimeD++;
	}
}

void Truck::AddJourney()
{
	TruckNoOfJourneys++;
}

void Truck::CalculateTruckUtilization(int simh,int simd) //NEEDED TO BE FIXED ,(CALLED  AT THE END OF SIMULATION)// needs total simulation time
{
	int totalsimulationtime = simh + (simd * 24);
	TruckUtilization = getNoDeliveredCargosByTruck() / (DeliveredCargosByTruck * TruckNoOfJourneys) * ((TruckTotalActiveTimeH + (TruckTotalActiveTimeD * 24))/totalsimulationtime);
}

void Truck::setTruckMoveTime(int h, int d)
{
	TruckMoveTimeHour = h;
	TruckMoveTimeDay = d;
	while (TruckMoveTimeHour > 23)
	{
		TruckMoveTimeHour = TruckMoveTimeHour - 23;
		TruckMoveTimeDay++;
	}
}

char Truck::getTruckType() const
{
	return TruckType;
}

int Truck::getTruckCapacity() const
{
	return TruckCapacity;
}

int Truck::getTruckMaintenanceTime() const
{
	return TruckMaintenanceTime;
}

int Truck::getTruckSpeed() const
{
	return TruckSpeed;
}

void Truck::getTruckDeliveryInterval(int& hours, int& days) //------------------->NEEDS CONTINUTATION
{
	//Cargo* c;
	//c=LoadingCargos.getLastNode();

	int comeD;
	int comeH;
	int FurthestCargoDeliveryDistance = getLoadedCargoFurthestDistance();
	getTimeToComeBack(comeH, comeD);
	//int FurthestCargoDeliveryDistance=c->getDeliveringDistance();
	TruckDeliveryIntervalH = FurthestCargoDeliveryDistance / getTruckSpeed() + getSumUnloadTimeCargos() +comeH;//+ time to come back;
	while (TruckDeliveryIntervalH > 23)
	{
		TruckDeliveryIntervalH = TruckDeliveryIntervalH - 23;
		TruckDeliveryIntervalD++;
	}
	hours=TruckDeliveryIntervalH; 
	days=TruckDeliveryIntervalD;
	//return TruckDeliveryIntervalH;
}

int Truck::getNoOfJourneys() const
{
	return TruckNoOfJourneys;
}
int Truck::getTruckID() const
{
	return TruckID;
}
int Truck::getNoDeliveredCargosByTruck() const
{
	return DeliveredCargosByTruck;
}
void Truck::getTruckMoveTime(int& h, int& d)
{
	h = TruckMoveTimeHour;
	d = TruckMoveTimeDay;
}
void Truck::LoadCargos(Cargo* c)
{
	c->setCargoDeliveryTime(TruckMoveTimeHour, TruckMoveTimeDay, TruckSpeed);//OPTION2
	c->setCargoWaitTime(TruckMoveTimeHour, TruckMoveTimeDay);
	c->setTruckLoadedOn(TruckID);
	LoadingCargos.enqueueAscending(c, c->getDeliveringDistance());//---->check descending or ascending
	//c->setTruckLoadedOn(this); //OPTION1
}

void Truck::UnloadCargo(PriQNode<Cargo*> delivered)
{
	LoadingCargos.dequeue(delivered);
}

bool Truck::LoadedCargosFull()
{
	if (LoadingCargos.getCount() == TruckCapacity)
		return true;
	else
		return false;
}

PriQ<Cargo*> Truck::getLoadedCargosInTruck() const
{
	return LoadingCargos;
}
void Truck::getTimeToComeBack(int &hour, int &day)
{
	//Cargo* lastnode = LoadingCargos.getLastNode();
	//int furthestdistance =lastnode->getDeliveringDistance();
	int furthestdistance = getLoadedCargoFurthestDistance();
	TimeToComeBackH = furthestdistance / TruckSpeed;
	while (TimeToComeBackH > 23)
	{
		TimeToComeBackH = TimeToComeBackH - 23;
		TimeToComeBackD++;
	}
}
Cargo* Truck::getLoadedCargosTop()
{
	Cargo* top=nullptr;
	PriQNode<Cargo*> node;
	LoadingCargos.peek(node);
	top=node.getItem();
	return top ;
}
int Truck::getLoadedCargoFurthestDistance()
{
	PriQ <Cargo*> Extra = getLoadedCargosInTruck();
	PriQNode<Cargo*>* node=nullptr;
	Extra.peek(*node);
	while (!Extra.isEmpty() && node->getNext() != nullptr)
	{
		Extra.dequeue(*node);
		node = node->getNext();
	}
	LoadedCargoFurthestDistance= node->getItem()->getDeliveringDistance();
	return LoadedCargoFurthestDistance;
}
int Truck::getSumUnloadTimeCargos()
{
	int sum=0;
	PriQ <Cargo*> Extra = getLoadedCargosInTruck();
	PriQNode<Cargo*>* node=NULL;
	Extra.peek(*node);
	while (!Extra.isEmpty() && node!= nullptr)
	{
		sum = sum + node->getItem()->getLoadTime();
		Extra.dequeue(*node);
		node = node->getNext();
	}
	return sum;
}
double Truck::getTruckUtilization()
{
	return TruckUtilization;
}
char Truck::getCargoLoadedType()
{
	PriQNode<Cargo*>top;
	LoadingCargos.peek(top);
	return top.getItem()->getCargoType();
}
Truck::~Truck()
{
}

ostream& operator<<(ostream& output, Truck* t)
{
	output << t->getTruckID();
	return output;
}
