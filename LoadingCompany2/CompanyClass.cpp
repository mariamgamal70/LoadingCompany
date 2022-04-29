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
/*void CompanyClass::FileLoading()
{
	ifstream inFile;
	inFile.open("input.txt");//open a file to perform read operation using file object
	You need to call ui to get file name
		Company class should have a pointer to UI to do so.


		if (!inFile)
		{
			cout << "Unable to open file";
			exit(1); // terminate with error
		}

	if (inFile.is_open())// 2D ARRAY OR  CIN EACH INTEGER?
	{ //checking whether the file is open


		TotalNumberOfTrucks = nN + nS + nV;
		How could you sum these variables while they have not loaded from file yet.


			inFile >> nN >> nS >> nV;
		inFile >> Ns >> Ss >> Vs;
		inFile >> Nc >> Sc >> Vc;
		inFile >> NoOfJourneys >> NCheckupTime >> SCheckupTime >> VCheckupTime;
		/ Truck(char type, int speed, int capacity, int noOfJourneys, int CheckupTime) /
			static int TruckID = 0;
		for (int i = 0; i < nN; i++)
		{
			TruckID++;
			Truck T1('N', Ns, Nc, Nj, NCheckupTime, TruckID);
			T1 is a local object.It will be automatically destroyed one this function end
				You should use pointersand create a dynamic object using new then enqueue the pointer
				This comment is applicable for all types of trucks you createand also for all events you create.

				NormalTruckQueue.enqueue(&T1);
		}
		for (int i = 0; i < nS; i++)
		{
			Truck T2('S', Ss, Sc, Sj, SCheckupTime, TruckID);
			specialTruckQueue.enqueue(&T2);
		}
		for (int i = 0; i < nV; i++)
		{
			Truck T3('V', Vs, Vc, Vj, VCheckupTime, TruckID);
			VIPTruckQueue.enqueue(&T3); //<<<<<------------------------------ASK----------------------------------------------
		}
		inFile >> AutoPDays >> MaxWaitHours;
		inFile >> NoOfEvents;
		while (count != NoOfEvents)
			Better make it for loop

		{
		inFile.get(EventType);

		switch (EventType)
		{
		case('R')://<<<<<---------------CALL PREPARATION EVENT--------------
		{
		inFile.get(CargoType);
		Just write inFile >> CargoType

		inFile >> EventTimeHours;
		Read days first the hours

		inFile.ignore(100, ':');
		You may simply replace this line by
		InFile >> dummy;
		Where dummy is a char variable

		inFile >> EventTimeDays;
		/ fscanf(inFile , "% d : % d", EventTimeHours, EventTimeDays); /
		inFile >> CargoID >> CargoDist >> CargoLoadTime >> CargoCost;
		PreparationEvent PrepE(CargoType, EventTimeHours, EventTimeDays, CargoID, CargoDist, CargoLoadTime, CargoCost);
		Eventlist.enqueue(&PrepE);
		count++;
		break;
		Why break.
		File is not finished yet*/

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
		//PreparationEvent* PrepE;
		//CancelEvent* CE;
		//PromoteEvent* PromoE;
		Event* E;
		for (int i = 0; i < NoOfEvents; i++)
		{
			inFile >> EventType;
			char dummy;

			if (EventType)
			{
				/*inFile >> EventTimeHours;
				inFile >> dummy;
				inFile >> EventTimeDays;
				inFile >> CargoID;*/

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
			
			//Eventlist.enqueue(PrepE);
			//Eventlist.enqueue(CE);
			
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

//void CompanyClass::PromoteCargo(int id)
//{
//	int loaded = 0;
//	Cargo c;
//	Truck t;
//	LoadingNormalTrucks.peek(t);
//	//instead of t using NormalLoadingTrucks
//	Cargo* deq = nullptr;
//	PriQ <Cargo*> q;
//	c = c.getCID(id);
//	while (t)
//	{
//		Cargo* c2 = t.getLoadedCargosInTruck().peek(); //get first cargo in queue of loadingcargos

//		while (c2->getCargoID() != NULL)
//		{
//			Cargo* c2 = t.getLoadedCargosInTruck().peek();
//			if (c2->getCargoID() == id)
//			{
//				loaded++;
//				break;
//			}
//			else
//			{
//				t.getLoadedCargosInTruck().dequeue(deq);
//				q.enqueueAscending(deq, deq->getLoadTime());
//			}
//			if (loaded == 1)
//				break;
//	LoadingNormalTrucks.dequeue(t);
//		}

//	}
//	if (c.getCargoType() == 'N' && loaded == 0)
//	{
//		c.setCargoType('V');
//		Cargo* cptr = &c;
//		VIPCargoPriQueue.enqueueAscending(cptr, cptr->getPreparationTimeDay());
//	}
//}



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
}

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

//	Cargo* temp = nullp

void CompanyClass::AddToVIPCargos(Cargo* C ,double priority)
{
	VIPCargoPriQueue.enqueueAscending(C, priority);
	SumVIPCargos++;
}*/
//
void CompanyClass::AddToAppropriateList(Cargo* Cl)
{
	/*char Type = Cl->getCargoType();
	int PrepD = Cl->getPreparationTimeDay();
	int PrepH = Cl->getPreparationTimeHour();
	int id = Cl->getCargoID();
	int dist = Cl->getDeliveringDistance();
	int LoadT = Cl->getLoadTime();
	int cost = Cl->getCargoDeliveringCost();
	
	c=new Cargo(Type, PrepD, PrepH, id, dist, LoadT, cost);*/
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
		int PrepHour = Cl->getPreparationTimeHour();
		int PrepDay = Cl->getPreparationTimeDay();
		int DeliveryDist = Cl->getDeliveringDistance();
		int CargoCost = Cl->getCargoDeliveringCost();
		VIPCargoPriority = (2 * (PrepHour + PrepDay) + 1 * DeliveryDist) / CargoCost;
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

/*void CompanyClass::AddTruckToCheckup(Truck* T)// SHERIF
{

	Truck* qnode;
	PriQ <Truck*> q;
	while (MovingTrucks.peek() != T)
	{
			MovingTrucks.dequeue(qnode);
			q.enqueueAscending(qnode, qnode->getTruckDeliveryIntervalDays());
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
		MovingTrucks.enqueueAscending(qnode, qnode->getTruckDeliveryIntervalDays());
	}
}*/
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


/*void CompanyClass::SimulatorFunction()
{
	FileLoading();
	int TimeStepCount = 0;
	Event* EventToBeExecuted;
	if (Eventlist.peek(EventToBeExecuted));


	while (!Eventlist.isEmpty())
	{
		while (EventToBeExecuted->GetHours() == Hour && EventToBeExecuted->GetDays() == Day)
		{
			Eventlist.dequeue(EventToBeExecuted);
			EventToBeExecuted->Execute();
		}
		if (TimeStepCount == 5)
		{
			Cargo* cargo;
			if (NormalCargos.peek(cargo))//<---CHECK
			{
				NormalDeliveredCargos.enqueue(cargo);
				NormalCargos.DeleteBeg();
			}
			else if (SpecialCargos.peek(cargo))
			{
				SpecialCargos.dequeue(cargo);
				SpecialDeliveredCargos.enqueue(cargo);
			}
			else if (!VIPCargoPriQueue.isEmpty())
			{
				VIPCargoPriQueue.dequeue(cargo);
				VIPDeliveredCargos.enqueue(cargo);
			}
			TimeStepCount = 0;
		}
		Hour++;
		Day++;
		while (Hour > 23) //24hour will be 00H:00MIN AM
		{
			Hour = Hour - 23;
			Day++;
		}
		TimeStepCount++;
		ui->waitforenter();
	}
}


*/


void CompanyClass::SimulatorFunction()
{
	FileLoading();
	int TimeStepCount = 0;
	//Event* EventToBeExecuted;
	//if (Eventlist.peek(EventToBeExecuted))
	//{
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
		
	//}
}


/*void CompanyClass::SimulatorFunction() //YARA CREATED
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
}*/


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