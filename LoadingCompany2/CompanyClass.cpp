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
	noOfAutoPCargos = 0;
	SumTruckActiveTimeH = 0;
	SumTruckActiveTimeD = 0;
	SumUtilization = 0;
	sumspecialloadtime = 0;
	sumnormalloadtime = 0;
	sumviploadtime = 0;
	ui = new UIclass(this);
}
CompanyClass::CompanyClass(UIclass* uii)
{
	this->ui = uii;
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
				if (EventType == 'R')//<<<<<---------------CALL PREPARATION EVENT--------------
				{
					inFile >> CargoType;
					inFile >> EventTimeDays;
					inFile >> dummy;
					inFile >> EventTimeHours;
					inFile >> CargoID;
					inFile >> CargoDist >> CargoLoadTime >> CargoCost;
					E = new PreparationEvent(CargoType, EventTimeHours, EventTimeDays, CargoID, CargoDist, CargoLoadTime, CargoCost);
					Eventlist.enqueue(E);
					count++;
					//break;
				}
				else if (EventType == 'X')//<<<---------------CALL CANCELLATION EVENT----------------
				{
					inFile >> EventTimeDays;
					inFile >> dummy;
					inFile >> EventTimeHours;
					inFile >> CargoID;
					E = new CancelEvent(EventTimeHours, EventTimeDays, CargoID);
					Eventlist.enqueue(E);
					count++;
					//break;
				}
				else if (EventType == 'P')//<<-----------------CALL PROMOTION EVENT-------------------
				{
					inFile >> EventTimeDays;
					inFile >> dummy;
					inFile >> EventTimeHours;
					inFile >> CargoID;
					inFile >> CargoExtraMoney;
					E = new PromoteEvent(EventTimeHours, EventTimeDays, CargoID, CargoExtraMoney);
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
void CompanyClass::OutputFile()
{
	ofstream fout;
	fout.open("output.txt");
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
	fout << "[N: " << getnumfinalnorm() << ", S: " << getnumfinalspec() << ", V: " << getnumfinalvip() << "]" << endl;
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
	fout << "Avg Active time= " << calcAvgActiveTime() << '%' << endl;
	fout << "Avg utilization= " << calcAvgUtilization() << endl;
	fout.close();

}

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
//--------------------------------------------ADDING TO LISTS--------------------------------------------//
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

void CompanyClass::AddToVIPCargos(Cargo* C, double priority)
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
	if (Cl->getCargoType() == 'N')
	{
		NormalCargos.InsertEnd(Cl);
		sumfinalnorm++;
	}
	else if (Cl->getCargoType() == 'S')
	{
		SpecialCargos.enqueue(Cl);
		sumfinalspec++;
	}
	else if (Cl->getCargoType() == 'V')
	{
		VIPCargoPriority = (2 * (PrepH + PrepD) + 1 * dist) / CargoCost;
		VIPCargoPriQueue.enqueueAscending(Cl, VIPCargoPriority);
		sumfinalvip++;
	}
}

void CompanyClass::AssignSpecialCargos()
{

	if (!SpecialCargos.isEmpty())
	{
		Cargo* specialcargo = nullptr;
		PriQ<Cargo*> ExtraCargoLoad;
		if (!SpecialTruckQueue.isEmpty())
		{
			Truck* specialtruck;
			SpecialTruckQueue.peek(specialtruck);

			if (SpecialCargos.getCount() >= specialtruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
				{
					SpecialCargos.dequeue(specialcargo);
					totalloadtime = totalloadtime + specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
					ExtraCargoLoad.enqueueAscending(specialcargo, specialcargo->getDeliveringDistance());
				}
				MoveTruckFromEmptyToLoading(specialtruck, totalloadtime, ExtraCargoLoad);
			}
			else if (SpecialCargos.getCount() > 0 && SpecialCargos.getCount() < specialtruck->getTruckCapacity())
			{
				SpecialCargos.peek(specialcargo);
				int cargotime = specialcargo->getPreparationTimeHour() + (specialcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
				int currtime = Hour + (Day * 24);
				if (cargotime <= currtime)//add check max wait (if condition)//LESS THAN NOT GREATER THAN
				{
					int totalloadtime = 0;
					for (int i = 0; i < SpecialCargos.getCount(); i++)
					{
						SpecialCargos.dequeue(specialcargo);
						totalloadtime = totalloadtime + specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
						ExtraCargoLoad.enqueueAscending(specialcargo, specialcargo->getDeliveringDistance());
					}
					MoveTruckFromEmptyToLoading(specialtruck, totalloadtime, ExtraCargoLoad);
				}
			}
		}
	}
}

void CompanyClass::AssignNormalCargos()
{
	if (!NormalCargos.isEmpty())
	{
		Cargo* normalcargo = nullptr;
		PriQ<Cargo*> ExtraCargoLoad;
		if (!NormalTruckQueue.isEmpty())
		{
			Truck* normaltruck;
			NormalTruckQueue.peek(normaltruck);

			if (NormalCargos.getCount() >= normaltruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
				{
					normalcargo = NormalCargos.peek();//peek
					totalloadtime = totalloadtime + normalcargo->getLoadTime();
					NormalCargos.DeleteBeg();
					ExtraCargoLoad.enqueueAscending(normalcargo, normalcargo->getDeliveringDistance());
				}
				MoveTruckFromEmptyToLoading(normaltruck, totalloadtime, ExtraCargoLoad);
			}
			else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < normaltruck->getTruckCapacity())
			{
				normalcargo = NormalCargos.peek();
				int cargotime = normalcargo->getPreparationTimeHour() + (normalcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
				int currtime = Hour + (Day * 24);
				if (cargotime <= currtime)//add check max wait (if condition)
				{
					int totalloadtime = 0;
					for (int i = 0; i < NormalCargos.getCount(); i++)
					{
						normalcargo = NormalCargos.peek();//peek
						totalloadtime = totalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						ExtraCargoLoad.enqueueAscending(normalcargo, normalcargo->getDeliveringDistance());
					}
					MoveTruckFromEmptyToLoading(normaltruck, totalloadtime, ExtraCargoLoad);
				}
			}
		}
		else if (!VIPTruckQueue.isEmpty())
		{
			Truck* viptruck;
			VIPTruckQueue.peek(viptruck);

			if (NormalCargos.getCount() >= viptruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < viptruck->getTruckCapacity(); i++)
				{
					normalcargo = NormalCargos.peek();
					totalloadtime = totalloadtime + normalcargo->getLoadTime();
					NormalCargos.DeleteBeg();
					ExtraCargoLoad.enqueueAscending(normalcargo, normalcargo->getDeliveringDistance());
				}
				MoveTruckFromEmptyToLoading(viptruck, totalloadtime, ExtraCargoLoad);
			}
			else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < viptruck->getTruckCapacity())
			{
				normalcargo = NormalCargos.peek();
				int cargotime = normalcargo->getPreparationTimeHour() + (normalcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
				int currtime = Hour + (Day * 24);
				if (cargotime <= currtime)//add check max wait (if condition)
				{
					int totalloadtime = 0;
					for (int i = 0; i < NormalCargos.getCount(); i++)
					{
						normalcargo = NormalCargos.peek();//peek
						totalloadtime = totalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						ExtraCargoLoad.enqueueAscending(normalcargo, normalcargo->getDeliveringDistance());
					}
					MoveTruckFromEmptyToLoading(viptruck, totalloadtime, ExtraCargoLoad);
				}
			}
		}
	}
}

void CompanyClass::AssignVIPcargos()
{
	if (!VIPCargoPriQueue.isEmpty())
	{
		Cargo* vipcargo = nullptr;
		PriQ<Cargo*> ExtraCargoLoad;

		if (!VIPTruckQueue.isEmpty())
		{
			Truck* viptruck;
			VIPTruckQueue.peek(viptruck);

			if (VIPCargoPriQueue.getCount() >= viptruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < viptruck->getTruckCapacity(); i++)
				{
					PriQNode <Cargo*> vipcargonode;
					VIPCargoPriQueue.dequeue(vipcargonode);
					vipcargo = vipcargonode.getItem();
					totalloadtime = totalloadtime + (vipcargo->getLoadTime());
					ExtraCargoLoad.enqueueAscending(vipcargo, vipcargo->getDeliveringDistance());
					//viptruck->LoadCargos(vipcargo);
				}
				MoveTruckFromEmptyToLoading(viptruck, totalloadtime, ExtraCargoLoad);
			}
		}
		else if (!SpecialTruckQueue.isEmpty())
		{
			Truck* specialtruck;
			SpecialTruckQueue.peek(specialtruck);

			if (VIPCargoPriQueue.getCount() >= specialtruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
				{
					VIPCargoPriQueue.dequeue(vipcargo);
					totalloadtime = totalloadtime + vipcargo->getLoadTime();
					ExtraCargoLoad.enqueueAscending(vipcargo, vipcargo->getDeliveringDistance());
					//specialtruck->LoadCargos(vipcargo);
				}
				MoveTruckFromEmptyToLoading(specialtruck, totalloadtime, ExtraCargoLoad);
			}
		}
		else if (!NormalTruckQueue.isEmpty())
		{
			Truck* normaltruck;
			NormalTruckQueue.peek(normaltruck);

			if (VIPCargoPriQueue.getCount() >= normaltruck->getTruckCapacity())
			{
				int totalloadtime = 0;
				for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
				{
					SpecialCargos.dequeue(vipcargo);
					totalloadtime = totalloadtime + vipcargo->getLoadTime();
					ExtraCargoLoad.enqueueAscending(vipcargo, vipcargo->getDeliveringDistance());
					//normaltruck->LoadCargos(vipcargo);
				}
				MoveTruckFromEmptyToLoading(normaltruck, totalloadtime, ExtraCargoLoad);
			}
		}
	}
}

