#include "TGAImage.h"


TGAImage::TGAImage() : data(nullptr), width(0), height(0), bytesPerPixel(0)
{

}

TGAImage::TGAImage(int width, int height, int bytesPerPixel) : data(nullptr), width(width), height(height), bytesPerPixel(bytesPerPixel)
{
	unsigned long numberOfBytes = width * height * bytesPerPixel;
	data = new unsigned char[numberOfBytes];
	memset(data, 0, numberOfBytes);
}

TGAImage::TGAImage(const TGAImage &image)
{
	width = image.width;
	height = image.height;
	bytesPerPixel = image.bytesPerPixel;
	unsigned long numberOfBytes = width * height * bytesPerPixel;
	data = new unsigned char[numberOfBytes];
	memcpy(data, image.data, numberOfBytes);
}

TGAImage::~TGAImage()
{
	if (data != nullptr)
	{
		delete[] data;
	}
}