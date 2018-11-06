#pragma once


#include "TGAImage.h"
#include "Geometry.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vector2int vertex0, Vector2int vertex1, Vector2int vertex2, TGAImage &image, TGAColor color);