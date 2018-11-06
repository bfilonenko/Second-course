#include "WorkWithModel.h"


void workWithModel(string fileName, int width, int height)
{
	Model *model = new Model(fileName);

	TGAImage image(width, height, TGAImage::RGB);

	///Wire Render
	//for (int i = 0; i < model->getNumberOfFaces(); ++i)
	//{
	//	vector<int> face = model->getFace(i);
	//	for (int j = 0; j < 3; ++j)
	//	{
	//		Vector3float vertex0 = model->getVertex(face[j]);
	//		Vector3float vertex1 = model->getVertex(face[(j + 1) % 3]);

	//		int x0 = int((vertex0.x + 1.f) * width * 0.5f);
	//		int y0 = int((vertex0.y + 1.f) * height * 0.5f);
	//		int x1 = int((vertex1.x + 1.f) * width * 0.5f);
	//		int y1 = int((vertex1.y + 1.f) * height * 0.5f);

	//		line(x0, y0, x1, y1, image, white);
	//	}
	//}

	///multi-colored model
	//for (int i = 0; i < model->getNumberOfFaces(); ++i)
	//{
	//	vector<int> face = model->getFace(i);

	//	Vector2int screenCoordinats[3];

	//	for (int j = 0; j < 3; j++)
	//	{
	//		Vector3float worldCoordinats = model->getVertex(face[j]);

	//		screenCoordinats[j] = Vector2int(int((worldCoordinats.x + 1.f) * width * 0.5f), int((worldCoordinats.y + 1.f) * height * 0.5f));
	//	}
	//	triangle(screenCoordinats[0], screenCoordinats[1], screenCoordinats[2], image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	//}

	Vector3float lightDirect(0, 0, -1);
	for (int i = 0; i < model->getNumberOfFaces(); ++i)
	{
		vector<int> face = model->getFace(i);

		Vector2int screenCoordinats[3];
		Vector3float worldCoordinats[3];

		for (int j = 0; j < 3; ++j)
		{
			Vector3float vertex = model->getVertex(face[j]);
			screenCoordinats[j] = Vector2int(int((vertex.x + 1.f) * width * 0.5f), int((vertex.y + 1.f) * height * 0.5f));
			worldCoordinats[j] = vertex;
		}

		Vector3float normal = (worldCoordinats[2] - worldCoordinats[0]) ^ (worldCoordinats[1] - worldCoordinats[0]);
		normal.normalize();

		float intensity = normal * lightDirect;
		if (intensity > 0)
		{
			triangle(screenCoordinats[0], screenCoordinats[1], screenCoordinats[2], image, TGAColor(int(intensity * 255), int(intensity * 255), int(intensity * 255), 255));
		}
	}


	image.flipVertically();
	image.writeTGAFile("output.tga");

	delete model;
}