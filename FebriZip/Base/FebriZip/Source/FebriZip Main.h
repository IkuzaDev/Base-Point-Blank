#include <windows.h>
#include <process.h>
#include <d3d9.h>
#include <math.h>

#include "Include Dubeta.h"
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma warning(disable:4244 4996 4101)
#pragma warning(disable: 4482 4018 4305 4553 4715)

#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define PINK			D3DCOLOR_XRGB(255, 000, 255)
#define PINK2			D3DCOLOR_XRGB(255, 130, 255)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define mBLACK			D3DCOLOR_ARGB(100, 000, 000, 205)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define WHITE2			D3DCOLOR_ARGB(100, 255, 255, 255)
#define RED2			D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN2			D3DCOLOR_ARGB(100, 000, 255, 000)
#define BLUE2			D3DCOLOR_ARGB(100, 000, 000, 255) 
#define BLACK2			D3DCOLOR_ARGB(100, 000, 000, 000)
#define PURPLE2			D3DCOLOR_ARGB(100, 125, 000, 255) 
#define GREY2			D3DCOLOR_ARGB(100, 128, 128, 128) 
#define YELLOW2			D3DCOLOR_ARGB(100, 255, 255, 000) 
#define ORANGE2			D3DCOLOR_ARGB(100, 255, 125, 000)
#define SKYBLUE			D3DCOLOR_ARGB(255, 0,   180, 255)
#define LGRAY		    D3DCOLOR_ARGB(255, 174, 174, 174)  
#define DARKBLUE		D3DCOLOR_ARGB(255, 0,   0,   153) 
#define LIGHTBLUE		D3DCOLOR_ARGB(255, 19, 84, 199) 
#define MAROON			D3DCOLOR_ARGB(255, 142, 30, 0)
#define POLICE          D3DCOLOR_ARGB(255, 125, 160, 200)
#define TERORI          D3DCOLOR_ARGB(255, 225, 100, 100)
#define TRANSPARANT	D3DCOLOR_ARGB(140, 0, 0, 0)
#define Xx 880
#define Yy 680
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
INPUT buffer[1];
DWORD Ticks,TimeReady;
//bool IsInBattle();
DWORD Tick = NULL;
static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];
BOOL IsKeyPressed(int Key,DWORD dwTimeOut)
{
	if( HIWORD( GetKeyState( Key ) ) )
	{
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) )
		{
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
			return TRUE;
		}
	}else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}

ID3DXFont* pFont = NULL;
LPD3DXLINE pLine = NULL;

LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;

const D3DCOLOR Red			= D3DCOLOR_ARGB (255,	255,	0,		0	);
const D3DCOLOR Yellow		= D3DCOLOR_ARGB (255,	255,	255,	0	);
const D3DCOLOR Green		= D3DCOLOR_ARGB (255,	0,		255,	0	);
const D3DCOLOR Blue			= D3DCOLOR_ARGB (255,	0,		0,		255 );
const D3DCOLOR Purple		= D3DCOLOR_ARGB (255,	102,	0,		153 );
const D3DCOLOR Pink			= D3DCOLOR_ARGB (255,	255,	20,		147 );
const D3DCOLOR Orange		= D3DCOLOR_ARGB (255,	255,	165,	0	);
const D3DCOLOR YellowGreen	= D3DCOLOR_ARGB (255,	154,	205,	50	);
const D3DCOLOR LightGrey	= D3DCOLOR_ARGB (255,	211,	211,	211	);
const D3DCOLOR LightCyan	= D3DCOLOR_ARGB (255,	122,	139,	139	);
const D3DCOLOR Snow			= D3DCOLOR_ARGB (255,	139,	137,	137	);
const D3DCOLOR TransBlue	= D3DCOLOR_ARGB (150,	0,		0,		255 );
const D3DCOLOR TransBlack	= D3DCOLOR_ARGB (150,	0,		0,		0	);
const D3DCOLOR TransBlack2	= D3DCOLOR_ARGB (80,	0,		0,		0	);
const D3DCOLOR AQUA			= D3DCOLOR_ARGB (255,	54,		231,	255	);
const D3DCOLOR White		= D3DCOLOR_ARGB (255,	255,	255,	255 );
const D3DCOLOR Black		= D3DCOLOR_ARGB (255,	0,		0,		0	);
const D3DCOLOR DGrey		= D3DCOLOR_ARGB (255,	59,		55,		57	);
const D3DCOLOR Grey			= D3DCOLOR_ARGB (255,	84,		79,		81	);
const D3DCOLOR Outline		= D3DCOLOR_ARGB (255,	140,	140,	140	);
CONST D3DCOLOR Cyan         = D3DCOLOR_ARGB(255, 000, 255, 255);

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RainbowTextTest			D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

void RainBow(){
	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
}
void RainBow2(){
if(RainbowTexts!=100)
{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	}

int ThreadTrial(char *url)
{
	char output[16];
	HINTERNET hInternet;
	HINTERNET hFile;
	DWORD ReadSize;
	BOOL bResult;
	hInternet = InternetOpenA("Some USER-AGENT", INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL, NULL);
	hFile = InternetOpenUrl(hInternet, url, NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	ReadSize = 15;
	Sleep(500);
	bResult = InternetReadFile(hFile, output, 15, &ReadSize);
	output[ReadSize] = '\0';

	if (strcmp("AKTIF", output) == 0)
	{
	}
	else{
		//MessageBox(0, "Cheat Nonactive", "Info", MB_ICONWARNING | MB_OK);
		//MessageBox(0, "FB: FebriZip.id", "Info!", MB_ICONWARNING | MB_OK);
		//MessageBox(0, "https://www.facebook.com/febrizip.id", "Info", MB_ICONWARNING | MB_OK);
		//system("https://www.facebook.com/febrizip.id");
		ExitProcess(0);
	}
	return 0;
}