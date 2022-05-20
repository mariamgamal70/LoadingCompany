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
#include "PromoteEvent.h"
//------------------------//
#include "CompanyClass.h"
using namespace std;
CompanyClass::CompanyClass()
{
	Hour = 1;
	Day = 1;
	TotalNumberOfTrucks = 0;
	sumfinalnorm = 0;
	sumfinalspec = 0;
	sumfinalvip = 0;
	SumCargos = 0;
	count = 0;
	//noOfPromotedCargos=0;
	noOfAutoPCargos=0;
	SumTruckActiveTimeH=0;
	SumTruckActiveTimeD=0;
	SumUtilization = 0; 
	sumspecialloadtime = 0;
	sumnormalloadtime = 0;
	sumviploadtime = 0;
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
				if(EventType=='R')//<<<<<---------------CALL PREPARATION EVENT--------------
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
				else if(EventType=='X')//<<<---------------CALL CANCELLATION EVENT----------------
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
				else if(EventType=='P')//<<-----------------CALL PROMOTION EVENT-------------------
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

	sumfinalnorm--;
}

void CompanyClass::PromoteCargo(int id)// change cost of cargo , increment no of promoted cargos
{
	Cargo* CargoToPromote = NormalCargos.findSpecificNode(id);

	if (CargoToPromote != nullptr)
	{
		NormalCargos.DeleteSpecificNode(id);

		VIPCargoPriority = ((Day + Hour) * 2 + CargoToPromote->getDeliveringDistance()) / CargoToPromote->getCargoDeliveringCost();

		VIPCargoPriQueue.enqueueAscending(CargoToPromote, VIPCargoPriority);

		CargoToPromote->setCargoType('V');

		sumfinalnorm--;

		sumfinalvip++;

	}
}
/*void CompanyClass::OutputFile()
{
		fout.open(output);
		fout << "CDT	" << "ID	" << "PT	" << "WT	" << "TID	";
		fout << endl;
		LinkedQueue<Cargo*>* deliveredcarg = new LinkedQueue<Cargo*>;
		int numcomp = deliveredcarg->getCount();
		Cargo* temp;
		for (int i = 0; i < numcomp; i++)
		{
			int day, hour, id, dday, hhour;
			deliveredcarg->dequeue(temp);
			temp->getCargoDeliveryTime(day, hour);
			id = temp->getCargoID();
			temp->getCargoWaitTime(dday, hhour);
			fout << day << ':' << hour << "	";
			fout << temp->getPreparationTimeDay() << "	";
			fout << dday << ':' << hhour << "	";
			fout << temp->getTruckLoadedOn() << "	";
			fout << endl;
		}
		fout << "\n ........................................................\n";
		fout << "\n ........................................................ \n";
		fout << "Cargos: " << getTotalNumberOfCargos() << " ";
		fout << "[N: " <<getnumfinalnorm() << ", S: " << getnumfinalspec() << ", V: " << getnumfinalvip() << "]" << endl;
		int d, h;
		calcCargoAvgWaitTime(d, h);
		fout << "Cargo Avg Wait= " << d << ':' << h << endl;
		fout << "Auto-promoted Cargos: ";
		if (getautopromnum() == 0)
		{
			fout << "None" << endl;
		}
		else
		{
			fout << ((float)getautopromnum() / (getnumfinalnorm() + getautopromnum()) * 100) << '%' << endl;
		}
		fout << "Trucks:" << getTotalNumberOfTrucks() << "  ";
		fout << "[N: " << getNumberOfNormalTrucks() << ", S: " << getNumberOfspecialTrucks() << ", V: " << getNumberOfVipTrucks() << "]" << endl;
		fout << "Avg Active time= " <<calcAvgActiveTime() << '%' << endl;
		fout << "Avg utilization= " <<calcAvgUtilization() << endl;
		fout.close();
	
}*/

/*void CompanyClass::AutoPromote(int id)
{
	Cargo* c=NormalCargos.findSpecificNode(id);
	if (c)
	{
		int hours = (c->getPreparationTimeDay()) * 24;
		hours = hours + c->getPreparationTimeHour();
		if (hours >= (AutoPDays * 24))
		{
			PromoteCargo(id);
		}
	}
}*/
/*double CompanyClass::setpriorityequation(int pH, int pD, int DD, int CC)
{
	VIPCargoPriority = (2 * (pH + pD) + 1 * DD) / CC;
	return VIPCargoPriority;
}*/

