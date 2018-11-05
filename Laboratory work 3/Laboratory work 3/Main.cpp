#include "WorkWithTGA.h"
#include "Geometry.h"


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);


int main()
{
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	line(30, 20, 70, 40, image, white);
	image.flipVertically();
	image.writeTGAFile("output.tga");
	return 0;
}