#include "WorkWithModel.h"


Matrix4float modelView;
Matrix4float viewPort;
Matrix4float projection;


IShader::~IShader() {}


void setViewport(int x, int y, int width, int height)
{
	viewPort = Matrix4float::identity();
	viewPort[0][3] = x + width / 2.f;
	viewPort[1][3] = y + height / 2.f;
	viewPort[2][3] = 255.f / 2.f;
	viewPort[0][0] = width / 2.f;
	viewPort[1][1] = height / 2.f;
	viewPort[2][2] = 255.f / 2.f;
}

void setProjection(float coefficient)
{
	projection = Matrix4float::identity();
	projection[3][2] = coefficient;
}

void lookat(Vector3float eye, Vector3float center, Vector3float up)
{
	Vector3float z = (eye - center).normalize();
	Vector3float x = cross(up, z).normalize();
	Vector3float y = cross(z, x).normalize();

	Matrix4float Minv = Matrix4float::identity();
	Matrix4float Tr = Matrix4float::identity();
	
	for (int i = 0; i < 3; i++)
	{
		Minv[0][i] = x[i];
		Minv[1][i] = y[i];
		Minv[2][i] = z[i];
		Tr[i][3] = -center[i];
	}
	modelView = Minv * Tr;
}


Vector3float barycentric(Vector2float A, Vector2float B, Vector2float C, Vector2float P)
{
	Vector3float s[2];

	for (int i = 2; i--; )
	{
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}

	Vector3float u = cross(s[0], s[1]);

	if (abs(u[2]) > 1e-2)
	{
		return Vector3float(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	}

	return Vector3float(-1, 1, 1);
}


void triangle(Vector4float *pts, IShader &shader, TGAImage &image, TGAImage &zbuffer, Model *model)
{
	Vector2float boundingBoxMin(numeric_limits<float>::max(), numeric_limits<float>::max());
	Vector2float boundingBoxMax(-numeric_limits<float>::max(), -numeric_limits<float>::max());

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			boundingBoxMin[j] = min(boundingBoxMin[j], pts[i][j] / pts[i][3]);
			boundingBoxMax[j] = max(boundingBoxMax[j], pts[i][j] / pts[i][3]);
		}
	}

	Vector2int p;

	TGAColor color;

	for (p.x = int(boundingBoxMin.x); p.x <= boundingBoxMax.x; p.x++)
	{
		for (p.y = int(boundingBoxMin.y); p.y <= boundingBoxMax.y; p.y++)
		{
			Vector3float c = barycentric(proj<2>(pts[0] / pts[0][3]), proj<2>(pts[1] / pts[1][3]), proj<2>(pts[2] / pts[2][3]), proj<2>(p));

			float z = pts[0][2] * c.x + pts[1][2] * c.y + pts[2][2] * c.z;
			float w = pts[0][3] * c.x + pts[1][3] * c.y + pts[2][3] * c.z;
			
			int fragDepth = max(0, min(255, int(z / w + 0.5f)));
			
			if (c.x < 0 || c.y < 0 || c.z<0 || zbuffer.get(p.x, p.y)[0] > fragDepth)
			{
				continue;
			}

			bool discard = shader.fragment(c, color, model);
			if (!discard)
			{
				zbuffer.set(p.x, p.y, TGAColor(fragDepth));
				image.set(p.x, p.y, color);
			}
		}
	}
}



void workWithModel(string fileName, int width, int height)
{
	Model *model = new Model(fileName);

	TGAImage image(width, height, TGAImage::RGB);
	TGAImage zBuffer(width, height, TGAImage::GRAYSCALE);



	Vector3float lightDirect(1, 1, 1);
	Vector3float eye(0, 1, 3);
	Vector3float center(0, 0, 0);
	Vector3float up(0, 1, 0);


	lookat(eye, center, up);
	setViewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
	setProjection(-1.f / (eye - center).norm());
	lightDirect.normalize();


	GouraudShader shader;

	for (int i = 0; i < model->getNumberOfFaces(); ++i)
	{
		Vector4float screenCoordinats[3];

		for (int j = 0; j < 3; ++j)
		{
			screenCoordinats[j] = shader.vertex(i, j, model, lightDirect);
		}
		triangle(screenCoordinats, shader, image, zBuffer, model);
	}

	image.flipVertically(); // to place the origin in the bottom left corner of the image
	zBuffer.flipVertically();
	image.writeTGAFile("output.tga");
	zBuffer.writeTGAFile("zbuffer.tga");

	delete model;
}