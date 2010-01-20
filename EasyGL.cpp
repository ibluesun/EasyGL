// EasyGL.cpp: implementation of the EasyGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EasyGL.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EasyGL::EasyGL()
{

	passn=0;
	firstpass=true;

	// InActive Render Processing.
	Rendering=FALSE;
	// Create Lights
	for (int i=0;i<=7;i++)
	{
		Lights[i]=new Light(this);
		Lights[i]->LightNumber=i;
	}
	//Font Defaults
	FontName="Times New Roman";
	FontWeight=FW_NORMAL;

	objectsTexture=NULL;

	ClearColor(0,0,0,1);
	FOG=FALSE;

	//Specify the default camera
	DefaultCamera();
			
	LastPickedObject = -100;

	BITMAP_RENDER=FALSE;

}

EasyGL::~EasyGL()
{
	wglMakeCurrent(NULL,NULL);
	if(BITMAP_RENDER)
		DeleteDC (GLDC);
	else
		ReleaseDC(GLWND,GLDC);
}

void EasyGL::CreateFromHWnd(HWND hWnd)
{
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion   = 1 ;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA ;
	pfd.cColorBits = 16 ;
	pfd.cDepthBits = 16 ;
	pfd.cAccumBits = 0 ;
	pfd.iLayerType = PFD_MAIN_PLANE ;
	//------------------
	GLWND = hWnd;
	GLDC = GetDC(GLWND);
	//
	int nPixelFormat = ChoosePixelFormat(GLDC, &pfd);
	//
	BOOL bResult = SetPixelFormat (GLDC, nPixelFormat, &pfd);
	//
	hRC = wglCreateContext(GLDC);
	wglMakeCurrent(GLDC,hRC);
	CurrentCamera=NULL;
	this->FontName="Arial";
	this->BuildFont(8);
	SELECTION=FALSE;
}

void EasyGL::CreateFromHDC(HDC hDC)
{
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion   = 1 ;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW ;
	pfd.iPixelType = PFD_TYPE_RGBA ;
	pfd.cColorBits = 16 ;
	pfd.cDepthBits = 16 ;
	pfd.iLayerType = PFD_MAIN_PLANE ;
	//------------------
	GLDC = hDC;
	GLWND = WindowFromDC(GLDC);
	//
	int nPixelFormat = ChoosePixelFormat(GLDC, &pfd);
	//
	BOOL bResult = SetPixelFormat (GLDC, nPixelFormat, &pfd);
	//
	hRC = wglCreateContext(GLDC);
	wglMakeCurrent(GLDC,hRC);
	CurrentCamera=NULL;
	this->BuildFont(8);
	SELECTION=FALSE;
}

void EasyGL::CreateForBitmap(int iWidth, int iHeight)
{  
	// Create a BITMAPINFOHEADER structure to describe the DIB
	BITMAPINFOHEADER BIH ;
	int iSize = sizeof(BITMAPINFOHEADER) ;
	memset(&BIH, 0, iSize);

	// Fill in the header info.
	BIH.biSize = iSize;
	BIH.biWidth = iWidth;
	BIH.biHeight = iHeight;
	BIH.biPlanes = 1;
	BIH.biBitCount = 32;
	BIH.biCompression = BI_RGB;

	bWidth = iWidth;
	bHeight = iHeight;

	
	GLDC = CreateCompatibleDC(NULL);

	//GLDC = CreateDC(NULL,NULL,NULL,NULL);
 

	GLWND = NULL;  // explictly null this is a bitmap


	// Create the DIB section.
	m_hbmp = CreateDIBSection(GLDC,
                   		(BITMAPINFO*)&BIH,
                   		DIB_RGB_COLORS,
                   		&m_pBits,
                   		NULL,
                   		0);

	BITMAP_RENDER = TRUE;
	// Select the new bitmap into the buffer DC
	if (m_hbmp)
	{
		m_hbmOld = (HBITMAP)SelectObject(GLDC, m_hbmp);
	}


	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion   = 1 ;
	pfd.dwFlags    = PFD_SUPPORT_GDI | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_BITMAP ;
	pfd.iPixelType = PFD_TYPE_RGBA ;
	pfd.cColorBits = 32 ;
	pfd.cDepthBits = 32 ;
	pfd.iLayerType = PFD_MAIN_PLANE ;


	//
	int nPixelFormat = ChoosePixelFormat(GLDC, &pfd);
	//
	BOOL bResult = SetPixelFormat (GLDC, nPixelFormat, &pfd);
	//
	hRC = wglCreateContext(GLDC);
	wglMakeCurrent(GLDC,hRC);
	CurrentCamera=NULL;

	this->BuildFont(8);
	SELECTION=FALSE;
}

