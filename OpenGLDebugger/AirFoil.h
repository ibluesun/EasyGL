#pragma once
#include <vector>
#include <fstream>
#include <gl\gl.h>
#include <gl\glu.h>


using namespace std;

class AirFoil
{

public:
	struct strucAirFoilPoint
	{
		float x;
		float y;
	};

public:
	AirFoil(void);
	void Read_dat_File(const char* filename);

	char Header[255];
	
	vector<strucAirFoilPoint> Points;

	//AirFoil properties

	float Span;     // width of airfoil
	float Chord;	// length of air foil

	void GLDraw();

	//some variables affecting the airfoil
	float TrailingLeftIncrease;   //increase the trailing edge to the left from Leading to Trailing
	//          |
	// ----------
	// @ = LeftIncrease / Chord
	// z=z-x*@

	float TrailingRightIncrease;


public:
	~AirFoil(void);
};
