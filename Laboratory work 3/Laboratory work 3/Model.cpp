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

	loadTexture(fileName, "_nm.tga", normalMap);

	loadTexture(fileName, "_spec.tga", specularMap);
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

Vector3float Model::getVertex(int faceIndex, int numberOfVertex)
{
	return vertex[faces[faceIndex][numberOfVertex][0]];
}


Vector3float Model::getNorm(int faceIndex, int numberOfVertex)
{
	int index = faces[faceIndex][numberOfVertex][2];
	return norms[index].normalize();
}

Vector3float Model::getNorm(Vector2float textureCoordinate)
{
	Vector2int temp(int(textureCoordinate[0] * normalMap.getWidth()), int(textureCoordinate[1] * normalMap.getHeight()));

	TGAColor color = normalMap.get(temp[0], temp[1]);

	Vector3float result;

	for (int i = 0; i < 3; i++)
	{
		result[2 - i] = (float)color[i] / 255.f * 2.f - 1.f;
	}

	return result;
}


Vector2float Model::getTextureCoordinate(int faceIndex, int numberOfVertex)
{
	return textureCoordinates[faces[faceIndex][numberOfVertex][1]];
}

TGAColor Model::getDiffuse(Vector2float textureCoordinate)
{
	Vector2int temp(int(textureCoordinate[0] * diffuseMap.getWidth()), int(textureCoordinate[1] * diffuseMap.getHeight()));

	return diffuseMap.get(temp[0], temp[1]);
}

float Model::getSpecular(Vector2float textureCoordinate)
{
	Vector2int temp(int(textureCoordinate[0] * specularMap.getWidth()), int(textureCoordinate[1] * specularMap.getHeight()));
	
	return specularMap.get(temp[0], temp[1])[0] / 1.f;
}