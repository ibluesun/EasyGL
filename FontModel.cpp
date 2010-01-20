// Fontmodel->cpp: implementation of the BaseModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Basemodel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


FontModel::~FontModel()
{
	KillFont();
}
void FontModel::BuildFont(EasyGL* cc,int nWidth,const char *ft, ...)								// Build Our Bitmap Font
{
	fmt=ft;
	modelTexture=NULL;
	Opacity = 1.0;
	//Font Defaults
	FontName="Arabic Transparent";
	FontWeight=FW_NORMAL;

	EGLDC = cc->Get_DC();
	HFONT	font;										// Windows Font ID

	fbase = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-nWidth*2,							// Height Of Font
						nWidth,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FontWeight,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET ,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						FontName);						// Font Name

	SelectObject(EGLDC, font);							// Selects The Font We Want

	wglUseFontOutlines( EGLDC,							// Select The Current DC
						  32,							// Starting Character
						96,							// Number Of Display Lists To 
						fbase,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve
}

void FontModel::KillFont(void)									// Delete The Font
{
	glDeleteLists(fbase, 96);							// Delete All 96 Characters
}

void FontModel::Render(void)
{
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

		float length=0;
		char		text[256];								// Holds Our String
#ifndef _MANAGED
		va_list		ap;										// Pointer To List Of Arguments

		if (fmt == NULL)									// If There's No Text
			return;											// Do Nothing
		va_start(ap, fmt);									// Parses The String For Variables
			vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
		va_end(ap);											// Results Are Stored In Text
#endif
		strcpy(text,fmt);
		
		for (unsigned int loop=0;loop<(strlen(text));loop++) // Loop To Find Text Length
		{
		}
		glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
		glListBase(fbase - 32);								// Sets The Base Character to 32
		glPushAttrib(GL_CURRENT_BIT);
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
		glPopAttrib();
		glPopAttrib();									// Pops The Display List Bits
	glPopMatrix();
}

