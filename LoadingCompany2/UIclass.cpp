#include "UIclass.h"
#include "CompanyClass.h"
#include<iostream>
#include <fstream>

using namespace std;
UIclass::UIclass(CompanyClass* company)
{
	this->comp = company;
}

void UIclass::printInteractive()
{
	//cout << "Current Time (Day:Hour): " << comp->getCurrentTimeHour() << ":" << comp->getCurrentTimeHour() << endl;
	comp->printwaitingcargos(); 
	cout << "\n--------------------------------------------------------\n";
	comp->printloadingtrucks();
	cout << "\n--------------------------------------------------------\n";
	comp->printavailtrucks();
	cout << "\n--------------------------------------------------------\n";
	comp->printmovingcargos();
	cout << "\n--------------------------------------------------------\n";
	comp->printcheckuptruck();
	cout << "\n--------------------------------------------------------\n";
	comp->printdeliveredcargo();
}
void UIclass::coutinteger(int m)
{
	cout << m;
}
void UIclass::coutstring(string k)
{
	cout << k;
}
void UIclass::coutchar(char s)
{
	cout << s;
}
string UIclass::cinfilename () 
{
    string inFile;
	cin >> inFile;
	inFile = inFile + ".txt";
	cout << endl;
	fin.open(inFile);
	while (!fin.is_open()) 
	{
		cout << "File is not found, Please re-enter the file you want to load: ";
		cin >> inFile;
		inFile = inFile + ".txt";
		fin.open(inFile);
	}
	return inFile;
}
void UIclass::printline()
{
	cout << "-----------------------------------------------------------------------------" << endl;
}
void UIclass::waitforenter()
{
	//char c;
	cin.get();
}

void UIclass::coutendl()
{
	cout << endl;
}


