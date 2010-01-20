#include "StdAfx.h"
#include "Rotor.h"

Rotor::Rotor(const char* airfoil_dat_file)
{
	this->Blade.Read_dat_File(airfoil_dat_file);

	ShaftBody =  gluNewQuadric();
	ShaftHead = gluNewQuadric();


	BladesNumber=2;
	BladeAngle=0;

	ShaftDiameter=1;
	ShaftLength=1;



}

Rotor::~Rotor(void)
{
}

void Rotor::GLDraw(void)
{
	float dq=360.0f/BladesNumber;

	//first draw the rotor shaft with its diameter
	gluQuadricDrawStyle(ShaftBody,GLU_FILL); 
	gluQuadricOrientation(ShaftBody,GLU_OUTSIDE);
	gluQuadricNormals(ShaftBody,GLU_SMOOTH);
	gluCylinder(ShaftBody,ShaftDiameter/2,ShaftDiameter/2,ShaftLength,40,20);

	//make the head mesurements 10% smaller
	gluQuadricDrawStyle(ShaftHead,GLU_FILL); 
	gluQuadricOrientation(ShaftHead,GLU_OUTSIDE);
	gluQuadricNormals(ShaftHead,GLU_SMOOTH);
	glPushMatrix();
	glTranslated(0,0,ShaftLength);
	gluCylinder(ShaftHead,ShaftDiameter/2,0,ShaftLength/2,40,20);

	//gluQuadricDrawStyle(ShaftHead,GLU_LINE); 
	//glTranslated(0,0,ShaftLength/2);
	//gluSphere(ShaftHead,(ShaftDiameter)/6,40,20);
	glPopMatrix();

	if(BladeAngle>0)
		Blade.Chord=ShaftLength+ShaftLength*cos(BladeAngle);  // make the air foil chord equal to the shaft length
	else
		Blade.Chord = ShaftLength;
	Blade.TrailingLeftIncrease =BladeAngle/90;
	for (int i=1;i<=BladesNumber;i++)
	{
		glPushMatrix();
			glRotated (dq*i,0,0,1);


			glRotated(90,0,1,0);// rotate the air foil so it will be tangent to z axis

			glTranslated( -ShaftLength,0.0,(Blade.Span/2)+(ShaftDiameter/2) ); // the center is in the middle of air foil so translate to the edge then the shaft diameter

			glRotated(BladeAngle,0,0,1);


			//glRotated(BladeAngle,-Blade.Span/2,1,0);

			
			Blade.GLDraw();
		glPopMatrix();
	}
}