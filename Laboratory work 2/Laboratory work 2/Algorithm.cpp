#include "Algorithm.h"

AlgorithmParameter::AlgorithmParameter()
{
	operations = 0;
	length = 0;

	next = nullptr;
}

AlgorithmParameter::~AlgorithmParameter()
{
	if (next != nullptr)
	{
		delete next;
	}
}


void Algorithm::goToBack()
{
	if (story.size() > 1)
	{
		story[story.size() - 2].next = new AlgorithmParameter(story[story.size() - 1]);
		story.pop_back();
	}
}

void Algorithm::save(string &name)
{
	ofstream fileOut(string("Data/Saved/" + name + ".dat"));

	fileOut << story.size() << "\n";

	for (int i = 0; i < story.size(); ++i)
	{
		fileOut << story[i].oldPositionOfMainIndex.size() << ' ';
		for (int j = 0; j < story[i].oldPositionOfMainIndex.size(); ++j)
		{
			fileOut << story[i].oldPositionOfMainIndex[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].mainIndexes.size() << ' ';
		for (int j = 0; j < story[i].mainIndexes.size(); ++j)
		{
			fileOut << story[i].mainIndexes[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].indexForHighlight.size() << ' ';
		for (int j = 0; j < story[i].indexForHighlight.size(); ++j)
		{
			fileOut << story[i].indexForHighlight[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].indexes.size() << ' ';
		for (int j = 0; j < story[i].indexes.size(); ++j)
		{
			fileOut << story[i].indexes[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].operations << ' ' << story[i].length << '\n';
		for (int j = 0; j < story[i].arrayOfValues.size(); ++j)
		{
			fileOut << story[i].arrayOfValues[j].first << ' ' << story[i].arrayOfValues[j].second << ' ';
		}
		fileOut << '\n';
	}
	if (story.size() > 0 && story.back().next != nullptr)
	{
		fileOut << 1;

		fileOut << story.back().next->oldPositionOfMainIndex.size() << ' ';
		for (int j = 0; j < story.back().next->oldPositionOfMainIndex.size(); ++j)
		{
			fileOut << story.back().next->oldPositionOfMainIndex[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story.back().next->mainIndexes.size() << ' ';
		for (int j = 0; j < story.back().next->mainIndexes.size(); ++j)
		{
			fileOut << story.back().next->mainIndexes[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story.back().next->indexForHighlight.size() << ' ';
		for (int j = 0; j < story.back().next->indexForHighlight.size(); ++j)
		{
			fileOut << story.back().next->indexForHighlight[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story.back().next->indexes.size() << ' ';
		for (int j = 0; j < story.back().next->indexes.size(); ++j)
		{
			fileOut << story.back().next->indexes[j] << ' ';
		}
		fileOut << '\n';

		fileOut << story.back().next->operations << ' ' << story.back().next->length << '\n';
		for (int j = 0; j < story.back().next->arrayOfValues.size(); ++j)
		{
			fileOut << story.back().next->arrayOfValues[j].first << ' ' << story.back().next->arrayOfValues[j].second << ' ';
		}
		fileOut << '\n';
	}

	fileOut.close();
}

void Algorithm::download(string &name)
{
	ifstream fileIn;
	fileIn.open(string("Data/Saved/" + name + ".dat"));

	if (fileIn)
	{
		story.clear();

		int length;
		fileIn >> length;

		for (int i = 0; i < length; ++i)
		{
			AlgorithmParameter temp;

			int tempLength, tempValue;
			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.oldPositionOfMainIndex.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.mainIndexes.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.indexForHighlight.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.indexes.push_back(tempValue);
			}

			fileIn >> temp.operations >> temp.length;
			for (int j = 0; j < temp.length; ++j)
			{
				int tempValue2;
				fileIn >> tempValue >> tempValue2;

				temp.arrayOfValues.push_back({ tempValue, tempValue2 });
			}
			story.push_back(temp);
		}
		bool needNext;
		fileIn >> needNext;
		if (needNext)
		{
			AlgorithmParameter temp;

			int tempLength, tempValue;
			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.oldPositionOfMainIndex.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.mainIndexes.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.indexForHighlight.push_back(tempValue);
			}

			fileIn >> tempLength;
			for (int j = 0; j < tempLength; ++j)
			{
				fileIn >> tempValue;
				temp.indexes.push_back(tempValue);
			}

			fileIn >> temp.operations >> temp.length;
			for (int j = 0; j < temp.length; ++j)
			{
				int tempValue2;
				fileIn >> tempValue >> tempValue2;

				temp.arrayOfValues.push_back({ tempValue, tempValue2 });
			}

			story[story.size() - 2].next = new AlgorithmParameter(temp);
		}

		fileIn.close();
	}
}

AlgorithmParameter *Algorithm::getStruct()
{
	return &story.back();
}