// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Material.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Material::Material()
{
	EMISSION[0]=0;
	EMISSION[1]=0;
	EMISSION[2]=0;
	EMISSION[3]=1;
	_Bronze();
}

Material::~Material()
{

}


void Material::ApplyMaterial(void)
{
	GLfloat ambi[4];
	GLfloat diff[4];
	GLfloat spec[4];
	GLfloat shin;

//Make a sepreation and assign every color to its varialble
// I think there is more easy way to Do this;

	ambi[0]=ADSS[0];ambi[1]=ADSS[1];ambi[2]=ADSS[2];ambi[3]=ADSS[3];
	diff[0]=ADSS[4];diff[1]=ADSS[5];diff[2]=ADSS[6];diff[3]=ADSS[7];
	spec[0]=ADSS[8];spec[1]=ADSS[9];spec[2]=ADSS[10];spec[3]=ADSS[11];
	shin=ADSS[12];

	glMaterialfv(GL_FRONT,GL_AMBIENT,ambi);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT,GL_EMISSION,EMISSION);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shin);
}

void Material::Ambient(float R,float G,float B,float A)
{
	ADSS[0]=R;
	ADSS[1]=G;
	ADSS[2]=B;
	ADSS[3]=A;
}
void Material::Diffuse(float R,float G,float B,float A)
{
	ADSS[4]=R;
	ADSS[5]=G;
	ADSS[6]=B;
	ADSS[7]=A;
}

void Material::Specular(float R,float G,float B,float A)
{
	ADSS[8]=R;
	ADSS[9]=G;
	ADSS[10]=B;
	ADSS[11]=A;
}

void Material::Shininess(float sh)
{
	ADSS[12]=sh;
}

void Material::Emission(float R,float G,float B,float A)
{
	EMISSION[0]=R;
	EMISSION[1]=G;
	EMISSION[2]=B;
	EMISSION[3]=A;
}

void Material::AssignADSS(float* _adss)
{
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=_adss[i];
	}
}

void Material::_Brass()
{
	double Brass[] = {
		0.329412, 0.223529, 0.027451, 1.000000,
		0.780392, 0.568627, 0.113725, 1.000000,
		0.992157, 0.941176, 0.807843, 1.000000,
		27.897400
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Brass[i];
	}
}
void Material::_Bronze()
{
	double Bronze[] = {
		0.212500, 0.127500, 0.054000, 1.000000,
		0.714000, 0.428400, 0.181440, 1.000000,
		0.393548, 0.271906, 0.166721, 1.000000,
		25.600000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Bronze[i];
	}
}
void Material::_Chrome()
{
	double Chrome[] = {
		0.250000, 0.250000, 0.250000, 1.000000,
		0.400000, 0.400000, 0.400000, 1.000000,
		0.774597, 0.774597, 0.774597, 1.000000,
		76.800003
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Chrome[i];
	}
}
void Material::_Copper()
{
	double Copper[] = {
		0.191250, 0.073500, 0.022500, 1.000000,
		0.703800, 0.270480, 0.082800, 1.000000,
		0.256777, 0.137622, 0.086014, 1.000000,
		12.800000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Copper[i];
	}
}
void Material::_Polished_Bronze()
{
	double Polished_Bronze[] = {
		0.250000, 0.148000, 0.064750, 1.000000,
		0.400000, 0.236800, 0.103600, 1.000000,
		0.774597, 0.458561, 0.200621, 1.000000,
		76.800003
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Polished_Bronze[i];
	}
}

void Material::_Black_Plastic()
{
	double Black_Plastic[] = {
		0.000000, 0.000000, 0.000000, 1.000000,
		0.010000, 0.010000, 0.010000, 1.000000,
		0.500000, 0.500000, 0.500000, 1.000000,
		32.000000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Black_Plastic[i];
	}
}

