// Light.cpp: implementation of the Light class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Light::Light(EasyGL* egl)
{
	Enabled=FALSE;
	ShowLightSource=false;
	EGL = egl;

}

Light::~Light()
{

}

void Light::Ambient(GLfloat R,GLfloat G,GLfloat B,GLfloat A)
{
	ambi[0]=R;
	ambi[1]=G;
	ambi[2]=B;
	ambi[3]=A;
	glLightfv (GL_LIGHT0+LightNumber, GL_AMBIENT, ambi);
}
void Light::Diffuse(GLfloat R,GLfloat G,GLfloat B,GLfloat A)
{
	diff[0]=R;
	diff[1]=G;
	diff[2]=B;
	diff[3]=A;
	glLightfv (GL_LIGHT0+LightNumber, GL_DIFFUSE, diff);
}
void Light::Specular(GLfloat R,GLfloat G,GLfloat B,GLfloat A)
{
	spec[0]=R;
	spec[1]=G;
	spec[2]=B;
	spec[3]=A;
	glLightfv (GL_LIGHT0+LightNumber, GL_SPECULAR, diff);
}
void Light::Position(GLfloat x,GLfloat y,GLfloat z,LightType lightType)
{
	pos[0]=x;
	pos[1]=y;
	pos[2]=z;
	pos[3] = (float)lightType; 
}
void Light::SpotDirection(GLfloat x,GLfloat y,GLfloat z)
{
	SPOT_DIRECTION[0]=x;
	SPOT_DIRECTION[1]=y;
	SPOT_DIRECTION[2]=z;

	glLightfv (GL_LIGHT0+LightNumber, GL_SPOT_DIRECTION, SPOT_DIRECTION);
}
void Light::SpotExponent(GLfloat SE)
{
	glLightf(GL_LIGHT0+LightNumber,GL_SPOT_EXPONENT,SE);
}
void Light::SpotCutOff(GLfloat SE)
{
	glLightf(GL_LIGHT0+LightNumber,GL_SPOT_CUTOFF,SE);
}
void Light::ConstantAttenuation(GLfloat SE)
{
	glLightf(GL_LIGHT0+LightNumber,GL_CONSTANT_ATTENUATION ,SE);
}
void Light::LinearAttenuation(GLfloat SE)
{
	glLightf(GL_LIGHT0+LightNumber,GL_LINEAR_ATTENUATION,SE);
}
void Light::QuadraticAttenuation(GLfloat SE)
{
	glLightf(GL_LIGHT0+LightNumber,GL_QUADRATIC_ATTENUATION,SE);
}

Light::LightType* Light::GetLightType(void)
{
	LightType* lt;
	if(pos[3]==0)
		lt = new LightType(Directional);
	else
		lt = new LightType(Positional);
	return lt;
}
void Light::SetLightType(LightType lightType)
{
	pos[3] = (int)lightType;
}

void Light::LightIt(void)
{
	if (Enabled==TRUE)
	{
		glEnable(GL_LIGHT0+LightNumber);

		glLightfv (GL_LIGHT0+LightNumber, GL_POSITION, pos);
		
		if(ShowLightSource)
		{
			//show any mean of geometry indicating light :(
		}
	}
	else
	{
		glDisable(GL_LIGHT0+LightNumber);
	}
}

