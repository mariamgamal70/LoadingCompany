#include <fstream>
#include <iostream>
//-------------------------//
#include "ArrayStack.h"
#include "LinkedQueue.h"
#include "PriQ.h"
#include"CargoLinkedList.h"
#include "Node.h"
#include "PriQNode.h"
//-------------------------//
#include "Truck.h"
#include"Cargo.h"
#include"UIclass.h"
//-------------------------//
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include"PromoteEvent.h"
//------------------------//
#include "CompanyClass.h"
using namespace std;
CompanyClass::CompanyClass()
{
	Hour = 1;
	Day = 1;
	TotalNumberOfTrucks = 0;
	SumNormalCargos = 0;
	SumSpecialCargos = 0;
	SumVIPCargos = 0;
	SumCargos = 0;
}
CompanyClass::CompanyClass(UIclass* uii)
{
	this->ui = uii;
}

void CompanyClass::FileLoading()
{
	ifstream inFile;
	//string filename = ui->cinfilename();//ACCORDING TO MALAK'S WORDS
	inFile.open("input.txt");//open a file to perform read operation using file object
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	if (inFile.is_open())
	{ //checking whether the file is open
		inFile >> nN >> nS >> nV;
		inFile >> Ns >> Ss >> Vs;
		inFile >> Nc >> Sc >> Vc;
		//TotalNumberOfTrucks = nN + nS + nV;
		inFile >> NoOfJourneys >> NCheckupTime >> SCheckupTime >> VCheckupTime;
		Truck* T1;
		static int TruckID = 0;
		for (int i = 0; i < nN; i++)
		{
			TruckID++;
			T1 = new Truck('N', Ns, Nc, Nj, NCheckupTime, TruckID);
			NormalTruckQueue.enqueue(T1);
		}
		for (int i = 0; i < nS; i++)
		{
			TruckID++;
			T1 = new Truck('S', Ss, Sc, Sj, SCheckupTime, TruckID);
			SpecialTruckQueue.enqueue(T1);
		}
		for (int i = 0; i < nV; i++)
		{
			TruckID++;
			T1 = new Truck('V', Vs, Vc, Vj, VCheckupTime, TruckID);
			VIPTruckQueue.enqueue(T1);
		}
		inFile >> AutoPDays >> MaxWaitHours;
		inFile >> NoOfEvents;

		Event* E;
		for (int i = 0; i < NoOfEvents; i++)
		{
			inFile >> EventType;
			char dummy;

			if (EventType)
			{
			if('R')//<<<<<---------------CALL PREPARATION EVENT--------------
			{
				inFile >> CargoType;
				inFile >> EventTimeDays;
				inFile >> dummy;
				inFile >> EventTimeHours;
				inFile >> CargoID;
				inFile>> CargoDist >> CargoLoadTime >> CargoCost;
				E=new PreparationEvent(CargoType, EventTimeHours, EventTimeDays, CargoID, CargoDist, CargoLoadTime, CargoCost);
				Eventlist.enqueue(E);
				count++;
				//break;
			}
			else if('X')//<<<---------------CALL CANCELLATION EVENT----------------
			{
				inFile >> EventTimeDays;
				inFile >> dummy;
				inFile >> EventTimeHours;
				inFile >> CargoID;
				E=new CancelEvent(EventTimeHours, EventTimeDays, CargoID);
				Eventlist.enqueue(E);
				count++;
				//break;
			}
			else if('P')//<<-----------------CALL PROMOTION EVENT-------------------
			{
				inFile >> EventTimeDays;
				inFile >> dummy;
				inFile >> EventTimeHours;
				inFile >> CargoID;
				inFile >> CargoExtraMoney;
				E=new PromoteEvent (EventTimeHours, EventTimeDays, CargoID, CargoExtraMoney);
				Eventlist.enqueue(E);
				count++;
				//break;
			}
			
			
			}
		}
		inFile.close(); //close the file object.
	}
}

//-------------------------------RELATED TO EXECUTE EVENTS---------------------------------

void CompanyClass::RemoveCargo(int id)
{
	NormalCargos.DeleteSpecificNode(id);
}