void Material::_Black_Rubber()
{
	double Black_Rubber[] = {
		0.020000, 0.020000, 0.020000, 1.000000,
		0.010000, 0.010000, 0.010000, 1.000000,
		0.400000, 0.400000, 0.400000, 1.000000,
		10.000000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Black_Rubber[i];
	}
}

void Material::_Emerald()
{
	double Emerald[] = {
		0.021500, 0.174500, 0.021500, 0.550000,
		0.075680, 0.614240, 0.075680, 0.550000,
		0.633000, 0.727811, 0.633000, 0.550000,
		76.800003
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Emerald[i];
	}
}

void Material::_Gold()
{
	double Gold[] = {
		0.247250, 0.199500, 0.074500, 1.000000,
		0.751640, 0.606480, 0.226480, 1.000000,
		0.628281, 0.555802, 0.366065, 1.000000,
		51.200001
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Gold[i];
	}
}



void Material::_Obsidian()
{
	double Obsidian[] = {
		0.053750, 0.050000, 0.066250, 0.820000,
		0.182750, 0.170000, 0.225250, 0.820000,
		0.332741, 0.328634, 0.346435, 0.820000,
		38.400002
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Obsidian[i];
	}
}
void Material::_Pearl()
{
	double Pearl[] = {
		0.250000, 0.207250, 0.207250, 0.922000,
		1.000000, 0.829000, 0.829000, 0.922000,
		0.296648, 0.296648, 0.296648, 0.922000,
		11.264000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Pearl[i];
	}
}
void Material::_Pewter()
{
	double Pewter[] = {
		0.105882, 0.058824, 0.113725, 1.000000,
		0.427451, 0.470588, 0.541176, 1.000000,
		0.333333, 0.333333, 0.521569, 1.000000,
		9.846150
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Pewter[i];
	}
}
void Material::_Polished_Gold()
{
	double Polished_Gold[] = {
		0.247250, 0.224500, 0.064500, 1.000000,
		0.346150, 0.314300, 0.090300, 1.000000,
		0.797357, 0.723991, 0.208006, 1.000000,
		83.199997
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Polished_Gold[i];
	}
}
void Material::_Polished_Silver()
{
	double Polished_Silver[] = {
		0.231250, 0.231250, 0.231250, 1.000000,
		0.277500, 0.277500, 0.277500, 1.000000,
		0.773911, 0.773911, 0.773911, 1.000000,
		89.599998
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Polished_Silver[i];
	}
}
void Material::_Ruby()
{
	double Ruby[] = {
		0.174500, 0.011750, 0.011750, 0.550000,
		0.614240, 0.041360, 0.041360, 0.550000,
		0.727811, 0.626959, 0.626959, 0.550000,
		76.800003
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Ruby[i];
	}
}
void Material::_Silver()
{
	double Silver[] = {
		0.192250, 0.192250, 0.192250, 1.000000,
		0.507540, 0.507540, 0.507540, 1.000000,
		0.508273, 0.508273, 0.508273, 1.000000,
		51.200001
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Silver[i];
	}
}
void Material::_Turquoise()
{
	double Turquoise[] = {
		0.100000, 0.187250, 0.174500, 0.800000,
		0.396000, 0.741510, 0.691020, 0.800000,
		0.297254, 0.308290, 0.306678, 0.800000,
		12.800000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Turquoise[i];
	}
}

void Material::_Jade()
{
	double Jade[] = {
		0.135000, 0.222500, 0.157500, 0.950000,
		0.540000, 0.890000, 0.630000, 0.950000,
		0.316228, 0.316228, 0.316228, 0.950000,
		12.800000
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Jade[i];
	}
}

void Material::_Polished_Copper()
{
	double Polished_Copper[] = {
		0.229500, 0.088250, 0.027500, 1.000000,
		0.550800, 0.211800, 0.066000, 1.000000,
		0.580594, 0.223257, 0.069570, 1.000000,
		51.200001
	};
	for (int i=0;i<=12;i++)
	{
		ADSS[i]=(float)Polished_Copper[i];
	}
}

