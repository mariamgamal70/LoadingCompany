#pragma once
#include "Event.h"
class Preparation :
    public Event
{
private:
    //int DIST;
    //int LT;
    //int Cost;
    char Ready;
    Cargo c;

public:
    Preparation();
    ~Preparation();
  /*  void SetDIST(); //use setdistance of Class Cargo and make it equal to our cargo
    void SetLT();
   
    void SetCost();
    int GetLT();
    int GetCost();*/
    void SetCargo(); //calls constructor of class cargo using our cargo
    Cargo GetCargo();
    void IsLetter(char ch);
    void Execute(Cargo c);

};

