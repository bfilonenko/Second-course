#include "QuickSort.h"


QuickSort::QuickSort()
{
	AlgorithmParameter algorithm;

	//mainIndexes 0 this l
	//mainIndexes 1 this r
	//mainIndexes 2 this i
	//indexes 0 this b
	//indexes 1 this e
	//indexes 2 this needSwap
	//indexes 3 this needSwap
	//indexes 4 this end of stack
	//indexes 5, 6, .... this stack

	algorithm.mainIndexes.push_back(0);
	algorithm.mainIndexes.push_back(9);
	algorithm.mainIndexes.push_back(4);

	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(9);
	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(-1);

	algorithm.length = 10;

	vector<int> temp;

	for (int i = 0; i < 10; ++i)
	{
		temp.push_back(rand() % 50);
	}

	vector<int> temp2(temp);
	sort(temp2.begin(), temp2.end());

	for (int i = 0; i < 10; ++i)
	{
		int index = -1;
		for (int j = 0; j < 10 && index == -1; ++j)
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

QuickSort::QuickSort(vector<int> &values)
{
	AlgorithmParameter algorithm;

	//mainIndexes 0 this l
	//mainIndexes 1 this r
	//mainIndexes 2 this i
	//indexes 0 this b
	//indexes 1 this e
	//indexes 2 this needSwap
	//indexes 3 this needSwap
	//indexes 4 this end of stack
	//indexes 5, 6, .... this stack

	algorithm.mainIndexes.push_back(0);
	algorithm.mainIndexes.push_back(int(values.size()) - 1);
	algorithm.mainIndexes.push_back((int(values.size()) - 1) / 2);

	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(int(values.size()) - 1);
	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(0);
	algorithm.indexes.push_back(-1);

	algorithm.length = int(values.size());

	vector<int> temp2(values);
	sort(temp2.begin(), temp2.end());

	for (int i = 0; i < values.size(); ++i)
	{
		int index = -1;
		for (int j = 0; j < values.size() && index == -1; ++j)
		{
			if (values[i] == temp2[j])
			{
				index = j;
			}
		}

		algorithm.arrayOfValues.push_back({ values[i], index });
	}

	story.push_back(algorithm);
}

QuickSort::~QuickSort()
{
	story.clear();
}

//mainIndexes 0 this l
//mainIndexes 1 this r
//mainIndexes 2 this i
//indexes 0 this b
//indexes 1 this e
//indexes 2 this needSwap
//indexes 3 this finish
//indexes 4 this end of stack
//indexes 5, 6, .... this stack

void QuickSort::goToNext()
{
	AlgorithmParameter algorithm(*getStruct());

	if (algorithm.indexes[3] == 0)
	{
		algorithm.oldPositionOfMainIndex.clear();
		algorithm.indexForHighlight.clear();

		if (algorithm.indexes[2] == 0)
		{
			if (algorithm.arrayOfValues[algorithm.mainIndexes[0]].first < algorithm.arrayOfValues[algorithm.mainIndexes[2]].first)
			{
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

				++algorithm.mainIndexes[0];
			}
			else if (algorithm.arrayOfValues[algorithm.mainIndexes[1]].first > algorithm.arrayOfValues[algorithm.mainIndexes[2]].first)
			{
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

				--algorithm.mainIndexes[1];
			}
			else if (algorithm.mainIndexes[0] <= algorithm.mainIndexes[1])
			{
				swap(algorithm.arrayOfValues[algorithm.mainIndexes[0]], algorithm.arrayOfValues[algorithm.mainIndexes[1]]);

				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[0]);
				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[1]);
				algorithm.indexes[2] = 1;
			}
			else
			{
				if (algorithm.indexes[0] < algorithm.mainIndexes[1])
				{
					algorithm.indexes.push_back(algorithm.indexes[0]);
					algorithm.indexes.push_back(algorithm.mainIndexes[1]);
				}
				if (algorithm.indexes[1] > algorithm.mainIndexes[0])
				{
					algorithm.indexes.push_back(algorithm.mainIndexes[0]);
					algorithm.indexes.push_back(algorithm.indexes[1]);
				}

				if (algorithm.indexes.back() != -1)
				{
					algorithm.indexes[1] = algorithm.indexes.back();
					algorithm.indexes.pop_back();
					algorithm.indexes[0] = algorithm.indexes.back();
					algorithm.indexes.pop_back();

					algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
					algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
					algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

					algorithm.mainIndexes[0] = algorithm.indexes[0];
					algorithm.mainIndexes[1] = algorithm.indexes[1];
					algorithm.mainIndexes[2] = (algorithm.mainIndexes[0] + algorithm.mainIndexes[1]) / 2;

				}
				else
				{
					algorithm.indexes[3] = 1;
					algorithm.mainIndexes.clear();
					algorithm.oldPositionOfMainIndex.clear();
				}
			}
		}
		else
		{
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

			++algorithm.mainIndexes[0];
			--algorithm.mainIndexes[1];
			algorithm.indexes[2] = 0;
		}


		++algorithm.operations;

		if (algorithm.next != nullptr)
		{
			delete algorithm.next;
			algorithm.next = nullptr;

			story.back().next = nullptr;
		}

		story.push_back(algorithm);
	}
}