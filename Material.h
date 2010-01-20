// Material.h: interface for the Material class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATERIAL_H__A1CBA67F_8856_470A_AEAE_EED8F27CDD18__INCLUDED_)
#define AFX_MATERIAL_H__A1CBA67F_8856_470A_AEAE_EED8F27CDD18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EasyGL.h"

class Material  
{
public:
	Material();
	virtual ~Material();
public:
	// Material parameters as it should be
	// Ambient,Diffuse,Specular,SHININESS
	float ADSS[13];
	float EMISSION[4];
	void ApplyMaterial(void);
	void Ambient(float R,float G,float B,float A);
	void Diffuse(float R,float G,float B,float A);
	void Specular(float R,float G,float B,float A);
	void Emission(float R,float G,float B,float A);
	void Shininess(float sh);
	void AssignADSS(float* _adss);

//Now Some Built In Materials
public:
	void _Brass(void);
	void _Bronze(void);
	void _Polished_Bronze(void);
	void _Chrome(void);
	void _Copper(void);
	void _Polished_Copper(void);
	void _Gold(void);
	void _Polished_Gold(void);
	void _Pewter(void);
	void _Silver(void);
	void _Polished_Silver(void);
	void _Emerald(void);
	void _Jade(void);
	void _Obsidian(void);
	void _Pearl(void);
	void _Ruby(void);
	void _Turquoise(void);
	void _Black_Plastic(void);
	void _Black_Rubber(void);
};

#endif // !defined(AFX_MATERIAL_H__A1CBA67F_8856_470A_AEAE_EED8F27CDD18__INCLUDED_)
