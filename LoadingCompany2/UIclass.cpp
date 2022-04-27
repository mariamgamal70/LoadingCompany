#include "UIclass.h"
#include "CompanyClass.h"
#include<iostream>
#include <fstream>
using namespace std;
UIclass::UIclass(CompanyClass* company)
{
	this->comp = company;
}
string UIclass::getidslinQcargo(LinkedQueue<Cargo*>* q)
{
	if (q->isEmpty())
	{
		return "";
	}
	LinkedQueue<Cargo*>* qu = new LinkedQueue<Cargo*>(*q);
	Cargo* temp;
	string id = "";
	Cargo* carg;
	qu->enqueue(carg);
	id += "," + to_string(carg->getCargoID());
	qu->dequeue(carg);
	while (qu->dequeue(temp))
	{
		id += "," + to_string(temp->getCargoID());
	}
	return id;
}
string UIclass::getidsPriQcargo(PriQ<Cargo*>* q)
{
	if (q->isEmpty())
	{
		return "";
	}
	PriQ<Cargo*>* qu = new PriQ<Cargo*>(*q);
	Cargo* temp;
	string id = "";
	while (qu->dequeue(temp))
	{
		id += "," + to_string(temp->getCargoID());
	}
	return id;
}
string UIclass::getidslinQtruck(LinkedQueue<Truck*>* q)
{
	if (q->isEmpty())
	{
		return "";
	}
	LinkedQueue<Truck*>* qu = new LinkedQueue<Truck*>(*q);
	Truck* temp;
	string id = "";
	Truck* truc;
	qu->enqueue(truc);
	id += "," + to_string(truc->getTruckID());
	qu->dequeue(truc);
	while (qu->dequeue(temp))
	{
		id += "," + to_string(temp->getTruckID());
	}
	return id;
}
string UIclass::getidsPriQtruck(PriQ<Truck*>* q)
{
	if (q->isEmpty())
	{
		return "";
	}
	PriQ<Truck*>* qu = new PriQ<Truck*>(*q);
	Truck* temp;
	string id = "";
	while (qu->dequeue(temp))
	{
		id += "," + to_string(temp->getTruckID());
	}
	return id;
}
string UIclass::getLinlistcargo(LinkedList<Cargo*>* lis)
{
	Node<Cargo*>* temp = lis->gethead();
	if (!temp)
	{
		return "";
	}
	string id = "";
	while (temp)
	{
		id += "," + to_string(temp->getItem()->getCargoID());
		temp = temp->next;
	}
	return id;
}
void UIclass::printwaitingcargos()
{
	LinkedList<Cargo*>* norm = comp->getNormalCargos();
	LinkedQueue<Cargo*>* special = comp->getSpecialCargos();
	PriQ<Cargo*>* vip = comp->getVIPCargos();
	int numofwait = norm->getcount() + special->getcount() + vip->getCount();
	cout << numofwait << " Waiting Cargos: ";
	cout << "[";
	cout << getLinlistcargo(norm); //normal cargos list
	cout << "]" << " ";
	cout << "(";
	cout << getidslinQcargo(special); //special Q
		cout << ")" << " ";
	cout << "{";
	cout << getidsPriQcargo(vip); //vip priQ
		cout << "}" << " ";
}
void UIclass::printInteractive()
{
	cout << "Current Time (Day:Hour): " << comp->getCurrentTimeHour() << ":" << comp->getCurrentTimeHour() << endl;
	printwaitingcargos(); 
		cout << "\n--------------------------------------------------------\n";
	//printloadingtrucks();
	cout << "\n--------------------------------------------------------\n";
	printavailtrucks();
	cout << "\n--------------------------------------------------------\n";
	//printmovingcargos();
	cout << "\n--------------------------------------------------------\n";
	printinCheckuptrucks();
	cout << "\n--------------------------------------------------------\n";
	printdeliveredcargo();
}
void UIclass::printinCheckuptrucks()
{
	LinkedQueue<Truck*>* norm = comp->getNormalTrucksUnderCheckup();
	LinkedQueue<Truck*>* special = comp->getSpecialTrucksUnderCheckup();
	LinkedQueue<Truck*>* vip = comp->getVIPTrucksUnderCheckup();
	int numcheckup = norm->getCount() + special->getCount() + vip->getCount();
	cout << numcheckup << " In-Checkup Trucks: ";
	cout << "[";
	cout << getidslinQtruck(norm);
	cout << "] ";
	cout << "{";
	cout << getidslinQtruck(special);
	cout << "} ";
	cout << "(";
	cout << getidslinQtruck(vip);
	cout << ")";
}