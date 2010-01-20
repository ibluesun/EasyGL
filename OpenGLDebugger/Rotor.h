#pragma once
#include "AirFoil.h"

class Rotor
{
public:
	Rotor(const char* airfoil_dat_file);

	int BladesNumber;
	float BladeAngle;

	float ShaftDiameter;
	float ShaftLength;


	void GLDraw(void);

	AirFoil Blade;

protected:
	GLUquadric* ShaftBody;
	GLUquadric* ShaftHead;


public:
	~Rotor(void);
};
