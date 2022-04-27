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
	cout << "Current Time (Day:Hour): " << comp->getCurrentTimeHour() << ":" << comp->getCurrentTimeHour() << endl;
	comp->printwaitingcargos(); 
	cout << "\n--------------------------------------------------------\n";
	//printloadingtrucks();
	cout << "\n--------------------------------------------------------\n";
	//printavailtrucks();
	cout << "\n--------------------------------------------------------\n";
	//printmovingcargos();
	cout << "\n--------------------------------------------------------\n";
	comp->printcheckuptruck();
	cout << "\n--------------------------------------------------------\n";
	//printdeliveredcargo();
}
void UIclass::coutinteger(int m)
{
	cout << m;
}
void UIclass::coutstring(string k)
{
	cout << "k";
}
void UIclass::coutchar(char s)
{
	cout << 's';
}
//void UIclass::waitforenter()
//{
//	cin.get();
//}
/*void UIclass::coutendl()
{
	cout << endl;
}
*/