void CompanyClass::PromoteCargo(int id)
{
	Cargo* CargoToPromote = NormalCargos.findSpecificNode(id);

	if (CargoToPromote != nullptr)
	{
		NormalCargos.DeleteSpecificNode(id);

		VIPCargoPriority = ((Day + Hour) * 2 + CargoToPromote->getDeliveringDistance()) / CargoToPromote->getCargoDeliveringCost();

		VIPCargoPriQueue.enqueueAscending(CargoToPromote, VIPCargoPriority);

		CargoToPromote->setCargoType('V');
	}
}

/*double CompanyClass::setpriorityequation(int pH, int pD, int DD, int CC)
{
	VIPCargoPriority = (2 * (pH + pD) + 1 * DD) / CC;
	return VIPCargoPriority;
}*/

void CompanyClass::AddToNormalCargos(Cargo* C)
{
	NormalCargos.InsertEnd(C);
	SumNormalCargos++;
}

void CompanyClass::AddToSpecialCargos(Cargo* C)
{
	SpecialCargos.enqueue(C);
	SumSpecialCargos++;
}

void CompanyClass::AddToVIPCargos(Cargo* C ,double priority)
{
	VIPCargoPriQueue.enqueueAscending(C, priority);
	SumVIPCargos++;
}

void CompanyClass::AddToAppropriateList(Cargo* Cl)
{
	char Type = Cl->getCargoType();
	int PrepD = Cl->getPreparationTimeDay();
	int PrepH = Cl->getPreparationTimeHour();
	int id = Cl->getCargoID();
	int dist = Cl->getDeliveringDistance();
	int LoadT = Cl->getLoadTime();
	int cost = Cl->getCargoDeliveringCost();
	//c=new Cargo(Type, PrepD, PrepH, id, dist, LoadT, cost);
	if(Cl->getCargoType() == 'N')
	{
		NormalCargos.InsertEndC(Cl);
		SumNormalCargos++;
		//break;
	}
	else if(Cl->getCargoType() == 'S')
	{
		SpecialCargos.enqueue(Cl);
		SumSpecialCargos++;
		//break;
	}
	else if(Cl->getCargoType() == 'V')
	{
		VIPCargoPriority = (2 * (PrepH + PrepD) + 1 * dist) / CargoCost;
		VIPCargoPriQueue.enqueueAscending(Cl, VIPCargoPriority);
		SumVIPCargos++;
		//break;
	}
}
void CompanyClass::MoveTruckFromEmptyToLoading(Truck* T)
{
	Truck* deq;
	LinkedQueue<Truck*>* extra = NULL;
	if (T->getTruckType() == 'N')
	{
		NormalTruckQueue.peek(deq);
		while (deq != T) //find T in queue
		{
			NormalTruckQueue.dequeue(deq);
			extra->enqueue(deq);
		}
		NormalTruckQueue.dequeue(T); //dequeue T and add it to loading truck
		LoadingNormalTrucks.enqueue(T);

		while (!extra->isEmpty()) // return emptytrucksnormal queue to its original form
		{
			extra->dequeue(deq);
			NormalTruckQueue.enqueue(deq);
		}
	}
	else if (T->getTruckType() == 'V')
	{
		VIPTruckQueue.peek(deq);
		while (deq != T)
		{
			VIPTruckQueue.dequeue(deq);
			extra->enqueue(deq);

		}
		VIPTruckQueue.dequeue(T);
		LoadingVIPTrucks.enqueue(T);

		while (!extra->isEmpty())
		{
			extra->dequeue(deq);
			VIPTruckQueue.enqueue(deq);
		}
	}
	else
	{
		NormalTruckQueue.peek(deq);
		while (deq != T)
		{
			SpecialTruckQueue.dequeue(deq);
			extra->enqueue(deq);
		}
		SpecialTruckQueue.dequeue(T);
		LoadingSpecialTrucks.enqueue(T);

		while (!extra->isEmpty())
		{
			extra->dequeue(deq);
			SpecialTruckQueue.enqueue(deq);
		}
	}
}

