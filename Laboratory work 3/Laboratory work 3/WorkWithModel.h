#pragma once


#include <algorithm>
#include <limits>
#include <cstdlib>
#include "Model.h"
#include "TGAImage.h"
#include "Geometry.h"


extern Matrix4float modelView;
extern Matrix4float viewPort;
extern Matrix4float projection;
const float depth = 2000.f;

extern float *shadowBuffer;


void setViewport(int x, int y, int width, int height);
void setProjection(float coefficient = 0.f);
void lookat(Vector3float eye, Vector3float center, Vector3float up);


struct IShader
{
	virtual ~IShader();

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect) = 0;

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model, int width, Vector3float &lightDirect) = 0;
};


struct GouraudShader : public IShader
{
	//Written by vertex shader, read by fragment shader
	Vector3float varyingIntensity;

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect)
	{
		Vector4float glVertex = embed<4>(model->getVertex(faceIndex, numberOfVertex));
		
		//Transform it to screen coordinates
		//glVertex = viewPort * projection * modelView * glVertex;     
		
		//Get diffuse lighting intensity
		varyingIntensity[numberOfVertex] = max(0.f, model->getNorm(faceIndex, numberOfVertex) * lightDirect); 
		
		return viewPort * projection * modelView * glVertex;
	}

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model, int width, Vector3float &lightDirect)
	{
		float intensity = Vector3float(varyingIntensity) * bar;

		if (intensity > 0.85f)
		{
			intensity = 1.f;
		}
		else if (intensity > 0.60f)
		{
			intensity = 0.80f;
		}
		else if (intensity > 0.45f)
		{
			intensity = 0.60f;
		}
		else if (intensity > 0.30f)
		{
			intensity = 0.45f;
		}
		else if (intensity > 0.15f)
		{
			intensity = 0.30f;
		}
		else
		{
			intensity = 0.f;
		}

		color = TGAColor(255, 155, 0) * intensity;
		return false;
	}
};


struct Shader : public IShader
{
	Matrix<4, 4, float> uniformM;  
	Matrix<4, 4, float> uniformMIT; 
	Matrix<4, 4, float> uniformMshadow; 
	Matrix<2, 3, float> varyingUV;  
	Matrix<3, 3, float> varyingTri; 

	Shader(Matrix4float M, Matrix4float MIT, Matrix4float MS) : uniformM(M), uniformMIT(MIT), uniformMshadow(MS), varyingUV(), varyingTri() {}

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect)
	{
		varyingUV.setCol(numberOfVertex, model->getTextureCoordinate(faceIndex, numberOfVertex));

		Vector4float glVertex = viewPort * projection * modelView * embed<4>(model->getVertex(faceIndex, numberOfVertex));
		
		varyingTri.setCol(numberOfVertex, proj<3>(glVertex / glVertex[3]));

		return glVertex;
	}

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model, int width, Vector3float &lightDirect)
	{
		Vector4float sbP = uniformMshadow * embed<4>(varyingTri * bar);
		sbP = sbP / sbP[3];

		int index = int(sbP[0]) + int(sbP[1]) * width;

		float shadow = 0.3f + 0.7f * (shadowBuffer[index] < sbP[2]);
		
		Vector2float uv = varyingUV * bar;

		Vector3float n = proj<3>(uniformMIT * embed<4>(model->getNorm(uv))).normalize();
		Vector3float l = proj<3>(uniformM * embed<4>(lightDirect)).normalize();
		Vector3float r = (n * (n *l * 2.f) - l).normalize();
		
		float specular = pow(max(r.z, 0.f), model->getSpecular(uv));
		float diffuse = max(0.f, n * l);

		TGAColor c = model->getDiffuse(uv);
		
		for (int i = 0; i < 3; i++)
		{
			color[i] = unsigned char(min<float>(20.f + float(c[i]) * shadow * (1.2f * diffuse + 0.6f * specular), 255));
		}

		return false;
	}
};

struct DepthShader : public IShader
{
	Matrix<3, 3, float> varyingTri;

	DepthShader() : varyingTri() {}

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect)
	{
		Vector4float glVertex = embed<4>(model->getVertex(faceIndex, numberOfVertex));

		glVertex = viewPort * projection * modelView * glVertex;
		
		varyingTri.setCol(numberOfVertex, proj<3>(glVertex / glVertex[3]));
		
		return glVertex;
	}

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model, int width, Vector3float &lightDirect)
	{
		Vector3float p = varyingTri * bar;

		color = TGAColor(255, 255, 255)*(p.z / depth);
		
		return false;
	}
};

void triangle(Vector4float *pts, IShader &shader, TGAImage &image, float *zBuffer, Model *model, Vector3float &lightDirect);


void workWithModel(string fileName, int width, int height);