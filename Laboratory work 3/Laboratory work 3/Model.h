#pragma once


#include <vector>
#include <fstream>
#include <sstream>
#include "Geometry.h"


class Model
{
	vector<Vector3float> vertex;
	vector<vector<int> > faces;
	
public:
	Model(const char *fileName);

	~Model();

	int getNumberOfVerts();
	int getNumberOfFaces();

	Vector3float getVertex(int i);
	vector<int> getFace(int i);
};