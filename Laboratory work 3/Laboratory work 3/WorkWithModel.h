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


void setViewport(int x, int y, int width, int height);
void setProjection(float coefficient = 0.f);
void lookat(Vector3float eye, Vector3float center, Vector3float up);


struct IShader
{
	virtual ~IShader();

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect) = 0;

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model) = 0;
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

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model)
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
	Vector3float varyingIntensity;
	Matrix<2, 3, float> varyingUV;        // same as above

	virtual Vector4float vertex(int faceIndex, int numberOfVertex, Model *model, Vector3float &lightDirect)
	{
		varyingUV.setCol(numberOfVertex, model->getTextureCoordinate(faceIndex, numberOfVertex));

		varyingIntensity[numberOfVertex] = max(0.f, model->getNorm(faceIndex, numberOfVertex) * lightDirect);

		Vector4float glVertex = embed<4>(model->getVertex(faceIndex, numberOfVertex));

		return viewPort * projection * modelView * glVertex;
	}

	virtual bool fragment(Vector3float bar, TGAColor &color, Model *model)
	{
		float intensity = Vector3float(varyingIntensity) * bar;

		Vector2float uv = varyingUV * bar;       

		color = model->getDiffuse(uv) * intensity;   

		return false;                          
	}
};

void triangle(Vector4float *pts, IShader &shader, TGAImage &image, TGAImage &zbuffer, Model *model);


void workWithModel(string fileName, int width, int height);