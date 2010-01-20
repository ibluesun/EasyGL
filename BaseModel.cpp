// Basemodel->cpp: implementation of the BaseModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Basemodel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BaseModel::BaseModel()
{
	modelTexture=NULL;
	modelMaterial=NULL;
	Opacity = 1.0;
	PickCallBackFunction = NULL;
	PickCallBackObject = NULL;
}

BaseModel::~BaseModel()
{
	
}

void BaseModel::AttachTexture(Texture *tex)
{
	modelTexture=tex;
}
void BaseModel::AttachMaterial(Material *mat)
{
	modelMaterial=mat;
}

void BaseModel::ChangeOpacity(GLdouble cc)
{
	Opacity=cc;
}

void BaseModel::ReleaseTexture()
{
	modelTexture=NULL;
}

void BaseModel::PickFunction(void* pkf)
{
	PickCallBackFunction = pkf;
}
void BaseModel::PickFunction(PickFunctionClass* pkf)
{
	PickCallBackObject=pkf;
}

void BaseModel::RunPickFunction()
{
	if (PickCallBackFunction!=NULL)
	{
		void* g=PickCallBackFunction;
		__asm call g;	
	}
	if(PickCallBackObject!=NULL)
	{
		PickCallBackObject->RunPickFunction();
	}

}

