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
				count--;
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
				curr = curr->getNext(); 
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

     void InsertBegC(Cargo* C)  
	 {
		Node<Cargo*>* R = new Node<Cargo*>(C);
		R->setNext(Head);
		Head = R;
		count++;
	 }
	 Cargo* peek()
	 {
		 return Head->getItem();
	 }

};
