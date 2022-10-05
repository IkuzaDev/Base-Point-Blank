////
#pragma warning (disable:4099 4554 4700)
int suicideplayers;
LPD3DXFONT pFonts	= NULL;
LPD3DXFONT fName	= NULL;
ID3DXFont*  pFont2;
ID3DXSprite* textSprite;
DWORD TeamColor;
D3DVIEWPORT9 g_ViewPort, ViewPortAim;
LPD3DXFONT      g_pFont = NULL;
LPD3DXFONT      i_pFont = NULL;
DWORD Ticket_Offset = (DWORD)EncodePointer((LPVOID)(0x17EAC));
 DWORD setRespawn = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x30));
DWORD Decrypt_setRespawn = (DWORD)DecodePointer((LPVOID)setRespawn);
#include "Include Dubeta.h"
int NoRecoil, FastShoot;
void  unk(void *adr, void *ptr, int size)
{

	DWORD NextProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &NextProtection);
	RtlMoveMemory(adr, ptr, size);
	VirtualProtect(adr, size, NextProtection, &NextProtection);
}
#ifndef _XORSTR_H
#define _XORSTR_H
#pragma once
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private: 
    XorStr();
public: 
    char s[BUFLEN];

    XorStr(const char* xs);
    ~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;}
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{

    int xvalue = XORSTART;
    int i = 0;
    for(;i<(BUFLEN-1);i++) {
        s[i] = xs[i-XREFKILLER]^xvalue;
        xvalue += 1;
        xvalue %= 256;
    }
    s[BUFLEN-1] = 0;
}
#endif
D3DVIEWPORT9 Viewport;
////
//////--------------------------------------ADDRES PB KAYBO ESP BASE PLAYER (Remake FebriZip Dubeta) -------------------------//
#define PTR_SLOT           0x17E34
DWORD  c_pCharaManager = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) + 0x13E8);

DWORD BlatteContextPBEvo = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) + 0x3a8);

#define mBasePlayer  (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) + 0x55c0)
//#define dwFramework ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandle("i3BaseDx.dll") + 0xB44D4) + 0x3C4) + 0x4) + 0x54) + 0x7E0) + 0x44))

#define dwRaycast  (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) -0x882BE8)


//#define mNoRecoilX ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandle("i3BaseDx.dll") + 0xB35D8) + 0x88) + 0x2C) + 0x20) + 0x348) - 0x843D31))

//#define dwCurHPReal  ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3BaseDx.dll") + 0xB60B0) + 0x524) + 0x9D0) + 0x730) + 0xBC8) + 0x3874))

DWORD c_pPlayer = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) + 0x55c0);

DWORD c_pPlayerEsp = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) + 0x55c0);
//DWORD ResultNameTag = mNoRecoilX + 0x82C64;
//DWORD ResultRaycast = mNoRecoilX - 0x441C9;
//DWORD ResultGetNoRecoil = mNoRecoilX + 0x1;
DWORD ResultBasePlayer	= mBasePlayer;
DWORD ResultBaseChara = c_pCharaManager;



	BYTE GetMySlot()
{
	return *(BYTE*)(*(DWORD*)(BlatteContextPBEvo)+PTR_SLOT);
}
class CBattleSlotContext
{
public:
	char* getNickForSlot(int iSlot) {
		return (char*)(*(DWORD*)((CBattleSlotContext*)(this) + (iSlot * 4 + (0x17E34 + 0x4))) + 8);
	}
	static int getMySlotIdx()
	{
		return (int)(*(DWORD*)(*(DWORD*)(BlatteContextPBEvo) + PTR_SLOT));
	}
	static CBattleSlotContext* Singleton()
	{
		return (CBattleSlotContext*)(*(DWORD*)(BlatteContextPBEvo));
	}
};
	bool GetUserBone(D3DXVECTOR3 &Out, int index, int BoneIndex) {
	string IncreasePos = "1.0f";
	if (BoneIndex == 8) IncreasePos = "1.7f"; if (BoneIndex ==7) IncreasePos = "1.5f";
	if (BoneIndex == 5) IncreasePos = "1.3f"; if (BoneIndex ==6) IncreasePos = "1.0f";
	Out.x = LPD3DXVECTOR3((DWORD)((CBattleSlotContext*)(CBattleSlotContext::Singleton()) + (0x1738 * index + 0x7B0)))->x;
	Out.y = LPD3DXVECTOR3((DWORD)((CBattleSlotContext*)(CBattleSlotContext::Singleton()) + (0x1738 * index + 0x7B0)))->y + stof(IncreasePos);
	Out.z = LPD3DXVECTOR3((DWORD)((CBattleSlotContext*)(CBattleSlotContext::Singleton()) + (0x1738 * index + 0x7B0)))->z;
	return true;
}
 D3DVIEWPORT9 ViewPort;