void CompanyClass::MoveTruckFromEmptyToLoading(Truck*& T, int TLD, PriQ<Cargo*>loadingcargos)
{
	if (LoadingTrucks.getCount() < 3)
	{
		int MTH = Hour + TLD;
		int MTD = Day;
		Truck* T2;
		PriQNode<Cargo*> cargonode;
		if (!NormalTruckQueue.isEmpty() && T->getTruckType() == 'N')
		{
			NormalTruckQueue.dequeue(T2);
			T->setTruckMoveTime(MTH, MTD);
			//setcargo wait time and delivery interval
			LoadingTrucks.enqueueAscending(T, MTH + (MTD * 24));
			while (!loadingcargos.isEmpty())
			{
				loadingcargos.dequeue(cargonode);
				T->LoadCargos(cargonode.getItem());
			}
		}
		else if (!VIPTruckQueue.isEmpty() && T->getTruckType() == 'V')
		{
			VIPTruckQueue.dequeue(T2);
			T->setTruckMoveTime(MTH, MTD);
			LoadingTrucks.enqueueAscending(T, MTH + (MTD * 24));
			while (!loadingcargos.isEmpty())
			{
				loadingcargos.dequeue(cargonode);
				T->LoadCargos(cargonode.getItem());
			}
		}
		else if (!SpecialTruckQueue.isEmpty() && T->getTruckType() == 'S')
		{
			SpecialTruckQueue.dequeue(T2);
			T->setTruckMoveTime(MTH, MTD);
			LoadingTrucks.enqueueAscending(T, MTH + (MTD * 24));
			while (!loadingcargos.isEmpty())
			{
				loadingcargos.dequeue(cargonode);
				T->LoadCargos(cargonode.getItem());
			}
		}
	}
}

