#pragma once
#include"CargoLinkedList.h"
#include"CompanyClass.h"


CargoLinkedList::CargoLinkedList()
{

}

void CargoLinkedList:: DeleteSpecificNode(int& value) 
{
	Node<Cargo*>* temp = nullptr;
	Node<Cargo*>* curr = Head;
	if (curr == nullptr)
		return;
	if (curr->getItem()->getCargoID() == value)
	{
		Head = curr->getNext();
		curr = nullptr;
		delete curr;
		count--;
	}
	else
	{
		temp = curr;
		curr = curr->getNext();
		while (curr && curr->getNext() != nullptr)
		{
			if (curr->getItem()->getCargoID() == value)
			{
				temp->setNext(curr->getNext());
				delete curr;
				curr = nullptr;
				count--;
				break;
			}
			temp = curr;
			curr = curr->getNext();
		}
	}
}


Cargo* CargoLinkedList:: findSpecificNode(int& value)
{
	Cargo* c = nullptr;
	Node<Cargo*>* temp = Head;

	if (temp == NULL)
	{
		return c;
	}
	else
	{
		while (temp)
		{
			if (temp->getItem()->getCargoID() == value)
			{
				c = temp->getItem();
				return c;
			}
			temp = temp->getNext();
		}
	}
}



void CargoLinkedList:: InsertBegC(Cargo* C)
{
	Node<Cargo*>* R = new Node<Cargo*>(C);
	R->setNext(Head);
	Head = R;
	count++;
}
Cargo* CargoLinkedList::peek()
{
	return Head->getItem();
}


void CargoLinkedList :: AutoPromoteCargo(CompanyClass* company_ptr, int Currentday, int Autopromote_days)
{
	Node<Cargo*>* ptr = Head;
	while (ptr)
	{
		if ((Currentday)-(ptr->getItem()->getPreparationTimeDay()) > Autopromote_days)
		{
			Cargo* Cargo_toAutoPromote = ptr->getItem();
			int Cargo_Idpromote = Cargo_toAutoPromote->getCargoID();
			company_ptr->PromoteCargo(Cargo_Idpromote);
		}
	}
}