class i3RenderContext {
public:
	//LPDIRECT3DDEVICE9 pDevice;
	char _0x0000[0x53D4];
	IDirect3DDevice9* pDevice;
	D3DXMATRIX* GetProjectMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
	}
	D3DXMATRIX* GetWorldMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
	}
	D3DXMATRIX* GetViewMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
	}
	
	bool WorldToScreen(D3DVECTOR Player, D3DVECTOR &PlayerScaled)
	{
		__try
		{
			D3DXVECTOR3 vScreen;
			D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
			ViewPort.X = ViewPort.Y = 0;
			ViewPort.MinZ = 0;
			ViewPort.MaxZ = 1;
			D3DXVec3Project(
				&vScreen,
				&PlayerPos,
				&ViewPort,
				this->GetProjectMatrix(),
				this->GetViewMatrix(),
				this->GetWorldMatrix()
				);
			if (vScreen.z < 1.0f &&
				vScreen.x > 0.0f &&
				vScreen.y > 0.0f &&
				vScreen.x < ViewPort.Width &&
				vScreen.y < ViewPort.Height)
			{
				PlayerScaled.x = vScreen.x;
				PlayerScaled.y = vScreen.y;
				PlayerScaled.z = vScreen.z;
				return true;
			}
			else
			{
				return false;
			}
		}
		__except (TRUE){ return false; }
	}
	static i3RenderContext* Singleton()
	{
		return (i3RenderContext*)(*(DWORD*)(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?g_pRenderContext@@3PAVi3RenderContext@@A")));
	}
};
//////
////
int Cross;
//#pragma once using namespace std;
//
////*---------------------------------------- Declaration FillRGB (Remake FebriZip Dubeta)----------------------------------------------------*/
void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
        if( w < 0 )w = 1;
        if( h < 0 )h = 1;
        if( x < 0 )x = 1;
        if( y < 0 )y = 1;
        D3DRECT rec = { x, y, x + w, y + h };
        pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
inline void CrossHair(LPDIRECT3DDEVICE9 pDevice)
{
	if (Cross)
	{
		pDevice->GetViewport(&ViewPort);
	DWORD ScreenX = ViewPort.Width / 2;
	DWORD ScreenY = ViewPort.Height / 2;
	FillRGB(ScreenX - 20, ScreenY, 40, 1, RED, pDevice);
	FillRGB(ScreenX, ScreenY - 20, 1, 40, RED, pDevice);
	FillRGB(ScreenX - 17, ScreenY, 34, 1, BLUE, pDevice);
	FillRGB(ScreenX, ScreenY - 17, 1, 34, BLUE, pDevice);
	FillRGB(ScreenX - 14, ScreenY, 28, 1, BLUE, pDevice);
	FillRGB(ScreenX, ScreenY - 14, 1, 28, BLUE, pDevice);
	FillRGB(ScreenX - 11, ScreenY, 22, 1, GREEN, pDevice);
	FillRGB(ScreenX, ScreenY - 11, 1, 22, GREEN, pDevice);
	FillRGB(ScreenX - 9, ScreenY, 18, 1, YELLOW, pDevice);
	FillRGB(ScreenX, ScreenY - 9, 1, 18, YELLOW, pDevice);
	FillRGB(ScreenX - 6, ScreenY, 12, 1, D3DCOLOR_ARGB(255, 255, 140, 000), pDevice);
	FillRGB(ScreenX, ScreenY - 6, 1, 12, D3DCOLOR_ARGB(255, 255, 140, 000), pDevice);
	FillRGB(ScreenX - 3, ScreenY, 6, 1, RED, pDevice);
	FillRGB(ScreenX, ScreenY - 3, 1, 6, RED, pDevice);
	}
}
bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	
	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
	D3DXVECTOR3 vScreen;
	pDevice->GetViewport(&Viewport);
	Viewport.X = Viewport.Y = 0;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, 
		i3RenderContext::Singleton()->GetProjectMatrix(), 
		i3RenderContext::Singleton()->GetViewMatrix(), 
		i3RenderContext::Singleton()->GetWorldMatrix());

	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
	{
		PlayerScaled.x = vScreen.x;
		PlayerScaled.y = vScreen.y;
		PlayerScaled.z = vScreen.z;
		return true;
	}
	return false;
	}
void DrawLineBone(float StartX, float StartY, float EndX, float EndY, float Width, D3DCOLOR dColor )
{
    pLine[0].SetWidth( Width ); 
    pLine[0].SetGLLines( 0 ); 
    pLine[0].SetAntialias( 1 ); 

    D3DXVECTOR2 v2Line[2]; 
    v2Line[0].x = StartX; 
    v2Line[0].y = StartY; 
    v2Line[1].x = EndX; 
    v2Line[1].y = EndY; 

    pLine[0].Begin(); 
    pLine[0].Draw( v2Line, 2, dColor ); 
    pLine[0].End(); 
}

void DrawLine(long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color) {
	if (!pLine){ D3DXCreateLine(i3RenderContext::Singleton()->pDevice, &pLine); }
	D3DXVECTOR2 vLine[2];
	pLine->SetAntialias(0);
	pLine->SetWidth((float)dwWidth);
	pLine->Begin();
	vLine[0][0] = (float)Xa;
	vLine[0][1] = (float)Ya;
	vLine[1][0] = (float)Xb;
	vLine[1][1] = (float)Yb;
	pLine->Draw(vLine, 2, Color);
	pLine->End();
}






	
void DrawLinebome(float x, float y, float x2, float y2, float width, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	if (pLine == NULL)
	{
		D3DXCreateLine(pDevice, &pLine);
	}
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex);
DWORD getGameCharaBoneContext;





	void DrawString(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	fName->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}
		void iDrawString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	D3DCOLOR colour = dwColour;

	RECT rct;
	rct.left     = x - 1;   
	rct.right    = x + 1;   
	rct.top      = y - 1 ;   
	rct.bottom   = y + 1;

	va_list va_alist;
	char logbuf[256] = {0};
	va_start(va_alist, text);
	_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end(va_alist);

	textSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawText(textSprite, logbuf, -1, &rct, Flag|DT_NOCLIP, colour);
	textSprite->End();	
}

void DrawOutlineString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, fName, text);
	iDrawString(x-1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, fName, text);
	iDrawString(x+1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, fName, text);
	iDrawString(x, y-1, 0xFF000000, DT_NOCLIP | DT_CENTER, fName, text);
	iDrawString(x, y+1, 0xFF000000, DT_NOCLIP | DT_CENTER, fName, text);
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, fName, text);
}



	#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)

	