void CompanyClass::ExecuteEvents()
{
	Event* EventToBeExecuted;
	while (!Eventlist.isEmpty()) //can assign and move from list to list while executing ? how?
	{
		Eventlist.peek(EventToBeExecuted);
		if (EventToBeExecuted->GetHours() == Hour && EventToBeExecuted->GetDays() == Day)//pointer and hours and days are incorrect
		{
			Eventlist.dequeue(EventToBeExecuted);
			EventToBeExecuted->Execute(this);
		}
		else
		{
			break;
		}
	}
}

void CompanyClass::AddToNormalCargos(Cargo* C)
{
	NormalCargos.InsertEnd(C);
	sumfinalnorm++;
}

void CompanyClass::AddToSpecialCargos(Cargo* C)
{
	SpecialCargos.enqueue(C);
	sumfinalspec++;
}

void CompanyClass::AddToVIPCargos(Cargo* C ,double priority)
{
	VIPCargoPriQueue.enqueueAscending(C, priority);
	sumfinalvip++;
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
		NormalCargos.InsertEnd(Cl);
		sumfinalnorm++;
	}
	else if(Cl->getCargoType() == 'S')
	{
		SpecialCargos.enqueue(Cl);
		sumfinalspec++;
	}
	else if(Cl->getCargoType() == 'V')
	{
		VIPCargoPriority = (2 * (PrepH + PrepD) + 1 * dist) / CargoCost;
		VIPCargoPriQueue.enqueueAscending(Cl, VIPCargoPriority);
		sumfinalvip++;
	}
}
void CompanyClass::MoveTruckFromEmptyToLoading(Truck* T)
{
	if (T->getTruckType() == 'N')
	{
		NormalTruckQueue.dequeue(T); //dequeue T and add it to loading truck
		LoadingNormalTrucks.enqueue(T);
	}
	else if (T->getTruckType() == 'V')
	{
		VIPTruckQueue.dequeue(T);
		LoadingVIPTrucks.enqueue(T);
	}
	else
	{
		SpecialTruckQueue.dequeue(T);
		LoadingSpecialTrucks.enqueue(T);
	}
}

void  CompanyClass::MoveTruckFromLoadingToMoving(Truck* T)
{
	if (T->LoadedCargosFull())
	{
		if (Hour >= 5 && Hour <= 23)
		{

			if (T->getTruckType() == 'N')
			{
				LoadingNormalTrucks.dequeue(T); //dequeue T and add it to MOVING truck
				int hours;
				int days;
				T->getTruckDeliveryInterval(hours, days);
				hours = hours + days * 24;
				MovingTrucks.enqueueAscending(T, hours);
			}
			else if (T->getTruckType() == 'V')
			{
				LoadingVIPTrucks.dequeue(T);
				int hours;
				int days;
				T->getTruckDeliveryInterval(hours, days);
				hours = hours + days * 24;
				MovingTrucks.enqueueAscending(T, hours);
			}
			else
			{
				LoadingSpecialTrucks.dequeue(T);
				int hours;
				int days;
				T->getTruckDeliveryInterval(hours, days);
				hours = hours + days * 24;
				MovingTrucks.enqueueAscending(T, hours);

			}
		}
	}
}
void CompanyClass::MoveTruckFromCheckupToAvailable(	Truck* T)
{
	if (T->getTruckType() == 'N')
	{
		if (T->getTruckMaintenanceTime() == NULL)
		{
			NormalTrucksUnderCheckup.dequeue(T);


			NormalTruckQueue.enqueue(T);
		}
	}
		else if (T->getTruckType() == 'V')
		{

		if (T->getTruckMaintenanceTime() == NULL)
		{
			VIPTrucksUnderCheckup.dequeue(T);


			VIPTruckQueue.enqueue(T);
		}
		}
		else
		{
		if (T->getTruckMaintenanceTime() == NULL)
		{
			SpecialTrucksUnderCheckup.dequeue(T);


			SpecialTruckQueue.enqueue(T);
		}
			
		}
}

void CompanyClass::MoveTruckFromMovingToCheckup(Truck* T) //->MARIAM
{
	PriQNode<Truck*> qnode;
	PriQ <Truck*> q;
	int TDIh, TDId;
	while (MovingTrucks.peek(qnode))//!= T)
	{
		if (qnode.getItem() != T)
		{
			MovingTrucks.dequeue(qnode);
			qnode.getItem()->getTruckDeliveryInterval(TDIh, TDId);
			q.enqueueAscending(qnode.getItem(),(TDIh)+(TDId * 24));
		}
		else
		{
			break;
		}
	}
	MovingTrucks.dequeue(qnode);
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
		qnode.getItem()->getTruckDeliveryInterval(TDIh, TDId);
		MovingTrucks.enqueueAscending(qnode.getItem(),(TDIh)+(TDId * 24));
	}
}

