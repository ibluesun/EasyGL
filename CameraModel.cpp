// ameraModel.cpp: implementation of the CameraModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CameraModel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CameraModel::CameraModel()
{
	for (int i=0;i<=15;i++){currentmatrix[i]=0;}
	currentmatrix[0]=1;
	currentmatrix[5]=1;
	currentmatrix[10]=1;
	currentmatrix[15]=1;
	ChangeCenter(0,0,0);
	ChangeEye(0,0,-5);
	ChangeLookUp(0,1,0);
	ChangePerspective(45);
}

CameraModel::~CameraModel()
{

}

void CameraModel::ChangeCenter(GLfloat x,GLfloat y,GLfloat z)
{
	cx=x;cy=y;cz=z;
}

void CameraModel::ChangeEye(GLfloat x, GLfloat y,GLfloat z)
{
	ex=x;ey=y;ez=z;
	currentmatrix[12]=x;
	currentmatrix[13]=y;
	currentmatrix[14]=z;
}

GLfloat CameraModel::GetDistantFromCenter(GLfloat x,GLfloat y,GLfloat z)
{
	return sqrt(((cx-x)*(cx-x))+((cy-y)*(cy-y))+((cz-z)*(cz-z)));
}


GLfloat CameraModel::GetDistantFromEye(GLfloat x,GLfloat y,GLfloat z)
{
	return sqrt(((ex-x)*(ex-x))+((ey-y)*(ey-y))+((ez-z)*(ez-z)));
}



void CameraModel::ChangeLookUp(GLfloat x,GLfloat y,GLfloat z)
{
	lx=x;ly=y;lz=z;
}
void CameraModel::ChangePerspective(GLfloat p)
{
	fovy=p;
}
void CameraModel::Setup(EasyGL* current)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluPerspective (fovy, current->Get_Aspect(), 0.01, 1000);
		gluLookAt(currentmatrix[12],currentmatrix[13],currentmatrix[14],cx,cy,cz,lx,ly,lz);
}
void CameraModel::SetupWithPicking(EasyGL* current,int x,int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

		gluPickMatrix(x,viewport[3]-y,5,5,viewport);	
		gluPerspective (fovy, current->Get_Aspect(), 1, 1000);
		gluLookAt(currentmatrix[12],currentmatrix[13],currentmatrix[14],cx,cy,cz,lx,ly,lz);


}
void CameraModel::Rotate(GLfloat x,GLfloat y,GLfloat z,GLfloat th)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glRotatef(th,x,y,z);
		glTranslatef(ex,ey,ez);
		glGetFloatv(GL_PROJECTION_MATRIX,currentmatrix);
	glPopMatrix();
}
void CameraModel::RotateAboutCenter(GLfloat x,GLfloat y,GLfloat z,GLfloat th)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
		glLoadIdentity();
		glRotatef(th,x,y,z);
		glTranslatef(ex-cx,ey-cy,ez-cz);
		glGetFloatv(GL_PROJECTION_MATRIX,currentmatrix);
	glPopMatrix();
	currentmatrix[12]+=cx;
	currentmatrix[13]+=cy;
	currentmatrix[14]+=cz;
}

void CameraModel::RotateAccum(GLfloat x,GLfloat y,GLfloat z,GLfloat th)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glRotatef(th,x-cx,y-cy,z-cz);
		//glTranslatef(ex,ey,ez);
		glMultMatrixf(currentmatrix);
		glGetFloatv(GL_PROJECTION_MATRIX,currentmatrix);
	glPopMatrix();
}
