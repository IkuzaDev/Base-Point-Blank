/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include "CallHack.h"
//------------------------------------------------------------------------------------------------------//
int MenuFolder[100];
int Drawing		= 0;
int Mpos		= 0;
int Mmax		= 0;
int DrawFont	= 1;
int Mvisible	= 1;
int Mxofs		= 25.0f;
int Mysize		= 15.0f;
int my			= 70;   // Up Down
int	mx			= 150;  // Right Left
char Mtitle[81]	= "";
//------------------------------------------ Color D3D --------------------------------------------------//
#define 	MENUMAXINDEX	100
#define 	MENUFOLDER		1
#define 	MENUTEXT		2
#define 	MENUITEM		3
#define		MENUCAT			4
#define		COLORFOLDER		YELLOW  
#define		COLORTEXT		GREEN   
#define		COLORON			SKYBLUE 
#define		COLOROFF		WHITE   
#define		COLORFITURE		WHITE
//-------------------------------------------------------------------------------------------------------//
struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}
//-------------------------------------------------------------------------------------------------------//
D3MENU[MENUMAXINDEX];
LPD3DXFONT pFont;
//---------------------------------- Declaration AddText ------------------------------------------------//
void AddItem(char *txt, char **opt, int *var, int maxvalue, int typ){
D3MENU[Mmax].typ=typ;
D3MENU[Mmax].txt=txt;
D3MENU[Mmax].opt=opt;
D3MENU[Mmax].var=var;
D3MENU[Mmax].maxvalue=maxvalue;
Mmax++;
}
//------------------------------------ Declaration AddText ----------------------------------------------//
void AddText(char *txt, char *opt){
D3MENU[Mmax].typ=MENUTEXT;
D3MENU[Mmax].txt=txt;
D3MENU[Mmax].opt=(char **)opt;
D3MENU[Mmax].var=0;
D3MENU[Mmax].maxvalue=0;
Mmax++;
}
//-------------------------------------- Declaration TextR ----------------------------------------------//
void DrawTextR(int x,int y,DWORD color,char *text){
RECT rect, rect1, rect2, rect3, rect4, rect5;
SetRect( &rect, x, y, x, y );
SetRect( &rect1, x-1, y, x-1, y );
SetRect( &rect2, x, y, x, y );
SetRect( &rect3, x, y+1, x, y+1 );
SetRect( &rect4, x, y, x, y );
SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
pFont->DrawTextA(NULL,text,-1,&rect5, DT_LEFT|DT_NOCLIP, color );
pFont->DrawTextA(NULL,text,-1,&rect,  DT_LEFT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect1, DT_LEFT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect3, DT_LEFT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect4, DT_LEFT|DT_WORDBREAK, BLACK );
}
//------------------------------------ Declaration TextL ------------------------------------------------//
void DrawTextL(int x,int y,DWORD color,char *text){
RECT rect, rect1, rect2, rect3, rect4, rect5;
SetRect( &rect, x, y, x, y );
SetRect( &rect1, x-1, y, x-1, y );
SetRect( &rect2, x, y, x, y );
SetRect( &rect3, x, y+1, x, y+1 );
SetRect( &rect4, x, y, x, y );
SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
pFont->DrawTextA(NULL,text,-1,&rect5, DT_RIGHT|DT_NOCLIP, color );
pFont->DrawTextA(NULL,text,-1,&rect,  DT_RIGHT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect1, DT_RIGHT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect2, DT_RIGHT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect3, DT_RIGHT|DT_WORDBREAK, BLACK );
pFont->DrawTextA(NULL,text,-1,&rect4, DT_RIGHT|DT_WORDBREAK, BLACK );
}
//------------------------------------ Declaration TextC ------------------------------------------------//
void DrawTextC(int x,int y,DWORD color,char *text ){
RECT rect, rect2;
SetRect( &rect, x, y, x, y );
SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
pFont->DrawTextA(NULL,text,-1,&rect2, DT_CENTER|DT_NOCLIP, 0x00000000 );
pFont->DrawTextA(NULL,text,-1,&rect, DT_CENTER|DT_NOCLIP, color );
}
//----------------------------------- Declaration ShowFahmi ----------------------------------------------//
void ShowFahmi(float x, float y, LPDIRECT3DDEVICE9 pDevice){
int i, val;
DWORD color;
DWORD texty;
char text[100];
if (!Mvisible) return;
for (i=0; i<Mmax; i++) {
val=(D3MENU[i].var)?(*D3MENU[i].var):0;
sprintf(text, "%s", D3MENU[i].txt);
if (i==Mpos){
color=GREEN;
texty=GREEN;
sprintf(text, "%s", D3MENU[i].txt);
}
else if (D3MENU[i].typ==MENUFOLDER){
color=DEEPSKYBLUE;
texty=DEEPSKYBLUE;
}
else if (D3MENU[i].typ==MENUTEXT){
color=YELLOW;
texty=YELLOW;
}
else{
color=(val)?RED:ORANGE;
texty=(val)?COLORFITURE:COLORFITURE;
}
if (D3MENU[i].opt){
if (D3MENU[i].typ==MENUITEM){
DrawTextL(x+3, y, texty,text);
y = y + 2;
}else{
DrawTextL(x+3, y, texty,text);
}}
if (D3MENU[i].opt) {
if (D3MENU[i].typ==MENUTEXT)
DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt);
else
DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt[val]);}
y+=Mysize;
}}
//--------------------------------- Declaration MenuNavigation ------------------------------------------//
void MenuNavFahmi(void){
if (IsKeyPressed(VK_INSERT, 0)&1){
Mvisible=(!Mvisible);
}
if (!Mvisible) return;
if (IsKeyPressed(VK_UP, 0)&1){
do {
Mpos--;
if (Mpos<0)  Mpos=Mmax-1;
} 
while (D3MENU[Mpos].typ==MENUTEXT);	
}else if (IsKeyPressed(VK_DOWN, 0)&1) {
do {
Mpos++;
if (Mpos==Mmax) Mpos=0;
} while (D3MENU[Mpos].typ==MENUTEXT);		
} else if (D3MENU[Mpos].var) {
int dir=0;
if ( ( IsKeyPressed(VK_LEFT, 0)&1 ) && *D3MENU[Mpos].var > 0 ) dir=-1;
if ( ( IsKeyPressed(VK_RIGHT, 0)&1 ) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
if (dir) {
*D3MENU[Mpos].var += dir;
if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
}}}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
char *Moptfolder  [] = {"Open","Close"};//Open Menu
char *Moptonoff	  [] = {"Off","On"};//Open Fitur
char *MoptCross	  [] = {"Off","Cross1","Cross2","Cross3"};//Croshair
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void TampilanFahmi(LPDIRECT3DDEVICE9 pDevice)
{
	AddText("Fahmi Santoso"				,"PointBlank Garena Indonesia");

	AddItem("Informasi"					, Moptfolder, &MenuFolder[1]	, 2, MENUFOLDER);
	if(MenuFolder[1])
	{
		AddItem("Crosshair"				, MoptCross,  &CROSS			, 4, MENUCAT);
		AddItem("Wallhack"				, Moptonoff,  &Wallhack			, 2, MENUCAT);
		AddItem("No Smoke&Fog"			, Moptonoff,  &DontSmoke		, 2, MENUCAT);
		AddItem("Show FPS"				, Moptonoff,  &ShowFPS			, 2, MENUCAT);
		AddItem("Time & Date"			, Moptonoff,  &ShowTime			, 2, MENUCAT);
		AddText("AntiOut"				, "[-Auto ON-]");
		AddText("Fast Exit"				, "[-F12-]");
	}
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/