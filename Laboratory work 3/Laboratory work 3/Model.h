#pragma once


#include <vector>
#include <fstream>
#include <sstream>
#include "Geometry.h"
#include "TGAImage.h"


class Model
{
	vector<Vector3float> vertex;
	vector<vector<Vector3int> > faces;
	
	vector<Vector3float> norms;
	vector<Vector2float> textureCoordinates;

	TGAImage diffuseMap;


	void loadTexture(string fileName, string suffix, TGAImage &image);

public:
	Model(string fileName);

	~Model();

	int getNumberOfVerts();
	int getNumberOfFaces();

	Vector3float getVertex(int i);
	vector<int> getFace(int i);

	Vector2int getTextureCoordinate(int faceIndex, int numberOfVertex);

	TGAColor getDiffuse(Vector2int textureCoordinate);
};