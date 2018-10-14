#include "Algorithm.h"

AlgorithmParameter::AlgorithmParameter()
{
	int operations = 0;
	int length = 0;
}


void Algorithm::goToBack()
{
	story.pop_back();
}

void Algorithm::save(string &name)
{
	ofstream fileOut(string("Data/" + name + ".dat"));

	fileOut << story.size() << "\n";

	for (int i = 0; i < story.size(); ++i)
	{
		fileOut << story[i].oldPositionOfMainIndex.size() << ' ';
		for (int j = 0; j < story[i].oldPositionOfMainIndex.size(); ++i)
		{
			fileOut << story[i].oldPositionOfMainIndex[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].mainIndexes.size() << ' ';
		for (int j = 0; j < story[i].mainIndexes.size(); ++i)
		{
			fileOut << story[i].mainIndexes[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].indexForHighlight.size() << ' ';
		for (int j = 0; j < story[i].indexForHighlight.size(); ++i)
		{
			fileOut << story[i].indexForHighlight[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].indexes.size() << ' ';
		for (int j = 0; j < story[i].indexes.size(); ++i)
		{
			fileOut << story[i].indexes[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].operations << ' ' << story[i].length << '\n';

		fileOut << story[i].arrayOfValues.size() << ' ';
		for (int j = 0; j < story[i].arrayOfValues.size(); ++i)
		{
			fileOut << story[i].arrayOfValues[i].first << ' ' << story[i].arrayOfValues[i].first << ' ';
		}
		fileOut << '\n';
	}
}

void Algorithm::download(string &name)
{
	ifstream fileIn(string("Data/" + name + ".dat"));

	int length;
	fileIn >> length;

	for (int i = 0; i < length; ++i)
	{
		AlgorithmParameter temp;

		int tempLength, tempValue;
		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			fileIn >> tempValue;
			temp.oldPositionOfMainIndex.push_back(tempValue);
		}

		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			fileIn >> tempValue;
			temp.mainIndexes.push_back(tempValue);
		}

		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			fileIn >> tempValue;
			temp.indexForHighlight.push_back(tempValue);
		}

		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			fileIn >> tempValue;
			temp.indexes.push_back(tempValue);
		}

		fileIn >> temp.operations >> temp.length;

		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			int tempValue2;
			fileIn >> tempValue >> tempValue2;

			temp.arrayOfValues.push_back({ tempValue, tempValue2 });
		}
		story.push_back(temp);
	}
}

AlgorithmParameter *Algorithm::getStruct()
{
	return &story.back();
}