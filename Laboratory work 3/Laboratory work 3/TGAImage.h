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
	union
	{
		struct
		{

			unsigned char b, g, r, a;
		};
		unsigned char raw[4];
		unsigned int value;
	};
	int bytesPerPixel;


	TGAColor() : value(0), bytesPerPixel(1)
	{

	}

	TGAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a), bytesPerPixel(4)
	{
	
	}

	TGAColor(int value, int bytesPerPixel) : value(value), bytesPerPixel(bytesPerPixel)
	{

	}

	TGAColor(const TGAColor &color) : value(color.value), bytesPerPixel(color.bytesPerPixel)
	{

	}

	TGAColor(const unsigned char *p, int bytesPerPixel) : value(0), bytesPerPixel(bytesPerPixel)
	{
		for (int i = 0; i < bytesPerPixel; ++i)
		{
			raw[i] = p[i];
		}
	}

	TGAColor &operator= (const TGAColor &right)
	{
		if (this != &right)
		{
			bytesPerPixel = right.bytesPerPixel;
			value = right.value;
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

	bool loadRunLengthEncodingData(ifstream &fileIn);

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
	

	TGAColor get(int x, int y);

	bool set(int x, int y, TGAColor color);


	bool flipHorizontally();
	
	bool flipVertically();

	
	bool readTGAFile(const char *filename);

	bool writeTGAFile(const char *fileName, bool runLengthEncoding = true);
};