void FillRGB2(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	if (w < 0)w = 1;
	if (h < 0)h = 1;
	if (x < 0)x = 1;
	if (y < 0)y = 1;
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}
	void DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice)
{
	FillRGB2(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB2(x, y, px, h, BorderColor, pDevice);
	FillRGB2(x, y, w, px, BorderColor, pDevice);
	FillRGB2((x + w - px), y, px, h, BorderColor, pDevice);
}
void  Text(int x, int y, LPSTR text,DWORD color, DWORD ST)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
}
void  DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };
	pD3D9->SetTexture(0, NULL);
	pD3D9->SetPixelShader(0);
	pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
	pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}
	void HealthBar(LPDIRECT3DDEVICE9 pDevice, float x, float y, float Health)
{
	DWORD HPcol = GREEN;
	if (Health < 90)HPcol = GREEN;
	if (Health < 70)HPcol = ORANGE;
	if (Health < 50)HPcol = YELLOW;
	if (Health < 30) HPcol = RED;
	if (Health < 15) HPcol = RED;
	DrawBorder(x - 1, y - 1, 52, 5, 1, BLACK, pDevice);
	FillRGB2(x, y, Health / 2, 3, HPcol, pDevice);
}
	
int GetTeam(char MyTeam)
{
	for(int i = 0; i < 16; i+=2)
		if(i == MyTeam)return 2;
	for(int i = 1; i < 16; i+=2)
		if(i == MyTeam)return 1;
	return -1;
}


	



