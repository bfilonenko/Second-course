#include "Algorithm.h"

AlgorithmParameter::AlgorithmParameter()
{
	int length = 0;
}


void Algorithm::save(string &name)
{
	ofstream fileOut(string("Data/" + name + ".dat"));

	fileOut << story.size() << "\n";

	for (int i = 0; i < story.size(); ++i)
	{
		fileOut << story[i].mainIndexes.size() << ' ';
		for (int j = 0; j < story[i].mainIndexes.size(); ++i)
		{
			fileOut << story[i].mainIndexes[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].indexes.size() << ' ';
		for (int j = 0; j < story[i].indexes.size(); ++i)
		{
			fileOut << story[i].indexes[i] << ' ';
		}
		fileOut << '\n';

		fileOut << story[i].length << '\n';

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
			temp.mainIndexes.push_back(tempValue);
		}

		fileIn >> tempLength;
		for (int j = 0; j < tempLength; ++i)
		{
			fileIn >> tempValue;
			temp.indexes.push_back(tempValue);
		}

		fileIn >> temp.length;

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