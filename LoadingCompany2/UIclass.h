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
	/*string getidslinQcargo(LinkedQueue<Cargo*>* q);
	string getidsPriQcargo(PriQ<Cargo*>* q);
	string getidslinQtruck(LinkedQueue<Truck*>* q);
	string getidsPriQtruck(PriQ<Truck*>* q);
	string getLinlistcargo(LinkedList<Cargo*>* lis);
	void printwaitingcargos();
	void printbeingdeliveredcargos();
	void printavailtrucks();
	void printinCheckuptrucks();
	void printdeliveredcargo();
	void printInteractive();	//Print Output in interactive
	void getinput();	//Open the inputs.txt file and read the data
	~UIclass();

	void coutinteger (int m);
	void coutstring (string "k"");
	void coutchar (char 's');
	
};
