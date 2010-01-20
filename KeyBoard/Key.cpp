#include "stdafx.h"
#include "Key.h"

//Front Face Width
#define FFW 0.6f

// Button Height
#define BH 0.45f 

/*
	KeyBoard Implementation
*/
KeyBoard::KeyBoard(HWND hWnd)
{
	this->egl = new EasyGL();
	egl->CreateFromHWnd(hWnd);
	
	//setup light
	egl->Lights[0]->Position(0.0,0,7, Light::LightType::Directional);
	egl->Lights[0]->Ambient(1,1,1,0);
	egl->Lights[0]->Diffuse(1,1,1,0);
	egl->Lights[0]->Specular(1,1,1,0);
	egl->Lights[0]->Enabled=true;	
	
	//egl->Lights[1]->Position(0,0,7,0);
	//egl->Lights[1]->Ambient(1,0,0,0);
	//egl->Lights[1]->Specular(0.5,0.5,0.5,1.0);
	//egl->Lights[1]->Diffuse(1,0,0,1.0);
	//egl->Lights[1]->Enabled=true;

	cm.ChangeEye(2.8,-2.5,9);
	cm.ChangeCenter(2.8,-1,0);
	cm.ChangeLookUp(0,1,0);
	cm.ChangePerspective(24);
	//cm.RotateAboutCenter(1,0,0,40);

	egl->AttachCamera(&cm);
	egl->ClearColor(0.2f,0.2f,0.8f,1.0f);


	m_Functions[0] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[1] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[2] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[3] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[4] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[5] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[6] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[7] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[8] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[9] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[10] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[11] = new Button(this,"Data\\Number_8.bmp");
	m_Functions[12] = new Button(this,"Data\\Number_8.bmp");

	m_Numbers[0] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[1] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[2] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[3] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[4] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[5] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[6] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[7] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[8] = new Button(this,"Data\\Number_8.bmp");
	m_Numbers[9] = new Button(this,"Data\\Number_8.bmp");


	m_Letters[0] = new Button(this,"Data\\Letter2.bmp");
	m_Letters[1] = new Button(this,"Data\\Letter1.bmp");
	m_Letters[2] = new Button(this,"Data\\Letter2.bmp");
	m_Letters[3] = new Button(this,"Data\\Letter3.bmp");
	m_Letters[4] = new Button(this,"Data\\Letter4.bmp");
	m_Letters[5] = new Button(this,"Data\\Letter5.bmp");
	m_Letters[6] = new Button(this,"Data\\Letter6.bmp");
	m_Letters[7] = new Button(this,"Data\\Letter7.bmp");
	m_Letters[8] = new Button(this,"Data\\Letter8.bmp");
	m_Letters[9] = new Button(this,"Data\\Letter9.bmp");
	m_Letters[10] = new Button(this,"Data\\Letter10.bmp");
	m_Letters[11] = new Button(this,"Data\\Letter11.bmp");
	m_Letters[12] = new Button(this,"Data\\Letter12.bmp");
	m_Letters[13] = new Button(this,"Data\\Letter13.bmp");
	m_Letters[14] = new Button(this,"Data\\Letter14.bmp");
	m_Letters[15] = new Button(this,"Data\\Letter15.bmp");
	m_Letters[16] = new Button(this,"Data\\Letter16.bmp");
	m_Letters[17] = new Button(this,"Data\\Letter17.bmp");
	m_Letters[18] = new Button(this,"Data\\Letter18.bmp");
	m_Letters[19] = new Button(this,"Data\\Letter19.bmp");
	m_Letters[20] = new Button(this,"Data\\Letter20.bmp");
	m_Letters[21] = new Button(this,"Data\\Letter21.bmp");
	m_Letters[22] = new Button(this,"Data\\Letter22.bmp");
	m_Letters[23] = new Button(this,"Data\\Letter23.bmp");
	m_Letters[24] = new Button(this,"Data\\Letter24.bmp");
	m_Letters[25] = new Button(this,"Data\\Letter25.bmp");
	m_Letters[26] = new Button(this,"Data\\Letter26.bmp");
	m_Letters[27] = new Button(this,"Data\\Letter27.bmp");
	m_Letters[28] = new Button(this,"Data\\Letter28.bmp");
	
	m_Ya2Dot = new Button(this,"Data\\Letter28.bmp");
	m_Hamza = new Button(this,"Data\\Letter28.bmp");
	m_HamzaOnYa = new Button(this,"Data\\Letter28.bmp");
	m_HamzaOnWow = new Button(this,"Data\\Letter28.bmp");
	m_La = new Button(this,"Data\\Letter28.bmp");
	m_TaMarbota= new Button(this,"Data\\Letter28.bmp");



	m_Minus = new Button(this,"Data\\Letter2.bmp");
	m_Equal = new Button(this,"Data\\Letter2.bmp");
	m_Div = new Button(this,"Data\\Letter2.bmp");
	m_BackSpace = new Button(this,"Data\\Letter2.bmp");


	m_TAB = new VariableButton(this,"Data\\Letter2.bmp",1.0f);
	m_CAPS = new VariableButton(this,"Data\\Letter2.bmp",1.2f);
	m_LSHIFT = new VariableButton(this,"Data\\Letter2.bmp",2.0f);
	m_RSHIFT = new VariableButton(this,"Data\\Letter2.bmp",4.0f);


	m_LCTRL = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_LWIN = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_LALT = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_SPACE = new VariableButton(this,"Data\\Letter2.bmp",9.86f);
	m_RALT = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_RWIN = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_APPS = new VariableButton(this,"Data\\Letter2.bmp",0.6f);
	m_RCTRL = new VariableButton(this,"Data\\Letter2.bmp",0.6f);

	m_Enter = new Enter(this,"Data\\Letter2.bmp");

	Build();	
}

