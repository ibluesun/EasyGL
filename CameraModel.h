// ameraModel.h: interface for the CameraModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AMERAMODEL_H__375DB838_7631_4CCE_BACA_0DB30DEB9E56__INCLUDED_)
#define AFX_AMERAMODEL_H__375DB838_7631_4CCE_BACA_0DB30DEB9E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EasyGL;
#include "EasyGL.h"

class CameraModel  
{
	friend class EasyGL;
public:
	CameraModel();
	virtual ~CameraModel();

private:
	GLfloat camera_x,camera_y,camera_z;
	GLfloat fovy;
	GLfloat ex,ey,ez,cx,cy,cz,lx,ly,lz;
	GLfloat currentmatrix[16];
public:
	void Setup(EasyGL* current);
	void SetupWithPicking(EasyGL* current,int x,int y);
	void ChangePerspective(GLfloat);
	void ChangeEye(GLfloat,GLfloat,GLfloat);
	void ChangeCenter(GLfloat,GLfloat,GLfloat);
	void ChangeLookUp(GLfloat,GLfloat,GLfloat);
	void Rotate (GLfloat,GLfloat,GLfloat,GLfloat);
	void RotateAboutCenter (GLfloat,GLfloat,GLfloat,GLfloat);
	void RotateAccum(GLfloat x,GLfloat y,GLfloat z,GLfloat th);
	GLfloat GetDistantFromCenter(GLfloat,GLfloat,GLfloat);
	GLfloat GetDistantFromEye(GLfloat,GLfloat,GLfloat);

};

#endif // !defined(AFX_AMERAMODEL_H__375DB838_7631_4CCE_BACA_0DB30DEB9E56__INCLUDED_)
