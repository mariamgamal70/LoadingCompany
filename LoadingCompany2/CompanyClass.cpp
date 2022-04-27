#include <fstream>
#include <iostream>
//-------------------------//
#include "ArrayStack.h"
#include "LinkedQueue.h"
#include "PriQ.h"
//-------------------------//
#include "Truck.h"
#include"Cargo.h"
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
void CompanyClass::FileLoading()
{
	ifstream inFile;
	inFile.open("input.txt");//open a file to perform read operation using file object
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	if (inFile.is_open())// 2D ARRAY OR  CIN EACH INTEGER?
	{ //checking whether the file is open


		TotalNumberOfTrucks = nN + nS + nV;

		inFile >> nN >> nS >> nV;
		inFile >> Ns >> Ss >> Vs;
		inFile >> Nc >> Sc >> Vc;
		inFile >> NoOfJourneys >> NCheckupTime >> SCheckupTime >> VCheckupTime;
		/*Truck(char type, int speed, int capacity, int noOfJourneys, int CheckupTime)*/
		static int TruckID = 0;
		for (int i = 0; i < nN; i++)
		{
			TruckID++;
			Truck T1('N', Ns, Nc, Nj, NCheckupTime, TruckID);
			NormalTruckQueue.enqueue(&T1);
		}
		for (int i = 0; i < nS; i++)
		{
			Truck T2('S', Ss, Sc, Sj, SCheckupTime, TruckID);
			SpecialTruckQueue.enqueue(&T2);
		}
		for (int i = 0; i < nV; i++)
		{
			Truck T3('V', Vs, Vc, Vj, VCheckupTime, TruckID);
			VIPTruckQueue.enqueue(&T3); //<<<<<------------------------------ASK----------------------------------------------
		}
		inFile >> AutoPDays >> MaxWaitHours;
		inFile >> NoOfEvents;
		while (count != NoOfEvents)
		{
			inFile.get(EventType);

			switch (EventType)
			{
			case('R')://<<<<<---------------CALL PREPARATION EVENT--------------
			{
				inFile.get(CargoType);
				inFile >> EventTimeHours;
				inFile.ignore(100, ':');
				inFile >> EventTimeDays;
				/*fscanf(inFile , "% d : % d", EventTimeHours, EventTimeDays);*/
				inFile >> CargoID >> CargoDist >> CargoLoadTime >> CargoCost;
				PreparationEvent PrepE(CargoType, EventTimeHours, EventTimeDays, CargoID, CargoDist, CargoLoadTime, CargoCost);
				Eventlist.enqueue(&PrepE);
				count++;
				break;
			}
			case('X')://<<<---------------CALL CANCELLATION EVENT----------------
			{
				inFile >> EventTimeHours;
				inFile.ignore(100, ':');
				inFile >> EventTimeDays;
				inFile >> CargoID;
				CancelEvent CE(EventTimeHours, EventTimeDays, CargoID);
				Eventlist.enqueue(&CE);
				count++;
				break;
			}
			case('P')://<<-----------------CALL PROMOTION EVENT-------------------
			{
				inFile >> EventTimeHours;
				inFile.ignore(100, ':');
				inFile >> EventTimeDays;
				inFile >> CargoID;
				inFile >> CargoExtraMoney;
				PromoteEvent PromoE(EventTimeHours, EventTimeDays, CargoID, CargoExtraMoney);
				Eventlist.enqueue(&PromoE);
				count++;
				break;
			}
			default:
				break;
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
		int loaded = 0;
		Cargo c;
		Truck t;
		PriQNode<Cargo*> dequeued;
		c = c.getCID(id);
		Cargo* c2 = t.getLoadedCargosInTruck().peek(); //get first cargo in queue of loadingcargos

		while (c2->getCargoID() != NULL)
		{
			Cargo* c2 = t.getLoadedCargosInTruck().peek();
			if (c2->getCargoID() == id)
			{
				loaded++;
				break;
			}
			else
				t.getLoadedCargosInTruck().dequeue(&dequeued);
		}
		if (c.getCargoType() == 'N' && loaded == 0)
			c.setCargoType('V');
	}
/*	Cargo* temp = nullptr;
	while (!(WaitingToLoadNormalTrucks.isEmpty()))
	{
		int priority = 0;

		WaitingToLoadNormalTrucks.dequeue(temp);
		if (temp->getCargoID() != id)
		{
			WaitingToLoadNormalTrucks.enqueue(temp);
		}
		else
		{
			int PrepHour = temp->getPreparationTimeHour();
			int PrepDay = temp->getPreparationTimeDay();
			int DeliveryDist = temp->getDeliveringDistance();
			int CargoCost = temp->getCargoDeliveringCost();

			priority = ((PrepHour + PrepDay) * DeliveryDist) / CargoCost;

			WaitingToLoadVIPTrucks.enqueue(&temp, priority);
		}
	}
}
*/

void CompanyClass::AddToAppropriateList(Cargo* C)
{
	char CargoType = C->getCargoType();
	switch (CargoType)
	{
	case('N'):
	{
		NormalCargos.InsertEnd(C);
		SumNormalCargos++;
		break;
	}
	case('S'):
	{
		SpecialCargos.enqueue(C);
		SumSpecialCargos++;
		break;
	}
	case('V'):
	{
		int PrepHour = C->getPreparationTimeHour();
		int PrepDay = C->getPreparationTimeDay();
		int DeliveryDist = C->getDeliveringDistance();
		int CargoCost = C->getCargoDeliveringCost();
		/*VIPCargoPriority = ((PrepHour + PrepDay) * DeliveryDist) / CargoCost;
		VIPCargoPriQueue.enqueueAscending(C, VIPCargoPriority);
		SumVIPCargos++;*/
		break;
	}
	default:
		break;
	}
}
void CompanyClass::MoveTruckFromEmptyToLoading(Truck* T)
{
	Truck* deq;
	LinkedQueue<Truck*>* extra=NULL;
	if (T->getTruckType() == 'N')
	{
		NormalTruckQueue.peek(deq);
		while (deq!= T) //find T in queue
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
		while ( deq!= T)
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

			while (!extra->isEmpty())//<----- -----el warning el hena asdo eh? msh zaher 3andy h3ml build // dereferencing null pointer asdo eh y3ny mmknnn el ptr da yb
			{

				extra->dequeue(deq);
				SpecialTruckQueue.enqueue(deq);

			}
	}
	}

void  CompanyClass::MoveTruckFromLoadingToMoving(Truck* T)
{
	Truck* deq;
	LinkedQueue<Truck*>* extra=NULL;
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

/*void CompanyClass::AddTruckToCheckup(Truck* T)----->MARIAM
{

	MovingTrucks.dequeue(T);//<------------------- someone fix this pls
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

}*/
	void CompanyClass::AddTruckToCheckup(Truck *T)
	{
		
		 PriQNode<Truck*> qnode;
		 PriQ <Truck*> q;
		 while (MovingTrucks.peek() != T)
		 {
			 MovingTrucks.dequeue(&qnode);
			 q.enqueueAscending(qnode.getItem(), qnode.getItem()->getTruckDeliveryIntervalDays());

		 }

		MovingTrucks.dequeue(&qnode);//<------------------- someone fix this pls
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
			q.dequeue(&qnode);
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
//----------------------------------------CALCULATIONS-------------------------------------//

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








void CompanyClass::SimulatorFunction()
{
	FileLoading();
	int count = 0;
	Event* E;
	Cargo* Head;

	while (!Eventlist.isEmpty())
	{
		Eventlist.dequeue(E);
		E->Execute();
		count++;
		if (count == 5)
		{
			Cargo* peeked;
			LinkedList <Cargo*>* temp=NULL;
			temp->peek(Head); // correct? //<-------------------------------CORRECT IT
			DeliveredCargos.enqueue(Head);
			SpecialCargos.peek(peeked);
			if (peeked->getPreparationTimeDay() == 0 && peeked->getPreparationTimeHour() == 0)
				DeliveredCargos.enqueue(peeked);

			if (VIPCargoPriQueue.peek()->getPreparationTimeDay() == 0 && VIPCargoPriQueue.peek()->getPreparationTimeHour() == 0)
				DeliveredCargos.enqueue(VIPCargoPriQueue.peek());
		}
		//missing "Print all applicable info to the interface as describes in Program interface section without truck info"
	}
}


/*void CompanyClass::Simulationfunc()
{
	Hour = 1;
	Day = 1;
	Node<Event*> * currEvent = NULL;
	while (!(Eventlist.isEmpty()))                           //<< < -------------------- - TIMESTEP---------------- -
	{
		Eventlist.dequeue(currEvent);
					Execute events
					check waiting list -> if exist assign to available trucks
					move cargos from waiting->loading->moving ->delivered
					move trucks from available->loading->moving ->checkup->available
					collect all the needed calculations for output file
					call ui class to print details on the output screen
					if time<24 increment time else increment day and reset time
	}

	CARGO DELIVERY TIME CALCULATIONS
}
				//produce output file <<<----------OUTPUTFILE---------------------*/
				/*
	LinkedList<Cargo*> NormalCargos; // to apply cancellation and promotion on it easier
	LinkedQueue<Cargo*> SpecialCargos;
	PriQ <Cargo*> VIPCargoPriQueue;
	void print
				*/
CompanyClass::~CompanyClass()
{
}