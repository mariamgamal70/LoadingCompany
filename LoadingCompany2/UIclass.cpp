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
	cin.get();
}

void UIclass::coutendl()
{
	cout << endl;
}
UIclass:: ~UIclass()
{

}
mode UIclass::choosethemode()
{
	cout << "Choose the mode\n1-Interactive\n2-Step-By-Step\n3-Silent" << endl;
	int option; cin >> option;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	switch (option)
	{
	case 1:
		modee = Interactive;
		return Interactive;
	case 2:
		modee = StepByStep;
		return StepByStep;
	case 3:
		modee = Silent;
		return Silent;
	default:
		break;
	}
}
void UIclass::printSilent()
{
	cout << "Silent Mode\nSimulation Starts...\nSimulation ends, Output file created";
}
void UIclass::printOutput()
{
	switch (modee)
	{
	case Interactive:
		printInteractive();
		break;
	case StepByStep:
		printInteractive();
		break;
	case Silent:
		printSilent();
		break;
	default:
		break;
	}
}
/*void UIclass::Write()
{
	fout.open(outputFile);
	fout << "CD	" << "ID	" << "FD	" << "WD	" << "ED	";
	fout << endl;
	float Wait = 0, Exec = 0;
	PriorityQueue<Mission*>* CompletedMission = new PriorityQueue<Mission*>(*station->getCompletedMissions());
	int completedNumber = station->getCompletedMissions()->getSize();
	Mission* temp;

	for (int i = 0; i < completedNumber; i++)
	{
		CompletedMission->pop(temp);
		fout << temp->getCompletionDay() << "	";
		fout << temp->getID() << "	";
		fout << temp->getEventDay() << "	";
		fout << temp->getWaitingDay() << "	";
		fout << temp->getExcutionDay() << "	";
		fout << endl;
		Wait = Wait + temp->getWaitingDay();
		Exec = Exec + temp->getExcutionDay();
	}
	fout << "\n …………………………………………………………………………………………………………………………………………… \n";
	fout << "\n …………………………………………………………………………………………………………………………………………… \n";

	fout << "Missions:" << station->getNumOfTotalMissions() << "  ";
	fout << "[M: " << station->getNumOfMounM() << ", P: " << station->getNumOfPolM() << ", E: " << station->getNumOfEmrM() << "]" << endl;

	fout << "Rovers:" << station->getNumOfTotalRovers() << "  ";
	fout << "[M: " << station->getNumOfMounR() << ", P: " << station->getNumOfPolR() << ", E: " << station->getNumOfEmrR() << "]" << endl;

	fout << "Avg Wait= ";
	fout << Wait / station->getNumOfTotalMissions() << ", ";
	fout << "Avg Exec= ";
	fout << Exec / station->getNumOfTotalMissions() << endl;

	fout << "Auto-promoted: ";
	if (station->getnumberofautoPromotedMissions() == 0)
		fout << "0";
	else
		fout << (float)station->getnumberofautoPromotedMissions() / (station->getNumOfMounM() + station->getnumberofautoPromotedMissions()) * 100;
	fout << "%" << endl;

	fout.close();
}
*/


