/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include <windows.h>
#include "Stdafx.h"
#include "File.h"
#include "Menu.h"
#include "Texture.h"
/*-----------------------------------------------------------------------------------------------------------------------*/
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;
/*-----------------------------------------------------------------------------------------------------------------------*/
void D3DFahmi(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1)
	{
		D3DXCreateFontA(pDevice, 13, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont);
		DrawFont = 0;
	}
	if(Drawing == 0)
	{
		if(Mmax==0) 
		TampilanFahmi(pDevice);
		ShowFahmi(mx,my,pDevice);
		MenuNavFahmi();
	}
	if(!g_pFont)	D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &g_pFont);//15
	if(!pLine)		D3DXCreateLine( pDevice, &pLine );
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	while(!npDevice){npDevice = pDevice;}
	D3DFahmi(pDevice);
	pDevice->GetViewport(&g_ViewPort);

	if(*(PBYTE)ResultBaseAmmo2 > NULL)
	{
	}

	if(!GetBattleState())
	{
	}

	if(CROSS){
		D3DVIEWPORT9 viewP;
		pDevice->GetViewport( &viewP );
		DWORD ScreenCenterX = viewP.Width / 2; 
		DWORD ScreenCenterY = viewP.Height / 2; 
		D3DRECT rec1 = {ScreenCenterX-35, ScreenCenterY, ScreenCenterX+ 35, ScreenCenterY+1};
		D3DRECT rec2 =	{ScreenCenterX, ScreenCenterY-35, ScreenCenterX+ 1,ScreenCenterY+35};  
	if(CROSS==1){	
		D3DRECT rec10 = {ScreenCenterX-6, ScreenCenterY, ScreenCenterX+ 6, ScreenCenterY+1};
		D3DRECT rec11 = {ScreenCenterX, ScreenCenterY-6, ScreenCenterX+ 1,ScreenCenterY+6};  
		pDevice->Clear( 1, &rec10, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 0.0, 1.0), 0,  0 );// green
		pDevice->Clear( 1, &rec11, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 0.0, 1.0), 0,  0 );
		D3DRECT rec12 = {ScreenCenterX-4, ScreenCenterY, ScreenCenterX+ 4, ScreenCenterY+1};
		D3DRECT rec13 = {ScreenCenterX, ScreenCenterY-4, ScreenCenterX+ 1,ScreenCenterY+4};  
		pDevice->Clear( 1, &rec12, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 1.0, 0.0, 1.0), 0,  0 );// yellow
		pDevice->Clear( 1, &rec13, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 1.0, 0.0, 1.0), 0,  0 );
		D3DRECT rec16 = {ScreenCenterX-1, ScreenCenterY, ScreenCenterX+ 1, ScreenCenterY+1};
		D3DRECT rec17 = {ScreenCenterX, ScreenCenterY-1, ScreenCenterX+ 1,ScreenCenterY+1};  
		pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
		pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
	}
	if(CROSS==2){	
		D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
		D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
		pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
		pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
	}}
	if(CROSS==3){
		Crosshair(pDevice, GREEN);
	}

return oEndScene(pDevice);
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK){Stream_Data->Release();}

	if(Wallhack==1){   
	if(allp){            
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
	}}

	if(GetBattleState()){
	if(DontSmoke==1){
	if ((NumVertices == 192) || (NumVertices == 256)){
	return D3D_OK;
	return 0;
	}}}

	if(GetBattleState()){
	if(DontSmoke==1){
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	}}

return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
//------------------------------------------------------------------------------//
                              // Reset Font //
//------------------------------------------------------------------------------//
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters){
if( g_pFont )
g_pFont->OnLostDevice();
if( pFont )
pFont->OnLostDevice();
if( pLine )
pLine->OnLostDevice();
if(oReset == D3D_OK) {
if( g_pFont )
g_pFont->OnResetDevice();
if( pFont )
pFont->OnResetDevice();
if( pLine )
pLine->OnResetDevice();
}
return oReset(pDevice, pPresentationParameters);
}
//------------------------------------------------------------------------------//
                            // Deklarasi Hook Engine //
//------------------------------------------------------------------------------//
#define HOOK(func,addy)	 CreateDetour((DWORD)func,(DWORD)addy,Detour_Type_0xE9, 5) 
DWORD EndRenderBCKx;
__declspec (naked) void HooMeUp(void){
__asm { 
mov eax,[ecx+0x04]
cmp eax,[ecx+0x08]
je Exit
mov [ecx+0x08],eax
jmp EndRenderBCKx
Exit:
mov [oEndScene],eax
mov eax,[hkEndScene]
ret
jmp EndRenderBCKx
}}
//------------------------------------------------------------------------------//
__declspec(naked)void HookES(){
_asm{
push eax
pop eax
jmp hkEndScene
}}
__declspec(naked)void HookDIP(){
_asm{
push eax
pop eax
jmp hkDrawIndexedPrimitive
}}
__declspec(naked)void HookRES(){
_asm{
push eax
pop eax
jmp hkReset
}}
//------------------------------------------------------------------------------//
DWORD WINAPI HookFahmi(){
if(ModuleGFX > 0){
DWORD tmp1 = dwGfxDx;
DWORD tmp2 = 0;
Sleep(1);
while(!pGDevice){
if(IsBadReadPtr((PDWORD)tmp1,4)==NULL)
tmp2 = *(PDWORD)((DWORD)(tmp1))+ResultHook;
if(IsBadReadPtr((PDWORD)tmp2,4)==NULL){
DWORD OldProtect;
VirtualAlloc((void*)tmp2, 4, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
VirtualProtectEx(GetCurrentProcess(),(void*)tmp2, 4, PAGE_READWRITE, &OldProtect);
memcpy(&pGDevice, (void *)tmp2, 4);
VirtualProtectEx(GetCurrentProcess(),(void*)tmp2, 4, OldProtect, &OldProtect );
}}
DWORD *g_pDevice = (DWORD*)pGDevice;
g_pDevice = (DWORD*)g_pDevice[0];
while(!npDevice)npDevice = (LPDIRECT3DDEVICE9)(DWORD*)g_pDevice;
*(PDWORD)&oEndScene	= g_pDevice[42];
*(PDWORD)&oDrawIndexedPrimitive	= g_pDevice[82];
*(PDWORD)&oReset	= g_pDevice[16];
HookedFahmi((PDWORD)(g_pDevice[1] - 5), (PDWORD)(g_pDevice[4] - 5));
HookedFahmi((PDWORD)(g_pDevice[2] - 5), (PDWORD)(g_pDevice[5] - 5));
HookedFahmi((PDWORD)(g_pDevice[3] - 5), (PDWORD)(g_pDevice[6] - 5));
HookedFahmi((PDWORD)(g_pDevice[4] - 5), (PDWORD)HookES);
HookedFahmi((PDWORD)(g_pDevice[5] - 5), (PDWORD)HookDIP);
HookedFahmi((PDWORD)(g_pDevice[6] - 5), (PDWORD)HookRES);
while(1){
g_pDevice[42] = (DWORD)g_pDevice[1] - 5;
g_pDevice[82] = (DWORD)g_pDevice[2] - 5;
g_pDevice[16] = (DWORD)g_pDevice[3] - 5;
Sleep(500); 
}}
return 0; 
}
/*-----------------------------------------------------------------------------------------------------------------------*/
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved){
if(dwReason == DLL_PROCESS_ATTACH){
DisableThreadLibraryCalls(hModule);
CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HookFahmi, NULL, NULL, NULL);
Beep(1000, 100);
}return TRUE;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/