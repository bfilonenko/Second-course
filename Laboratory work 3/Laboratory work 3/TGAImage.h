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
	unsigned char bgra[4];
	unsigned char bytesPerPixel;


	TGAColor() : bytesPerPixel(1)
	{
		for (int i = 0; i < 4; ++i)
		{
			bgra[i] = 0;
		}
	}
		
	TGAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : bytesPerPixel(4)
	{
		bgra[0] = b;
		bgra[1] = g;
		bgra[2] = r;
		bgra[3] = a;
	}

	TGAColor(unsigned char value) : bytesPerPixel(1)
	{
		for (int i = 1; i < 4; ++i)
		{
			bgra[i] = 0;
		}
		bgra[0] = value;
	}

	TGAColor(const unsigned char *p, int bytesPerPixel) : bytesPerPixel(bytesPerPixel)
	{
		for (int i = 0; i < int(bytesPerPixel); ++i)
		{
			bgra[i] = p[i];
		}
		for (int i = int(bytesPerPixel); i < 4; ++i)
		{
			bgra[i] = 0;
		}
	}

	TGAColor operator * (float intensity) const
	{
		TGAColor result = *this;

		intensity = (intensity > 1.f ? 1.f : (intensity < 0.f ? 0.f : intensity));

		for (int i = 0; i < 4; ++i)
		{
			result.bgra[i] = unsigned char(bgra[i] * intensity);
		}
		return result;
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


	int getWidth();

	int getHeight();


	bool flipHorizontally();
	
	bool flipVertically();

	
	bool readTGAFile(const char *filename);

	bool writeTGAFile(const char *fileName, bool runLengthEncoding = true);
};