void CompanyClass::AssignCargoToTruck()
{
	if (Hour >= 5 && Hour <= 23)
	{
		Truck* specialtruck;
		Truck* normaltruck;
		Truck* viptruck;
		
		//LOADING SPECIAL CARGO
		if (!SpecialCargos.isEmpty())
		{
			Cargo* specialcargo = nullptr;

			if (!SpecialTruckQueue.isEmpty())
			{
				SpecialTruckQueue.peek(specialtruck);

				if (SpecialCargos.getCount() >= specialtruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(specialtruck); 

					for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
					{
						SpecialCargos.dequeue(specialcargo);
						sumspecialloadtime= sumspecialloadtime+ specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
						specialtruck->LoadCargos(specialcargo);
					}
				}
				else if (SpecialCargos.getCount() > 0 && SpecialCargos.getCount() < specialtruck->getTruckCapacity())
				{
					if (getCurrentTimeHour() + (getCurrentTimeDay() * 24) >= MaxWaitHours)//add check max wait (if condition)
					{
						for (int i = 0; i < SpecialCargos.getCount(); i++)
						{
							SpecialCargos.dequeue(specialcargo);
							sumspecialloadtime = sumspecialloadtime + specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
							specialtruck->LoadCargos(specialcargo);
						}
					}
				}
			}
		}
		//LOADING NORMAL CARGO (FIRST NORMAL TRUCK THEN VIP TRUCK)
		if (!NormalCargos.isEmpty())
		{
			Cargo* normalcargo = nullptr;

			if (!NormalTruckQueue.isEmpty())
			{
				NormalTruckQueue.peek(normaltruck);

				if (NormalCargos.getCount() >= normaltruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(normaltruck);//COMMENTED TILL FUNCTION IS COMPLETE

					for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
					{
						normalcargo = NormalCargos.peek();//peek
						sumnormalloadtime = sumnormalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						normaltruck->LoadCargos(normalcargo);
					}
				}
				else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < normaltruck->getTruckCapacity())
				{
					if (getCurrentTimeHour() + (getCurrentTimeDay() * 24) >= MaxWaitHours)//add check max wait (if condition)
					{
						for (int i = 0; i < NormalCargos.getCount(); i++)
						{
							normalcargo = NormalCargos.peek();//peek
							sumnormalloadtime = sumnormalloadtime + normalcargo->getLoadTime();
							NormalCargos.DeleteBeg();
							normaltruck->LoadCargos(normalcargo);
						}
					}
				}
			}
			else if (!VIPTruckQueue.isEmpty())
			{
				VIPTruckQueue.peek(viptruck);

				if (NormalCargos.getCount() >= viptruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(viptruck);//COMMENTED TILL FUNCTION IS COMPLETE

					for (int i = 0; i < viptruck->getTruckCapacity(); i++)
					{
						normalcargo = NormalCargos.peek();
						sumnormalloadtime = sumnormalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						viptruck->LoadCargos(normalcargo);
					}
				}
				else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < viptruck->getTruckCapacity())
				{
					if (getCurrentTimeHour() + (getCurrentTimeDay() * 24) >= MaxWaitHours)//add check max wait (if condition)
					{
						for (int i = 0; i < NormalCargos.getCount(); i++)
						{
							normalcargo = NormalCargos.peek();//peek
							sumnormalloadtime = sumnormalloadtime + normalcargo->getLoadTime();
							NormalCargos.DeleteBeg();
							viptruck->LoadCargos(normalcargo);
						}
					}
				}
			}
		}
		//LOADING VIP CARGO
		if (!VIPCargoPriQueue.isEmpty())
		{
			Cargo* vipcargo = nullptr;

			if (!VIPTruckQueue.isEmpty())
			{
				VIPTruckQueue.peek(viptruck);

				if (VIPCargoPriQueue.getCount() >= viptruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(viptruck);//COMMENTED TILL FUNCTION IS COMPLETE

					for (int i = 0; i < viptruck->getTruckCapacity(); i++)
					{
						VIPCargoPriQueue.dequeue(vipcargo);
						sumviploadtime = sumviploadtime + vipcargo->getLoadTime();
						viptruck->LoadCargos(vipcargo);
					}
				}
			}
			else if (!SpecialTruckQueue.isEmpty())
			{
				SpecialTruckQueue.peek(specialtruck);

				if (VIPCargoPriQueue.getCount() >= specialtruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(specialtruck);//COMMENTED TILL FUNCTION IS COMPLETE

					for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
					{
						VIPCargoPriQueue.dequeue(vipcargo);
						sumviploadtime = sumviploadtime + vipcargo->getLoadTime();
						specialtruck->LoadCargos(vipcargo);
					}
				}
			}
			else if (!NormalTruckQueue.isEmpty())
			{
				NormalTruckQueue.peek(normaltruck);

				if (VIPCargoPriQueue.getCount() >= normaltruck->getTruckCapacity())
				{
					MoveTruckFromEmptyToLoading(normaltruck);//COMMENTED TILL FUNCTION IS COMPLETE

					for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
					{
						SpecialCargos.dequeue(vipcargo);
						sumviploadtime = sumviploadtime + vipcargo->getLoadTime();
						normaltruck->LoadCargos(vipcargo);
					}
				}
			}
		}
	}
}
/*void CompanyClass::AddToDeliveredCargos()
{
	PriQ<Cargo*> Calternative;
	PriQNode<Truck*> NodeT;
	PriQNode<Truck*> currT;
	PriQNode<Cargo*> NodeC;
	PriQNode<Cargo*> DeliveredCargoNode;
	Cargo* CargoDelivered;
	Truck* T;
	bool unloadmorecargo = true;
	int CDTH, CDTD;
	while(!MovingTrucks.isEmpty())
	{
		MovingTrucks.peek(NodeT);
		T = NodeT.getItem();
		Calternative = T->getLoadedCargosInTruck();
		while (!Calternative.isEmpty() && !unloadmorecargo)
		{
			Calternative.peek(NodeC);
			NodeC.getItem()->getCargoDeliveryTime(CDTH, CDTD);
			if (CDTH == Hour && CDTD == Day)
			{
				T->UnloadCargo(DeliveredCargoNode);
				CargoDelivered = DeliveredCargoNode.getItem();
				if (CargoDelivered->getCargoType() == 'N')
				{
					NormalDeliveredCargos.enqueue(CargoDelivered);
				}
				else if (CargoDelivered->getCargoType() == 'S')
				{
					SpecialDeliveredCargos.enqueue(CargoDelivered);
				}
				else if (CargoDelivered->getCargoType() == 'V')
				{
					VIPDeliveredCargos.enqueue(CargoDelivered);
				}
				Calternative.dequeue(NodeC);
			}
			unloadmorecargo = false;
		}
		//MovingTrucks.
	}
}*/
void CompanyClass::AddToDeliveredCargos() //trial2
{
	while (!MovingTrucks.isEmpty())
	{
		Truck* truck;
		PriQ<Truck*> ExtraMovingTruck;
		//MovingTrucks.dequeue(truck); -----------------------------------------------------------------------------

	}
}