//
// BitBlt DIB section to the screen. Does not mess with the palette.
//
void EasyGL::Draw(HDC hDC, int x, int y) 
{
    // Note: you do not need to select the palette into
    // the memory DC because the DIB section is using palette
    // index values not colors
    BitBlt( hDC,
		x, y,
        bWidth, bHeight,
        GLDC,
        0, 0,
        SRCCOPY);
}

HBITMAP EasyGL::GetHBITMAP(void)
{
	return m_hbmp;
}


double EasyGL::Get_Aspect(void)
{
	RECT rc;
	int cx;
	int cy;
	if(BITMAP_RENDER)
	{
		cx = bWidth;
		cy = bHeight;
	}
	else
	{
		GetClientRect(GLWND,&rc);
		cx=rc.right-rc.left;	
		cy=rc.bottom-rc.top;
	}
    
	if (!cy) return 0;

	GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	return gldAspect;
}

HDC EasyGL::Get_DC()
{
	return GLDC;
}

void EasyGL::ClearColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	clsColor[0]=r;
	clsColor[1]=g;
	clsColor[2]=b;
	clsColor[3]=a;
}
void EasyGL::Cls(void)
{
	glClearColor(clsColor[0],clsColor[1],clsColor[2],clsColor[3]);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EasyGL::AttachTexture(Texture *tex)
{
	objectsTexture=tex;
}
void EasyGL::ReleaseTexture()
{
	objectsTexture=NULL;
}

void EasyGL::BeginRender()
{
	

	wglMakeCurrent(GLDC,hRC);

	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	if (CurrentCamera!=NULL)  
	{
		if (SELECTION)      //setup camera for selection Look to another part in end render
		{
			CurrentCamera->SetupWithPicking(this,CursorX,CursorY);
		}
		else
		{
			//remember i got this code 
			//from end render 
			//
			CurrentCamera->Setup(this);
		}
	}

	
	if (SELECTION)
	{
		glSelectBuffer( PICK_BUFFER_SIZE, this->PickBuffer );
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(-1);


	}
	if (Rendering==FALSE) // If rendering process is off
	{

		glMatrixMode(GL_MODELVIEW);
		this->Cls();


		// Turn rendering process on
		Rendering=TRUE; 

		//Light our life
		//glEnable(GL_CULL_FACE); // Do not calculate inside of jet
		//glFrontFace(GL_CCW); // Counter clock-wise polygons face out
		glEnable (GL_LIGHTING);	
		//glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
		//glEnable ( GL_COLOR_MATERIAL ) ;
		for (int i=0;i<=7;i++){this->Lights[i]->LightIt();} 


		// Adjust the depth buffer	
		glEnable(GL_DEPTH_TEST); // Enables Depth Testing
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really ?!

		// Fog
		if (FOG)
		{
			glFogi(GL_FOG_MODE, _fogMode); // Fog Mode
			glFogfv(GL_FOG_COLOR, _fogColor); // Set Fog Color
			glFogf(GL_FOG_DENSITY, _fogDensity); // How Dense Will The Fog Be
			glHint(GL_FOG_HINT, GL_DONT_CARE); // Fog Hint Value
			glFogf(GL_FOG_START, _fogStart); // Fog Start Depth
			glFogf(GL_FOG_END, _fogEnd); // Fog End Depth
			glEnable(GL_FOG); // Enables GL_FOG
		}
		if (!FOG)
		{
			glDisable(GL_FOG);
		}
	}
		


}



void EasyGL::EndRender()
{

	GLfloat mx,my,mz,mcd;

	// now after we know our camera we will make our delayed objects
	for (LModel=LateModels.begin();LModel!=LateModels.end();LModel++)
	{
		// calculate the space between the object and camera
		(*LModel)->get_postion(&mx,&my,&mz);
		mcd = CurrentCamera->GetDistantFromEye(mx,my,mz);

		// put it in the map SLateModels with distant
		SLateModels.insert(map <GLfloat,BaseModel*>::value_type(mcd,(*LModel)));
		
		//the above code has a bug that when two objects have the same
		// length the last object will replace the previuos object
		// try to solve this bug sooon  .,,  for me "Ahmed Sadek:"


	}
	
	passn++;


	glEnable(GL_BLEND); // Turn Blending On
	glDepthMask (GL_FALSE); // Turn Depth Testing Off		

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blending Function For Translucency

	// loop but in map and draw the objects
	for (SLModel=SLateModels.begin();SLModel!=SLateModels.end();SLModel++)
	{
		glLoadName((*SLModel).second->pkname); // the name in selection
		// render it

		(*SLModel).second->Render();
	}

	glDepthMask (GL_TRUE); // Turn Depth Testing On
	glDisable(GL_BLEND); // Turn Blending Off

	//setup camera for displaying this tricky thing
	// coz if put it in begin render something wrong happen  he he he

	if (CurrentCamera!=NULL) 
	{
		if (SELECTION)
		{
			CurrentCamera->Setup(this);
		}
	}

	// Turn Rendering process off
	Rendering=FALSE;
}
void EasyGL::UpdateRender()
{
	if (Rendering!=TRUE) //If rendering process is inactive
	{

			glFlush();

			//if (firstpass)
			//{
			//	firstpass=false;
			//	glAccum(GL_LOAD,1.0);
			//}
			//if(passn<330 && passn>0)
			//{			
			//	//glClearAccum(0,0,0,1);
			//	//glClearAccum(0.0,0.0,0.0,0.0);
			//	glAccum(GL_MULT,0.5);
			//	passn++;
			//}
			//if(passn>330)
			//{
			//	glAccum(GL_MULT,0.5);
			//	glAccum(GL_RETURN,1.0);
			//	
			//	//passn=0;
			//	//firstpass = true;
			//}

		//reset selection state
		if (SELECTION == TRUE)
		{
			SELECTION=FALSE;
			Nhits = glRenderMode (GL_RENDER);
			if (Nhits!=0)	processHits2(Nhits,PickBuffer,0);
		}

		if (SELECTION==FALSE)
		{

			SwapBuffers(GLDC) ;
		}

		//Clear the buffered objects
		SLateModels.clear();
		LateModels.clear();
	}

}

void EasyGL::Pset(double X,double Y,double Z)
{
	if (Rendering==TRUE)
	{
		glPushMatrix();	
		glPushAttrib(GL_CURRENT_BIT);
		glBegin(GL_POINTS);
			glVertex3d(X,Y,Z);
		glEnd();
		glPopAttrib();
		glPopMatrix();
	}
}

void EasyGL::Line (double X1,double Y1,double Z1,double X2,double Y2,double Z2)
{
	if (Rendering==TRUE)
	{
		glPushMatrix();	
		glPushAttrib(GL_CURRENT_BIT);
		glBegin(GL_LINES);
			glVertex3d(X1,Y1,Z1);
			glVertex3d(X2,Y2,Z2);
		glEnd();
		glPopAttrib();
		glPopMatrix();
	}
}
	
void EasyGL::Sphere(double x,double y,double z,double Radius)
{
	if (Rendering==TRUE)
	{
		GLUquadricObj* sph=gluNewQuadric();
		gluQuadricDrawStyle(sph,GLU_FILL); 
		gluQuadricNormals(sph,GLU_SMOOTH); 
		if (objectsTexture!=NULL)
		{
			gluQuadricTexture(sph,GL_TRUE);		// To Calculate Tex Coor
			glEnable(GL_TEXTURE_2D);
			objectsTexture->ApplyTexture();
		}
		glPushMatrix();	
			glPushAttrib(GL_CURRENT_BIT);
				glTranslated(x,y,z);
				gluSphere(sph,Radius,20,40);
			glPopAttrib();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(sph);
	}
}
void EasyGL::Draw2dText(LPCSTR str,double x,double y,int volume)
{
	// The text must be written into the eye coordinate
	// I haven't implemented this yet

	if (Rendering==TRUE)
	{
		
		glPushMatrix();
			KillFont();
			glPushAttrib(GL_CURRENT_BIT);
			BuildFont(volume);
				//glTranslatef((float)x,(float)y,0.0f);						// Move One Unit Into The Screen
				// Position The Text On The Screen
				glRasterPos2d(x,y);
				glPrint(x,y,str);
			glPopAttrib();
		glPopMatrix();
	}
}

void EasyGL::Cube(double cenx,double ceny,double cenz,double unit)
{
	if (Rendering==TRUE)
	{
		if (objectsTexture!=NULL)
		{
			glEnable(GL_TEXTURE_2D);
			objectsTexture->ApplyTexture();
		}
		glPushMatrix();	
			glTranslated(cenx,ceny,cenz);
			glScaled(unit,unit,unit);
			glPushAttrib(GL_CURRENT_BIT);
			glBegin(GL_QUADS);
				// Front Face
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 1 (Front)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 2 (Front)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Front)
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 4 (Front)
				// Back Face
				glNormal3f( 0.0f, 0.0f,-1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Back)
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point 2 (Back)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 3 (Back)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 4 (Back)
				// Top Face
				glNormal3f( 0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point 1 (Top)
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 2 (Top)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Top)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 4 (Top)
				// Bottom Face
				glNormal3f( 0.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Bottom)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 2 (Bottom)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 3 (Bottom)
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 4 (Bottom)
				// Right face
				glNormal3f( 1.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Point 1 (Right)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Point 2 (Right)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Point 3 (Right)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Point 4 (Right)
				// Left Face
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Left)
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Point 2 (Left)
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Point 3 (Left)
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Point
			glEnd();
			glPopAttrib();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
}
void EasyGL::RenderModel(BaseModel* BM)
{
	if (Rendering==TRUE && BM!=NULL)
	{
		if (BM->pkname==LastPickedObject)
		{
			BM->RunPickFunction();
			LastPickedObject = -1;
		}
		glLoadName(BM->pkname);
		BM->Render();
	}
}
void EasyGL::operator <<(BaseModel& BM)
{
	// Buffer For Late Rendering
	// used specifically in blending
	if ((&BM)!=NULL)
	{
		if (BM.pkname==LastPickedObject)
		{
			BM.RunPickFunction();
			LastPickedObject = -1;
		}
		
		LateModels.push_back(&BM);
	}
	if (Rendering==TRUE && (&BM)!=NULL)
	{
		//BM.Render();
	}
}

void EasyGL::DefaultCamera()
{
	CurrentCamera = new CameraModel;
	CurrentCamera->Setup(this);
}

void EasyGL::WhileSizing(void)
{
	if (GLWND!=NULL){
	wglMakeCurrent(GLDC,hRC);
	//----------------------------------------------
	RECT rc;
	GetClientRect(GLWND,&rc);
	int cx=rc.right-rc.left;
	int cy=rc.bottom-rc.top;
    
	if (!cy) return;

	GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
			glClear(GL_ACCUM_BUFFER_BIT);

	glViewport(0, 0, cx, cy);
	if (CurrentCamera!=NULL){
			CurrentCamera->Setup(this);
		}//else{DefaultCamera();}
	}
}

void EasyGL::AttachCamera(CameraModel* cam)
{
		CurrentCamera=cam;
}
void EasyGL::ReleaseCamera()
{
	CurrentCamera=NULL;
}

void EasyGL::BuildFont(int nWidth)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-nWidth*2,							// Height Of Font
						nWidth,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FontWeight,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						DEFAULT_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						FontName);					// Font Name

	SelectObject(GLDC, font);							// Selects The Font We Want

	wglUseFontBitmaps(GLDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
}

