#pragma once
#include <fstream>
#include "LinkedQueue.h"
#include "PriQ.h"
#include "LinkedList.h"
#include "Event.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include <string>
#include "Truck.h"
#include "Cargo.h"


using namespace std;
class CompanyClass;

class UIclass
{
private:
	ofstream fout;
	ifstream fin;
	CompanyClass* comp;
public:
	UIclass(CompanyClass* company);
	int getidslinQcargo(LinkedQueue<Cargo*>* q);
	int getidsPriQcargo(PriQ<Cargo*>* q);
	int getidslinQtruck(LinkedQueue<Truck*>* q);
	int getidsPriQtruck(PriQ<Truck*>* q);
	int getLinlistcargo(LinkedList<Cargo*>* lis);
	void printwaitingcargos();
	void printbeingdeliveredcargos();
	void printavailtrucks();
	void printinCheckuptrucks();
	void printdeliveredcargo();
	void printInteractive();	//Print Output in interactive
	void write();   //open txt file and Write data
	void getinput();	//Open the inputs.txt file and read the data
	~UIclass();
	
};