void KeyBoard::Build(void)
{
	/// First build drawing pattern

	//static int Row1[]={8,1,2,3,4,5,6,7,8,9,0}
	Row1.push_back(m_Letters[9]);
	Row1.push_back(m_Numbers[1]);
	Row1.push_back(m_Numbers[2]);
	Row1.push_back(m_Numbers[3]);
	Row1.push_back(m_Numbers[4]);
	Row1.push_back(m_Numbers[5]);
	Row1.push_back(m_Numbers[6]);
	Row1.push_back(m_Numbers[7]);
	Row1.push_back(m_Numbers[8]);
	Row1.push_back(m_Numbers[9]);
	Row1.push_back(m_Numbers[0]);
	Row1.push_back(m_Minus);
	Row1.push_back(m_Equal);
	Row1.push_back(m_Div);
	Row1.push_back(m_BackSpace);
	MyKeys.insert(KeyHash::value_type(0xC0,m_Letters[9]));m_Letters[9]->pkname=0xC0;
	MyKeys.insert(KeyHash::value_type(0x31,m_Numbers[1]));m_Numbers[1]->pkname=0x31;
	MyKeys.insert(KeyHash::value_type(0x32,m_Numbers[2]));m_Numbers[2]->pkname=0x32;
	MyKeys.insert(KeyHash::value_type(0x33,m_Numbers[3]));m_Numbers[3]->pkname=0x33;
	MyKeys.insert(KeyHash::value_type(0x34,m_Numbers[4]));m_Numbers[4]->pkname=0x34;
	MyKeys.insert(KeyHash::value_type(0x35,m_Numbers[5]));m_Numbers[5]->pkname=0x35;
	MyKeys.insert(KeyHash::value_type(0x36,m_Numbers[6]));m_Numbers[6]->pkname=0x36;
	MyKeys.insert(KeyHash::value_type(0x37,m_Numbers[7]));m_Numbers[7]->pkname=0x37;
	MyKeys.insert(KeyHash::value_type(0x38,m_Numbers[8]));m_Numbers[8]->pkname=0x38;
	MyKeys.insert(KeyHash::value_type(0x39,m_Numbers[9]));m_Numbers[9]->pkname=0x39;
	MyKeys.insert(KeyHash::value_type(0x30,m_Numbers[0]));m_Numbers[0]->pkname=0x30;
	MyKeys.insert(KeyHash::value_type(0xBD,m_Minus));m_Minus->pkname=0xBD;
	MyKeys.insert(KeyHash::value_type(0xBB,m_Equal));m_Equal->pkname=0xBB;
	MyKeys.insert(KeyHash::value_type(0xDC,m_Div));m_Div->pkname=0xDC;
	MyKeys.insert(KeyHash::value_type(0x08,m_BackSpace));m_BackSpace->pkname=0x08;
	

	//static int Row2[]={15,14,4,21,20,19,18,26,7,6,5,8};
	Row2.push_back(m_TAB);
	Row2.push_back(m_Letters[15]);
	Row2.push_back(m_Letters[14]);
	Row2.push_back(m_Letters[4]);
	Row2.push_back(m_Letters[21]);
	Row2.push_back(m_Letters[20]);
	Row2.push_back(m_Letters[19]);
	Row2.push_back(m_Letters[18]);
	Row2.push_back(m_Letters[26]);
	Row2.push_back(m_Letters[7]);
	Row2.push_back(m_Letters[6]);
	Row2.push_back(m_Letters[5]);
	Row2.push_back(m_Letters[8]);

	MyKeys.insert(KeyHash::value_type(0x09,m_TAB));m_TAB->pkname=0x09;
	MyKeys.insert(KeyHash::value_type(0x51,m_Letters[15]));m_Letters[15]->pkname=0x51;
	MyKeys.insert(KeyHash::value_type(0x57,m_Letters[14]));m_Letters[14]->pkname=0x57;
	MyKeys.insert(KeyHash::value_type(0x45,m_Letters[4]));m_Letters[4]->pkname=0x45;
	MyKeys.insert(KeyHash::value_type(0x52,m_Letters[21]));m_Letters[21]->pkname=0x52;
	MyKeys.insert(KeyHash::value_type(0x54,m_Letters[20]));m_Letters[20]->pkname=0x54;
	MyKeys.insert(KeyHash::value_type(0x59,m_Letters[19]));m_Letters[19]->pkname=0x59;
	MyKeys.insert(KeyHash::value_type(0x55,m_Letters[18]));m_Letters[18]->pkname=0x55;
	MyKeys.insert(KeyHash::value_type(0x49,m_Letters[26]));m_Letters[26]->pkname=0x49;
	MyKeys.insert(KeyHash::value_type(0x4F,m_Letters[7]));m_Letters[7]->pkname=0x4F;
	MyKeys.insert(KeyHash::value_type(0x50,m_Letters[6]));m_Letters[6]->pkname=0x50;
	MyKeys.insert(KeyHash::value_type(0xDB,m_Letters[5]));m_Letters[5]->pkname=0xDB;
	MyKeys.insert(KeyHash::value_type(0xDD,m_Letters[8]));m_Letters[8]->pkname=0xDD;

	//static int Row3[]={13,12,0,2,23,1,3,25,24,22,16};
	Row3.push_back(m_CAPS);
	Row3.push_back(m_Letters[13]);
	Row3.push_back(m_Letters[12]);
	Row3.push_back(m_Ya2Dot);
	Row3.push_back(m_Letters[2]);
	Row3.push_back(m_Letters[23]);
	Row3.push_back(m_Letters[1]);
	Row3.push_back(m_Letters[3]);
	Row3.push_back(m_Letters[25]);
	Row3.push_back(m_Letters[24]);
	Row3.push_back(m_Letters[22]);
	Row3.push_back(m_Letters[16]);

	MyKeys.insert(KeyHash::value_type(0x14,m_CAPS));m_CAPS->pkname=0x14;
	MyKeys.insert(KeyHash::value_type(0x41,m_Letters[13]));m_Letters[13]->pkname=0x41;
	MyKeys.insert(KeyHash::value_type(0x53,m_Letters[12]));m_Letters[12]->pkname=0x53;
	MyKeys.insert(KeyHash::value_type(0x44,m_Ya2Dot));m_Ya2Dot->pkname =0x44;
	MyKeys.insert(KeyHash::value_type(0x46,m_Letters[2]));m_Letters[2]->pkname=0x46;
	MyKeys.insert(KeyHash::value_type(0x47,m_Letters[23]));m_Letters[23]->pkname=0x47;
	MyKeys.insert(KeyHash::value_type(0x48,m_Letters[1]));m_Letters[1]->pkname=0x48;
	MyKeys.insert(KeyHash::value_type(0x4A,m_Letters[3]));m_Letters[3]->pkname=0x4A;
	MyKeys.insert(KeyHash::value_type(0x4B,m_Letters[25]));m_Letters[25]->pkname=0x4B;
	MyKeys.insert(KeyHash::value_type(0x4C,m_Letters[24]));m_Letters[24]->pkname=0x4C;
	MyKeys.insert(KeyHash::value_type(0xBA,m_Letters[22]));m_Letters[22]->pkname=0xBA;
	MyKeys.insert(KeyHash::value_type(0xDE,m_Letters[16]));m_Letters[16]->pkname=0xDE;

	//static int Row4[]={0,0,0,10,0,28,0,27,11,17};
	Row4.push_back(m_LSHIFT);
	Row4.push_back(m_HamzaOnYa);
	Row4.push_back(m_Hamza);
	Row4.push_back(m_HamzaOnWow);
	Row4.push_back(m_Letters[10]);
	Row4.push_back(m_La);
	Row4.push_back(m_Letters[28]);
	Row4.push_back(m_TaMarbota);
	Row4.push_back(m_Letters[27]);
	Row4.push_back(m_Letters[11]);
	Row4.push_back(m_Letters[17]);
	Row4.push_back(m_RSHIFT);
	MyKeys.insert(KeyHash::value_type(0x5A,m_HamzaOnYa));m_HamzaOnYa->pkname=0x5a;
	MyKeys.insert(KeyHash::value_type(0x58,m_Hamza));m_Hamza->pkname=0x58;
	MyKeys.insert(KeyHash::value_type(0x43,m_HamzaOnWow));m_HamzaOnWow->pkname=0x43;
	MyKeys.insert(KeyHash::value_type(0x56,m_Letters[10]));m_Letters[10]->pkname=0x56;
	MyKeys.insert(KeyHash::value_type(0x42,m_La));m_La->pkname=0x42;
	MyKeys.insert(KeyHash::value_type(0x4E,m_Letters[28]));m_Letters[28]->pkname=0x4E;
	MyKeys.insert(KeyHash::value_type(0x4D,m_TaMarbota));m_TaMarbota->pkname=0x4D;
	MyKeys.insert(KeyHash::value_type(0xBC,m_Letters[27]));m_Letters[27]->pkname=0xBC;
	MyKeys.insert(KeyHash::value_type(0xBE,m_Letters[11]));m_Letters[11]->pkname=0xBE;
	MyKeys.insert(KeyHash::value_type(0xBF,m_Letters[17]));m_Letters[17]->pkname=0xBF;


	Row5.push_back(m_LCTRL);
	Row5.push_back(m_LWIN);
	Row5.push_back(m_LALT);
	Row5.push_back(m_SPACE);
	Row5.push_back(m_RALT);
	Row5.push_back(m_RWIN);
	Row5.push_back(m_APPS);
	Row5.push_back(m_RCTRL);
	MyKeys.insert(KeyHash::value_type(VK_LWIN,m_LWIN));m_LWIN->pkname=VK_LWIN;
	MyKeys.insert(KeyHash::value_type(VK_RWIN,m_RWIN));m_RWIN->pkname=VK_RWIN;
	MyKeys.insert(KeyHash::value_type(VK_APPS,m_APPS));m_APPS->pkname=VK_APPS;
	MyKeys.insert(KeyHash::value_type(VK_SPACE,m_SPACE));m_SPACE->pkname=VK_SPACE;
	MyKeys.insert(KeyHash::value_type(VK_RETURN,m_Enter));m_Enter->pkname=VK_RETURN;


}