void CompanyClass::MoveTruckFromLoadingToMoving()
{
	PriQNode<Truck*> vipnode;
	Truck* viptruck;
	int TDIh, TDId;
	if (!VIPTruckQueue.isEmpty())
	{
		//if (VIPTruckQueue.peek(vipnode))
		{
			viptruck=vipnode.getItem();
			if (viptruck->LoadedCargosFull())
			{
				VIPTruckQueue.dequeue(viptruck);
				viptruck->getTruckDeliveryInterval(TDIh, TDId);
				MovingTrucks.enqueueAscending(viptruck,(TDIh)+(TDId *24));
			}
		}
	}

}

//-------------------------------------------GETTERS----------------------------------------//
/*double CompanyClass::getCargoAvgTime()
{
	CargoAvgTime = SumAllloadTime / SumCargos;
	return CargoAvgTime;
}*/
int CompanyClass::getTotalNumberOfCargos()
{
	SumCargos = sumfinalnorm + sumfinalspec + sumfinalvip;
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
int CompanyClass::getNumberOfNormalTrucks()
{
	return nN;
}
int CompanyClass::getNumberOfspecialTrucks()
{
	return nS;
}
int CompanyClass::getNumberOfVipTrucks()
{
	return nV;
}
int CompanyClass::getnumfinalnorm()
{
	return sumfinalnorm;
}
int CompanyClass::getnumfinalspec()
{
	return sumfinalspec;
}
int CompanyClass::getnumfinalvip()
{
	return sumfinalvip;
}
int CompanyClass::getautopromnum()
{
	return noOfAutoPCargos;
}

//----------------------------------------PRINTING-------------------------------------//

void CompanyClass::printWNormalCargos()
{
	NormalCargos.printList();
}

Cargo* CompanyClass::dequeueDeliveredCargo()
{
	Cargo* deq;
	DeliveredCargos.dequeue(deq);
	return deq;
}

void CompanyClass::printWspecialCargos()
{
	SpecialCargos.PrintQueue();
}

void CompanyClass::printWvipCargos()
{
	VIPCargoPriQueue.printList();
}

/*void CompanyClass::printHeadLine()
{
	ui->coutstring("Current Time (Day:Hour)");//<----- trace el code keda
	ui->coutinteger(Day);
	ui->coutchar(':');
	ui->coutinteger(Hour);
	ui->coutendl();
}*/

/*void CompanyClass::printLnormalTrucks()
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
}*/


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

void CompanyClass::SimulatorFunction()
{
	FileLoading();
	ui->choosethemode();
	//while total no of cargos!= delivered  ,at first 0=0 quit?

	ExecuteEvents();
	//printHeadLine();
	
				//MALAK SHOULD ADD DELIVERCARGOS

				/*Truck* Normal;
				Truck* Special;
				Truck* VIP;
				LoadingNormalTrucks.peek(Normal);// add while loop to check on each truck in loading? and if list is not empty?
				LoadingSpecialTrucks.peek(Special);
				LoadingVIPTrucks.peek(VIP);
				if (Normal->getNoOfJourneys()%NoOfJourneys==0)
				{
					AddTruckToCheckup(Normal);
				}
				if (Special->getNoOfJourneys()%NoOfJourneys==0)
				{
					AddTruckToCheckup(Special);
				}
				if (VIP->getNoDeliveredCargosByTruck()%NoOfJourneys==0)
				{
					AddTruckToCheckup(VIP);
				}*/

				/*if (!NormalCargos.isEmpty())
				{
					NormalCargos.AutoPromoteCargo(this,Day,AutoPDays)

				}*/
	AssignCargoToTruck();
	MoveTruckFromLoadingToMoving();
	//MoveTruckFromMovingToCheckup();
	ui->printOutput();
	Hour++;
	while (Hour > 23) //24hour will be 00H:00MIN AM
	{
		Hour = Hour - 23;
		Day++;
	}
	ui->waitforenter(); 
	//end while loop

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

void CompanyClass::printloadingtrucks() //----------------------------------------------------------------- in checkup also
{
	int z = 0;
	ui->coutinteger(z);
	ui->coutstring(" Loading Trucks: ");
	ui->coutstring("[] ");
	ui->coutstring("() ");
	ui->coutstring("{} ");
	ui->coutendl();
}

void CompanyClass::printmovingcargos() //-----------------------------------------------------------------------
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
	LinkedQueue<Cargo*> extra;
	Cargo* car;
	ui->coutinteger(DeliveredCargos.getCount());
	ui->coutstring(" Delivered Cargos: ");
	while (!DeliveredCargos.isEmpty())
	{
		DeliveredCargos.dequeue(car);
		if (car->getCargoType() == 'N')
		{
			ui->coutchar('[');
			ui->coutinteger(car->getCargoID());
			ui->coutchar('] ');
		}
		if (car->getCargoType() == 'S')
		{
			ui->coutchar('(');
			ui->coutinteger(car->getCargoID());
			ui->coutchar(') ');
		}
		if (car->getCargoType() == 'V')
		{
			ui->coutchar('{');
			ui->coutinteger(car->getCargoID());
			ui->coutchar('} ');
		}
		extra.enqueue(car);
	}
	while (!extra.isEmpty())
	{
		extra.dequeue(car);
		DeliveredCargos.enqueue(car);
	}
}

void CompanyClass::calcCargoAvgWaitTime(int& h, int& d)
{
	h = SumWaitTimeH / SumCargos;
	d = SumWaitTimeD / SumCargos;
}

int CompanyClass::calcAutoPromotedCargos()
{
	int percentage= noOfAutoPCargos / sumfinalnorm * 100; //divided by sumfinalnorm or nopromotedcargos?
	return percentage;
}

double CompanyClass::calcAvgActiveTime()
{
	int activetime = SumTruckActiveTimeH + (SumTruckActiveTimeD * 24);
	double avgactivetime = activetime / TotalNumberOfTrucks * 100;
	return avgactivetime;
}

double CompanyClass::calcAvgUtilization()
{
	double avgUt = SumUtilization / TotalNumberOfTrucks *100;
	return avgUt;
}
CompanyClass::~CompanyClass()
{
}