#include "..\EasyGL.h"
#include <vector>

#include <map>
#include <string>

using namespace std;

class IKey;
class Button;
class VariableButton;
class Enter;

class KeyBoard
{
public:
	
	Button* m_Functions[13]; //F1 F2 F3 ...
	Button* m_Numbers[10]; //0-9
	Button* m_Letters[29];	//Arabic alphabit

	Button* m_Ya2Dot;
	Button* m_Hamza;
	Button* m_HamzaOnYa;
	Button* m_HamzaOnWow;
	Button* m_La;
	Button* m_TaMarbota;

	Button* m_ESC;
	Button* m_Minus;
	Button* m_Equal;
	Button* m_Div;
	Button* m_BackSpace;

	VariableButton* m_TAB;
	VariableButton* m_CAPS;
	VariableButton* m_LSHIFT;
	VariableButton* m_RSHIFT;


	vector <IKey*> FunctionsRow;
	vector <IKey*> Row1;
	vector <IKey*> Row2;
	vector <IKey*> Row3;
	vector <IKey*> Row4;


	VariableButton* m_LCTRL;
	VariableButton* m_LWIN;
	VariableButton* m_LALT;
	VariableButton* m_SPACE;
	VariableButton* m_RALT;
	VariableButton* m_RWIN;
	VariableButton* m_APPS;
	VariableButton* m_RCTRL;
	vector <IKey*> Row5;

	Enter* m_Enter;

	vector <IKey*>::const_iterator ptrKey;

	typedef map <int,IKey*> KeyHash;
	KeyHash MyKeys;

public :
	EasyGL* egl;
	CameraModel cm;
	KeyBoard(HWND hWnd);
	void Test(void);
	
	void Draw(void);
	void Build(void);

	
	void SendVK(WPARAM wp,LPARAM lp);
	void ReSetVK(WPARAM wp,LPARAM lp);
	
};

class IKey:public SimpleModel
{
protected:
	bool marked;
	KeyBoard* MyKeyBoard;
	LPSTR LetterImage;
	Texture tex;
	Material ml;
public:
	float x,y;
	IKey();
	IKey(KeyBoard*);
	void Mark(void);
	void UnMark(void);
	bool IsMarked(void);
	bool Pressed;
	virtual void Draw(float x,float y,unsigned int cases)=0;
	string KeyLetterName;
	void RunPickFunction(void);
	void Render(void);
};

class Button:public IKey
{
private:
public:
	Button(KeyBoard*,LPSTR li);
	//drawing button
	//vertex data of button
	//with center being in top left corner
	void Draw(float x,float y,unsigned int cases);
};

class VariableButton:public IKey
{
public:
	float ExtendedWidth;
	VariableButton(KeyBoard*,LPSTR li,float);
	void Draw(float x,float y,unsigned int cases);
};
class Enter:public IKey
{
public:
	Enter(KeyBoard*,LPSTR li);
	void Draw(float x,float y,unsigned int cases);
};