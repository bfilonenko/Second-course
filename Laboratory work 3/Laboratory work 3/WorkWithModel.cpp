#include "WorkWithModel.h"


void workWithModel(string fileName, int width, int height)
{
	Model *model = new Model(fileName);

	TGAImage image(width, height, TGAImage::RGB);

	for (int i = 0; i < model->getNumberOfFaces(); ++i)
	{
		vector<int> face = model->getFace(i);
		for (int j = 0; j < 3; ++j)
		{
			Vector3float vertex0 = model->getVertex(face[j]);
			Vector3float vertex1 = model->getVertex(face[(j + 1) % 3]);

			int x0 = int((vertex0.x + 1.f) * width * 0.5f);
			int y0 = int((vertex0.y + 1.f) * height * 0.5f);
			int x1 = int((vertex1.x + 1.f) * width * 0.5f);
			int y1 = int((vertex1.y + 1.f) * height * 0.5f);

			line(x0, y0, x1, y1, image, white);
		}
	}

	image.flipVertically();
	image.writeTGAFile("output.tga");

	delete model;
}