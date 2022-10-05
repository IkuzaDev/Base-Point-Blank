/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "AutoLogger.h"
#include "Class.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
//-------------------------------------------------------------------------------//
D3DVIEWPORT9 Viewport;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DDEVICE9 npDevice; 
LPDIRECT3DDEVICE9 pDevice; 
LPDIRECT3DDEVICE9 pGDevice = NULL;
LPD3DXFONT g_pFont  = NULL;
LPD3DXLINE pLine    = NULL;
//-------------------------------------------------------------------------------//
DWORD TeamColor;
D3DVECTOR Player;
D3DVECTOR HeadPos;
D3DVECTOR PlayerScaled;
D3DVECTOR HeadScaled;
D3DVECTOR BonePos;
BOOL Create;
//-------------------------------------------------------------------------------//
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define PINK			D3DCOLOR_XRGB(255, 0  , 255)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255)  
#define DEEPSKYBLUE     D3DCOLOR_ARGB(255, 30,  144, 255)
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define LIGHTBLUE		D3DCOLOR_ARGB(255, 19,  84,  199) 
//-------------------------------------------------------------------------------//
int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)
//-------------------------------------------------------------------------------//
static struct key_s{
bool bPressed;
DWORD dwStartTime;
}
//-------------------------------------------------------------------------------//
kPressingKey[256];
//-------------------------------------------------------------------------------//
BOOL IsKeyPressed(int Key,DWORD dwTimeOut){
if( HIWORD( GetKeyState( Key ) ) ){
if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) ){
kPressingKey[Key].bPressed = TRUE;
if( dwTimeOut > NULL )
kPressingKey[Key].dwStartTime = GetTickCount( );
return TRUE;
}
}else
kPressingKey[Key].bPressed = FALSE;
return FALSE;
}
//------------------------------------------------------------------------------//
void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice ){
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
//---------------------------------------------------------------------------//
void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice ){
FillRGB( x, (y + h - px), w, px, BorderColor, pDevice );
FillRGB( x, y, px, h, BorderColor, pDevice );
FillRGB( x, y, w, px, BorderColor, pDevice );
FillRGB( (x + w - px), y, px, h, BorderColor, pDevice );
}
//-------------------------------------------------------------------------------//
bool GetBattleState() { 
DWORD BaseG = (DWORD)GetModuleHandleA("PointBlank.exe");
unsigned long xBase = *(DWORD*)(BaseG + ResultBaseAmmo); 
if(xBase > NULL){ 
return true; }
return false; 
}
//------------------------------------------------------------------------------//
int GetTeam(int Zigo){
for(int i = 0; i<=15; i+=2)
if( i == Zigo ) return 1;
for(int i = 1; i<=15; i+=2)
if( i == Zigo ) return 2;
return 0;
}
//-------------------------------------------------------------------------------//
int GetMyCharaIndex(){
unsigned long dwBase	= *(DWORD*)ResultBasePlayer2;
CTeam *MyTeam = (CTeam*) ((dwBase + ResultTEAM));
return MyTeam->iTeam;
}
//-------------------------------------------------------------------------------//
bool IsAlive(int Index){
unsigned long dwBase2	= *(DWORD*)(ResultBaseHealth2);
CHealth		*Health		= (CHealth*) ((dwBase2 + ResultHEALTH) + Index * ResultHEALTHSIZE);
if(Health->CurHP > 0.1f)
return true;
return false;
}
//-------------------------------------------------------------------------------//
void HookedFahmi(PDWORD target, PDWORD newfunc){
DWORD Jmpto=(DWORD)(newfunc)-(DWORD)target-5;
DWORD a;
VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &a);
*(PBYTE)(target)=0xE9;
*(PDWORD)((DWORD)(target)+1)=Jmpto;
VirtualProtect(target, 8, a, &a);
}
//------------------------------------------------------------------------------//
DWORD GetAmmoIndex(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1){
DWORD C=0;
if (IsBadReadPtr((PDWORD)dwPtr,4)==0){
C=*(PDWORD)((DWORD)(dwPtr))+A1;
if (IsBadReadPtr((PDWORD )C,4)==0){
C=*(PDWORD)((DWORD)(C ))+ B1;
if (IsBadReadPtr((PDWORD)C,4)==0) {
C=*(PDWORD)((DWORD)(C ))+ C1;
if (IsBadReadPtr((PDWORD)C,4)==0) {
return *(PDWORD)C;
}}}}
return C;
}
//-------------------------------------------------------------------------------//
void PrivateOnly(void *adr, void *ptr, int size){ 
DWORD NextProtection;
VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &NextProtection);
Sleep(1);
Sleep(1);
RtlCopyMemory(adr,ptr,size);
Sleep(1);
Sleep(1);
VirtualProtect(adr,size,NextProtection, &NextProtection);
}
//-------------------------------------------------------------------------------//
void WeaponHack2(DWORD B,DWORD A1,DWORD B1, DWORD ISI){ 
DWORD A=0;
if (IsBadReadPtr((PDWORD)B,1)==0){ 
A=*(PDWORD)((DWORD)(B))+A1;
if (IsBadReadPtr((PDWORD)A,1)==0){ 
A=*(PDWORD)((DWORD)(A))+B1;
if (IsBadReadPtr((PDWORD)A,1)==0){
*(PDWORD)A=ISI;
}}}}
//-------------------------------------------------------------------------------//
DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1){
DWORD C=0;
if (IsBadReadPtr((PDWORD)dwPtr,4)==0){
C=*(PDWORD)((DWORD)(dwPtr))+A1;
if (IsBadReadPtr((PDWORD )C,4)==0){
C=*(PDWORD)((DWORD)(C ))+ B1;
if (IsBadReadPtr((PDWORD)C,4)==0){
C=*(PDWORD)((DWORD)(C ))+ C1;
if (IsBadReadPtr((PDWORD)C,4)==0){
return *(PDWORD)C; 
}}}}
return C;
}
//-------------------------------------------------------------------------------//
void *DetourFunction (BYTE *src, const BYTE *dst, const int len){
BYTE *jmp = (BYTE*)malloc(len+5);
DWORD dwBack;
VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
memcpy(jmp, src, len);  
jmp += len;
jmp[0] = 0xE9;
*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;
src[0] = 0xE9;
*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
for (int i=5; i<len; i++)  src[i]=0x90;
VirtualProtect(src, len, dwBack, &dwBack);
return (jmp-len);
}
//-------------------------------------------------------------------------------//
void *DetourFunc(BYTE *src, const BYTE *dst, const int len){
BYTE *jmp = (BYTE*)malloc(len+5);
DWORD dwback;
VirtualProtect(src, len, PAGE_READWRITE, &dwback);
memcpy(jmp, src, len);	jmp += len;
jmp[0] = 0xE9;
*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;
src[0] = 0xE9;
*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
VirtualProtect(src, len, dwback, &dwback);
return (jmp-len);
}
//-------------------------------------------------------------------------------//
void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD WriteValue){
DWORD Temp=0;
if (IsBadReadPtr((PDWORD)Adr, 4) == 0){ 
Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){
*(PDWORD)Temp = WriteValue;
}}}}}
//-------------------------------------------------------------------------------//
void PatchValue(DWORD BaseOfs, DWORD Offset1, DWORD Offset2, DWORD Offset3, DWORD Value){
DWORD Temp=0;
if (IsBadReadPtr((PDWORD)BaseOfs, 4) == 0){ 
Temp = *(PDWORD)((DWORD)(BaseOfs)) + Offset1;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
Temp = *(PDWORD)((DWORD)(Temp)) + Offset2;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
Temp = *(PDWORD)((DWORD)(Temp)) + Offset3;
if (IsBadReadPtr((PDWORD)Temp,4) == 0){
*(PDWORD)Temp = Value;
}}}}}
//------------------------------------------------------------------------------//
BYTE Weapon,Pistol,Knife,Bomb,Smokee,Dual;
void __ReadMem(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, int opt){
DWORD Temp =0;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
switch (opt){
case 1:
Weapon = *(PBYTE)Temp;
case 2:
Pistol = *(PBYTE)Temp;
case 3:
Knife = *(PBYTE)Temp;
case 4:
Bomb = *(PBYTE)Temp;
case 5:
Smokee = *(PBYTE)Temp;
case 6:
Dual = *(PBYTE)Temp;
}}}}}}
//-------------------------------------------------------------------------------//
void Function_One (DWORD Base,DWORD Ofs1, BYTE Value){
DWORD Temp=NULL;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
*(PBYTE)Temp=Value;
}}}
//-------------------------------------------------------------------------------//
void PachtChara(DWORD B,DWORD A1,DWORD B1, DWORD ISI){
DWORD A=0;
if (IsBadReadPtr((PDWORD)B,4)==0){
A=*(PDWORD)((DWORD)(B))+A1;
if (IsBadReadPtr((PDWORD )A,4)==0){
A=*(PDWORD)((DWORD)(A ))+ B1;
if (IsBadReadPtr((PDWORD)A,4)==0) {
{*(PDWORD)A=ISI;
}}}}}
//-------------------------------------------------------------------------------//
DWORD addworx1;
void ChangesVirtualProtect(void* address, char bytes){
VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &addworx1);
}
void RestoreVirtualProtect(void* address, char bytes){
VirtualProtect(address,bytes,addworx1,&addworx1);
}
char Mem_ASM(void* address, void* val, char bytes)
{ChangesVirtualProtect(address, bytes);
memcpy(address, val, bytes);
RestoreVirtualProtect(address, bytes);
return(0);
}
//-------------------------------------------------------------------------------//
int WritePtr (unsigned long ads, unsigned long ptr, int value){
__try{
unsigned long WrtPointer = false;
WrtPointer = *(unsigned long*)((ads))+ptr;
*(int*)(WrtPointer) = value;
return true;
}__except (EXCEPTION_EXECUTE_HANDLER){
return false;
}}
//-------------------------------------------------------------------------------//
void LongPtr ( DWORD adress, DWORD offset, DWORD offset2, int Value ){
__try{
DWORD OldPtr;
OldPtr = *(PDWORD)((DWORD)adress) + offset;
OldPtr = *(PDWORD)((DWORD)OldPtr) + offset2;
*(int*)(OldPtr) = Value;
}__except (EXCEPTION_EXECUTE_HANDLER){
}}
//-------------------------------------------------------------------------------//
void gEtWeapon_IndexA(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, DWORD Value){ 
DWORD Temp=0;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
*(PDWORD)Temp=Value;}}}}
}
//-------------------------------------------------------------------------------//
DWORD Read(DWORD dwPtr, DWORD dwOfs){ 
DWORD C; 
if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
if(IsBadReadPtr((PDWORD)(C),4)==0){ 
return *(PDWORD)C; 
}}
return C;
}
//-------------------------------------------------------------------------------//
void JMPE9(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen){
DWORD dwOldProtect, dwBkup, dwRelAddr;
VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
*pAddress = 0xE9;
*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
return;
}
//------------------------------------------------------------------------------//
void c_WeaponIndex_B(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned long Ofset3, unsigned long Ofset4, DWORD dwValue){ 
DWORD A=0;
if(IsBadReadPtr((PDWORD)adr,4))return;
A=*(PDWORD)((DWORD)(adr))+Ofset1;
if(IsBadReadPtr((PDWORD)A,4))return;
A=*(PDWORD)((DWORD)(A))+Ofset2;
if(IsBadReadPtr((PDWORD)A,4))return;
A=*(PDWORD)((DWORD)(A))+Ofset3;
if(IsBadReadPtr((PDWORD)A,4))return;
A=*(PDWORD)((DWORD)(A))+Ofset4;
if(IsBadReadPtr((PDWORD)A,4))return;
if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}
//------------------------------------------------------------------------------//
DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget){
DWORD dwOldProtect,dwBkup;
DWORD dwRetn = *(DWORD*)(MemoryTarget);
VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
*((DWORD *)(MemoryTarget)) = FunctionTarget;
VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
return dwRetn;
}
//------------------------------------------------------------------------------//
void patchPTR(unsigned long adr, unsigned long Ofset1, DWORD dwValue){ 
DWORD A=0;
if(IsBadReadPtr((PDWORD)adr,4))return;
A=*(PDWORD)((DWORD)(adr))+Ofset1;
if(IsBadReadPtr((PDWORD)A,4))return;
if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}
//------------------------------------------------------------------------------//
void GetWeapon_IndexA(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, DWORD Value){ 
DWORD Temp=0;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
*(PDWORD)Temp=Value;}}}}
}
//-------------------------------------------------------------------------------//
DWORD WritePTR(DWORD Base,DWORD PTR1,DWORD Byte){ 
if (!IsBadReadPtr((PDWORD)Base,4)){DWORD RPTR1=*(PDWORD)((DWORD)(Base))+PTR1;
if (!IsBadReadPtr((PDWORD)RPTR1,4)){*(PDWORD)RPTR1=Byte;}}
return 0;
}
//-------------------------------------------------------------------------------//
void MakeJMP( BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen ){
__try{
DWORD dwOldProtect, dwBkup, dwRelAddr;
VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
*pAddress = 0xE9;
*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
return;
}__except ( EXCEPTION_EXECUTE_HANDLER ){
return;
}}
//-------------------------------------------------------------------------------//
bool MakePoint(unsigned long ADRexec, int OFSexec, int PTRexec){
if (!IsBadReadPtr((void*)ADRexec, sizeof(unsigned long))){
if (!IsBadReadPtr((void*)(*(unsigned long*)ADRexec + OFSexec), sizeof(unsigned long))){
*(int*)(*(unsigned long*)ADRexec + OFSexec) = PTRexec;
}}
return 0;
}
//-------------------------------------------------------------------------------//
void MemWrite(void *adr, void *byte, int size){
DWORD X;
VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &X);
memcpy(adr, byte, size);   
VirtualProtect(adr,size,X,&X);
}
//------------------------------------------------------------------------------//
D3DXVECTOR3 GetUserBonePos(int Idx ,int BoneIdx){
D3DXVECTOR3 Out;
DWORD dwI3EXEC	 = (DWORD)GetModuleHandleA("PointBlank.exe");
unsigned long dwGameBase = *(DWORD*)(dwI3EXEC + ResultBaseHealth);
if ( dwGameBase ){
CGameCharaBase* GameBase = (CGameCharaBase*)( *(DWORD*)(dwGameBase + 0x14 + ( 0x4 * Idx ) ) );
if ( GameBase && GameBase->m_BoneContext ){
Out.x = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._41;
Out.y = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._42;
Out.z = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._43;
}}
return Out;
}
//------------------------------------------------------------------------------//
bool GetUserBone( D3DXVECTOR3 &Out,  int BoneIdx ,int Idx){
DWORD dwGameBase = *(DWORD*)ResultBaseHealth2;
if ( dwGameBase ){
CGameBase* GameBase = (CGameBase*)( *(DWORD*)(dwGameBase + 0x14 + ( 0x4 * Idx ) ) );
if ( GameBase && GameBase->Bones){
Out.x = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._41;
Out.y = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._42;
Out.z = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._43;
return true;
}}
return false;
}
//------------------------------------------------------------------------------//
bool YoWorlToScreenGa(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled){
D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
D3DXMATRIX identity;
D3DXVECTOR3 vScreen;
pDevice->GetViewport(&Viewport);
Viewport.X = Viewport.Y = 0;
Viewport.MinZ     = 0;
Viewport.MaxZ     = 1;
D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height){
PlayerScaled.x = vScreen.x;
PlayerScaled.y = vScreen.y ;
PlayerScaled.z = vScreen.z;
return true; 
}return false;
}
//------------------------------------------------------------------------------//
#define PISSS 3.14159265
//------------------------------------------------------------------------------//
D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V){
D3DTLVERTEX v;
v.fX = X;
v.fY = Y;
v.fZ = Z;
v.fRHW = RHW;
v.Color = color;
v.fU = U;
v.fV = V;
return v;
}
//------------------------------------------------------------------------------//
void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice){
const int NUMPOINTS = 34;
if(!center){
x -= rad;
y -= rad;
}
D3DTLVERTEX Circle[NUMPOINTS + 1];
int i;
float X;
float Y;
float Theta;
float WedgeAngle;
WedgeAngle = (float)( (2*PISSS) / NUMPOINTS );
for( i=0; i<=NUMPOINTS; i++ ){
Theta = i * WedgeAngle;
X = (float)( x + rad * cos(Theta) );
Y = (float)( y - rad * sin(Theta) );
Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
}
pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
pDevice->SetTexture( 0, NULL );
pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}
//------------------------------------------------------------------------------//
bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled){
D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
D3DXMATRIX identity;
D3DXVECTOR3 vScreen;
pDevice->GetViewport(&Viewport);
Viewport.X = Viewport.Y = 0;
Viewport.MinZ     = 0;
Viewport.MaxZ     = 1;
D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height){
PlayerScaled.x = vScreen.x;
PlayerScaled.y = vScreen.y ;
PlayerScaled.z = vScreen.z;
return true; 
}
return false;
}
//---------------------------------------------------------------------------//
void DrawBoxz(int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice){
FillRGB( x, y, w, h, BoxColor, pDevice );
DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
}
//---------------------------------------------------------------------------//
void HealthBarNew(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health){
DWORD HPcol = GREEN;
if (Health < 90) HPcol = YELLOW;
if (Health < 80) HPcol = ORANGE;
if (Health < 40) HPcol = RED;
if (Health < 10) HPcol = BLACK;
DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
FillRGB(x,y,Health/2,3,HPcol,pDevice );
}
//---------------------------------------------------------------------------//
void  DrawLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color ){
D3DXVECTOR2 vLine[ 2 ];
pLine->SetAntialias( 0 );
pLine->SetWidth( (float)dwWidth );
pLine->Begin();
vLine[ 0 ][ 0 ] = (float)Xa;
vLine[ 0 ][ 1 ] = (float)Ya;
vLine[ 1 ][ 0 ] = (float)Xb;
vLine[ 1 ][ 1 ] = (float)Yb;
pLine->Draw( vLine, 2, Color );
pLine->End();
}
//---------------------------------------------------------------------------//
void DrawBoxVote( int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice ){
FillRGB( x, y, w, h, BoxColor, pDevice );
DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
}
//---------------------------------------------------------------------------//
void DrawBoxKick( int x, int y, IDirect3DDevice9* pDevice ){
if( !pDevice )
return;
DrawBoxVote( x, y, 167, 18,BLACK, WHITE, pDevice );
}
//---------------------------------------------------------------------------//
void DrawStringESP(int x, int y, DWORD color, const char *fmt, ...){
RECT FontPos = { x, y, x + 120, y + 16 };
char buf[1024] = {'\0'};
va_list va_alist;
va_start(va_alist, fmt);
vsprintf_s(buf, fmt, va_alist);
va_end(va_alist);
g_pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}
//---------------------------------------------------------------------------//
void DrawVoteKick(int x, int y, DWORD color, const char *fmt, ...){
RECT FontPos = { x, y, x + 120, y + 16 };
char buf[1024] = {'\0'};
va_list va_alist;
va_start(va_alist, fmt);
vsprintf_s(buf, fmt, va_alist);
va_end(va_alist);
g_pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}
//---------------------------------------------------------------------------//
BOOL IsInFiturBox(int x,int y,int w,int h){
POINT MousePosition; 
GetCursorPos(&MousePosition); 
ScreenToClient(GetForegroundWindow(),&MousePosition);
return(MousePosition.x > (x - 18) && MousePosition.x < (x + w - 18) && MousePosition.y > (y - 10) && MousePosition.y < (y + h - 10));
}
//---------------------------------------------------------------------------//
void FillRGBBOX( float x, float y, float w, float h, D3DCOLOR color){
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
D3DRECT rec = { x, y, x + w, y + h };
npDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
//---------------------------------------------------------------------------//
void DrawBorder( float x, float y, float w, float h, int px, float Health){
FillRGBBOX( x, (y + h - px), w, px, TeamColor);
FillRGBBOX( x, y, px, h, TeamColor);
FillRGBBOX( x, y, w, px, TeamColor);
FillRGBBOX( (x + w - px), y, px, h, TeamColor); 
}
//---------------------------------------------------------------------------//
void DrawBoxESP( int x, int y, int w, int h, float Health, IDirect3DDevice9* pDevice ){
DWORD HPcol = YELLOW;
if (Health < 90) HPcol = GREEN;
if (Health < 80) HPcol = GREEN;
if (Health < 40) HPcol = GREEN;
if (Health < 10) HPcol = GREEN;
DrawBorder( x, y, w, h, 1, HPcol, pDevice );
}
//---------------------------------------------------------------------------//
bool GetBonePos(CGameCharaBase*m_CharaBase,D3DXVECTOR3 &outpos,int BoneIndex){
outpos.x = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._41;
outpos.y = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._42;
outpos.z = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._43;
return true;
}
//---------------------------------------------------------------------------//
void DrawLineBone ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color ){
D3DXVECTOR2 vLine[ 2 ];
pLine->SetAntialias( 0 );
pLine->SetWidth( (float)dwWidth );
pLine->Begin();
vLine[ 0 ][ 0 ] = (float)Xa;
vLine[ 0 ][ 1 ] = (float)Ya;
vLine[ 1 ][ 0 ] = (float)Xb;
vLine[ 1 ][ 1 ] = (float)Yb;
pLine->Draw( vLine, 2, Color );
pLine->End();
}
//---------------------------------------------------------------------------//
void DrawBone(CGameCharaBase* m_CharaBase,int Start,int End,DWORD Color,LPDIRECT3DDEVICE9 pDevice){
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
if(GetBonePos(m_CharaBase,vStart,Start)){
if(GetBonePos(m_CharaBase,vEnd,End)){
if(ADDXW2S(pDevice,vStart,vvStart)){
if(ADDXW2S(pDevice,vEnd,vvEnd)){
DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,Color);
}}}}}
//---------------------------------------------------------------------------//
void DrawSkeleton(CGameCharaBase* m_CharaBase,DWORD Color,LPDIRECT3DDEVICE9 pDevice){
float wraw = 2;
DrawBone(m_CharaBase,0,6,Color,pDevice);
DrawBone(m_CharaBase,6,10,Color,pDevice);
DrawBone(m_CharaBase,6,11,Color,pDevice);
DrawBone(m_CharaBase,0,12,Color,pDevice);
DrawBone(m_CharaBase,0,13,Color,pDevice);
DrawBone(m_CharaBase,12,14,Color,pDevice);
DrawBone(m_CharaBase,13,15,Color,pDevice);
DrawBone(m_CharaBase,14,8,Color,pDevice);
DrawBone(m_CharaBase,15,9,Color,pDevice);
}
//---------------------------------------------------------------------------//
void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR Color){
int x = ( GetSystemMetrics( 0 ) / 2);
int y = ( GetSystemMetrics( 1 ) / 2);
Circle (x,y,6,true,Color,pDevice);
FillRGB(x-10, y, 7, 1,Color,pDevice);
FillRGB(x+4, y, 7, 1,Color,pDevice);
FillRGB(x, y-10, 1, 7,Color,pDevice);
FillRGB(x, y+4, 1, 7,Color,pDevice);
}
//------------------------------------------------------------------------------//
                              // Time/Date/FPS //
//------------------------------------------------------------------------------//
int	FPScounter=0;
int Fps=0;
CHAR TimeAndDate[MAX_PATH];
time_t TimeValue;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";
char sFPS[20];
char Resolution[MAX_PATH];
float FPSfLastTickCount=0.0f;
float FPSfCurrentTickCount;
//------------------------------------------------------------------------------//
                                  // FPS //
//------------------------------------------------------------------------------//
void FPScheck(char *str, char *format){
FPSfCurrentTickCount = clock() * 0.001f;
FPScounter++;	if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f) {
FPSfLastTickCount = FPSfCurrentTickCount;
sprintf(str,format,FPScounter);
FPScounter = 0;
}}