void CriarCaixa(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{

	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);

}
void DesenharCaixa(int x, int y, int w, int h, D3DCOLOR COLOR, LPDIRECT3DDEVICE9 pDevice)
{
	CriarCaixa(x, y, 2, h, COLOR, pDevice);
	CriarCaixa(x, y + h, w, 2, COLOR, pDevice);
	CriarCaixa(x, y, w, 2, COLOR, pDevice);
	CriarCaixa(x + w, y, 2, h + 2, COLOR, pDevice);
}
void DrawLine2(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void Box3D(int HeadX, int HeadY, int bottomX, int bottomY, float Distance_Player, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	float drawW = 245 / Distance_Player;
	float drawW2 = 135 / Distance_Player;
	float drawW3 = 55 / Distance_Player;

	DrawLine2(bottomX - drawW, bottomY, bottomX + drawW, bottomY, 1, Color);
	DrawLine2(HeadX - drawW, HeadY, HeadX + drawW, HeadY, 1, Color);
	DrawLine2(HeadX - drawW, HeadY, bottomX - drawW, bottomY, 1, Color);
	DrawLine2(HeadX + drawW, HeadY, bottomX + drawW, bottomY, 1, Color);
	DrawLine2(HeadX - drawW2, HeadY - drawW3, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine2(bottomX - drawW, bottomY, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine2(HeadX - drawW, HeadY, HeadX - drawW2, HeadY - drawW3, 1, Color);
	DrawLine2((HeadX + drawW) + drawW2, HeadY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine2(bottomX + drawW, bottomY, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine2(HeadX + drawW, HeadY, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine2(HeadX - drawW2, HeadY - drawW3, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine2(bottomX - drawW2, bottomY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
}
float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB){
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}












	



int cTeamFind(int Idx)
{
	for (int a = 0; a <= 14; a += 2)if (Idx == a)return 1;
	for (int b = 1; b <= 15; b += 2)if (Idx == b)return 2;
	return 0;
}


int ESPHealth,Skeleto;
int Distancia;


int Spanw;



///////////////-----------------aimbot ---------------------//
//****************************************** Calss CBattleSlotContext *********************************************
//****************************************** Calss CBattleSlotContext *********************************************
//****************************************** Calss CBattleSlotContext *********************************************
//****************************************** Calss CBattleSlotContext *********************************************

struct GAMEINFO_CHARACTER
{
	char _0x0000[52];
	BYTE Death; //0x0034 
	char _0x0035[123];
	D3DXVECTOR3 RootPos;
	char _0x00BC[4];
};

struct NickPlayer
{
	char _0x0000[4];
	wchar_t Name[12]; //0x0004 
	char _0x001C[67];
};

class CGameCharaManager;
class CGameCharaBase;

class CBattleSlotContextnew
{
public:
	char* getNickForSlot(int iSlot) {
		return (char*)(*(DWORD*)((CBattleSlotContext*)(this) + (iSlot * 4 + (0x17E3C))) + 8);
	}

	GAMEINFO_CHARACTER* getGameInfo_Chara(int slot){
		return (GAMEINFO_CHARACTER*)(((DWORD)this + 0x700) +
			(slot * 0x1738));
	}

	static int getMySlotIdx()
	{
		return (int)(*(DWORD*)(*(DWORD*)(BlatteContextPBEvo)+ PTR_SLOT));
	}
	static CBattleSlotContextnew* Singletonss()
	{
		return (CBattleSlotContextnew*)(*(DWORD*)(BlatteContextPBEvo));
	}
};




inline bool DeathCheck(int iSlot)
{
	if (CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(iSlot)->Death > 0)
		return true;
	return false;

}
void CriarCaixas(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{

	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);

}
VOID DesenharBox(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	CriarCaixas(x, y, w / 3, px, BorderColor, pDevice);
	CriarCaixas(x + w - (w / 3), y, w / 3, px, BorderColor, pDevice);
	CriarCaixas(x, (y + h - px), w / 3, px, BorderColor, pDevice);
	CriarCaixas(x + w - (w / 3), (y + h - px), w / 3, px, BorderColor, pDevice);
	CriarCaixas(x, y, px, w / 3, BorderColor, pDevice);
	CriarCaixas(x, (y + h - px) - h / 6, px, w / 3, BorderColor, pDevice);
	CriarCaixas(w + x, y, px, w / 3, BorderColor, pDevice);
	CriarCaixas(w + x, (y + h) - (h / 6), px, w / 3, BorderColor, pDevice);
}
int Box3s;
int Linia,He4lths,Nam3s,Reloadnew,FastSwith,fallfunc,Baladuraintem ,RespawnFunc;  
int Espname, EspDistance;
void DrawBorderESP(float x, float y, float w, float h, float px, D3DCOLOR COLOR, IDirect3DDevice9* pDevice, int iSlot) {

	DWORD ScreenX = Viewport.Width / 2;
	DWORD ScreenY = Viewport.Height;
	/*if (Espname) {
		DrawNick(iSlot, pDevice, 0, COLOR);
	}*/
	if (Box3s) { DesenharBox(x, y, w, h, px, COLOR, pDevice); }
	
	if (Linia)
	{
		DrawLine(ScreenX, ScreenY, x + w - 4, y + h, 1, COLOR);
	}
}


//*********************************************** getCurHP *********************************************************
//*********************************************** getCurHP *********************************************************
//*********************************************** getCurHP *********************************************************
//*********************************************** getCurHP *********************************************************



#define i3InputDx XorStr<0x9D,14,0x277CE534>("\xF4\xAD\xD6\xCE\xD1\xD7\xD7\xE0\xDD\x88\xC3\xC4\xC5"+0x277CE534).s
#define i3SceneDx /*i3SceneDx.dll*/XorStr<0xEE,14,0x9DA3250D>("\x87\xDC\xA3\x92\x97\x9D\x91\xB1\x8E\xD9\x9C\x95\x96"+0x9DA3250D).s
#define i3FrameworkDx /*i3FrameworkDx.dll*/XorStr<0x20,18,0xAC3D749D>("\x49\x12\x64\x51\x45\x48\x43\x50\x47\x5B\x41\x6F\x54\x03\x4A\x43\x5C"+0xAC3D749D).s
#define p_i3UI_getViewer /*?getViewer@i3UI@@YAPAVi3Viewer@@XZ*/XorStr<0x43,35,0x44BF914F>("\x7C\x23\x20\x32\x11\x21\x2C\x3D\x2E\x3E\x0D\x27\x7C\x05\x18\x12\x13\x0D\x14\x06\x16\x0E\x30\x69\x0D\x35\x38\x29\x3A\x12\x21\x22\x3B\x3E"+0x44BF914F).s
#define	p_i3CollideeLine_new_object_fun /*?new_object_fun@i3CollideeLine@@SAPAV1@XZ*/XorStr<0xD5,42,0xC3DBDC62>("\xEA\xB8\xB2\xAF\x86\xB5\xB9\xB6\xB8\xBD\xAB\xBF\x87\x97\x8D\xA4\x8C\xD5\xA4\x87\x85\x86\x82\x88\x88\x8B\xA3\x99\x9F\x97\xB3\xB4\xA6\xB7\xA7\xB9\xAF\xCB\xBB\xA4\xA7"+0xC3DBDC62).s
#define	p_i3Viewer_GetFramework /*?GetFramework@i3Viewer@@QAEPAVi3Framework@@XZ*/XorStr<0xF5,46,0x431953BF>("\xCA\xB1\x92\x8C\xBF\x88\x9A\x91\x98\x89\x90\x72\x6A\x42\x6A\x37\x53\x6F\x62\x7F\x6C\x78\x4B\x4C\x5C\x4F\x4A\x40\x50\x44\x7A\x27\x53\x64\x76\x75\x7C\x6D\x74\x6E\x76\x5E\x5F\x78\x7B"+0x431953BF).s
#define	p_i3CollideeLine_SetStart /*?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xE3,43,0xC794B4CA>("\xDC\xB7\x80\x92\xB4\x9C\x88\x98\x9F\xAC\x84\xDD\xAC\x9F\x9D\x9E\x9A\x90\x90\x93\xBB\x91\x97\x9F\xBB\xBC\xAC\xBF\xBA\x58\x51\x43\x57\x52\x40\x45\x34\x4C\x49\x4A\x4B\x56"+0xC794B4CA).s
#define	p_i3CollideeLine_SetEnd	/*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xBA,41,0xA536FBF5>("\x85\xE8\xD9\xC9\xFB\xD1\xA4\x81\xAB\xF0\x87\xAA\xAA\xAB\xA1\xAD\xAF\xAE\x80\xA4\xA0\xAA\x90\x91\x83\x92\x91\x8D\x86\x96\x8C\x8F\x9F\x98\xEF\x99\x9E\x9F\xA0\xBB"+0xA536FBF5).s
#define p_4VEC3D /*??4VEC3D@@QAEAAT0@ABT0@@Z*/XorStr<0x20,26,0xFE1BB7EB>("\x1F\x1E\x16\x75\x61\x66\x15\x63\x68\x69\x7B\x6A\x69\x6C\x6F\x7B\x00\x71\x73\x71\x60\x05\x76\x77\x62"+0xFE1BB7EB).s

#define i3SceneDx /*i3SceneDx.dll*/XorStr<0xEE,14,0x9DA3250D>("\x87\xDC\xA3\x92\x97\x9D\x91\xB1\x8E\xD9\x9C\x95\x96"+0x9DA3250D).s
#define i3FrameworkDx /*i3FrameworkDx.dll*/XorStr<0x20,18,0xAC3D749D>("\x49\x12\x64\x51\x45\x48\x43\x50\x47\x5B\x41\x6F\x54\x03\x4A\x43\x5C"+0xAC3D749D).s
#define p_i3UI_getViewer /*?getViewer@i3UI@@YAPAVi3Viewer@@XZ*/XorStr<0x43,35,0x44BF914F>("\x7C\x23\x20\x32\x11\x21\x2C\x3D\x2E\x3E\x0D\x27\x7C\x05\x18\x12\x13\x0D\x14\x06\x16\x0E\x30\x69\x0D\x35\x38\x29\x3A\x12\x21\x22\x3B\x3E"+0x44BF914F).s
#define	p_i3CollideeLine_new_object_fun /*?new_object_fun@i3CollideeLine@@SAPAV1@XZ*/XorStr<0xD5,42,0xC3DBDC62>("\xEA\xB8\xB2\xAF\x86\xB5\xB9\xB6\xB8\xBD\xAB\xBF\x87\x97\x8D\xA4\x8C\xD5\xA4\x87\x85\x86\x82\x88\x88\x8B\xA3\x99\x9F\x97\xB3\xB4\xA6\xB7\xA7\xB9\xAF\xCB\xBB\xA4\xA7"+0xC3DBDC62).s
#define	p_i3CollideeLine_SetStart /*?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xE3,43,0xC794B4CA>("\xDC\xB7\x80\x92\xB4\x9C\x88\x98\x9F\xAC\x84\xDD\xAC\x9F\x9D\x9E\x9A\x90\x90\x93\xBB\x91\x97\x9F\xBB\xBC\xAC\xBF\xBA\x58\x51\x43\x57\x52\x40\x45\x34\x4C\x49\x4A\x4B\x56"+0xC794B4CA).s
#define	p_i3CollideeLine_SetEnd	/*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xBA,41,0xA536FBF5>("\x85\xE8\xD9\xC9\xFB\xD1\xA4\x81\xAB\xF0\x87\xAA\xAA\xAB\xA1\xAD\xAF\xAE\x80\xA4\xA0\xAA\x90\x91\x83\x92\x91\x8D\x86\x96\x8C\x8F\x9F\x98\xEF\x99\x9E\x9F\xA0\xBB"+0xA536FBF5).s
#define	p_i3Viewer_GetFramework /*?GetFramework@i3Viewer@@QAEPAVi3Framework@@XZ*/XorStr<0xF5,46,0x431953BF>("\xCA\xB1\x92\x8C\xBF\x88\x9A\x91\x98\x89\x90\x72\x6A\x42\x6A\x37\x53\x6F\x62\x7F\x6C\x78\x4B\x4C\x5C\x4F\x4A\x40\x50\x44\x7A\x27\x53\x64\x76\x75\x7C\x6D\x74\x6E\x76\x5E\x5F\x78\x7B"+0x431953BF).s

PDWORD GetModule(char* Module, char* strFunc)
{
	PDWORD Result = (PDWORD)GetProcAddress(GetModuleHandleA(Module), strFunc);
	return Result;
}

class i3PhysixHitResult {
public:
	char _0x0000[28];
	D3DXVECTOR3 FinalPos;
	float Distance;
};

class i3CollideeLine {
public:
	D3DXVECTOR3 * SetStart(D3DXVECTOR3* vecEnd)
	{
		return((D3DXVECTOR3* (__thiscall*)(i3CollideeLine*, D3DXVECTOR3*)) GetModule(i3SceneDx, p_i3CollideeLine_SetStart))(this, vecEnd);
	}
	D3DXVECTOR3* SetEnd(D3DXVECTOR3* vecEnd)
	{
		return((D3DXVECTOR3* (__thiscall*)(i3CollideeLine*, D3DXVECTOR3*)) GetModule(i3SceneDx, p_i3CollideeLine_SetEnd))(this, vecEnd);
	}
	static i3CollideeLine* Singleton()
	{
		typedef i3CollideeLine* (__stdcall * tgetHandler)();
		tgetHandler getHandler = (tgetHandler)((DWORD)GetProcAddress(GetModuleHandleA(i3SceneDx), p_i3CollideeLine_new_object_fun));
		return (i3CollideeLine*)(getHandler());
	}
};

class i3Framework {
public:
	i3PhysixHitResult * RaycastClosest(i3CollideeLine* Line)
	{
		return((i3PhysixHitResult* (__thiscall*)(i3Framework*, i3CollideeLine*, int))dwRaycast)(this, Line, 0);
	}

	/*static i3Framework* Framework()
	{
		return (i3Framework*)(*(DWORD*)(dwFramework));
	}*/
};

class i3Viewer {
public:
	i3Framework * GetFramework()
	{
		return((i3Framework* (__thiscall*)(i3Viewer*))GetModule(i3FrameworkDx, p_i3Viewer_GetFramework))(this);
	}
};

class i3UI {
public:
	static i3Viewer* getViewer()
	{
		typedef i3UI* (__stdcall * tgetHandler)();
		tgetHandler getHandler = (tgetHandler)((DWORD)GetProcAddress(GetModuleHandleA(i3FrameworkDx), p_i3UI_getViewer));
		return (i3Viewer*)(getHandler());
	}
};

bool isVisible(int TargetIndex)
{
	__try
	{
		if (TargetIndex < 0)return false;
		i3CollideeLine* Line = i3CollideeLine::Singleton();
		D3DXVECTOR3 vTarget, vLocal;
		GetUserBone(vLocal, CBattleSlotContext::getMySlotIdx(), 5);
		GetUserBone(vTarget, TargetIndex, 7);
		vLocal.y += 0.1f;
		Line->SetStart((D3DXVECTOR3*)&vLocal.x);
		Line->SetEnd((D3DXVECTOR3*)&vTarget.x);
		i3PhysixHitResult* PhysixHitResult = i3UI::getViewer()->GetFramework()->RaycastClosest(Line);
		if (PhysixHitResult == NULL)return false;
		float Dist = sqrt(
			((vLocal.x - vTarget.x) * (vLocal.x - vTarget.x)) +
			((vLocal.y - vTarget.y) * (vLocal.y - vTarget.y)) +
			((vLocal.z - vTarget.z) * (vLocal.z - vTarget.z))
			);
		if (PhysixHitResult->Distance >= Dist)
			return (PhysixHitResult->Distance >= Dist);
		else
			return false;
	}
	__except (true) {}
}

bool CheckSpawn(int i)
{
	DWORD CharaManager = *(DWORD*)(c_pCharaManager);
	if (CharaManager != NULL)
	{
		__try
		{
			float Spawn = *(float*)(*(DWORD*)(CharaManager + 0x14 + (i * 0xE0)) + 0x17C);
			if (Spawn >= -4)
				return true;
			else
				return false;
		}
		__except (true)
		{
			return false;
		}
	}
	else return false;
}





int getUserDeath(int i)
{
	DWORD GameManager = *(DWORD*)(c_pCharaManager);
	_try
	{
		return *(DWORD*)(GameManager + 0x18 + i * 0xE0);

	}
		__except (EXCEPTION_EXECUTE_HANDLER){}
}
int Visible=0;
void DrawEsp2(IDirect3DDevice9* pDevice) {
	if (ResultBaseChara) {
		for (int iSlot = 0; iSlot <= 15; iSlot++) {
			if (CBattleSlotContext::Singleton()->getMySlotIdx() != iSlot && CBattleSlotContext::Singleton()->getMySlotIdx() % 2 != iSlot % 2) {
				float fMaxDistance, TelaX, TelaY;
				D3DXVECTOR3 OnScreen, OnWorld, MyPlayer;
				if (GetUserBone(OnWorld, iSlot, 0)) {
					if (WorldToScreen(i3RenderContext::Singleton()->pDevice, OnWorld, OnScreen)) {
						GetUserBone(MyPlayer, CBattleSlotContext::Singleton()->getMySlotIdx(), 0);
						fMaxDistance = CalcDistance(OnWorld, MyPlayer);
						TelaX = (int)OnScreen.x - (9000 / fMaxDistance) / 40;
						TelaY = (int)OnScreen.y - (16000 / fMaxDistance) / 40;
						{
							{

								if (getUserDeath(iSlot) == 2)
								{

								//	DrawBorderESP(TelaX, TelaY, 50000 / fMaxDistance / 6 * 2 / 40, 50000 / fMaxDistance / 3 * 2 / 40, 1, RED, i3RenderContext::Singleton()->pDevice, iSlot);
								//	
								//	if (isVisible(iSlot))
								//	{
								//	
								//			DrawBorderESP(TelaX, TelaY, 50000 / fMaxDistance / 6 * 2 / 40, 50000 / fMaxDistance / 3 * 2 / 40, 1, GREEN, i3RenderContext::Singleton()->pDevice, iSlot);
								//		}
								//}
								//	}

							if(Visible && (isVisible (iSlot)== true))
							{
								DrawBorderESP(TelaX, TelaY, 50000 / fMaxDistance / 6 * 2 / 40, 50000 / fMaxDistance / 3 * 2 / 40, 1, YELLOW ,i3RenderContext::Singleton()->pDevice, iSlot);
							}
							else
				
					if (Spanw && *(float*)(*(DWORD*)((DWORD)(*(DWORD*)(c_pCharaManager)) + 0xE0 * iSlot + 0x14) + 0x17C) >= -4)
					DrawBorderESP(TelaX, TelaY, 50000 / fMaxDistance / 6 * 2 / 40, 50000 / fMaxDistance / 3 * 2 / 40, 1, YELLOW, i3RenderContext::Singleton()->pDevice, iSlot);
				else
					DrawBorderESP(TelaX, TelaY, 50000 / fMaxDistance / 6 * 2 / 40, 50000 / fMaxDistance / 3 * 2 / 40, 1, BLUE, i3RenderContext::Singleton()->pDevice, iSlot);
									
						}
					}
				}
					}}
		}
		}}}

void DrawESP22(LPDIRECT3DDEVICE9 pDevice)
{
	if (CBattleSlotContext::Singleton() != nullptr)
	{
		int MyTeam = cTeamFind(CBattleSlotContextnew::Singletonss()->getMySlotIdx());
		for (int slot = 0; slot < 16; slot++)
		{
			D3DXVECTOR3 pos = CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(slot)->RootPos;
			D3DXVECTOR3 Playerpos,HeadScreen,BoneHead,NameHead;

			D3DVIEWPORT9 viewP;
			pDevice->GetViewport(&viewP);
			DWORD OnTopX = viewP.Width / 2;
			DWORD OnTopY = viewP.Y;
			D3DXVECTOR3 pLocal, pPlayer, PBody, PHead;
			pPlayer = CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(slot)->RootPos;
			pLocal = CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(CBattleSlotContextnew::Singletonss()->getMySlotIdx())->RootPos;
			D3DXVECTOR3 MyDistance = pLocal - pPlayer;
			int cDistance = CalcDistance(CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(slot)->RootPos, CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(CBattleSlotContextnew::Singletonss()->getMySlotIdx())->RootPos);
			int iTeam = cTeamFind(slot);
			if (iTeam == MyTeam)continue;
			GetUserBone(BoneHead, slot, 7);
			WorldToScreen(pDevice, BoneHead, NameHead);
			if (WorldToScreen(pDevice, pos, HeadScreen))
			{

			
				if (getUserDeath(slot) == 2)
								{


					if (Espname != 0){
						char *buf = new char[32];
						sprintf(buf, "%ws", *(DWORD*)(*(DWORD*)(BlatteContextPBEvo)+(0x17E3C + 4 * slot)) + 0x8);
						if (DeathCheck(slot))
						{

							
							

							if(Visible && (isVisible (slot)== true))
							{
								DrawOutlineString((float)NameHead.x,(float)NameHead.y-25,SKYBLUE, DT_NOCLIP,fName, buf);
							}
							else if (Spanw && *(float*)(*(DWORD*)((DWORD)(*(DWORD*)(c_pCharaManager)) + 0xE0 * slot + 0x14) + 0x17C) >= -4)
								DrawOutlineString((float)NameHead.x,(float)NameHead.y-25,BLUE, DT_NOCLIP,fName, buf);
							else
								DrawOutlineString((float)NameHead.x,(float)NameHead.y-25,YELLOW, DT_NOCLIP,fName, buf);
						}
						else if (Espname == 1){ /*DrawString2(Playerpos.x - 25, Playerpos.y - 45, GREEN, buf);*/ 
							DrawOutlineString((float)NameHead.x,(float)NameHead.y-25,RED, DT_NOCLIP,fName, buf);
						}
					}
					if(EspDistance){
						char dist[20];
						sprintf(dist, "%d M", cDistance);
						DrawOutlineString((float)HeadScreen.x, (float)HeadScreen.y+17, WHITE, DT_NOCLIP, fName, dist);
					}
				}
			}
		}
	}
}








//
//
//
//int MultiSnife;
//void CuchilloRapido() {
//	
//
//			
//if (MultiSnife && GetAsyncKeyState(VK_LBUTTON))
//		{
//			
//	
//	*(BYTE*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(ResultBasePlayer)+0x2C) + 0x2C) + 0x6B) = 66;
//
//	
//	}
//	else 
//		if (MultiSnife)
//		{
//	*(BYTE*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(ResultBasePlayer)+0x2C) + 0x2C) + 0x6B) = 66;	
//		
//				
//		}
//		//	if(GetAsyncKeyState(VK_LBUTTON))
//		//	{
//		//		*(BYTE*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(ResultBasePlayer)+0x2C)+0x2C)+0x6B) = 66;
//		//	}
//		//}
//}
////
////
#define Desativado               0xB7A7C5AC 
#define CuponSize                0x48
//#define g_pAFK                   (c_pGameContext + 0x1D8)
DWORD Ativado3 = 0x3F4CE1C6;
DWORD Ativado2 = 0x44096546;
DWORD Desativado2 = 0x00000000;
DWORD Ativado = 0x3F40E1C6;
DWORD Ativado1 = 0x454CE1C6;
DWORD AtivaAgilidade = 0x3E95BA80;



DWORD setReload2 = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x10));

DWORD Decrypt_setReload = (DWORD)DecodePointer((LPVOID)setReload2);


void FastReload()
{
		if (Reloadnew == 3)
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
		}
	}
	else if (Reloadnew == 2)
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado2 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado2;
		}
	}
	else if (Reloadnew == 1 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado3 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado3)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado3;
		}
	}
	else if (Reloadnew == 0 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado3 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)  
				*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1 ;
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setReload + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
		}
	}
}




