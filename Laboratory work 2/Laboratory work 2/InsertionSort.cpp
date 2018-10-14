#include "InsertionSort.h"


InsertionSort::InsertionSort()
{
	forConstructor(20);
}

void InsertionSort::forConstructor(int number)
{
	AlgorithmParameter algorithm;

	//mainIndexes 0 this i
	//mainIndexes 1 this j
	//indexes 0 this k

	algorithm.mainIndexes.push_back(1);
	algorithm.mainIndexes.push_back(0);

	algorithm.indexes.push_back(1);

	algorithm.length = number;

	vector<int> temp;

	for (int i = 0; i < number; ++i)
	{
		temp.push_back(rand() % 50);
	}

	vector<int> temp2(temp);
	sort(temp2.begin(), temp2.end());

	for (int i = 0; i < number; ++i)
	{
		int index = -1;
		for (int j = 0; j < number && index == -1; ++j)
		{
			if (temp[i] == temp2[j])
			{
				index = j;
			}
		}

		algorithm.arrayOfValues.push_back({ temp[i], index });
	}

	story.push_back(algorithm);
}

void InsertionSort::goToNext()
{
	AlgorithmParameter algorithm(*getStruct());

	if (algorithm.indexes[0] < algorithm.length)
	{
		algorithm.oldPositionOfMainIndex.clear();
	
		if (algorithm.indexForHighlight.size() == 0)
		{
			if (algorithm.arrayOfValues[algorithm.mainIndexes[1]].first > algorithm.arrayOfValues[algorithm.mainIndexes[0]].first)
			{
				swap(algorithm.arrayOfValues[algorithm.mainIndexes[1]], algorithm.arrayOfValues[algorithm.mainIndexes[0]]);

				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[0]);
				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[1]);
			}
			else
			{
				algorithm.indexForHighlight.clear();

				++algorithm.indexes[0];

				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);

				algorithm.mainIndexes[0] = algorithm.indexes[0];
				algorithm.mainIndexes[1] = algorithm.indexes[0] - 1;
			}
		}
		else
		{
			algorithm.indexForHighlight.clear();

			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);

			if (algorithm.mainIndexes[0] > 1)
			{
				--algorithm.mainIndexes[0];
				--algorithm.mainIndexes[1];
			}
			else
			{
				++algorithm.indexes[0];

				algorithm.mainIndexes[0] = algorithm.indexes[0];
				algorithm.mainIndexes[1] = algorithm.indexes[0] - 1;
			}
		}
		
		++algorithm.operations;

		if (algorithm.next != nullptr)
		{
			delete algorithm.next;
			algorithm.next = nullptr;
		}

		story.push_back(algorithm);
	}
}