void KeyBoard::Draw(void)
{
	int i=0;

	egl->BeginRender();

	//glLoadIdentity();
	//glTranslated(0.5,0.0,0.0);
	//glBegin(GL_QUADS);
	//	glVertex3d(-1,0,-0.5);
	//	glVertex3d(1,0,-0.5);
	//	glVertex3d(1,0,0.5);
	//	glVertex3d(-1,0,0.5);
	//glEnd();

	//ROW 1
	for(ptrKey=Row1.begin();ptrKey!=Row1.end();ptrKey++)
	{
		IKey* kk=(*ptrKey);
		kk->x=i*2;
		kk->y=4;
		egl->RenderModel(kk);
		//kk->Draw(i*2,4,0);
		i++;
	}

	//ROW 2
	i=0;
	ptrKey=Row2.begin();
	(*ptrKey)->x=(i*2)+.5;
	(*ptrKey)->y=2;
	egl->RenderModel((*ptrKey));
	//(*ptrKey)->Draw((i*2)+.5,2,0);
	ptrKey++;
	for(;ptrKey!=Row2.end();ptrKey++)
	{
		IKey* kk=(*ptrKey);
		kk->x=(i*2)+2.9;
		kk->y=2;
		egl->RenderModel(kk);
		//(*ptrKey)->Draw((i*2)+2.9,2,0);
		i++;
	}

	//ROW 3
	i=0;
	ptrKey=Row3.begin();
	(*ptrKey)->x=(i*2)+.6;
	(*ptrKey)->y=0;
	egl->RenderModel((*ptrKey));
	//(*ptrKey)->Draw((i*2)+.6,0,0);
	ptrKey++;
	for(;ptrKey!=Row3.end();ptrKey++)
	{
		IKey* kk=(*ptrKey);
		kk->x=(i*2)+3.2;
		kk->y=0;
		egl->RenderModel(kk);
		//(*ptrKey)->Draw((i*2)+3.2,0,0);
		i++;
	}
	
	//ROW 4
	i=0;
	ptrKey=Row4.begin();
	(*ptrKey)->Draw((i*2)+1,-2,0);
	ptrKey++;
	for(;ptrKey!=Row4.end();ptrKey++)
	{
		if((ptrKey+1)==Row4.end())break;
		IKey* kk=(*ptrKey);
		kk->x=(i*2)+4;
		kk->y=-2;
		egl->RenderModel(kk);
		//(*ptrKey)->Draw((i*2)+4,-2,0);
		i++;
	}
	(*ptrKey)->Draw((i*2)+6,-2,0);

	//LAST ROW
	m_LCTRL->Draw(0+0.3,-4,0);
	m_LWIN->Draw((2.6)+0.3,-4,0);
	m_LALT->Draw((2*2.6)+0.3,-4,0);
	m_SPACE->Draw((3*2.6)+4.93,-4,0);
	m_RALT->Draw((7.55*2.6)+0.3,-4,0);
	m_RWIN->Draw((8.55*2.6)+0.3,-4,0);
	m_APPS->Draw((9.55*2.6)+0.3,-4,0);
	m_RCTRL->Draw((10.55*2.6)+0.3,-4,0);


	m_Enter->x=27.4;
	m_Enter->y=1;
	this->egl->RenderModel(m_Enter);

	egl->EndRender();
	egl->UpdateRender();
}

