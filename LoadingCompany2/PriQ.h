#pragma once
#include <iostream>
#include "PriQNode.h"
using namespace std;

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
	bool enqueueAscending(T newEntry, const int& newKey)//removed astricks before newentry
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
	bool enqueueDescending(T newEntry, const int& newKey)//removed astricks before newentry
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
	bool dequeue(PriQNode<T>& temp)
	{
		if (isEmpty())
			return false;

		temp = Head;
		Head = Head->getNext();
		return true;
	}
	//Function the checks the first element.and copies the front of this queue to the passed param.
	bool peek(PriQNode<T>& temp)
	{
		if (isEmpty())
			return false;

		temp = Head;
		return true;
	}
	//function that returns the value of first element
	T peek()
	{
		if (Head)
			return Head->getItem();
		else
			return;
	}
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
			cout << curr->getItem() << " ";
			curr = curr->getNext();

		}
		cout << endl;
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
};