#pragma once
#include "Cargo.h"
#include "LinkedList.h"
class CargoLinkedList :public LinkedList<Cargo*>
{
	//Node<Cargo*>* Head;
	//int countc;
public:
	CargoLinkedList()
	{
		Head = nullptr;
		count = 0;
	}
	void DeleteSpecificNode(int& value)
	{
		Node<Cargo*>* temp = Head;
		if (temp == nullptr)
			return;
		if (temp->getNext() == NULL)
		{
			if (temp->getItem()->getCargoID() == value)
			{
				delete temp;
				temp = NULL;
				Head = NULL;
			}
		}
		else
		{
			Node<Cargo*>* curr = temp->getNext();
			while (curr)
			{
				if (curr->getItem()->getCargoID() == value)
				{
					temp->setNext(curr->getNext());
					delete curr;
					curr = nullptr;
					break;

				}
				temp = curr;
				curr = curr->getNext(); //FY warning hena ya sherif
			}
		}
	}

	Cargo* findSpecificNode(int& value)
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
				if (temp->getItem()->getCargoID()==value)
				{
					c = temp->getItem();
					return c;
				}
				temp = temp->getNext();
			}
		}
	}
	/*void InsertEndC(Cargo* data)
	{
		if (count==0) //emptylist
		{
			InsertBegC(data);
		}
		else
		{
			Node<Cargo*>* P = Head;
			while (P->getNext() != nullptr)
			{
				P = P->getNext();
			}
			Node<Cargo*>* R = new Node<Cargo*>(data);
			R->setNext(nullptr);
			P->setNext(R);
		}
	}*/

     void InsertBegC(Cargo* C)  
	 {
		Node<Cargo*>* R = new Node<Cargo*>(C);
		R->setNext(Head);
		Head = R;
		count++;
	 }
	 Cargo* getHead()
	 {
		 return Head->getItem();
	 }

};
