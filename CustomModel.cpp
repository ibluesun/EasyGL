// CustomModel.cpp: implementation of the CustomModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseModel.h"

CustomModel::CustomModel()
{
	RenderAddr = NULL;
	Opacity = 1.0;
}
void CustomModel::RenderAddress(void* addr)
{
	RenderAddr = addr;
}

void CustomModel::Render(void)
{
	void* g=RenderAddr;
	if (modelMaterial != NULL)
	{
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
				
		if (modelTexture==NULL)
		{
			__asm call g;	
		}

		if (modelTexture!=NULL)
		{
			glEnable(GL_TEXTURE_2D);
			modelTexture->ApplyTexture();
			//
			/////////////////////////////
			///Run Render Address
			__asm call g;
			//
			glDisable(GL_TEXTURE_2D);
		}

	glPopMatrix();
}