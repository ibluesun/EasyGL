// Light.h: interface for the Light class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__21ADAD99_1308_4581_981A_9364C4800765__INCLUDED_)
#define AFX_LIGHT_H__21ADAD99_1308_4581_981A_9364C4800765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EasyGL;
#include "EasyGL.h"



class Light  
{
	friend class EasyGL;

public:
	enum LightType
	{
		Directional = 0,
		Positional = 1
	};	
private:
	GLfloat ambi[4];
	GLfloat diff[4];
	GLfloat spec[4];
	GLfloat pos[4];
	GLfloat SPOT_DIRECTION[3];
	int LightNumber;
	void LightIt(void);//Lighting the scene and it is private for EasyGL class.

	EasyGL* EGL;
	

public:
	Light(EasyGL* egl);
	virtual ~Light();
	void Ambient(GLfloat,GLfloat,GLfloat,GLfloat);
	void Diffuse(GLfloat,GLfloat,GLfloat,GLfloat);
	void Specular(GLfloat,GLfloat,GLfloat,GLfloat);
	void Position(GLfloat x,GLfloat y,GLfloat z,LightType lightType);
	void SpotDirection(GLfloat,GLfloat,GLfloat);
	void SpotExponent(GLfloat);
	void SpotCutOff(GLfloat);
	void ConstantAttenuation(GLfloat);
	void LinearAttenuation(GLfloat);
	void QuadraticAttenuation(GLfloat);

	BOOL Enabled;
	LightType* GetLightType(void);
	void SetLightType(LightType lightType);

	GLboolean ShowLightSource;
};


#endif // !defined(AFX_LIGHT_H__21ADAD99_1308_4581_981A_9364C4800765__INCLUDED_)
