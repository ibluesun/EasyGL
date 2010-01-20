// GeometricModel.cpp: implementation of the CustomModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseModel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GeometricModel::GeometricModel()
{
	selector=0;
	quad=gluNewQuadric();
	Opacity = 1.0;
}

GeometricModel::~GeometricModel()
{
	gluDeleteQuadric(quad);
}

////////////////////////////////////////////////////
/////////////////
////////////


void GeometricModel::ItIsDisk(GLdouble inRad,GLdouble outRad)
{
	selector=3;
	innerRadius = inRad;
	outerRadius = outRad;
}
void GeometricModel::ItIsPartialDisk(GLdouble inRad,GLdouble outRad,GLdouble startAng,GLdouble sweepAng)
{
	selector=5;
	innerRadius = inRad;
	outerRadius = outRad;
	startAngle = startAng;
	sweepAngle = sweepAng;

}
void GeometricModel::ItIsCylinder(GLdouble baseRad,GLdouble topRad,GLdouble hi)
{
	selector=4;
	baseRadius = baseRad;
	topRadius = topRad;
	cheight = hi;
}

void GeometricModel::ItIsSphere(GLdouble Rad)
{
	selector=2;
	Radius=Rad;
}

void GeometricModel::ItIsCube(GLdouble uni)
{
	selector=1;
	unit=uni;
}

void GeometricModel::Render(void)
{
	int slices=10;
	int loops=5;

	if (modelMaterial != NULL)
	{
		modelMaterial->ADSS[3]=Opacity;
		modelMaterial->ADSS[7]=Opacity;
		modelMaterial->ADSS[11]=Opacity;
		modelMaterial->ApplyMaterial();
	}
	if (usepath==TRUE)
	{
		GetNextPoint();
	}

	glPushMatrix();
		
		glLoadMatrixf(effectmatrix); //Get the current transformation

		if (camerame!=NULL) // if camera is attached
		{
			// Move its center
			camerame->ChangeCenter(effectmatrix[12],effectmatrix[13],effectmatrix[14]);
		}

		if (cameraEye!=NULL) // if camera eye is attached
		{
			// Move its center
			cameraEye->ChangeEye
				(effectmatrix[12],effectmatrix[13],effectmatrix[14]);
		}

		// 1 = cube
		if (selector==1) 
		{
			if (modelTexture!=NULL)
			{
				glEnable(GL_TEXTURE_2D);
				modelTexture->ApplyTexture();
			}
			glScaled(unit,unit,unit);
			glPushAttrib(GL_CURRENT_BIT);
			glBegin(GL_QUADS);
				// Front Face
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 1 (Front)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 2 (Front)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Front)
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 4 (Front)
				// Back Face
				glNormal3f( 0.0f, 0.0f,-1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Back)
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point 2 (Back)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 3 (Back)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 4 (Back)
				// Top Face
				glNormal3f( 0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point 1 (Top)
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 2 (Top)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Top)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 4 (Top)
				// Bottom Face
				glNormal3f( 0.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Bottom)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 2 (Bottom)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 3 (Bottom)
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 4 (Bottom)
				// Right face
				glNormal3f( 1.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 1 (Right)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 2 (Right)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Right)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 4 (Right)
				// Left Face
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Left)
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 2 (Left)
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 3 (Left)
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point
			glEnd();	
			glPopAttrib();
		glDisable(GL_TEXTURE_2D);
		}
		
		//2 = Sphere
		if (selector==2)
		{
			gluQuadricDrawStyle(quad,GLU_FILL); 
			gluQuadricNormals(quad,GLU_SMOOTH); 
			if (modelTexture!=NULL)
			{
				gluQuadricTexture(quad,GL_TRUE);		// To Calculate Tex Coor
				glEnable(GL_TEXTURE_2D);
				modelTexture->ApplyTexture();
			}
			glPushAttrib(GL_CURRENT_BIT);
			gluSphere(quad,Radius,slices,loops);
			glPopAttrib();
			glDisable(GL_TEXTURE_2D);
		}

		//3 = Disk
		if (selector==3)
		{
			gluQuadricDrawStyle(quad,GLU_FILL); 
			gluQuadricNormals(quad,GLU_SMOOTH); 
			if (modelTexture!=NULL)
			{
				gluQuadricTexture(quad,GL_TRUE);		// To Calculate Tex Coor
				glEnable(GL_TEXTURE_2D);
				modelTexture->ApplyTexture();
			}
			glPushAttrib(GL_CURRENT_BIT);
			gluDisk(quad,innerRadius,outerRadius,slices,loops);
			glPopAttrib();
			glDisable(GL_TEXTURE_2D);
		}

		//4 = Cylinder
		if (selector==4)
		{
			gluQuadricDrawStyle(quad,GLU_FILL); 
			gluQuadricNormals(quad,GLU_SMOOTH); 
			if (modelTexture!=NULL)
			{
				gluQuadricTexture(quad,GL_TRUE);		// To Calculate Tex Coor
				glEnable(GL_TEXTURE_2D);
				modelTexture->ApplyTexture();
			}
			glPushAttrib(GL_CURRENT_BIT);
			gluCylinder(quad,baseRadius,topRadius,cheight,slices,loops);
			glPopAttrib();
			glDisable(GL_TEXTURE_2D);
		}

		//5 = PartialDisk
		if (selector==5)
		{
			gluQuadricDrawStyle(quad,GLU_FILL); 
			gluQuadricNormals(quad,GLU_SMOOTH); 
			if (modelTexture!=NULL)
			{
				gluQuadricTexture(quad,GL_TRUE);		// To Calculate Tex Coor
				glEnable(GL_TEXTURE_2D);
				modelTexture->ApplyTexture();
			}
			glPushAttrib(GL_CURRENT_BIT);
			gluPartialDisk(quad,innerRadius,outerRadius,slices,loops,startAngle,sweepAngle);
			glPopAttrib();
			glDisable(GL_TEXTURE_2D);
		}
	glPopMatrix();
}