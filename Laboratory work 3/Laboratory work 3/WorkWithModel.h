#pragma once


#include "Model.h"
#include "WorkWithTGA.h"


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);


void workWithModel(string fileName, int width, int height, int depth);