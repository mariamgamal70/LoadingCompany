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
#include <iostream>
#ifdef _WIN32
#include <Windows.h>

enum mode
{
	Interactive=1,
	StepByStep=2,
	Silent=3
};
using namespace std;
class CompanyClass;

class UIclass
{
private:
	ofstream fout;
	ifstream fin;
	mode modee;
	CompanyClass* comp;
	string output="OUTPUT.txt";
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
	*/
	
	void printInteractive();	//Print Output in interactive
	//void getinput();	//Open the inputs.txt file and read the data
	void coutinteger(int m);
    void coutstring(string k);
    void coutchar(char s);
    void coutendl();
	void waitforenter();
	string cinfilename();
	void printline();
    ~UIclass();
	mode choosethemode();
		void printSilent();
		void printOutput();
		void Write();
};
#endif