void  CompanyClass::MoveTruckFromLoadingToMoving()
{
	while (!LoadingTrucks.isEmpty())
	{
		PriQNode<Truck*> loadingnode;
		Truck* toptruck;
		int mh, md;
		LoadingTrucks.peek(loadingnode);
		toptruck = loadingnode.getItem();
		toptruck->getTruckMoveTime(mh, md);
		if (mh == Hour && md == Day)
		{
			int h, d;
			toptruck->getLoadedCargosTop()->getCargoDeliveryTime(h, d); 
			MovingTrucks.enqueueAscending(toptruck, h + (d * 24));
			LoadingTrucks.dequeue(toptruck);
		}
		else
		{
			break;
		}
	}
}

void CompanyClass:: MoveTruckFromMovingToCheckup_or_Available(Truck * truck_finishedjourney) //Truck is back to company and empty
{
	truck_finishedjourney->AddJourney();

	if (truck_finishedjourney->getNoOfJourneys()==NoOfJourneys)    //Truck---->Maintainance 
	{
		if (truck_finishedjourney->getTruckType() == 'N')  //Normal
		{
			NormalTrucksUnderCheckup.enqueue(truck_finishedjourney);
		}

		else if (truck_finishedjourney->getTruckType() == 'S')  //Special
		{
			SpecialTrucksUnderCheckup.enqueue(truck_finishedjourney);
		}
		else if (truck_finishedjourney->getTruckType() == 'V')  //VIP
		{
			VIPTrucksUnderCheckup.enqueue(truck_finishedjourney);
		}
	}
	else                                                         //Maintainance time is not reached yet
	{
		if (truck_finishedjourney->getTruckType() == 'N')  //Normal
		{
			NormalTruckQueue.enqueue(truck_finishedjourney);
		}
		else if (truck_finishedjourney->getTruckType() == 'S')  //Special
		{
			SpecialTruckQueue.enqueue(truck_finishedjourney);
		}
		else if (truck_finishedjourney->getTruckType() == 'V')  //VIP
		{
			VIPTruckQueue.enqueue(truck_finishedjourney);
		}
	}
}

