#pragma once
#include"Event.h"
class PreparationEvent :public Event
{
private:
    int CargoCost;
    int LoadTime;
    int DeliveryDistance;
    char CargoType;
    Cargo* CargoReady;

public:
    PreparationEvent();
    PreparationEvent(char CargoT, int EventTimeHours, int EventTimeDays, int CargoID, int CargoDist, int LoadTimeHours, int Cost);

    void Execute(CompanyClass*Event_Executed);
    int GetCargoCost() const;
    int GetLoadTime() const;
    int GetDeliveryDistance() const;
    char GetCargoType() const;

    void SetCost(int Cost);
    void SetLoadtime(int Loadt);
    void SetDeliveryDist(int Distance);
    void SetCargotype(char t);

    ~PreparationEvent();

   
  

};

