#pragma once


#include <fstream>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <math.h>


using namespace std;


#pragma pack(push,1)
struct TGAHeader {
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char  bitsPerPixel;
	char  imageDescriptor;
};
#pragma pack(pop)


struct TGAColor
{
	unsigned char r, g, b, a;


	TGAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a)
	{
	
	}

	TGAColor &operator= (const TGAColor &right)
	{
		if (this != &right) {
			r = right.r;
			g = right.g;
			b = right.b;
			a = right.a;
		}
		return *this;
	}
};


class TGAImage
{
	unsigned char* data;
	int width;
	int height;
	int bytesPerPixel;

	bool unloadRunLengthEncodingData(ofstream &fileOut);

public:
	enum Format
	{
		GRAYSCALE = 1,
		RGB = 3,
		RGBA = 4
	};

	TGAImage();
	TGAImage(int width, int height, int bytesPerPixel);
	TGAImage(const TGAImage &image);

	~TGAImage();

	bool writeTgaFile(const char *fileName, bool runLengthEncoding = true);
};