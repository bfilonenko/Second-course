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


bool TGAImage::unloadRunLengthEncodingData(ofstream &fileOut)
{
	const unsigned char maxChunkLength = 128;
	unsigned long numberOfPixels = width * height;
	unsigned long currentOfPixels = 0;

	while (currentOfPixels < numberOfPixels)
	{
		unsigned long chunkStart = currentOfPixels * bytesPerPixel;
		unsigned long currentByte = currentOfPixels * bytesPerPixel;
		unsigned char runLength = 1;
		bool raw = true;

		while (currentOfPixels + runLength < numberOfPixels && runLength < maxChunkLength)
		{
			bool checker = true;
			for (int i = 0; checker && i < bytesPerPixel; ++i)
			{
				checker = (data[currentByte + i] == data[currentByte + i + bytesPerPixel]);
			}

			currentByte += bytesPerPixel;
			
			if (runLength == 1)
			{
				raw = !checker;
			}
			if (raw && checker)
			{
				--runLength;
				break;
			}
			if (!raw && !checker)
			{
				break;
			}
			++runLength;
		}

		currentOfPixels += runLength;

		fileOut.put(raw ? runLength - 1 : runLength + 127);
		if (!fileOut.good())
		{
			cerr << "can't dump the tga file\n";

			return false;
		}

		fileOut.write((char *)(data + chunkStart), (raw ? runLength * bytesPerPixel : bytesPerPixel));
		if (!fileOut.good())
		{
			cerr << "can't dump the tga file\n";

			return false;
		}
	}
	return true;
}


bool TGAImage::writeTgaFile(const char *fileName, bool runLengthEncoding)
{
	unsigned char developerAreaReference[4] = { 0, 0, 0, 0 };
	unsigned char extensionAreaReference[4] = { 0, 0, 0, 0 };
	unsigned char footer[18] = { 'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0' };

	ofstream fileOut;

	fileOut.open(fileName, ios::binary);
	if (!fileOut.is_open())
	{
		cerr << "can't open file " << fileName << "\n";

		fileOut.close();

		return false;
	}

	TGAHeader header;
	memset((void *)&header, 0, sizeof(header));

	header.bitsPerPixel = bytesPerPixel << 3;
	header.width = width;
	header.height = height;
	header.dataTypeCode = (bytesPerPixel == GRAYSCALE ? (runLengthEncoding ? 11 : 3) : (runLengthEncoding ? 10 : 2));
	header.imageDescriptor = 0x20;				//top-left origin
	
	fileOut.write((char *)&header, sizeof(header));
	if (!fileOut.good())
	{
		cerr << "can't dump the tga file\n";

		fileOut.close();

		return false;
	}

	if (!runLengthEncoding)
	{
		fileOut.write((char *)data, width * height * bytesPerPixel);
		if (!fileOut.good())
		{
			cerr << "can't unload raw data\n";

			fileOut.close();

			return false;
		}
	}
	else
	{
		if (!unloadRunLengthEncodingData(fileOut))
		{
			cerr << "can't unload rle data\n";

			fileOut.close();

			return false;
		}
	}

	fileOut.write((char *)developerAreaReference, sizeof(developerAreaReference));
	if (!fileOut.good())
	{
		cerr << "can't dump the tga file\n";

		fileOut.close();

		return false;
	}

	fileOut.write((char *)extensionAreaReference, sizeof(extensionAreaReference));
	if (!fileOut.good())
	{
		cerr << "can't dump the tga file\n";

		fileOut.close();
		
		return false;
	}

	fileOut.write((char *)footer, sizeof(footer));
	if (!fileOut.good())
	{
		cerr << "can't dump the tga file\n";

		fileOut.close();

		return false;
	}

	fileOut.close();

	return true;
}