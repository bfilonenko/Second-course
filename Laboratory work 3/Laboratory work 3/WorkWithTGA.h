#pragma once


#include "TGAImage.h"
#include "Geometry.h"
#include "Model.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vector3int vertex0, Vector3int vertex1, Vector3int vertex2, Vector2int textureCoordinate0, Vector2int textureCoordinate1, Vector2int textureCoordinate2, TGAImage &image, Model *model, float intensity, int *zBuffer);