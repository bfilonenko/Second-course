#include "SelectionSort.h"


SelectionSort::SelectionSort()
{
	AlgorithmParameter algorithm;

	//mainIndexes 0 this i
	//mainIndexes 1 this j
	//mainIndexes 2 this k

	algorithm.mainIndexes.push_back(1);
	algorithm.mainIndexes.push_back(1);
	algorithm.mainIndexes.push_back(0);

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

SelectionSort::SelectionSort(vector<int> &values)
{
	AlgorithmParameter algorithm;

	//mainIndexes 0 this i
	//mainIndexes 1 this j
	//mainIndexes 2 this k

	algorithm.mainIndexes.push_back(1);
	algorithm.mainIndexes.push_back(1);
	algorithm.mainIndexes.push_back(0);

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

SelectionSort::~SelectionSort()
{
	story.clear();
}

void SelectionSort::goToNext()
{
	AlgorithmParameter algorithm(*getStruct());

	if (algorithm.mainIndexes.size() != 0 && algorithm.mainIndexes[2] < algorithm.length - 1)
	{
		algorithm.oldPositionOfMainIndex.clear();

		if (algorithm.indexForHighlight.size() > 0)
		{
			algorithm.indexForHighlight.clear();

			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

			++algorithm.mainIndexes[2];
			algorithm.mainIndexes[0] = algorithm.mainIndexes[2] + 1;
			algorithm.mainIndexes[1] = algorithm.mainIndexes[2] + 1;
		}
		else if (algorithm.arrayOfValues[algorithm.mainIndexes[1]].first < algorithm.arrayOfValues[algorithm.mainIndexes[0]].first)
		{
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
			algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

			algorithm.mainIndexes[0] = algorithm.mainIndexes[1];
		}
		else
		{
			if (algorithm.mainIndexes[1] < algorithm.length - 1)
			{
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);
				++algorithm.mainIndexes[1];
			}
			else if (algorithm.arrayOfValues[algorithm.mainIndexes[2]] > algorithm.arrayOfValues[algorithm.mainIndexes[0]])
			{
				swap(algorithm.arrayOfValues[algorithm.mainIndexes[2]], algorithm.arrayOfValues[algorithm.mainIndexes[0]]);

				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[0]);
				algorithm.indexForHighlight.push_back(algorithm.mainIndexes[2]);
			}
			else
			{
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[0]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[1]);
				algorithm.oldPositionOfMainIndex.push_back(algorithm.mainIndexes[2]);

				++algorithm.mainIndexes[2];
				algorithm.mainIndexes[0] = algorithm.mainIndexes[2] + 1;
				algorithm.mainIndexes[1] = algorithm.mainIndexes[2] + 1;
			}
		}


		++algorithm.operations;

		if (algorithm.next != nullptr)
		{
			delete algorithm.next;
			algorithm.next = nullptr;

			story.back().next = nullptr;
		}

		if (algorithm.mainIndexes[2] == algorithm.length - 1)
		{
			algorithm.mainIndexes.clear();
			algorithm.oldPositionOfMainIndex.clear();
		}

		story.push_back(algorithm);
	}
}