void KeyBoard::SendVK(WPARAM wp,LPARAM lp)
{
	//0x30-0x39     0-9
	//0x41-0x5A		A-Z

	KeyHash::const_iterator it;
	it=MyKeys.find(wp);
	if(it!=MyKeys.end())
	{
		it->second->Pressed=true;	
	}

	int ScanCode = HIWORD(lp);
	if(wp==VK_SHIFT)
	{
		unsigned short l=GetKeyState(VK_LSHIFT);
		unsigned short r=GetKeyState(VK_RSHIFT);
		unsigned short rl=l&0xf000;
		unsigned short rr=r&0xf000;
		if(rl==0xf000)m_LSHIFT->Pressed=true;
		if(rr==0xf000)m_RSHIFT->Pressed=true;
	}
	if(wp==VK_CONTROL)
	{
		unsigned short l=GetKeyState(VK_LCONTROL);
		unsigned short r=GetKeyState(VK_RCONTROL);
		unsigned short rl=l&0xf000;
		unsigned short rr=r&0xf000;
		if(rl==0xf000)m_LCTRL->Pressed=true;
		if(rr==0xf000)m_RCTRL->Pressed=true;
	}
}

void KeyBoard::ReSetVK(WPARAM wp,LPARAM lp)
{
	//0x30-0x39     0-9
	//0x41-0x5A		A-Z

	KeyHash::const_iterator it;
	it=MyKeys.find(wp);
	if(it!=MyKeys.end())
	{
		it->second->Pressed=false;
	}

	int ScanCode = HIWORD(lp);
	if(wp==VK_SHIFT)
	{
		unsigned short l=GetKeyState(VK_LSHIFT);
		unsigned short r=GetKeyState(VK_RSHIFT);
		unsigned short rl=l&0xf000;
		unsigned short rr=r&0xf000;
		if(rl==0x0000)m_LSHIFT->Pressed=false;
		if(rr==0x0000)m_RSHIFT->Pressed=false;
	}
	
	if(wp==VK_CONTROL)
	{
		unsigned short l=GetKeyState(VK_LCONTROL);
		unsigned short r=GetKeyState(VK_RCONTROL);
		unsigned short rl=l&0xf000;
		unsigned short rr=r&0xf000;
		if(rl==0x0000)m_LCTRL->Pressed=false;
		if(rr==0x0000)m_RCTRL->Pressed=false;
	}
	
}


