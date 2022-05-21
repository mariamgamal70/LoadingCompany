#ifndef _LINKEDLIST
#define _LINKEDLIST
#pragma once

#include"Cargo.h"
#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class LinkedList
{
protected:
	Node<T>* Head;	//Pointer to the head of the list
	int count;
	//You can add tail pointer too (depending on your problem)
public:
	LinkedList()
	{
		Head = nullptr;
		count = 0;
	}
	~LinkedList()//List is being desturcted ==> delete all items in the list
	{
		DeleteAll();
	}
	void InsertBeg(const T& data)//Creates a new node and adds it to the beginning of a linked list,
	//data : The value to be stored in the new node.

	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}

	void DeleteAll()//Deletes all nodes of the list.
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}
	/*void InsertEnd(const T& data) //Create new node at the end of the list
	{
		Node<T>* R = new Node<T>(data);
		Node<T>* curr = Head;
		if (!Head)
		{
			Head = R;
			R->setNext(NULL);
		}
		else
		{
			while (curr->getNext() != nullptr)
			{
				curr = curr->getNext();
			}
			curr->setNext(R);
			R->setNext(NULL);
		}
		count++;
	}*/
	void InsertEnd(const T& data)
	{
		if (!Head) //emptylist
		{
			InsertBeg(data);
		}
		else
		{
			Node<T>* P = Head;
			while (P->getNext() != nullptr)
			{
				P = P->getNext();
			}
			Node<T>* R = new Node<T>(data);
			R->setNext(nullptr);
			P->setNext(R);
		}
		count++;
	}

	void printList()
	{
		Node<T>* curr = Head;
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
	}

	bool peek(Node<T>& c)
	{
		if (!Head)
			return false;
		else
		{
			c = Head->getItem();
			return true;
		}
	}

	void DeleteSpecificNode(const T& value) //CHECK COUNT DECREMENTENTATION
	{
		Node<T>* temp = Head;
		if (temp == nullptr)
			return;

		if (temp->getNext() == NULL)
		{
			if (temp->getItem() == value)
			{
				delete temp;
				temp = NULL;
				Head = NULL;
				count--;
			}
		}
		else
		{
			Node<T>* curr = temp->getNext();
			while (curr)
			{
				if (curr->getItem() == value)
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

	void DeleteBeg()
	{
		if (!Head)
			return;
		Node<T>* temp = Head;
		if (Head->getNext() != nullptr)
		{
			Head = Head->getNext();
			delete temp;
			temp = nullptr;
		}
		else
		{
			delete Head;
			Head = nullptr;
		}
		count--;
	}

	void DeleteEnd()
	{
		if (!Head)
			return;
		Node<T>* prev = Head;
		if (Head->getNext() == NULL)
		{
			delete Head;
			Head = NULL;
		}
		else
		{
			Node<T>* curr = prev->getNext();
			while (curr->getNext() != NULL)
			{
				prev = curr;
				curr = curr->getNext();
			}
			prev->setNext(curr->getNext());
			delete curr;
			curr = NULL;
		}
		count--;
	}

	int getCount()
	{
		return count;
	}

	T getLastNode()
	{
		if (!Head)
			return;

		if (Head->getNext() == NULL)
			return(Head->getItem());

		Node<T>* curr = Head;
		while (curr->getNext() != nullptr)
		{
			curr = curr->getNext();
		}
		return (curr->getItem());
	}
	bool isEmpty()
	{
		if (!Head)
			return true;
		else
			return false;
	}
};

#endif