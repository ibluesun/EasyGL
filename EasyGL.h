// EasyGL.h: interface for the EasyGL class.
// By Ahmed Sadek
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EASYGL_H__F3E2061E_221C_4BE3_90E9_0AE027089A6B__INCLUDED_)
#define AFX_EASYGL_H__F3E2061E_221C_4BE3_90E9_0AE027089A6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
//#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>
#include <gl\glu.h>
#include <assert.h>

class Light;
#include "Light.h"

class BaseModel;
#include "BaseModel.h"

#include "CameraModel.h"
#include "Material.h"

class Texture;
#include "Texture.h"

#pragma warning(disable:4786)
#include <vector>
#include <map>
using namespace std;

class GLUquadric
{
};

class EasyGL  
{
	friend class CameraModel;
private:
	HWND GLWND;
	HDC GLDC;
	HGLRC hRC;
	PIXELFORMATDESCRIPTOR pfd;
	CameraModel* CurrentCamera;
	double Get_Aspect(void);
	void DefaultCamera(void);
	int passn;
	bool firstpass;

// Picking Stuff

	#define PICK_BUFFER_SIZE 1024
	unsigned int PickBuffer[PICK_BUFFER_SIZE]; /* picking buffer*/
	BOOL SELECTION;

	GLint Nhits;
	void processHits2 (GLint hits, GLuint buffer[], int sw);

	int LastPickedObject;

public:
	void FlushPicking(void);

	HDC Get_DC(void);
	EasyGL();
	virtual ~EasyGL();

	int CursorX,CursorY;

// Window Control
	void CreateFromHWnd(HWND hWnd);// Create an opengl context from existing window
	void CreateFromHDC(HDC hDC);//    Create  from DC :)

	void WhileSizing(void);

//Drawing Functions
	void Pset (double X,double Y,double Z);
	void Line (double X1,double Y1,double Z1,double X2,double Y2,double Z2);
	void Sphere(double x,double y,double z,double Radius);
	//void Disk();
	//void PartialDisk();
	//void Cylinder();
	void Cube(double cenx,double ceny,double cenz,double unit);
	void Draw2dText(LPCSTR str,double,double,int);
	// For Immediate Rendering
	void RenderModel(BaseModel* BM);
	// For Buffered Rendering
	void operator<< (BaseModel& BM);


//Render Control
	void BeginRender(void);
	void EndRender(void);
	void Cls(void);
	void UpdateRender(void);
	void ClearColor(GLfloat,GLfloat,GLfloat,GLfloat);

	
//Buffered Rendering control
	vector <BaseModel*> LateModels;
	vector <BaseModel*>::iterator LModel;

	map <GLfloat,BaseModel*> SLateModels;
	map <GLfloat,BaseModel*>::iterator SLModel;
	

private:
	BOOL Rendering;
	GLfloat clsColor[4];

//Display Control
public:
	void AttachCamera(CameraModel* cam);
	void ReleaseCamera(void);

//Lighting Properties
public:
	Light* Lights[8];
	void LightModelLocalViewer(GLfloat);
	void LightModelTwoSided(GLfloat);
	void LightModelAmbient(GLfloat,GLfloat,GLfloat,GLfloat);

//Font Control
private:	
	void BuildFont(int);
    void KillFont(void);
	GLuint	base;				// Base Display List For The Font Set
public:
	GLvoid glPrint(GLint x, GLint y,const char *fmt, ...);
	LPCSTR FontName;
	int FontWeight;

//Texture Control
private:
	Texture *objectsTexture; // used in rendering internal objects
public:
	void AttachTexture(Texture *tex);
	void ReleaseTexture(void);

//Fog Control
private:
	GLuint _fogMode; // { GL_EXP, GL_EXP2, GL_LINEAR }
	GLfloat _fogColor[4];
	GLfloat _fogDensity;
	GLfloat _fogStart;
	GLfloat _fogEnd;
	BOOL FOG;
public:
	void FogSelectEXP(void);
	void FogSelectEXP2(void);
	void FogSelectLINEAR(void);
	void FogColor(GLfloat,GLfloat,GLfloat,GLfloat);
	void FogDensity(GLfloat);
	void FogStart(GLfloat);
	void FogEnd(GLfloat);
	void EnableFog(void);
	void DisableFog(void);

//Bitmap Rendering
private:
	BOOL BITMAP_RENDER;
	HBITMAP m_hbmp ;
	HBITMAP m_hbmOld ;
	void* m_pBits ;		// Pointer to the bits.
public:
	int bWidth;
	int bHeight;
	void Draw(HDC hDC, int x, int y) ;
	void CreateForBitmap(int width, int height);
	HBITMAP EasyGL::GetHBITMAP(void);

};

#endif // !defined(AFX_EASYGL_H__F3E2061E_221C_4BE3_90E9_0AE027089A6B__INCLUDED_)
