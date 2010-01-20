// SimpleModel.cpp: implementation of the SimpleModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseModel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SimpleModel::SimpleModel()
{
	usepath=FALSE;
	camerame=NULL;
	cameraEye=NULL;
	Opacity=1.0;

}

SimpleModel::~SimpleModel()
{

}
///////////
// I want you to know  that the effect matrix is consider a volatile 
// matrix and it must not load something but the rendering motion
//

void SimpleModel::Translate(GLfloat x,GLfloat y,GLfloat z,BOOL acc)
{
	if (acc==FALSE) 
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glTranslatef(x,y,z);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);
		glPopMatrix();
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glTranslatef(x,y,z);
			glMultMatrixf(effectmatrix);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);
		glPopMatrix();
	}
}

void SimpleModel::Rotate(GLfloat deg,GLfloat x,GLfloat y,GLfloat z,BOOL acc)
{
	if (acc==FALSE) 
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRotatef(deg,x,y,z);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);
		glPopMatrix();
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRotatef(deg,x,y,z);
			glMultMatrixf(effectmatrix);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);

		glPopMatrix();
	}

}

void SimpleModel::Scale(GLfloat x,GLfloat y,GLfloat z,BOOL acc)
{
	if (acc==FALSE) 
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glScalef(x,y,z);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);
		glPopMatrix();
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glScalef(x,y,z);
			glMultMatrixf(effectmatrix);
			glGetFloatv(GL_MODELVIEW_MATRIX,effectmatrix);
		glPopMatrix();
	}
}

/////////////////////////////////////////////////////
/////// path implementation
///

void SimpleModel::translateelement::Run(GLfloat tempmatrix[16])
{

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y,z);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempmatrix);
	glPopMatrix();

}
void SimpleModel::rotateelement::Run(GLfloat tempmatrix[16])
{
	glPushMatrix();
		glLoadIdentity();
		glRotatef(deg,x,y,z);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempmatrix);
	glPopMatrix();

}
void SimpleModel::TRelement::Run(GLfloat tempmatrix[16])
{
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y,z);
		glRotatef(deg,vx,vy,vz);
		glGetFloatv(GL_MODELVIEW_MATRIX,tempmatrix);
	glPopMatrix();	
}


void SimpleModel::addTpoint(GLfloat x,GLfloat y,GLfloat z)
{
	poi=new translateelement;
	poi->x=x;
	poi->y=y;
	poi->z=z;
	Ppoints.push_back(poi);
}

void SimpleModel::addRpoint(GLfloat x,GLfloat y,GLfloat z,GLfloat degree)
{
	roi=new rotateelement;
	roi->x=x;
	roi->y=y;
	roi->z=z;
	roi->deg=degree;
	Ppoints.push_back(roi);
}

void SimpleModel::addTRpoint(GLfloat x,GLfloat y,GLfloat z,GLfloat rx,GLfloat ry,GLfloat rz,GLfloat degree)
{
	proi=new TRelement;
	proi->x=x;
	proi->y=y;
	proi->z=z;
	proi->vx=rx;
	proi->vy=ry;
	proi->vz=rz;
	proi->deg=degree;
	Ppoints.push_back(proi);
}
void SimpleModel::clearthepath()
{
	if (usepath)
	{
		usepath=FALSE;
		vector <translateelement*>::iterator dd;
		for (dd=Ppoints.begin();dd<=Ppoints.end()-1;dd++)
		{
			delete (*dd);
		}
		Ppoints.clear();
	}
}

void SimpleModel::EnablePathTrace(void)
{
	usepath=TRUE;
	Pp=Ppoints.begin();
}

void SimpleModel::DisablePathTrace(void)
{
	usepath=FALSE;
}

void SimpleModel::GetNextPoint()
{
	if (usepath==TRUE)
	{
		(*Pp)->Run(effectmatrix);

		if (Pp < (Ppoints.end()-1)) {Pp++ ;} 
			else Pp=Ppoints.begin();
	}

}

void SimpleModel::AttachCamera(CameraModel* cm)
{
	camerame=cm;
}

void SimpleModel::AttachCameraEye(CameraModel* cm)
{
	cameraEye=cm;
}

void SimpleModel::ReleaseCamera()
{
	camerame=NULL;
	cameraEye=NULL;
}

void SimpleModel::get_postion(GLfloat* x,GLfloat* y,GLfloat* z)
{
	*x=effectmatrix[12];
	*y=effectmatrix[13];
	*z=effectmatrix[14];
}

void SimpleModel::Unitize()
{

}

void SimpleModel::Scale(GLfloat sc)
{

}

void SimpleModel::ReverseWinding()
{

}
