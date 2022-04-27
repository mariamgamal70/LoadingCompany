#pragma once
#include "Cargo.h"
#include "LinkedList.h"//dy class gedida  hya nafs el linked list fya kol 7agat el linked list ma3ada delete node, shofy eza me7tageen peek specialized lel cargo wala la2
class CargoLinkedList :public LinkedList<Cargo*>// da 3ashan delete node, le event cancellation
{//nafs el class da ba2a e7temal ne7tag ne3mel zayo priQ sepecific lel cargo
	Node<Cargo*>* Head;// leeh dh class gdyyd hn3ml fyh eh??    efta7y meeting yala dlwa2tyy link 3al whatsapp
public:
	CargoLinkedList()
	{
		Head = nullptr;
	}
	void DeleteSpecificNode(int& value)
	{
		//Node<Cargo*> top;
		//peek(top);
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


};