DWORD setWeapon = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0xC));
DWORD Decrypt_setWeapon = (DWORD)DecodePointer((LPVOID)setWeapon);
 void WeaponFastSwitch()
{
	if (FastSwith == 3)
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
		}
	}
	else if (FastSwith == 2 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado2 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado2;
		}
	}
	else if (FastSwith == 1 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado3 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado3)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado3;
		}
	}
	else if (FastSwith == 0 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado3;
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setWeapon + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
		}
	}
}



 int IntenHP;
 DWORD setHPExtra2 = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x2C));
DWORD Decrypt_setHPExtra = (DWORD)DecodePointer((LPVOID)setHPExtra2);

 void HPExtra()
{
	if (IntenHP == 1 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setHPExtra + CBattleSlotContext::getMySlotIdx() * CuponSize) != 1248139380 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setHPExtra + CBattleSlotContext::getMySlotIdx() * CuponSize) == 1248139380)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setHPExtra + CBattleSlotContext::getMySlotIdx() * CuponSize) = 1248139380; //1036834633
		}
	}
	else 
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setHPExtra + CBattleSlotContext::getMySlotIdx() * CuponSize) == 1248139380) //1248139380
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setHPExtra + CBattleSlotContext::getMySlotIdx() * CuponSize) = 3081225644;
		}
	}
}


 
DWORD SetFall2 = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x34));
DWORD Decrypt_setFall = (DWORD)DecodePointer((LPVOID)SetFall2);
// void NoFall()
//{
//	if (fallfunc == 1 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
//		}
//	}
//	else if (fallfunc == 0)
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado;
//		}
//	}
//}
  void NoFall()
{
	if (fallfunc == 1 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + Decrypt_setFall + Decrypt_setHPExtra+ CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
		}
	}
	else if (fallfunc == 0)
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setFall + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado;
		}
	}
}