void EasyGL::KillFont(void)									// Delete The Font
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid EasyGL::glPrint(GLint x, GLint y,const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text
	
	RECT rc;
	GetClientRect(GLWND,&rc);

	glRasterPos2i(x,y);
	glPushAttrib(GL_LIST_BASE);
		glListBase(base - 31);								// Sets The Base Character to 32
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();

}

void EasyGL::LightModelAmbient(GLfloat R,GLfloat G,GLfloat B,GLfloat A)
{
	GLfloat amb[4];
	amb[0]=R;
	amb[1]=G;
	amb[2]=B;
	amb[3]=A;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
}
void EasyGL::LightModelLocalViewer(GLfloat LV)
{
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,LV);
}
void EasyGL::LightModelTwoSided(GLfloat TS)
{
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,TS);
}

//////////////////////////////////////////////////////////
//// Just for Fog

void EasyGL::FogSelectEXP()
{
	_fogMode=GL_EXP;
}
void EasyGL::FogSelectEXP2()
{
	_fogMode=GL_EXP2;
}
void EasyGL::FogSelectLINEAR()
{
	_fogMode=GL_LINEAR;
}

void EasyGL::FogColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	_fogColor[0]=r;
	_fogColor[1]=g;
	_fogColor[2]=b;
	_fogColor[3]=a;
}

void EasyGL::FogDensity(GLfloat fd)
{
	_fogDensity=fd;
}

void EasyGL::FogStart(GLfloat fs)
{
	_fogStart=fs;
}
void EasyGL::FogEnd(GLfloat fe)
{
	_fogEnd=fe;
}

void EasyGL::EnableFog()
{
	FOG=TRUE;
}
void EasyGL::DisableFog()
{
	FOG=FALSE;
}


/////////////////////////////////////////////////////////
///////////////////////
//// this is the picking code
///
//
void EasyGL::processHits2(GLint hits,GLuint buffer[],int sw)
{
   GLint i, j, numberOfNames;
   GLuint names, *ptr, minZ,*ptrNames;

   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  
	  ptr += names+2;
	}
   

   if (numberOfNames > 0) {
	  ptr = ptrNames;
	  for (j = 0; j < numberOfNames; j++,ptr++) { 
		  LastPickedObject = *ptr;
	  }
	}
}

void EasyGL::FlushPicking (void)
{
	//Just make selection flag true and it auomatically return to false.
	SELECTION = TRUE;
}