void KeyBoard::Test(void)
{
	egl->BeginRender();

	Button* bb;

	//Row 1
	for(int i=1;i<=13;i++)
	{
		bb=new Button(this,"Data\\Number_8.bmp");
		bb->Draw(i*2,4,0);
		delete bb;
	}

	//Row 2
	for(int i=1;i<=12;i++)
	{
		bb=new Button(this,"Data\\Letter26.bmp");
		bb->Draw((i*2)+1,2,0);
		delete bb;
	}

	//Row 3
	for(int i=1;i<=11;i++)
	{
		bb=new Button(this,"Data\\Letter2.bmp");
		if ((i%2)==0)
			bb->Draw((i*2)+2,0,1);
		else
			bb->Draw((i*2)+2,0,0);
		delete bb;
	}

	//Row 4
	for(int i=1;i<=10;i++)
	{
		bb=new Button(this,"Data\\Letter26.bmp");
		bb->Draw((i*2)+3,-2,0);
		delete bb;
	}

	egl->EndRender();
	egl->UpdateRender();
}


/*
	IKey Implementation
*/
IKey::IKey()
{
	this->MyKeyBoard=NULL;
	this->Pressed=false;
}
IKey::IKey(KeyBoard* ParentKB)
{
	this->MyKeyBoard = ParentKB;
}

