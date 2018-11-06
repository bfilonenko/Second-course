#include "Model.h"


Model::Model(string fileName)
{
	ifstream fileIn;

	fileIn.open(fileName);
	if (fileIn.fail())
	{
		return;
	}

	string line;
	while (!fileIn.eof())
	{
		getline(fileIn, line);
		istringstream iss(line);
		
		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			
			Vector3float v;
			
			for (int i = 0; i < 3; i++)
			{
				iss >> v[i];
			}
			vertex.push_back(v);
		}
		else if (!line.compare(0, 2, "f "))
		{
			vector<int> f;

			int itrash, i;
			iss >> trash;
			
			while (iss >> i >> trash >> itrash >> trash >> itrash)
			{
				i--;
				f.push_back(i);
			}
			faces.push_back(f);
		}
	}

	cerr << "# v# " << vertex.size() << " f# " << faces.size() << std::endl;
}

Model::~Model()
{

}


int Model::getNumberOfVerts()
{
	return int(vertex.size());
}

int Model::getNumberOfFaces()
{
	return int(faces.size());
}


vector<int> Model::getFace(int i)
{
	return faces[i];
}

Vector3float Model::getVertex(int i)
{
	return vertex[i];
}