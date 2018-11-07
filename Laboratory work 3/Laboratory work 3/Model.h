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
	TGAImage normalMap;
	TGAImage specularMap;

	void loadTexture(string fileName, string suffix, TGAImage &image);

public:
	Model(string fileName);

	~Model();

	int getNumberOfVerts();
	int getNumberOfFaces();

	Vector3float getVertex(int i);
	Vector3float getVertex(int faceIndex, int numberOfVertex);

	vector<int> getFace(int i);
	
	Vector3float getNorm(int faceIndex, int numberOfVertex);
	Vector3float getNorm(Vector2float textureCoordinate);

	Vector2float getTextureCoordinate(int faceIndex, int numberOfVertex);

	TGAColor getDiffuse(Vector2float textureCoordinate);

	float getSpecular(Vector2float textureCoordinate);
};