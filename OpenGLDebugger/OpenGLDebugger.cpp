// OpenGLDebugger.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenGLDebugger.h"
#include <mmsystem.h>

#include "AirFoil.h"
#include "Rotor.h"


#define MAX_LOADSTRING 100

//EasyGL using
#include "..\EasyGL.h"
EasyGL* egl;

Texture tex;
GeometricModel* gm;
Material* mtl;
CameraModel cm;

void RenderVan();
void RenderCubeVA();
void RenderTurbine();

CustomModel TurbineModel;

Rotor rot("naca0021.dat");

void render(void);
	int va[]={-1,-1,1,
		1,-1,1,
		1,1,1,
		-1,1,1,

		-1,-1,-1,
		-1,1,-1,
		1,1,-1,
		1,-1,-1,

		-1,1,-1,
		-1,1,1,
		1,1,1,
		1,1,-1,

		-1,-1,-1,
		1,-1,-1,
		1,-1,1,
		-1,-1,1,

		1,-1,-1,
		1,1,-1,
		1,1,1,
		1,-1,1,

		-1,-1,-1,
		-1,-1,1,
		-1,1,1,
		-1,1,-1};

	int no[]={0,0,1,
	0,0,-1,
	0,1,0,
	0,-1,0,
	1,0,0,
	-1,0,0};

class MyPickedObject:public PickFunctionClass
{
private:
		GeometricModel* gm;
public:
	MyPickedObject(GeometricModel* bm)
	{
		gm = bm;
	}
	void RunPickFunction(void)
	{
		gm->ItIsCylinder(1,3,0.5);
	}
};
MyPickedObject* gg;