/*void CompanyClass::MoveTruckFromMovingToCheckup() //->MARIAM
{
	PriQNode<Truck*> qnode;
	PriQ <Truck*> Extra;
	int TDIh, TDId;

	while (MovingTrucks.peek(qnode))
	{
		if (qnode.getItem()->getNoOfJourneys()>=NoOfJourneys)
		{
			MovingTrucks.dequeue(qnode);
			qnode.getItem()->getTruckDeliveryInterval(TDIh, TDId);
			q.enqueueAscending(qnode.getItem(), (TDIh)+(TDId * 24));
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
		MovingTrucks.enqueueAscending(qnode.getItem(), (TDIh)+(TDId * 24));
	}
}*/
//void CompanyClass::MoveTruckFromCheckupToAvailable(Truck* T)
//{
//	if (T->getTruckType() == 'N')
//	{
//		if (T->getTruckMaintenanceTime() == NULL)
//		{
//			NormalTrucksUnderCheckup.dequeue(T);
//			NormalTruckQueue.enqueue(T);
//		}
//	}
//	else if (T->getTruckType() == 'V')
//	{
//
//		if (T->getTruckMaintenanceTime() == NULL)
//		{
//			VIPTrucksUnderCheckup.dequeue(T);
//			VIPTruckQueue.enqueue(T);
//		}
//	}
//	else
//	{
//		if (T->getTruckMaintenanceTime() == NULL)
//		{
//			SpecialTrucksUnderCheckup.dequeue(T);
//			SpecialTruckQueue.enqueue(T);
//		}
//	}
//}


