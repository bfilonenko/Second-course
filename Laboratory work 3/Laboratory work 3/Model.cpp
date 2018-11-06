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
			
			Vector3float vector;
			
			for (int i = 0; i < 3; ++i)
			{
				iss >> vector[i];
			}
			vertex.push_back(vector);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;

			Vector3float norm;

			for (int i = 0; i < 3; ++i)
			{
				iss >> norm[i];
			}
			norms.push_back(norm);
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;

			Vector2float textureCoordinate;

			for (int i = 0; i < 2; ++i)
			{
				iss >> textureCoordinate[i];
			}
			textureCoordinates.push_back(textureCoordinate);
		}
		else if (!line.compare(0, 2, "f "))
		{
			vector<Vector3int> face;

			Vector3int temp;

			iss >> trash;
			
			while (iss >> temp[0] >> trash >> temp[1] >> trash >> temp[2])
			{
				for (int i = 0; i < 3; ++i)
				{
					--temp[i];
				}
				
				face.push_back(temp);
			}
			faces.push_back(face);
		}
	}

	cerr << "# v# " << vertex.size() << " f# " << faces.size() << " vt# " << textureCoordinates.size() << " vn# " << norms.size() << '\n';

	loadTexture(fileName, "_diffuse.tga", diffuseMap);
}


void Model::loadTexture(string filename, string suffix, TGAImage &image)
{
	string texfile(filename);

	size_t dot = texfile.find_last_of(".");

	if (dot != string::npos)
	{
		texfile = texfile.substr(0, dot) + suffix;

		cerr << "texture file " << texfile << " loading " << (image.readTGAFile(texfile.c_str()) ? "ok" : "failed") << '\n';
		
		image.flipVertically();
	}
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
	vector<int> face;

	for (int j = 0; j < int(faces[i].size()); ++j)
	{
		face.push_back(faces[i][j][0]);
	}

	return face;
}

Vector3float Model::getVertex(int i)
{
	return vertex[i];
}


Vector2int Model::textureCoordinate(int faceIndex, int numberOfVertex)
{
	int index = faces[faceIndex][numberOfVertex][1];
	return Vector2int(int(textureCoordinates[index].x * float(diffuseMap.getWidth())), int(textureCoordinates[index].y * float(diffuseMap.getHeight())));
}

TGAColor Model::diffuse(Vector2int textureCoordinate)
{
	return diffuseMap.get(textureCoordinate.x, textureCoordinate.y);
}