void  CompanyClass::MoveTruckFromLoadingToMoving(Truck* T)
{
	Truck* deq;
	LinkedQueue<Truck*>* extra = nullptr; //for all trucks??? all conditions? or could be initialized for each condition?---ANSWER: each type is separated and all trucks in the list are loading so it doesnt matter since it's only used by one type'------------------------------>
	//if u do = nullptr it says dereferencing nullptr ,if left this way it says uninitialized local variable
	if (T->getTruckType() == 'N')
	{
		LoadingNormalTrucks.peek(deq);
		while (deq != T) //find T in queue
		{
			LoadingNormalTrucks.dequeue(deq);
			extra->enqueue(deq);
		}
		LoadingNormalTrucks.dequeue(T); //dequeue T and add it to MOVING truck
		MovingTrucks.enqueueAscending(T, T->getTruckDeliveryIntervalDays());

		while (!extra->isEmpty()) // return emptytrucksnormal queue to its original form
		{
			extra->dequeue(deq);
			LoadingNormalTrucks.enqueue(deq);
		}
	}
	else if (T->getTruckType() == 'V')
	{
		LoadingVIPTrucks.peek(deq);
		while (deq != T)
		{
			LoadingVIPTrucks.dequeue(deq);
			extra->enqueue(deq);
		}
		LoadingVIPTrucks.dequeue(T);
		MovingTrucks.enqueueAscending(T, T->getTruckDeliveryIntervalDays());

		while (!extra->isEmpty())
		{
			extra->dequeue(deq);
			LoadingVIPTrucks.enqueue(deq);
		}
	}
	else
	{
		LoadingSpecialTrucks.peek(deq);
		while (deq != T)
		{
			LoadingSpecialTrucks.dequeue(deq);
			extra->enqueue(deq);

		}
		LoadingSpecialTrucks.dequeue(T);
		MovingTrucks.enqueueAscending(T, T->getTruckDeliveryIntervalDays());

		while (!extra->isEmpty())
		{
			extra->dequeue(deq);
			LoadingSpecialTrucks.enqueue(deq);
		}
	}
}

void CompanyClass::AddTruckToCheckup(Truck* T) //->MARIAM
{
	PriQNode<Truck*> qnode;
	PriQ <Truck*> q;
	while (MovingTrucks.peek(qnode))//!= T)
	{
		if (qnode.getItem() != T)
		{
			MovingTrucks.dequeue(qnode);
			q.enqueueAscending(qnode.getItem(), qnode.getItem()->getTruckDeliveryIntervalDays());
		}
		else
		{
			break;
		}
	}
	MovingTrucks.dequeue(qnode);//<------------------- someone fix this pls
	switch (T->getTruckType())
	{
	case('N'):
	{
		NormalTrucksUnderCheckup.enqueue(T);
		break;
	}
	case('S'):
	{
		SpecialTrucksUnderCheckup.enqueue(T);
		break;
	}
	case ('V'):
	{
		VIPTrucksUnderCheckup.enqueue(T);
		break;
	}
	default:
		break;
	}
	while (!q.isEmpty())
	{
		q.dequeue(qnode);
		MovingTrucks.enqueueAscending(qnode.getItem(), qnode.getItem()->getTruckDeliveryIntervalDays());
	}
}

//-------------------------------------------GETTERS----------------------------------------//
double CompanyClass::getCargoAvgTime()
{
	CargoAvgTime = SumAllloadTime / SumCargos;
	return CargoAvgTime;
}
int CompanyClass::getTotalNumberOfCargos()
{
	SumCargos = SumNormalCargos + SumSpecialCargos + SumVIPCargos;
	return SumCargos;
}