// DWORD setBalaDeFerro = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x18));
//DWORD Decrypt_setBalaDeFerro = (DWORD)DecodePointer((LPVOID)setBalaDeFerro);
//
//  void BalaDeFerro()
//{
//	if (Baladuraintem == 1 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setBalaDeFerro + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setBalaDeFerro + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setBalaDeFerro + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
//		}
//	}
//	else if (Baladuraintem == 0 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setBalaDeFerro + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setBalaDeFerro + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
//		}
//	}
//}
//  int Coletefunc;
//
//  DWORD setColete = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x20));
//DWORD Decrypt_setColete = (DWORD)DecodePointer((LPVOID)setColete);
// void Colete()
//{
//
//if (Coletefunc == 1 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setColete + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setColete + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setColete + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
//		}
//	}
//	else if (Coletefunc == 0 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setColete + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setColete + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
//		}
//	}
//}
//int RespawnFunc;


//DWORD ResultNoRespawn = mNoRecoilX + 0x19A914;
 void RespawnVoid()
{
		if (RespawnFunc == 3 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado1;
		}
	}
	 else if (RespawnFunc == 2 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado2 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado2;
		}
	}
else if (RespawnFunc == 1)
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) != Ativado3 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado3)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado3;
		}
	}
	else if (RespawnFunc == 0 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado1 ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) == Ativado2)
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) = Ativado3 ;
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setRespawn + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
		}
	}
}


 DWORD setAgilidade = (DWORD)EncodePointer((LPVOID)((DWORD)DecodePointer((LPVOID)Ticket_Offset) + 0x24));