void IKey::Mark(void)
{
	this->marked=true;
}

void IKey::UnMark(void)
{
	this->marked=false;
}

bool IKey::IsMarked(void)
{
	return this->marked;
}


/*
	Button Implementation
*/

Button::Button(KeyBoard* ParentKB,LPSTR li)
{
	this->MyKeyBoard = ParentKB;
	this->LetterImage=li;
	tex.ReadImage(LetterImage);
}
void Button::Draw(float x,float y,unsigned int cases)
{		
	if(!Pressed)
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.5f,0.5f,0.5f,0.5f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
		
	}
	else
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.4f,0.4f,0.4f,0.4f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
	}

	ml.ApplyMaterial();

	glEnable(GL_TEXTURE_2D);
	tex.ApplyTexture();

	glPushMatrix();
		glLoadIdentity();
		glScalef(0.2,0.2,0.2);
		if(!Pressed)
		{
			glTranslatef(x,y,0.0f);
		}
		else
			glTranslatef(x,y,-(BH-BH/8));

		glBegin(GL_QUADS);
			//Front Face
			glNormal3f( 0.0f, 0.0f, BH);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-FFW, -FFW, BH); // Point 1 (Front)
			glTexCoord2f(1.0f, 0.0f); glVertex3f( FFW, -FFW, BH); // Point 2 (Front)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( FFW, FFW, BH); // Point 3 (Front)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-FFW, FFW, BH); // Point 4 (Front)
	
			//// Back Face
			//ml._Bronze();
			//ml.ApplyMaterial();
			//glVertex3f(-1.0f, -1.0f, -BH); // Point 1 (Back)
			//glVertex3f(-1.0f, 1.0f, -BH); // Point 2 (Back)
			//glVertex3f( 1.0f, 1.0f, -BH); // Point 3 (Back)
			//glVertex3f( 1.0f, -1.0f, -BH); // Point 4 (Back)
			
			// Top Face
			glNormal3f(-0.1f,1.0f,-BH);glVertex3f(-1.0f, 1.0f, -BH); // Point 1 (Top)
			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW, FFW, BH); // Point 2 (Top)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW, FFW, BH); // Point 3 (Top)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f, 1.0f, -BH); // Point 4 (Top)

			// Bottom Face
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f, -1.0f, -BH); // Point 1 (Bottom)
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f, -1.0f, -BH); // Point 2 (Bottom)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW, -FFW, BH); // Point 3 (Bottom)
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW, -FFW, BH); // Point 4 (Bottom)
			
			// Right face
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f, -1.0f, -BH); // Point 1 (Right)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f, 1.0f, -BH); // Point 2 (Right)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW, FFW, BH); // Point 3 (Right)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW, -FFW, BH); // Point 4 (Right)
			
			// Left Face
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f, -1.0f, -BH); // Point 1 (Left)
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW, -FFW, BH); // Point 2 (Left)
			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW, FFW, BH); // Point 3 (Left)
			glNormal3f(-1.0f,1.0f,-BH);glVertex3f(-1.0f, 1.0f, -BH); // Point

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
	VariableButton Implementation
