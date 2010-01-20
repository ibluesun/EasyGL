#include "StdAfx.h"
#include "AirFoil.h"



AirFoil::AirFoil(void)
{
	Span=1;
}

AirFoil::~AirFoil(void)
{
}
void AirFoil::Read_dat_File(const char* filename)
{
	/*
	For reference, the original airfoils in the list and new ones 
	added by Selig are in an x,y format starting from trailing edge,
	along the upper surface to the leading edge and back around the
	lower surface to trailing edge
	*/

	ifstream dat;
	dat.open(filename);
	dat.getline(Header,255);

	this->Chord=0;

	while(!dat.eof())
	{
		//ignore spaces if found
		while(!isalnum(dat.peek()) && !dat.eof() && dat.peek()!='-')
			dat.ignore(1);
		if(dat.eof())
			break;

		//get the x value
		char x[10];
		dat.getline(x,10,' ');

		//ignore spaces if found
		while(!isalnum(dat.peek()) && dat.peek()!='-')
			dat.ignore(1);
	
		//get the y value
		char y[10];
		dat.getline(y,10);

		strucAirFoilPoint pp;

		pp.x = (float)atof(x);
		pp.y = (float)atof(y);

		if(pp.x>Chord)
			this->Chord = pp.x;

		Points.push_back(pp);
	}

	dat.close();
}

void AirFoil::GLDraw()
{
	glPushMatrix();	
	glPushAttrib(GL_CURRENT_BIT);
	glBegin(GL_TRIANGLE_STRIP);

	for(int i=0;i<Points.size()-1;i+=2)
	{
		float x0 = Points[i].x;
		float x1 = Points[i].x;
		float x2 = Points[i+1].x;
		float x3 = Points[i+1].x;

		float y0 = Points[i].y;
		float y1 = Points[i+1].y;
		float y2 = Points[i+1].y;
		float y3 = Points[i+1].y;

		float z0 = Span/2;
		float z1 = -Span/2;
		float z2 = Span/2;
		float z3 = -Span/2;


		/* Compute vectors */
		float x20 = x2 - x0;
		float y20 = y2 - y0;
		float z20 = z2 - z0;
		float x13 = x1 - x3;
		float y13 = y1 - y3;
		float z13 = z1 - z3;
		/* Compute the cross product */
		float cpx = (z20 * y13) - (y20 * z13);
		float cpy = (x20 * z13) - (z20 * x13);
		float cpz = (y20 * x13) - (x20 * y13);

		/* Normalize the result to get the unit-length facet
		normal */
		float r = sqrt(cpx * cpx + cpy * cpy + cpz * cpz);
		float nx = cpx / r;
		float ny = cpy / r;
		float nz = cpz / r;

	
		glNormal3d(nx,ny,nz);

		glVertex3d(Points[i].x*Chord,Points[i].y,+(Span/2)+(Points[i].x*(TrailingRightIncrease/Chord)));

		glVertex3d(Points[i].x*Chord,Points[i].y,-(Span/2)-(Points[i].x*(TrailingLeftIncrease/Chord)));

		glVertex3d(Points[i+1].x*Chord,Points[i+1].y,+(Span/2)+(Points[i+1].x*(TrailingRightIncrease/Chord)));

		glVertex3d(Points[i+1].x*Chord,Points[i+1].y,-(Span/2)-(Points[i+1].x*(TrailingLeftIncrease/Chord)));

	}

	glEnd();
	glPopAttrib();
	glPopMatrix();
}