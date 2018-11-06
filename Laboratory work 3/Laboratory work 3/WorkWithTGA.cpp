#include "WorkWithTGA.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	int derror = abs(dy) * 2;
	int error = 0;

	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
		error += derror;

		if (error > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void triangle(Vector3int vertex0, Vector3int vertex1, Vector3int vertex2, Vector2int textureCoordinate0, Vector2int textureCoordinate1, Vector2int textureCoordinate2, TGAImage &image, Model *model, float intensity, int *zBuffer)
{
	if (vertex0.y == vertex1.y && vertex1.y == vertex2.y)
	{
		return;
	}

	if (vertex0.y > vertex1.y)
	{
		swap(vertex0, vertex1);
		swap(textureCoordinate0, textureCoordinate1);
	}
	if (vertex0.y > vertex2.y)
	{
		swap(vertex0, vertex2);
		swap(textureCoordinate0, textureCoordinate2);
	}
	if (vertex1.y > vertex2.y)
	{
		swap(vertex1, vertex2);
		swap(textureCoordinate1, textureCoordinate2);
	}

	int height = vertex2.y - vertex0.y;
	for (int i = 0; i <= height; ++i)
	{
		bool secondHalf = vertex0.y + i > vertex1.y || vertex0.y == vertex1.y;

		int segmentHeight = secondHalf ? vertex2.y - vertex1.y : vertex1.y - vertex0.y;

		float alpha = float(i) / height,
			beta = float(i - (secondHalf ? vertex1.y - vertex0.y : 0)) / segmentHeight;

		Vector3int vectorA = vertex0 + Vector3float(vertex2 - vertex0) * alpha,
			vectorB = secondHalf ? vertex1 + Vector3float(vertex2 - vertex1) * beta : vertex0 + Vector3float(vertex1 - vertex0) * beta;

		Vector2int textureCoordinateA = textureCoordinate0 + (textureCoordinate2 - textureCoordinate0) * alpha,
			textureCoordinateB = secondHalf ? textureCoordinate1 + (textureCoordinate2 - textureCoordinate1) * beta : textureCoordinate0 + (textureCoordinate1 - textureCoordinate0) * beta;

		if (vectorA.x > vectorB.x)
		{
			swap(vectorA, vectorB);
			swap(textureCoordinateA, textureCoordinateB);
		}

		for (int j = vectorA.x; j <= vectorB.x; ++j)
		{
			float phi = vectorA.x == vectorB.x ? 1.f : float(j - vectorA.x) / float(vectorB.x - vectorA.x);
			
			Vector3int p = Vector3float(vectorA) + Vector3float(vectorB - vectorA) * phi;
			Vector2int textureCoordinateP = textureCoordinateA + (textureCoordinateB - textureCoordinateA) * phi;

			int index = p.x + p.y * image.getWidth();

			if (zBuffer[index] < p.z)
			{
				zBuffer[index] = p.z;

				TGAColor color = model->getDiffuse(textureCoordinateP);

				image.set(p.x, p.y, color * intensity);
			}
		}
	}

}