int CompanyClass::getTotalNumberOfTrucks()
{
	TotalNumberOfTrucks = nN + nS + nV;
	return TotalNumberOfTrucks;
}
int CompanyClass::getCurrentTimeHour()
{
	return Hour;
}
int CompanyClass::getCurrentTimeDay()
{
	return Day;
}
/*LinkedList<Cargo*> CompanyClass::getNormalCargos()//to call in UI class
{
	return NormalCargos;
}
LinkedQueue<Cargo*> CompanyClass::getSpecialCargos()
{
	return SpecialCargos;
}
PriQ<Cargo*> CompanyClass::getVIPCargos()
{
	return VIPCargoPriQueue;
}
LinkedQueue<Truck*>  CompanyClass::getLoadingNormalTrucks()
{
	return LoadingNormalTrucks;
}
LinkedQueue<Truck*>  CompanyClass::getLoadingSpecialTrucks()
{
	return LoadingSpecialTrucks;
}
LinkedQueue<Truck*>  CompanyClass::getLoadingVIPTrucks()
{
	return LoadingVIPTrucks;
}
LinkedQueue<Truck*> CompanyClass::getNormalTrucksUnderCheckup()
{
	return NormalTrucksUnderCheckup;
}
LinkedQueue<Truck*> CompanyClass::getSpecialTrucksUnderCheckup()
{
	return SpecialTrucksUnderCheckup;
}
LinkedQueue<Truck*> CompanyClass::getVIPTrucksUnderCheckup()
{
	return VIPTrucksUnderCheckup;
}
LinkedQueue<Cargo*> CompanyClass::getDeliveredCargos()
{
	return DeliveredCargos;
}*/
//----------------------------------------PRINTING-------------------------------------//

void CompanyClass::printWNormalCargos()
{
	NormalCargos.printList();
}

void CompanyClass::printWspecialCargos()
{
	SpecialCargos.PrintQueue();
}

void CompanyClass::printWvipCargos()
{
	VIPCargoPriQueue.printList();
}

void CompanyClass::printLnormalTrucks()
{
	LoadingNormalTrucks.PrintQueue();
}

void CompanyClass::printLspecialTrucks()
{
	LoadingSpecialTrucks.PrintQueue();
}

void CompanyClass::printLVIPTrucks()
{
	LoadingVIPTrucks.PrintQueue();
}


void CompanyClass::printCheckupNormal()
{
	NormalTrucksUnderCheckup.PrintQueue();
}

void CompanyClass::printCheckupSpecial()
{
	SpecialTrucksUnderCheckup.PrintQueue();
}

void CompanyClass::printCheckupVIP()
{
	VIPTrucksUnderCheckup.PrintQueue();
}


void CompanyClass::printEmptyNormalTrucks()
{
	NormalTruckQueue.PrintQueue();
}

void CompanyClass::printEmptySpecialTrucks()
{
	SpecialTruckQueue.PrintQueue();
}

void CompanyClass::printEmptyVIPTrucks()
{
	VIPTruckQueue.PrintQueue();
}


void CompanyClass::printNormalDeliveredCargos()
{
	NormalDeliveredCargos.PrintQueue();
}


void CompanyClass::printSpecialDeliveredCargos()
{
	SpecialDeliveredCargos.PrintQueue();
}



void CompanyClass::printVIPDeliveredCargos()
{
	VIPDeliveredCargos.PrintQueue();
}

void CompanyClass::SimulatorFunction()
{
	FileLoading();
	int TimeStepCount = 0;
		while (!Eventlist.isEmpty())
		{			
			while (Hour > 23) //24hour will be 00H:00MIN AM
			{
				Hour = Hour - 23;
				Day++;
			}
			ui->coutstring("Current Time (Day:Hour)");//<----- trace el code keda
			ui->coutinteger(Day);
			ui->coutchar(':');
			ui->coutinteger(Hour);
 			ui->coutendl(); 
			Event* EventToBeExecuted;
			Eventlist.peek(EventToBeExecuted);
			if (EventToBeExecuted->GetHours() == Hour && EventToBeExecuted->GetDays() == Day)//pointer and hours and days are incorrect
			{
				Eventlist.dequeue(EventToBeExecuted);
				EventToBeExecuted->Execute();
			}
			if (TimeStepCount % 5 == 0 && TimeStepCount!=0)
			{
				Cargo* specialcargo;
				Node<Cargo*> normalcargo;
				PriQNode<Cargo*> vipcargo;
				if (NormalCargos.peek(normalcargo))//<---CHECK
				{
					NormalDeliveredCargos.enqueue(normalcargo.getItem());
					NormalCargos.DeleteBeg();
				}
				if (SpecialCargos.peek(specialcargo))
				{
					SpecialCargos.dequeue(specialcargo);
					SpecialDeliveredCargos.enqueue(specialcargo);
				}
				if (!VIPCargoPriQueue.isEmpty())
				{
					VIPCargoPriQueue.dequeue(vipcargo.getItem());
					VIPDeliveredCargos.enqueue(vipcargo.getItem());
				}
			}
			printwaitingcargos();
			printloadingtrucks();
			printavailtrucks();
			printmovingcargos();
			printcheckuptruck();
			printdeliveredcargo();
			//ui->printInteractive();
			Hour++;
			TimeStepCount++;
			ui->waitforenter();
		}
		//produce output file <<<----------OUTPUTFILE---------------------*/
}
				

