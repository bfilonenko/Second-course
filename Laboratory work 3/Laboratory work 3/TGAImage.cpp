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


TGAColor TGAImage::get(int x, int y)
{
	if (data == nullptr || x < 0 || y < 0 || x >= width || y >= height)
	{
		return TGAColor();
	}
	return TGAColor(data + (x + y * width) * bytesPerPixel, bytesPerPixel);
}

bool TGAImage::set(int x, int y, TGAColor color)
{
	if (data == nullptr || x < 0 || y < 0 || x >= width || y >= height)
	{
		return false;
	}

	memcpy(data + (x + y * width) * bytesPerPixel, color.raw, bytesPerPixel);
	
	return true;
}


int TGAImage::getWidth()
{
	return width;
}

int TGAImage::getHeight()
{
	return height;
}


bool TGAImage::flipHorizontally()
{
	if (data == nullptr)
	{
		return false;
	}

	int half = width >> 1;
	for (int i = 0; i < half; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			TGAColor color1 = get(i, j);
			TGAColor color2 = get(width - 1 - i, j);
			set(i, j, color2);
			set(width - 1 - i, j, color1);
		}
	}

	return true;
}

bool TGAImage::flipVertically()
{
	if (data == nullptr)
	{
		return false;
	}

	unsigned long bytesPerLine = width * bytesPerPixel;
	unsigned char *line = new unsigned char[bytesPerLine];

	int half = height >> 1;
	for (int i = 0; i < half; ++i)
	{
		unsigned long line1 = i * bytesPerLine;
		unsigned long line2 = (height - 1 - i) * bytesPerLine;

		memmove((void *)line, (void *)(data + line1), bytesPerLine);
		memmove((void *)(data + line1), (void *)(data + line2), bytesPerLine);
		memmove((void *)(data + line2), (void *)line, bytesPerLine);
	}

	delete[] line;

	return true;
}


bool TGAImage::loadRunLengthEncodingData(ifstream &fileIn)
{
	unsigned long pixelCount = width * height;
	unsigned long currentPixel = 0;
	unsigned long currentByte = 0;

	TGAColor colorbuffer;
	do
	{
		unsigned char chunkHeader = 0;

		chunkHeader = fileIn.get();
		if (!fileIn.good())
		{
			cerr << "an error occured while reading the data\n";

			return false;
		}

		if (chunkHeader < 128)
		{
			++chunkHeader;
			for (int i = 0; i < chunkHeader; ++i)
			{
				fileIn.read((char *)colorbuffer.raw, bytesPerPixel);
				if (!fileIn.good())
				{
					cerr << "an error occured while reading the header\n";

					return false;
				}

				for (int j = 0; j < bytesPerPixel; ++j)
				{
					data[currentByte++] = colorbuffer.raw[j];
				}

				++currentPixel;
				if (currentPixel > pixelCount)
				{
					cerr << "Too many pixels read\n";

					return false;
				}
			}
		}
		else
		{
			chunkHeader -= 127;

			fileIn.read((char *)colorbuffer.raw, bytesPerPixel);
			if (!fileIn.good())
			{
				cerr << "an error occured while reading the header\n";

				return false;
			}

			for (int i = 0; i < chunkHeader; ++i)
			{
				for (int j = 0; j < bytesPerPixel; ++j)
				{
					data[currentByte++] = colorbuffer.raw[j];
				}

				currentPixel++;
				if (currentPixel > pixelCount)
				{
					cerr << "Too many pixels read\n";

					return false;
				}
			}
		}
	}
	while (currentPixel < pixelCount);

	return true;
}

bool TGAImage::readTGAFile(const char *filename)
{
	if (data != nullptr)
	{
		delete[] data;
	}
	data = nullptr;

	ifstream fileIn;

	fileIn.open(filename, ios::binary);
	if (!fileIn.is_open())
	{
		cerr << "can't open file " << filename << "\n";

		fileIn.close();

		return false;
	}

	TGAHeader header;

	fileIn.read((char *)&header, sizeof(header));
	if (!fileIn.good())
	{
		cerr << "an error occured while reading the header\n";

		fileIn.close();

		return false;
	}

	width = header.width;
	height = header.height;

	bytesPerPixel = header.bitsPerPixel >> 3;

	if (width <= 0 || height <= 0 || (bytesPerPixel != GRAYSCALE && bytesPerPixel != RGB && bytesPerPixel != RGBA))
	{
		cerr << "bad bytesPerPixel (or width/height) value\n";

		fileIn.close();

		return false;
	}

	unsigned long numberOfBytes = bytesPerPixel * width * height;
	data = new unsigned char[numberOfBytes];

	if (header.dataTypeCode = 3|| header.dataTypeCode == 2)
	{
		fileIn.read((char *)data, numberOfBytes);
		if (!fileIn.good())
		{
			cerr << "an error occured while reading the data\n";

			fileIn.close();

			return false;
		}
	}
	else if (header.dataTypeCode == 10 || header.dataTypeCode == 11)
	{
		if (!loadRunLengthEncodingData(fileIn))
		{
			cerr << "an error occured while reading the data\n";
			
			fileIn.close();

			return false;
		}
	}
	else
	{
		cerr << "unknown file format " << (int)header.dataTypeCode << "\n";
	
		fileIn.close();

		return false;
	}

	if (!(header.imageDescriptor &0x20))
	{
		flipVertically();
	}

	if (header.imageDescriptor &0x10)
	{
		flipHorizontally();
	}

	cerr << width << "x" << height << "/" << bytesPerPixel * 8 << "\n";
	
	fileIn.close();
	
	return true;
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

bool TGAImage::writeTGAFile(const char *fileName, bool runLengthEncoding)
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