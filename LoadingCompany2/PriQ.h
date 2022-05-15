#pragma once
#include <iostream>
#include "Cargo.h"
#include "PriQNode.h"
//#include"Cargo.h"
//#include"Truck.h"
using namespace std;


//class Cargo;
//class Truck;
template <typename T>
class PriQ
{
private:

	PriQNode<T>* Head;
	int count;

public:
	//Constructor
	PriQ()
	{
		Head = NULL;
		count = 0;
	}

	//Function that enqueues the elements sorted ASCENDING ORDER according to the key(small->big)
	bool enqueueAscending(T newEntry, const double& newKey)//removed astricks before newentry
	{
		//Creating the new node to be inserted 
		PriQNode<T>* temp = new PriQNode<T>(newEntry, newKey);
		PriQNode<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == NULL || (temp->getKey() < Head->getKey()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		count++;
		return true;
	}

	//Function that enqueues the elements sorted DESCENDING ORDER according to the key(BIG->SMALL)
	bool enqueueDescending(T newEntry, const double& newKey)//removed astricks before newentry
	{
		//Creating the new node to be inserted 
		PriQNode<T>* temp = new PriQNode<T>(newEntry, newKey);
		PriQNode<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == NULL || (temp->getKey() > Head->getKey()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != NULL && ptr->getNext()->getKey() >= temp->getKey())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		count++;
		return true;
	}
	//Function the takes out elements out of the queue
	/*bool dequeue(PriQNode<T>* temp)
	{
		if (isEmpty())
			return false;

		temp = Head;
		Head = Head->getNext();
		count--;
		return true;
	}
	*/

	bool dequeue(T value)
	{
		if (isEmpty())
			return false;

		PriQNode<T>*temp = Head;
		value = temp->getItem();

		Head = Head->getNext();
		delete temp;
		count--;
		return true;
	}

	//Function the checks the first element.and copies the front of this queue to the passed param.
	bool peek(PriQNode<T>& temp)
	{
		if (isEmpty())
			return false;

		temp = *Head;
		return true;
	}
	//function that returns the value of first element
	/*T peek()
	{
		if (Head)
			return Head->getItem();
		else
			return 0;
	}*/
	//Function that checks whether the queue is empty or not
	bool isEmpty()
	{
		return (Head == NULL);
	}
	int getCount()
	{
		return count;
	}

	void printList()
	{
		PriQNode<T>* curr = Head;
		while (curr != nullptr)
		{

		if(curr->getNext()==NULL)
		{
			cout << curr->getItem();

		}
		else
		{
		cout << curr->getItem() << ","<<" ";


		}
			curr = curr->getNext();
		}
		//cout << endl;
	}
	T getLastNode()
	{
		PriQNode<T>* prev = NULL;
		PriQNode<T>* curr = Head;
		while (curr->getNext() != nullptr)
		{
			prev = curr;
			curr = curr->getNext();
		}
		T LastNode = curr->getItem();
		return LastNode;
	}
	bool dequeue(PriQNode<T>& temp)   
	{
		if (isEmpty())
			return false;

		temp = *Head;
		Head = Head->getNext();
		count--;
		//delete temp;
		//temp = NULL;
		return true;
	}
	
};
/*	class Cargo;
	template<>
	class PriQ <Cargo*>
	{
	private:
		PriQNode<Cargo*>* Head;	//Pointer to the head of the list
		int count;
	public:
		bool dequeue(Cargo* temp)
		{
			if (isEmpty())
				return false;

			temp = Head->getItem();
			Head = Head->getNext();
			count--;
			return true;
		}
		bool isEmpty()
		{
			return (Head == NULL);
		}
		Cargo* peek()
		{
			if (Head)
				return Head->getItem();
			else
				return 0;
		}
		void printList()
		{
			PriQNode<Cargo*>* curr = Head;
			while (curr != nullptr)
			{
				cout << curr->getItem() << " ";
				curr = curr->getNext();

			}
			cout << endl;
		}
		Cargo* getLastNode()
		{
			PriQNode<Cargo*>* prev = NULL;
			PriQNode<Cargo*>* curr = Head;
			while (curr->getNext() != nullptr)
			{
				prev = curr;
				curr = curr->getNext();
			}
			Cargo* LastNode = curr->getItem();
			return LastNode;
		}
		bool enqueueAscending(Cargo* newEntry, const int& newKey)//removed astricks before newentry
		{
			//Creating the new node to be inserted 
			PriQNode<Cargo*>* temp = new PriQNode<Cargo*>(newEntry, newKey);
			PriQNode<Cargo*>* ptr;

			//If the entry is in the first place or the list is empty
			if (Head == NULL || (temp->getKey() < Head->getKey()))
			{
				temp->setNext(Head);
				Head = temp;
			}
			//General Case
			else
			{
				ptr = Head;
				while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
					ptr = ptr->getNext();

				temp->setNext(ptr->getNext());
				ptr->setNext(temp);
			}
			count++;
			return true;
		}

		//Function that enqueues the elements sorted DESCENDING ORDER according to the key(BIG->SMALL)
		bool enqueueDescending(Cargo* newEntry, const int& newKey)//removed astricks before newentry
		{
			//Creating the new node to be inserted 
			PriQNode<Cargo*>* temp = new PriQNode<Cargo*>(newEntry, newKey);
			PriQNode<Cargo*>* ptr;

			//If the entry is in the first place or the list is empty
			if (Head == NULL || (temp->getKey() > Head->getKey()))
			{
				temp->setNext(Head);
				Head = temp;
			}
			//General Case
			else
			{
				ptr = Head;
				while (ptr->getNext() != NULL && ptr->getNext()->getKey() >= temp->getKey())
					ptr = ptr->getNext();

				temp->setNext(ptr->getNext());
				ptr->setNext(temp);
			}
			count++;
			return true;

		}
		int getCount()
		{
			return count;
		}
	};*/