void CompanyClass::printwaitingcargos()
{
	int numofwait = NormalCargos.getCount() + SpecialCargos.getCount() + VIPCargoPriQueue.getCount();
	ui->coutinteger(numofwait);
	ui->coutstring(" Waiting Cargos: ");
	ui->coutchar('[');
	NormalCargos.printList();
	ui->coutchar(']');
	ui->coutchar(' ');
	ui->coutchar('(');
	SpecialCargos.PrintQueue();
	ui->coutchar(')');
	ui->coutchar(' ');
	ui->coutchar('{');
	VIPCargoPriQueue.printList();
	ui->coutchar('}');
	ui->coutendl();
}

void CompanyClass::printcheckuptruck()
{
	int numofchkup = NormalTrucksUnderCheckup.getCount() + SpecialTrucksUnderCheckup.getCount() + VIPTrucksUnderCheckup.getCount();
	ui->coutinteger(numofchkup);
	ui->coutstring(" In-Checkup Trucks: ");
	ui->coutchar('[');
	NormalTrucksUnderCheckup.PrintQueue();
	ui->coutchar(']');
	ui->coutchar(' ');
	ui->coutchar('(');
	SpecialTrucksUnderCheckup.PrintQueue();
	ui->coutchar(')');
	ui->coutchar(' ');
	ui->coutchar('{');
	VIPTrucksUnderCheckup.PrintQueue();
	ui->coutchar('}');
	ui->coutendl();
}

void CompanyClass::printloadingtrucks()
{
	int z = 0;
	ui->coutinteger(z);
	ui->coutstring(" Loading Trucks: ");
	ui->coutstring("[] ");
	ui->coutstring("() ");
	ui->coutstring("{} ");
	ui->coutendl();
}

void CompanyClass::printmovingcargos()
{
	int z = 0;
	ui->coutinteger(z);
	ui->coutstring(" Moving Cargos: ");
	ui->coutstring("[] ");
	ui->coutstring("() ");
	ui->coutstring("{} ");
	ui->coutendl();
}

void CompanyClass::printavailtrucks()
{
	int numofavlt = NormalTruckQueue.getCount() + SpecialTruckQueue.getCount() + VIPTruckQueue.getCount();
	ui->coutinteger(numofavlt);
	ui->coutstring(" Empty Trucks: ");
	ui->coutchar('[');
	NormalTruckQueue.PrintQueue();
	ui->coutchar(']');
	ui->coutchar(' ');
	ui->coutchar('(');
	SpecialTruckQueue.PrintQueue();
	ui->coutchar(')');
	ui->coutchar(' ');
	ui->coutchar('{');
	VIPTruckQueue.PrintQueue();
	ui->coutchar('}');
	ui->coutendl();
}
void CompanyClass::printdeliveredcargo()
{
	int numdelivcargo = NormalDeliveredCargos.getCount() + SpecialDeliveredCargos.getCount() + VIPDeliveredCargos.getCount();
	ui->coutinteger(numdelivcargo);
	ui->coutstring(" Delivered Cargos: ");
	ui->coutchar('[');
	NormalDeliveredCargos.PrintQueue();
	ui->coutchar(']');
	ui->coutchar(' ');
	ui->coutchar('(');
	SpecialDeliveredCargos.PrintQueue();
	ui->coutchar(')');
	ui->coutchar(' ');
	ui->coutchar('{');
	VIPDeliveredCargos.PrintQueue();
	ui->coutchar('}');
	ui->coutendl();
}

CompanyClass::~CompanyClass()
{
}