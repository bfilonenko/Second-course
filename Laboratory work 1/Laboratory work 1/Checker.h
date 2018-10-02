#pragma once


#include "ListOnLinkedList.h"
#include "CyclicListOnLinkedList.h"
#include "ListOnDynamicArray.h"
#include "CyclicListOnDynamicArray.h"
#include "ListOnLibraryFunction.h"
#include "CyclicListOnLibraryFunction.h"


template<typename T>
void checker(List<T> &list, bool(*criterion)(T))
{
	string help = "Available commands: \n-1 - exit\n0 - showMenu\n1 - showAll\n2 - pushBack(number)\n3 - popBack\n4 - pushFront(number)\n5 - popFront\n\
6 - addElement(number, position)\n7 - deleteElement(position)\n8 - getElement(position)\n9 - getIndex(value)\n10 - reverse\n11 - clear\n12 - addRandomElements\n\
13 - getSize\n14 - getElememtMetchingCriterion\n";
	cout << help;
	while (true)
	{
		T number;
		int massage;
		cin >> massage;
		if (massage == -1)
		{
			break;
		}
		else if (massage == 0)
		{
			cout << help;
		}
		else if (massage == 1)
		{
			list.showAll();
		}
		else if (massage == 2)
		{
			cin >> number;
			list.pushBack(number);
		}
		else if (massage == 3)
		{
			list.popBack();
		}
		else if (massage == 4)
		{
			cin >> number;
			list.pushFront(number);
		}
		else if (massage == 5)
		{
			list.popFront();
		}
		else if (massage == 6)
		{
			int position;
			cin >> number >> position;
			list.addElement(number, position);
		}
		else if (massage == 7)
		{
			int position;
			cin >> position;
			list.deleteElement(position);
		}
		else if (massage == 8)
		{
			int position;
			cin >> position;
			if (list.getElement(position) == T())
			{
				cout << "Error: element not found\n";
			}
			else
			{
				cout << list.getElement(position) << '\n';
			}
		}
		else if (massage == 9)
		{
			cin >> number;
			cout << list.getIndex(number) << '\n';
		}
		else if (massage == 10)
		{
			list.reverse();
		}
		else if (massage == 11)
		{
			list.clear();
		}
		else if (massage == 12)
		{
			list.addRandomElements();
		}
		else if (massage == 13)
		{
			cout << list.getSize() << '\n';
		}
		else if (massage == 14)
		{
			if (list.getElememtMetchingCriterion(criterion) == T())
			{
				cout << "Error: element not found\n";
			}
			else
			{
				cout << list.getElememtMetchingCriterion(criterion) << '\n';
			}
		}

		cout << "**********************************\n";
	}
}