*/
VariableButton::VariableButton(KeyBoard* ParentKB,LPSTR li,float ExWidth=0)
{
	this->MyKeyBoard = ParentKB;
	this->LetterImage=li;
	tex.ReadImage(LetterImage);
	this->ExtendedWidth=ExWidth;
}
void VariableButton::Draw(float x,float y,unsigned int cases)
{		
	if(!Pressed)
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.5f,0.5f,0.5f,0.5f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
		
	}
	else
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.4f,0.4f,0.4f,0.4f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
	}
	ml.ApplyMaterial();
	glEnable(GL_TEXTURE_2D);
	tex.ApplyTexture();

	glPushMatrix();
		glLoadIdentity();
		glScalef(0.2,0.2,0.2);
		if(!Pressed)
		{
			glTranslatef(x,y,0.0f);
		}
		else
			glTranslatef(x,y,-(BH-BH/8));

		glBegin(GL_QUADS);
			//Front Face
			glNormal3f( 0.0f, 0.0f, BH);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-FFW-ExtendedWidth/2, -FFW, BH); // Point 1 (Front)
			glTexCoord2f(1.0f, 0.0f); glVertex3f( FFW+ExtendedWidth/2, -FFW, BH); // Point 2 (Front)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( FFW+ExtendedWidth/2, FFW, BH); // Point 3 (Front)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-FFW-ExtendedWidth/2, FFW, BH); // Point 4 (Front)
	
			//// Back Face
			//ml._Bronze();
			//ml.ApplyMaterial();
			//glVertex3f(-1.0f, -1.0f, -BH); // Point 1 (Back)
			//glVertex3f(-1.0f, 1.0f, -BH); // Point 2 (Back)
			//glVertex3f( 1.0f, 1.0f, -BH); // Point 3 (Back)
			//glVertex3f( 1.0f, -1.0f, -BH); // Point 4 (Back)
			
			// Top Face
			glNormal3f(-0.1f,1.0f,-BH);glVertex3f(-1.0f-ExtendedWidth/2, 1.0f, -BH); // Point 1 (Top)
			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW-ExtendedWidth/2, FFW, BH); // Point 2 (Top)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW+ExtendedWidth/2, FFW, BH); // Point 3 (Top)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f+ExtendedWidth/2, 1.0f, -BH); // Point 4 (Top)

			// Bottom Face
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f-ExtendedWidth/2, -1.0f, -BH); // Point 1 (Bottom)
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f+ExtendedWidth/2, -1.0f, -BH); // Point 2 (Bottom)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW+ExtendedWidth/2, -FFW, BH); // Point 3 (Bottom)
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW-ExtendedWidth/2, -FFW, BH); // Point 4 (Bottom)
			
			// Right face
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f+ExtendedWidth/2, -1.0f, -BH); // Point 1 (Right)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f+ExtendedWidth/2, 1.0f, -BH); // Point 2 (Right)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW+ExtendedWidth/2, FFW, BH); // Point 3 (Right)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW+ExtendedWidth/2, -FFW, BH); // Point 4 (Right)
			
			// Left Face
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f-ExtendedWidth/2, -1.0f, -BH); // Point 1 (Left)
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW-ExtendedWidth/2, -FFW, BH); // Point 2 (Left)
			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW-ExtendedWidth/2, FFW, BH); // Point 3 (Left)
			glNormal3f(-1.0f,1.0f,-BH);glVertex3f(-1.0f-ExtendedWidth/2, 1.0f, -BH); // Point

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/*
	Enter Implementation
*/
Enter::Enter(KeyBoard* ParentKB,LPSTR li)
{
	this->MyKeyBoard = ParentKB;
	this->LetterImage=li;
	tex.ReadImage(LetterImage);
}
void Enter::Draw(float x,float y,unsigned int cases)
{		
	if(!Pressed)
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.5f,0.5f,0.5f,0.5f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
		
	}
	else
	{
		ml.Ambient(0.0f,0.0f,0.0f,0.0f);
		ml.Diffuse(0.4f,0.4f,0.4f,0.4f);
		ml.Emission(0.0f,0.0f,0.0f,0.0f);
		ml.Specular(0.0f,0.0f,0.0f,0.0f);
	}

	ml.ApplyMaterial();

	glEnable(GL_TEXTURE_2D);
	tex.ApplyTexture();

	glPushMatrix();
		glLoadIdentity();
		glScalef(0.2,0.2,0.2);
		if(!Pressed)
		{
			glTranslatef(x,y,0.0f);
		}
		else
			glTranslatef(x,y,-(BH-BH/8));

		glBegin(GL_QUADS);
			//Front Face
			glNormal3f( 0.0f, 0.0f, BH);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-FFW*1.6, -FFW*2, BH); // Point 1 (Front)
			glTexCoord2f(1.0f, 0.0f); glVertex3f( FFW*1.6, -FFW*2, BH); // Point 2 (Front)
			glTexCoord2f(1.0f, 1.0f); glVertex3f( FFW*1.6, FFW*2, BH); // Point 3 (Front)
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-FFW*1.6, FFW*2, BH); // Point 4 (Front)
	
			//// Back Face
			//ml._Bronze();
			//ml.ApplyMaterial();
			//glVertex3f(-1.0f, -1.0f, -BH); // Point 1 (Back)
			//glVertex3f(-1.0f, 1.0f, -BH); // Point 2 (Back)
			//glVertex3f( 1.0f, 1.0f, -BH); // Point 3 (Back)
			//glVertex3f( 1.0f, -1.0f, -BH); // Point 4 (Back)
			
			// Top Face
			glNormal3f(-0.1f,1.0f,-BH);glVertex3f(-1.0f*1.6, 1.0f*2, -BH); // Point 1 (Top)
			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW*1.6, FFW*2, BH); // Point 2 (Top)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW*1.6, FFW*2, BH); // Point 3 (Top)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f*1.6, 1.0f*2, -BH); // Point 4 (Top)

			// Bottom Face
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f((-1.0f*1.6)-1.6, -1.0f*2, -BH); // Point 1 (Bottom)
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f*1.6, -1.0f*2, -BH); // Point 2 (Bottom)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW*1.6, -FFW*2, BH); // Point 3 (Bottom)
			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW*2, BH); // Point 4 (Bottom)
			
			// Right face
			glNormal3f(1.0f,-1.0f,-BH);glVertex3f( 1.0f*1.6, -1.0f*2, -BH); // Point 1 (Right)
			glNormal3f(1.0f,1.0f,-BH);glVertex3f( 1.0f*1.6, 1.0f*2, -BH); // Point 2 (Right)
			glNormal3f(FFW,FFW,BH);glVertex3f( FFW*1.6, FFW*2, BH); // Point 3 (Right)
			glNormal3f(FFW,-FFW,BH);glVertex3f( FFW*1.6, -FFW*2, BH); // Point 4 (Right)
			
			// Left Face Part 1/2 length
			//glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f*1.6, -1.0f/6, -BH); // Point 1 (Left)
			//glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW*1.6, -FFW/2, BH); // Point 2 (Left)

			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f*1.6, 0, -BH); // Point 1 (Left)
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW*1.6, -FFW, BH); // Point 2 (Left)

			glNormal3f(-FFW,FFW,BH);glVertex3f(-FFW*1.6, FFW*2, BH); // Point 3 (Left)
			glNormal3f(-1.0f,1.0f,-BH);glVertex3f(-1.0f*1.6, (1.0f*2), -BH); // Point

			//Rest of ENTER//

			//start of the extended block
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f(-1.0f*1.6, 0, -BH); 
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW*1.6, -FFW, BH); 
			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW, BH); 
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f((-1.0f*1.6)-1.6, 0, -BH); 

			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW*1.6, -FFW, BH); 
			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW, BH);
			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW*2, BH);
			glNormal3f(-FFW,-FFW,BH);glVertex3f(-FFW*1.6, -FFW*2, BH); 

			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW*2, BH);
			glNormal3f(-FFW,-FFW,BH);glVertex3f((-FFW*1.6)-1.6, -FFW, BH);
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f((-1.0f*1.6)-1.6, 0, -BH); 
			glNormal3f(-1.0f,-1.0f,-BH);glVertex3f((-1.0f*1.6)-1.6, -1.0f*2, -BH); // Point 1 (Bottom)


		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void IKey::Render()
{
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
	this->Draw(x,y,0);
	glPopMatrix();
}
void IKey::RunPickFunction(void)
{
	this->Pressed=!this->Pressed;
}