DWORD Decrypt_setAgilidade = (DWORD)DecodePointer((LPVOID)setAgilidade);



int agilidadfunc;
void Agilidade()
{
	if (agilidadfunc == 1 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) != AtivaAgilidade ||
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) == AtivaAgilidade)
			*(DWORD*)(*(DWORD*)CBattleSlotContext::Singleton()->getMySlotIdx(), 0);
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) = AtivaAgilidade;
		}
	}
	else if (agilidadfunc == 0 )
	{
		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) == AtivaAgilidade)
		{
			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
		}
	}
}
//

bool GetBattleState()
{
	unsigned long xBase = *(DWORD*)(ResultBasePlayer);
	if(xBase > 0)
	{
		return true;
	}
	return false;
}

int macro;
DWORD WriteHooking_Macro(void)//this complete & running smoothly
{
	while(1)
	{
		if(macro == 1)
		{
			if(IsKeyPressed(VK_LBUTTON, 0) && 1 == 1)
			{
				if(GetBattleState())
				{
					keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
					{
						Sleep(50);
					}
					keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
					{
						Sleep(50);
					}
					keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
			}
		}
		Sleep(50);
	}
}


DWORD getIndexBone;

int GetCharaToAim()
{
	int Result = -1;
	float fMaxDistance = 5000.0f;
	D3DXVECTOR3 MyPosition, EnemyPos, EndPos;
	for(int iSlot = 0; iSlot < 16; iSlot++)
	{
		if(DeathCheck(iSlot) && (isVisible(iSlot)== true))
		{
			if(CBattleSlotContext::Singleton()->getMySlotIdx() % 2 != iSlot % 2)
			{
				EnemyPos = CBattleSlotContextnew::Singletonss()->getGameInfo_Chara(iSlot)->RootPos;
				GetUserBone(MyPosition, CBattleSlotContext::Singleton()->getMySlotIdx(), getIndexBone);
				{
					if(GetUserBone(EndPos, iSlot , getIndexBone) && CalcDistance(EnemyPos, MyPosition) < fMaxDistance)
					{
						fMaxDistance = CalcDistance(EnemyPos, MyPosition);
						Result = iSlot;
					}
				}
			}
		}
	}
	return Result;
}
int AimBot			= 0;
int TargetLock		= 0;
RECT rect, rect2, rect3, rect4;
void _fastcall DoAimBot(IDirect3DDevice9 *pDevice)
{
	if(TargetLock == 1){
		getIndexBone = 5.0f;
	}
	else{
		getIndexBone = 7.0f;
	}
	if(AimBot)
	{
		pDevice->GetViewport(&ViewPortAim);
		int SetDistance = GetCharaToAim();
#define DistanceNear (int)DistX > -249 && (int)DistY > -190
		if(SetDistance != -1)
		{
			D3DXVECTOR3 OnWorld, OnScreen;
			if(GetUserBone(OnWorld, SetDistance, getIndexBone))
			{
				if(WorldToScreen(pDevice, OnWorld, OnScreen))
				{
					int curx = (int)OnScreen.x;
					int cury = (int)OnScreen.y;
					float DistX = (float)curx - ViewPortAim.Width / 2.0f;
					float DistY = (float)cury - ViewPortAim.Height / 2.0f;
					DistX /= (float)1 * 0.5f;
					DistY /= (float)1 * 0.5f;
					if(DistanceNear)
					{
						mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, NULL, NULL);
					}
				}
			}
		}
	}
}





int AutoReady;
int AutoBundi;
int AutoKiller;
int UnlockPass;
int ForceServer;
int SetBrust;
int BUNUHTEMAN;
int AimKey;
int Aimbot;
int getBoneIndex;
int HideNick;
int KickAllPlayer;
int SpeedHack;
int NoRecoil1;
#define VK_4           0x34
//void CallGBMode(IDirect3DDevice9 *pDevice)
//{
//
//	if (SpeedHack == 1 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) != AtivaAgilidade ||
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) == AtivaAgilidade)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) = AtivaAgilidade;
//		}
//	}
//	else if (SpeedHack == 0 )
//	{
//		if (*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) == AtivaAgilidade)
//		{
//			*(DWORD*)(*(DWORD*)BlatteContextPBEvo + Decrypt_setAgilidade + CBattleSlotContext::getMySlotIdx() * CuponSize) = Desativado2;
//		}
//	}
//
//}