bool zoom;
bool rMouse;
bool rMouse2;


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OPENGLDEBUGGER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_OPENGLDEBUGGER);

	// Main message loop:
	while (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		render();
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_OPENGLDEBUGGER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_OPENGLDEBUGGER;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

	egl = new EasyGL();
	egl->CreateFromHWnd(hWnd);
	//setup light

	egl->LightModelAmbient(0.2,0.2,0.2,1);

	egl->Lights[0]->Position(0,0,1,Light::LightType::Positional);
	egl->Lights[0]->Ambient(1.0,1.0,1.0,0);
	egl->Lights[0]->Diffuse(1,1,1,1);
	egl->Lights[0]->Specular(1,1,1,1);
	egl->Lights[1]->SpotCutOff(180);
	egl->Lights[0]->SpotDirection(0,0,1);
	egl->Lights[0]->SpotExponent(100);
	egl->Lights[0]->Enabled=true;

	
	egl->Lights[1]->Position(0,0,0.1,Light::LightType::Directional);
	egl->Lights[1]->Ambient(1,1,1,1);
	egl->Lights[1]->Diffuse(0,0,1,1);
	egl->Lights[1]->Specular(1,1,1,1);
	egl->Lights[1]->SpotCutOff(180);
	egl->Lights[1]->SpotDirection(0,0,1);
	egl->Lights[1]->SpotExponent(100);
	egl->Lights[1]->Enabled=true;
	egl->Lights[1]->ShowLightSource  = true;

		
	egl->Lights[2]->Position(0,2,4,Light::LightType::Positional);
	egl->Lights[2]->Ambient(0,1,1,1);
	egl->Lights[2]->Diffuse(0,0,1,1);
	egl->Lights[2]->Specular(0,1,1,1);
	//egl->Lights[2]->Enabled=true;

	gm = new GeometricModel();
	mtl = new Material();
	mtl->_Polished_Silver();

	gm->ItIsSphere(0.2);

	gm->AttachMaterial(mtl);
	cm.ChangeEye(0,0.1,4);
	cm.ChangeCenter(0,0,0);
	cm.ChangeLookUp(0,1,0);
	cm.ChangePerspective(60);
	
	//mm.RenderAddress(&RenderVan);
	TurbineModel.RenderAddress(&RenderTurbine);

	//gm->picking=true;
	//gm->pkname=10;
	//gg=new MyPickedObject(gm);
	//gm->PickFunction(gg);

	//tex.ReadImage("E:\\Sunset.jpg");
	//gm->AttachTexture(&tex);

	egl->AttachCamera(&cm);
	egl->ClearColor(0.0,0.0,0.0,1.0);
	egl->FogColor(0.5,0.5,0.5,1.0);
	egl->FogDensity(5);
	egl->FogSelectEXP();
	egl->FogEnd(5);
	egl->FogStart(-5);
	//egl->EnableFog();

   
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

int lX = 0;
int lY = 0;
int cX = 0;
int cY = 0;
float rotX, rotY, rotZ;
float ez = 4;
float ex=2, ey=2;

int rpm=10;

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_SPHERE:
			gm->ItIsSphere(0.2);
			break;
		case ID_DISK:
			gm->ItIsDisk(0.2,1);
			break;
		case ID_PARTIALDISK:
			gm->ItIsPartialDisk(0.2,1,0,250);
			break;
		case ID_CYLINDER:
			gm->ItIsCylinder(0.2,1,1);
			break;
		case ID_CUBE:
			gm->ItIsCube(0.2);
			break;
		case ID_CAMERA_RESET:
			ez = 4;
			ey = 2;
			ex = 2;
			break;

		case ID_VANRPM_20:
			rpm = 20;
			break;
		case ID_VANRPM_40:
			rpm = 40;
			break;
		case ID_VANRPM_60:
			rpm = 60;
			break;
		case ID_VANRPM_100:
			rpm = 100;
			break;
		case ID_VANRPM_200:
			rpm = 200;
			break;
		case ID_VANRPM_400:
			rpm = 400;
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	//case WM_SIZING:
	//	egl->WhileSizing();
	//	break;

	case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		egl->WhileSizing();
		break;
	

	//for mouse 
	case WM_LBUTTONDOWN:
		rMouse2=true;
		break;
	case WM_LBUTTONUP:
		rMouse2=false;
			egl->CursorX=LOWORD(lParam);
			egl->CursorY=HIWORD(lParam);
			egl->FlushPicking();
		break;
	case WM_RBUTTONDOWN:
		rMouse=true;
		break;
	case WM_RBUTTONUP:
		rMouse=false;
		break;

	case WM_MBUTTONDOWN:
		zoom=true;
		break;
	case WM_MBUTTONUP:
		zoom=false;
		break;

	case WM_MOUSEMOVE:
		{
			cX = LOWORD(lParam);
			cY = HIWORD(lParam);
			float nYDiff = (cY - lY)/2;
			float nXDiff = (cX - lX)/2;

			if (zoom)
			{
				ez += nYDiff/5;
			}
			if(rMouse)
			{
				rotY += nXDiff;
			}
			if(rMouse2)
			{
				rotX -= nYDiff;
			}
			lX = LOWORD(lParam);
			lY = HIWORD(lParam);
		}

		break;

	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
float i=-3.14;
float v=0;
void render(void)
{
	if(i<3.14)
	{
		i+=0.05;
	}
	else
	{
		i=-3.14;
	}
	if(v<360)
	{
		v+=1;
	}
	else
	{
		v=0;
	}


	static long pt = timeGetTime();
	long ct = timeGetTime();

	static GLdouble dd=0;
	double scs;
	if (ct>pt)
	{
		//calculate how many seconds
		long pr  = ct-pt;

		scs = (double)pr/1000;

		pt = ct;

		dd+=(rpm*6)*scs;
		if(dd>360)
		{
			dd=dd-360;
		}
	}

	TurbineModel.Translate(0,0,-1.1,false);
	TurbineModel.Rotate(-dd,0,0,1,true);

	gm->Translate(0,0,1.5,false);
	//gm->Rotate(v,1,0,0,true);


	cm.ChangeEye(ex, ey, ez);
	cm.Rotate(0, -1, 0, rotY);
	cm.RotateAccum(1, 0, 0, rotX);

	Material TurbineMaterial;
	TurbineMaterial._Silver();
	TurbineModel.AttachMaterial(&TurbineMaterial);


	egl->BeginRender();
		
		egl->Line(0,0,0,10,0,0);
		egl->Line(0,0,0,0,10,0);
		egl->Line(0,0,-10,0,0,10);

		egl->RenderModel(gm);		

		egl->RenderModel(&TurbineModel);
		

		
	egl->EndRender();
	egl->UpdateRender();
}
void RenderVan()
{
	static int g=0;
	//glScalef(size,size,size);

	const int wings=6;	
	const float dq=360/wings;
	if (g<360){g+=1;}else {g=0;}

	for (int i=1;i<=wings;i++)
	{
		glPushMatrix();
			glRotated (dq*i,0,0,1);
			glBegin(GL_TRIANGLES);
				//x  y      z
				//1, 0.15 , -0.15
				//1, 0    , 0

				glVertex3i(0,0,0);
				
				glNormal3d(1,0.25,-0.25);
				glColor3f(0.0,0.1,0.5);
				glVertex3d(1,0.25,-0.25);
				
				glNormal3d(1,0,0);
				glVertex3d(1,0,0);
			glEnd();
		glPopMatrix();
		
	}
}
void RenderTurbine()
{

	rot.ShaftDiameter = 2.54;   //Diameter = 45 mm  Length=
	rot.ShaftLength = 1;	


	rot.BladeAngle = 30;     //increase the trailing edge with the angle men na7iet el estwana
	rot.BladesNumber=8;
	rot.Blade.Span=0.95;


	rot.GLDraw();
}

void RenderCubeVA()
{


	glVertexPointer(3,GL_INT,0,va);
	glNormalPointer(3,GL_INT,no);
	

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	
	glPushMatrix();
		//glScalef(0.2,0.2,0.2);
		glDrawArrays(GL_QUADS,0,24);

	glPopMatrix();
}