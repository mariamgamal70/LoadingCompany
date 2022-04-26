#pragma once
#include "Event.h"
//#include"CompanyClass.h"
class CompanyClass;
class PreparationEvent :public Event
{
private:
    //Event* E;
    //int DIST;
    //int LT;
    //int Cost;
    //char Ready;
    //  CompanyClass* AddToList;
     //   Cargo* c;
    int CargoCost;
    int LoadTime;
    int DeliveryDistance;
    char CargoType;

public:
    PreparationEvent();
    PreparationEvent(char CargoT, int EventTimeHours, int EventTimeDays, int CargoID, int CargoDist, int LoadTimeHours, int Cost);
    void Execute();


    int GetCargoCost() const;
    int GetLoadTime() const;
    int GetDeliveryDistance() const;
    char GetCargoType() const;

    void SetCost(int Cost);
    void SetLoadtime(int Loadt);
    void SetDeliveryDist(int Distance);
    void SetCargotype(char t);

    ~PreparationEvent();




    // PreparationEvent();
   /*void SetDIST(Cargo c, int d); //use setdistance of Class Cargo and make it equal to our cargo
   void SetLT(Cargo c, int lt);

   void SetCost(Cargo c, int co);
   int GetLT(Cargo c);
   int GetCost(Cargo c);
   //void SetCargoOfExecute(Cargo c, char type, int lt, int dc, int dd, int td, int th);

   int GetDist(Cargo c);
   //void Execute(LinkedQueue<Cargo> Lspecial, LinkedQueue<Cargo> Lnormal, LinkedQueue<Cargo> Lvip, char type, int lt, int dc, int dd, int td, int th); //missing add to "appropriate list"
  */

};

