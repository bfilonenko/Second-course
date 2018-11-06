#include "WorkWithModel.h"


void workWithModel(string fileName, int width, int height, int depth)
{
	Model *model = new Model(fileName);

	TGAImage image(width, height, TGAImage::RGB);


	int *zBuffer = new int[width * height];

	for (int i = 0; i < width * height; ++i)
	{
		zBuffer[i] = numeric_limits<int>::min();
	}


	Vector3float lightDirect = Vector3float(1, -1, 1).normalize();
	Vector3float eye(1, 1, 3);
	Vector3float center(0, 0, 0);

	Matrix modelView = lookat(eye, center, Vector3float(0, 1, 0));
	Matrix projection = Matrix::identity(4);
	Matrix viewPort = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);

	projection[3][2] = -1.f / (eye - center).norm();

	cerr << modelView << '\n';
	cerr << projection << '\n';
	cerr << viewPort << '\n';

	Matrix temp = (viewPort * projection * modelView);

	cerr << temp << '\n';

	for (int i = 0; i < model->getNumberOfFaces(); ++i)
	{
		vector<int> face = model->getFace(i);

		Vector3int screenCoordinats[3];
		Vector3float worldCoordinats[3];

		float intensity[3];

		for (int j = 0; j < 3; ++j)
		{
			Vector3float vertex = model->getVertex(face[j]);
			screenCoordinats[j] = Vector3int(Vector3float(viewPort * projection * modelView * Matrix(vertex)));
			worldCoordinats[j] = vertex;
			intensity[j] = model->getNorm(i, j) * lightDirect;
		}

		triangle(screenCoordinats[0], screenCoordinats[1], screenCoordinats[2], intensity[0], intensity[1], intensity[2], image, zBuffer);
	}


	TGAImage zBufferImage(width, height, TGAImage::GRAYSCALE);

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			zBufferImage.set(i, j, TGAColor(zBuffer[i + j * width]));
		}
	}

	zBufferImage.flipVertically();
	zBufferImage.writeTGAFile("zbuffer.tga");


	image.flipVertically();
	image.writeTGAFile("output.tga");

	delete model;

	delete[] zBuffer;
}