void CompanyClass::MoveTruckFromCheckupToAvailable()
{
	//LinkedQueue<Truck*>Normal_temp_checkup;      
	//LinkedQueue<Truck*>Special_temp_checkup;     
	//LinkedQueue<Truck*>VIP_temp_checkup;          

	int MoveTime_H = 0;
	int MoveTime_D = 0;
	int Deliveryinterval_H = 0;
	int Deliveryinterval_D = 0;

	Truck* T;
	while (!NormalTrucksUnderCheckup.isEmpty())
	{
	
		NormalTrucksUnderCheckup.peek(T);
		T->getTruckMoveTime(MoveTime_H, MoveTime_D);
		T->getTruckDeliveryInterval(Deliveryinterval_H, Deliveryinterval_D);
		int MoveTimeTotal_inHours = MoveTime_H + (MoveTime_D * 24);
		int DeliveryIntervalTotal_inHours = Deliveryinterval_H + (Deliveryinterval_D * 24);


		if (MoveTimeTotal_inHours+DeliveryIntervalTotal_inHours+NCheckupTime==(Hour+(Day*24)))  //Checkup finished condition
		{
			NormalTrucksUnderCheckup.dequeue(T);

			NormalTruckQueue.enqueue(T);

		}
		else
		{
			//Normal_temp_checkup.enqueue(T);
			break;
		}

	}
	/*while (!Normal_temp_checkup.isEmpty())
	{
		Normal_temp_checkup.dequeue(T);
		NormalTrucksUnderCheckup.enqueue(T);

	}*/
	
	while (!SpecialTrucksUnderCheckup.isEmpty())
	{

		SpecialTrucksUnderCheckup.peek(T);
		T->getTruckMoveTime(MoveTime_H, MoveTime_D);
		T->getTruckDeliveryInterval(Deliveryinterval_H, Deliveryinterval_D);
		int MoveTimeTotal_inHours = MoveTime_H + (MoveTime_D * 24);
		int DeliveryIntervalTotal_inHours = Deliveryinterval_H + (Deliveryinterval_D * 24);

		if (MoveTimeTotal_inHours + DeliveryIntervalTotal_inHours + SCheckupTime == Hour + (Day * 24))
		{
			SpecialTrucksUnderCheckup.dequeue(T);
			SpecialTruckQueue.enqueue(T);

		}
		else
		{
			//Special_temp_checkup.enqueue(T);
			break;
		}

	}

	/*while (!Special_temp_checkup.isEmpty())
	{
		Special_temp_checkup.dequeue(T);
		SpecialTrucksUnderCheckup.enqueue(T);

	}*/
	while (!VIPTrucksUnderCheckup.isEmpty())
	{
		VIPTrucksUnderCheckup.peek(T);
		T->getTruckMoveTime(MoveTime_H, MoveTime_D);
		T->getTruckDeliveryInterval(Deliveryinterval_H, Deliveryinterval_D);
		int MoveTimeTotal_inHours = MoveTime_H + (MoveTime_D * 24);
		int DeliveryIntervalTotal_inHours = Deliveryinterval_H + (Deliveryinterval_D * 24);


		if (MoveTimeTotal_inHours + DeliveryIntervalTotal_inHours + VCheckupTime == Hour + (Day * 24))
		{
			VIPTrucksUnderCheckup.dequeue(T);
			VIPTruckQueue.enqueue(T);

		}
		else
		{
			//VIP_temp_checkup.enqueue(T);
			break;
		}


	}
	////while (!VIP_temp_checkup.isEmpty())
	//{
	//	VIP_temp_checkup.dequeue(T);
	//	VIPTrucksUnderCheckup.enqueue(T);

	//}
}
//--------------------------------------------------------------ASSIGNMENT-----------------------------------------------------------------//
void CompanyClass::AssignCargoToTruck() //DIVIDE INTO SEPARATE FUNCTIONS TO BE EASIER TO TRACE
{
	if (Hour >= 5 && Hour <= 23)
	{
		AssignVIPcargos();
		AssignSpecialCargos();
		AssignNormalCargos();
		/*Truck* specialtruck;
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
					int totalloadtime = 0;
					for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
					{
						SpecialCargos.dequeue(specialcargo);
						totalloadtime = totalloadtime + specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
						specialtruck->LoadCargos(specialcargo);
					}
					MoveTruckFromEmptyToLoading(specialtruck, totalloadtime);
				}
				else if (SpecialCargos.getCount() > 0 && SpecialCargos.getCount() < specialtruck->getTruckCapacity())
				{
					SpecialCargos.peek(specialcargo);
					int cargotime = specialcargo->getPreparationTimeHour() + (specialcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
					int currtime = Hour + (Day * 24);
					if (cargotime <= currtime)//add check max wait (if condition)//LESS THAN NOT GREATER THAN
					{
						int totalloadtime = 0;
						for (int i = 0; i < SpecialCargos.getCount(); i++)
						{
							SpecialCargos.dequeue(specialcargo);
							sumspecialloadtime = sumspecialloadtime + specialcargo->getLoadTime();//save currenttime in variable,keep checking in if condition if currenttime+cargoloadtime is currenttime
							specialtruck->LoadCargos(specialcargo);
						}
						MoveTruckFromEmptyToLoading(specialtruck, totalloadtime);
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
					int totalloadtime = 0;
					for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
					{
						normalcargo = NormalCargos.peek();//peek
						totalloadtime = totalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						normaltruck->LoadCargos(normalcargo);
					}
					MoveTruckFromEmptyToLoading(normaltruck, totalloadtime);
				}
				else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < normaltruck->getTruckCapacity())
				{
					normalcargo = NormalCargos.peek();
					int cargotime = normalcargo->getPreparationTimeHour() + (normalcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
					int currtime = Hour + (Day * 24);
					if (cargotime <= currtime)//add check max wait (if condition)
					{
						int totalloadtime = 0;
						for (int i = 0; i < NormalCargos.getCount(); i++)
						{
							normalcargo = NormalCargos.peek();//peek
							totalloadtime = totalloadtime + normalcargo->getLoadTime();
							NormalCargos.DeleteBeg();
							normaltruck->LoadCargos(normalcargo);
						}
						MoveTruckFromEmptyToLoading(normaltruck, totalloadtime);
					}
				}
			}
			else if (!VIPTruckQueue.isEmpty())
			{
				VIPTruckQueue.peek(viptruck);

				if (NormalCargos.getCount() >= viptruck->getTruckCapacity())
				{
					int totalloadtime = 0;
					for (int i = 0; i < viptruck->getTruckCapacity(); i++)
					{
						normalcargo = NormalCargos.peek();
						totalloadtime = totalloadtime + normalcargo->getLoadTime();
						NormalCargos.DeleteBeg();
						viptruck->LoadCargos(normalcargo);
					}
					MoveTruckFromEmptyToLoading(viptruck, totalloadtime);
				}
				else if (NormalCargos.getCount() > 0 && NormalCargos.getCount() < viptruck->getTruckCapacity())
				{
					normalcargo = NormalCargos.peek();
					int cargotime = normalcargo->getPreparationTimeHour() + (normalcargo->getPreparationTimeDay() * 24) + MaxWaitHours;
					int currtime = Hour + (Day * 24);
					if (cargotime <= currtime)//add check max wait (if condition)
					{
						int totalloadtime = 0;
						for (int i = 0; i < NormalCargos.getCount(); i++)
						{
							normalcargo = NormalCargos.peek();//peek
							totalloadtime = totalloadtime + normalcargo->getLoadTime();
							NormalCargos.DeleteBeg();
							viptruck->LoadCargos(normalcargo);
						}
						MoveTruckFromEmptyToLoading(viptruck, totalloadtime);
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
					int totalloadtime = 0;
					for (int i = 0; i < viptruck->getTruckCapacity(); i++)
					{
						PriQNode <Cargo*> vipcargonode;
						VIPCargoPriQueue.dequeue(vipcargonode);
						vipcargo = vipcargonode.getItem();
						totalloadtime = totalloadtime + (vipcargo->getLoadTime());
						viptruck->LoadCargos(vipcargo);
					}
					MoveTruckFromEmptyToLoading(viptruck, totalloadtime);
				}
			}
			else if (!SpecialTruckQueue.isEmpty())
			{
				SpecialTruckQueue.peek(specialtruck);

				if (VIPCargoPriQueue.getCount() >= specialtruck->getTruckCapacity())
				{
					int totalloadtime = 0;
					for (int i = 0; i < specialtruck->getTruckCapacity(); i++)
					{
						VIPCargoPriQueue.dequeue(vipcargo);
						totalloadtime = totalloadtime + vipcargo->getLoadTime();
						specialtruck->LoadCargos(vipcargo);
					}
					MoveTruckFromEmptyToLoading(specialtruck, totalloadtime);
				}
			}
			else if (!NormalTruckQueue.isEmpty())
			{
				NormalTruckQueue.peek(normaltruck);

				if (VIPCargoPriQueue.getCount() >= normaltruck->getTruckCapacity())
				{
					int totalloadtime = 0;
					for (int i = 0; i < normaltruck->getTruckCapacity(); i++)
					{
						SpecialCargos.dequeue(vipcargo);
						totalloadtime = totalloadtime + vipcargo->getLoadTime();
						normaltruck->LoadCargos(vipcargo);
					}
					MoveTruckFromEmptyToLoading(normaltruck, totalloadtime);
				}
			}
		}*/
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

int CompanyClass::getNumberOfMovingCargos()
{
	PriQ<Truck*>Extra = MovingTrucks;
	PriQNode<Truck*>TruckExtra;
	int count = MovingTrucks.getCount();
	int movingcargos = 0;
	for (int i = 0; i < count; i++)
	{
		Extra.peek(TruckExtra);
		movingcargos = movingcargos + TruckExtra.getItem()->getLoadedCargosInTruck().getCount();
		Extra.dequeue(TruckExtra);
	}
	return movingcargos;
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
//---------------------------------------------------------SIMULATION FUNCTION-------------------------------------------//
//add new function corner case check whether trucks are empty , do not continue simulation function 
bool CompanyClass::checkfunction()
{
	//bool keepchecking=true;
	if (VIPTruckQueue.isEmpty() && NormalTruckQueue.isEmpty() && SpecialTruckQueue.isEmpty())//to be removed after adding checkuptoavailabletruck
	{
		if (NormalCargos.isEmpty() && SpecialCargos.isEmpty() && VIPCargoPriQueue.isEmpty())
		{
			if (LoadingTrucks.isEmpty())//LoadingNormalTrucks.isEmpty() && LoadingSpecialTrucks.isEmpty() && LoadingVIPTrucks.isEmpty())
			{
				if (MovingTrucks.isEmpty())
				{
					if (NormalTrucksUnderCheckup.isEmpty() && SpecialTrucksUnderCheckup.isEmpty() && VIPTrucksUnderCheckup.isEmpty())
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}
void CompanyClass::SimulatorFunction()
{
	FileLoading();
	ui->choosethemode();
	while (checkfunction())
	{
		ExecuteEvents();
		AssignCargoToTruck();
		MoveTruckFromLoadingToMoving();
		//MoveTruckFromMovingToCheckup();
		if (!NormalCargos.isEmpty())
		{
			NormalCargos.AutoPromoteCargo(this, Day, AutoPDays);
		}
		ui->printOutput();
		Hour++;
		while (Hour > 23) //24hour will be 00H:00MIN AM
		{
			Hour = Hour - 23;
			Day++;
		}
	}
	//produce output file <<<----------OUTPUTFILE---------------------*/
	OutputFile();
}

//---------------------------------------------------------PHASE 1 PRINT FUNCTIONS--------------------------------------------------//
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
	//ui->coutendl();
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
	//ui->coutendl();
}

void CompanyClass::printloadingtrucks() //----------------------------------------------------------------- in checkup also
{
	int numofloadingt = LoadingTrucks.getCount();
	ui->coutinteger(numofloadingt);
	ui->coutstring(" Loading Trucks: ");
	/*if (numofloadingt == 0)
	{
		ui->coutstring("[]  ()  {}  ");
	}
	*/
	PriQNode<Truck*> trcnode;
	Truck* trc;
	PriQ<Truck*> goo = LoadingTrucks;
	for (int i = 0; i < numofloadingt; i++)
	{
		goo.dequeue(trcnode);
		trc = trcnode.getItem();
		if (trc->getCargoLoadedType() == 'N')
		{
			ui->coutinteger(trc->getTruckID());
			ui->coutchar('[');
			//for loop existed till get count of 
			trc->getLoadedCargosInTruck().printList();
			ui->coutstring("]  ");
		}
		else if (trc->getCargoLoadedType() == 'S')
		{
			ui->coutinteger(trc->getTruckID());
			ui->coutchar('(');
			trc->getLoadedCargosInTruck().printList();
			ui->coutstring(")  ");
		}
		else if (trc->getCargoLoadedType() == 'V')
		{
			ui->coutinteger(trc->getTruckID());
			ui->coutchar('{');
			trc->getLoadedCargosInTruck().printList();
			ui->coutstring("}  ");
		}
	}
}


void CompanyClass::printmovingcargos()
{
	PriQ<Truck*> gooo = MovingTrucks;
	int movingcargoscount = getNumberOfMovingCargos();
	ui->coutinteger(movingcargoscount);
	ui->coutstring(" Moving Cargos: ");
	PriQNode<Truck*> trucknodea;
	Truck* trcca;
	while (!gooo.isEmpty())
	{
		gooo.peek(trucknodea);
		trcca = trucknodea.getItem();
		if (trcca->getCargoLoadedType() == 'N')
		{
			ui->coutinteger(trcca->getTruckID());
			ui->coutchar('[');
			trcca->getLoadedCargosInTruck().printList();
			ui->coutstring("]  ");
		}
		else if (trcca->getCargoLoadedType() == 'S')
		{
			ui->coutinteger(trcca->getTruckID());
			ui->coutchar('(');
			trcca->getLoadedCargosInTruck().printList();
			ui->coutstring(")  ");
		}
		else if (trcca->getCargoLoadedType() == 'V')
		{
			ui->coutinteger(trcca->getTruckID());
			ui->coutchar('{');
			trcca->getLoadedCargosInTruck().printList();
			ui->coutstring("}  ");
		}
		gooo.dequeue(trucknodea);
	}
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
	//ui->coutendl();
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
void CompanyClass::dequeueLoadingTruck(Truck* deq)
{
	LoadingTrucks.dequeue(deq);
}
void CompanyClass::dequeueMovingTruck(Truck* deq)
{
	MovingTrucks.dequeue(deq);
}
//--------------------------------------------------OUTPUT FILE CALCULATIONS-------------------------------------------------//
void CompanyClass::calcCargoAvgWaitTime(int& h, int& d)
{
	h = SumWaitTimeH / SumCargos;
	d = SumWaitTimeD / SumCargos;
}

int CompanyClass::calcAutoPromotedCargos()
{
	int percentage = noOfAutoPCargos / sumfinalnorm * 100; //divided by sumfinalnorm or nopromotedcargos?
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
	double avgUt = SumUtilization / TotalNumberOfTrucks * 100;
	return avgUt;
}

CompanyClass::~CompanyClass()
{
}