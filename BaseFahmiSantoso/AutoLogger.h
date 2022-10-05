#include <windows.h>
#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <iostream>
#include <d3dx9math.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>
/*-----------------------------------------------------------------------------------------------------------------------*/
#pragma warning(disable:4244)
#pragma warning(disable:4700)
#pragma warning(disable:4996)
#pragma warning(disable:4305)
#pragma warning(disable:4715)
using namespace std;
ofstream infile;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
bool ChekLogPortal = false;
bool CHekHook=false;
/*-----------------------------------------------------------------------------------------------------------------------*/
#define Result_Address			1
#define Result_PTRByte			2
#define Result_PTR4Byte			3
#define Result_AddressString	4
#define Result_PTRStringByte	5
#define Result_PTRString4Byte	6
/*-----------------------------------------------------------------------------------------------------------------------*/
char *GetDirectoryFile(char *filename);
void __cdecl add_log (const char * fmt, ...);
void thethread();
char dlldir[320];
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[]){ 
unsigned int i = NULL; 
int iLen = strlen( pszMask ) - 1; 
for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ){ 
if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ){ 
if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
} 
else i = NULL; 
}
return NULL; 
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD GetSizeofCode( const char* szModuleName ) { 
HMODULE hModule = GetModuleHandleA( szModuleName ); 
if ( !hModule ) return NULL; 
PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
if( !pDosHeader ) return NULL; 
PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
if( !pNTHeader ) return NULL; 
PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
if( !pOptionalHeader ) return NULL; 
return pOptionalHeader->SizeOfCode; 
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD ModulePB			= (DWORD)GetModuleHandleA("PointBlank.exe");;
DWORD ModuleSizePB      = GetSizeofCode("PointBlank.exe");
DWORD ModuleGF			= (DWORD)GetModuleHandleA("ModuleSizeGF.dll");
DWORD ModuleSizeGF		= GetSizeofCode("ModuleSizeGF.dll");
DWORD ModuleIP			= (DWORD)GetModuleHandleA("i3InputDx.dll");
DWORD ModuleSizeIP		= GetSizeofCode("i3InputDx.dll");
DWORD ModuleSC			= (DWORD)GetModuleHandleA("i3SceneDx.dll");
DWORD ModuleSizeSC		= GetSizeofCode("i3SceneDx.dll");
DWORD ModuleFW			= (DWORD)GetModuleHandle("i3FrameworkDx.dll");
DWORD ModuleSizeFW		= GetSizeofCode("i3FrameworkDx.dll");
DWORD ModuleNX			= (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
DWORD ModuleSizeNX		= GetSizeofCode("NxCharacter.2.8.1.dll");
DWORD ModuleD3D9		= (DWORD)GetModuleHandleA("d3d9.dll");
DWORD ModuleSizeD3D9	= GetSizeofCode("d3d9.dll");
DWORD ModuleDX			= (DWORD)GetModuleHandle("i3BaseDx_Cli.dll");
DWORD ModuleSizeDX		= GetSizeofCode("i3BaseDx_Cli.dll");
/*-----------------------------------------------------------------------------------------------------------------------*/
char *GetDirectoryFile(char *filename){
static char path[320];
strcpy(path, dlldir);
strcat(path, filename);
return path;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
bool CheckWindowsVersion(DWORD dwMajorVersion,DWORD dwMinorVersion,DWORD dwProductType){
OSVERSIONINFOEX VersionInfo;
ZeroMemory(&VersionInfo,sizeof(OSVERSIONINFOEX));
VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
GetVersionEx((OSVERSIONINFO*)&VersionInfo);
if ( VersionInfo.dwMajorVersion == dwMajorVersion ){
if ( VersionInfo.dwMinorVersion == dwMinorVersion ){
if ( VersionInfo.wProductType == dwProductType ){
return ( TRUE );
}}}
return ( FALSE );
}
/*-----------------------------------------------------------------------------------------------------------------------*/
void __cdecl BaseLog (const char *fmt, ...){
if(infile != NULL){
if(!fmt) { return; }
va_list va_alist;
char logbuf[256] = {0};
va_start (va_alist, fmt);
_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
va_end (va_alist);
infile << logbuf << endl;
}}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD FindPattern(DWORD dwdwAdd,DWORD dwLen,DWORD Address){
for(DWORD i=0; i<dwLen; i++)
if (*(PDWORD)(dwdwAdd+i)==Address)
return (DWORD)(dwdwAdd+i);
return 0;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask){
DWORD STR = FindPattern((DWORD)dwdwAdd, (DWORD)dwLen, (PBYTE)bMask,szMask); 
if(STR!=NULL){
DWORD PUSH = FindPattern((DWORD)ModulePB, (DWORD)ModuleSizePB, STR)-1;
if(PUSH!=NULL){
return PUSH;
}}
return 0;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD Func_SmartModuleStart(DWORD A){
DWORD ModuleStart;
if(A==1)
ModuleStart=(DWORD)ModuleNX;
else if(A==2)
ModuleStart=(DWORD)ModuleFW;
else if(A==3)
ModuleStart=(DWORD)ModuleGF;
else if(A==4)
ModuleStart=(DWORD)ModuleIP;
else if(A==5)
ModuleStart=(DWORD)ModuleSC;
else if(A==6)
ModuleStart=(DWORD)ModuleD3D9;
else if(A==7)
ModuleStart=(DWORD)ModuleDX;
else
ModuleStart=ModulePB;
return ModuleStart;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD Func_SmartModuleEnd(DWORD A){
DWORD ModuleEnd;
if(A==1)
ModuleEnd=(DWORD)ModuleSizeNX;
else if(A==2)
ModuleEnd=(DWORD)ModuleSizeFW;
else if(A==3)
ModuleEnd=(DWORD)ModuleSizeGF;
else if(A==4)
ModuleEnd=(DWORD)ModuleSizeIP;
else if(A==5)
ModuleEnd=(DWORD)ModuleSizeSC;
else if(A==6)
ModuleEnd=(DWORD)ModuleSizeD3D9;
else if(A==7)
ModuleEnd=(DWORD)ModuleSizeDX;
else
ModuleEnd=(DWORD)ModuleSizePB;
return ModuleEnd;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD Func_CrazyFindSystem(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete,int Result){
if(FindPattern(dwdwAdd,dwLen,bMask,szMask) != NULL){
DWORD ADR = FindPattern(dwdwAdd,dwLen,bMask,szMask);
if(ADR != NULL){
if(Result==Result_Address){
if((DWORD)(ADR + Offsete) != NULL)
return (DWORD)(ADR + Offsete);
else return 0;
}else
if(Result==Result_PTRByte){
if(*(BYTE*)(ADR + Offsete))
return *(BYTE*)(ADR + Offsete);
else return 0;
}else
if(Result==Result_PTR4Byte){
if(*(DWORD*)(ADR + Offsete))
return *(DWORD*)(ADR + Offsete);
else return 0;
}else
if(Result==Result_AddressString){
if(FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR)){
DWORD PUSH = FindPattern((DWORD)dwdwAdd				,(DWORD)dwLen		,ADR)-1;
if(PUSH!=NULL)
if((DWORD)(PUSH + Offsete))
return (DWORD)(PUSH + Offsete);
else return 0;
else return 0;
}
else return 0;
}else
if(Result==Result_PTRStringByte){
if(FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR)){
DWORD PUSH = FindPattern((DWORD)dwdwAdd				,(DWORD)dwLen		,ADR)-1;
if(PUSH!=NULL)
if(*(BYTE*)(PUSH + Offsete))
return *(BYTE*)(PUSH + Offsete);
else return 0;
else return 0;
}
else return 0;
}
else
if(Result==Result_PTRString4Byte){
if(FindPattern((DWORD)ModulePB						,(DWORD)ModuleSizePB		,ADR)){
DWORD PUSH = FindPattern((DWORD)ModulePB		    ,(DWORD)ModuleSizePB		,ADR)-1;
if(PUSH!=NULL)
if(*(DWORD*)(PUSH + Offsete))
return *(DWORD*)(PUSH + Offsete);
else return 0;
else return 0;
}
else return 0;
}
else return 0;
}
else return 0;
}
else return 0;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD Func_SmartPattern(DWORD A,DWORD B,DWORD C,BYTE *D,char *E){
DWORD Smart=0;
DWORD ModuleStart	=Func_SmartModuleStart(A);
DWORD ModuleEnd		=Func_SmartModuleEnd(A);
if(B == Result_Address)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
else 
if(C == Result_PTRByte)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
else 
if(C == Result_PTR4Byte)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
else 
if(C == Result_AddressString)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
else 
if(C == Result_PTRStringByte)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
else 
if(C == Result_PTRString4Byte)
Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
if(Smart!=NULL)
return Smart;
}
#define Pattern_AmmoStatus "\x52\xE8\x00\x00\x00\x00\x83\xC4\x08\x8B\x45\xFC\x8B\x4D\x08\x89\x88\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x51\x89\x4D"						
#define Mask_AmmoStatus "xx????xxxxxxxxxxx??xxxxxxxxxxxxxx"
#define Pattern_Suicide "\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xAC\x51\xD9\xE8\xD9\x1C\x24\x51\xD9\xEE"
#define Mask_Suicide "xxxxx?xxxxxxxxxxxx"
#define Pattern_SKILL "\x83\xC4\x14\x8B\x4D\xF4\x8B\x55\xF0\x89\x84\x8A\x00\x00\x00\x00"
#define Mask_SKILL "xxxxxxxxxxxx????"
#define Pattern_i3Damage "\xD9\x45\xF0\x5E\x8B\xE5\x5D\xC2\x04"
#define Mask_i3Damage "xxxxxxxxx"
#define Pattern_NoRecoil "\xD9\x45\xF8\x8B\xE5\x5D\xC3\x55\x8B\xEC\x83\xEC\x00\x89\x4D\x00\xF3\x0F\x10\x05\x00\x00\x00\x00\xF3\x0F\x11\x45\x00\x8B\x45\x00\x8B\x88\x00\x00\x00\x00\x8B\x55\x00\x8B\x82\x00\x00\x00\x00\x8B\x11\x8B\xC8\x8B\x82\x00\x00\x00\x00\xFF\xD0\xD9"
#define Mask_NoRecoil "xxxxxxxxxxxx?xx?xxxx????xxxx?xx?xx????xx?xx????xxxxxx????xxx"
/*-----------------------------------------------------------------------------------------------------------------------*/
#define Pattern_Range			"\xD9\x45\xFC\x8B\xE5\x5D\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xCC\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xF8\x8B\x45\xF8\x8B\x88\x00\x00\x00\x00\x8B\x55\xF8\x8B\x82\x00\x00\x00\x00\x8B\x11\x8B\xC8"
#define Mask_Range				"xxxxxxx???????????xxxxxx?xxxxxxxx????xxxxx????xxxx"
#define Pattern_RID1			"\x44\x61\x6D\x61\x67\x65\x00\x00\x00\x00\x00\x00"
#define Mask_RID1				"xxxxxx??????"
#define Pattern_RID2			"\x00\x00\x80\x3F"
#define Mask_RID2				"??xx"
#define Pattern_Plant			"\x55\x8B\xEC\x83\xEC\x0C\x89\x4D\xF4\x8B\x4D\xF4\xE8\xFF\xFF\xE1"
#define Mask_Plant				"xxxxxxxxxxxxx??x"
#define Pattern_Defuse			"\x55\x8B\xEC\x83\xEC\x10\x89\x4D\xF0\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x89\x45\xF8\xC7\x45\x00\x00\x00\x00\x00\xC7\x45\x00\x00\x00\x00\x00\x8B\x45\xF8\x50\x8B\x4D\xF0\xE8\x00\x00\x00\x00\x85\xC0\x74\x18\x83\x7D\x08\x00\x75\x12\x8B\x4D\xF0\xF3\x0F\x10\x05\x00\x00\x00\x00\xF3\x0F\x11\x41\x00\xEB\x0E"
#define Mask_Defuse				"xxxxxxxxxxx????x????xxxxx?????xx?????xxxxxxxx????xxxxxxxxxxxxxxxxx????xxxx?xx"
#define Pattern_Stage			"\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x4D\xFC\x8B\x40\x04\x2B\x01\xC1\xF8\x02\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x08\x8B\x55\x08\x8D\x04\x91\x8B\xE5\x5D\xC2\x04\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x83\xEC\x08\x89\x4D\xF8\x8B\x45\xF8\x89\x45\xFC\x8B\x4D\xF8\xE8\x00\x00\x00\x00\x8B\x4D\xFC\x51\x8B\x0D\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x4D\xFC\xFF\x15\x00\x00\x00\x00\x8B\x45\xFC\xC7\x00\x00\x00\x00\x00\x8B\x4D\xFC\xC7\x41\x00\x00\x00\x00\x00\x8B\x45\xFC\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC"
#define Maks_Stage				"xxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx????xx????xxxxxxxxxxxxxxxxxxxxx????xxxxx????xxxxx?????xxxxxxxxxxxxx"

//----------------------------------------------------------------------------------------------------------//
                                   // Declaration Modul Game //
//----------------------------------------------------------------------------------------------------------//
DWORD dwi3GfxDx		 = (DWORD)GetModuleHandleA("i3GfxDx.dll");
HMODULE hGfxDx		 = LoadLibrary("i3GfxDx.dll");
HMODULE ModuleGFX	 = LoadLibrary("i3GfxDx.dll");
DWORD i3GfxDx        = GetSizeofCode("i3GfxDx.dll");
DWORD dwPBExe        = (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD i3PBExe        = GetSizeofCode("PointBlank.exe");
DWORD dwFrameW		 = (DWORD)GetModuleHandle("i3FrameworkDx.dll");
DWORD FrameW		 = GetSizeofCode("i3FrameworkDx.dll");
DWORD dwNxChara      = (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
DWORD NxCharakter2   = (DWORD)LoadLibraryA("NxCharacter.2.8.1.dll");
DWORD i3NxChara      = GetSizeofCode("NxCharacter.2.8.1.dll");
//----------------------------------------------------------------------------------------------------------//
                                       // Declaration ArrayOFByte //
//----------------------------------------------------------------------------------------------------------//
DWORD dwGfxDx		 = (DWORD)GetProcAddress(ModuleGFX,"?g_pRenderContext@@3PAVi3RenderContext@@A");
DWORD HookBaseRender = (DWORD)GetProcAddress(hGfxDx,"?g_pRenderContext@@3PAVi3RenderContext@@A") - dwi3GfxDx;
DWORD dwHook	     = FindPattern(dwi3GfxDx,i3GfxDx,(PBYTE)"\x8B\x80\x00\x00\x00\x00\x8B\x08\x8D\x54\x24\x00\x52\x50\x8B\x41\x00\xFF\xD0","xx????xxxxx?xxxx?xx");
DWORD dwBaseAddress  = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x89\x45\x00\x8B\x4D\x00\x8B\x11","xx????x????xx?xx?xx");
DWORD DwBullet	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x50\x8D\x8D\x14\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x8B\x4D\xEC\xE8\x00\x00\x00\x00\x0F\xB6\xC8\x85\xC9","xxxxxxxx?????xxxx????xxxxx");
DWORD dwSkill		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x0F\xB6\x94\x01\x00\x00\x00\x00","xxxx????");
DWORD dwHelmed		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8D\x84\x10\x00\x00\x00\x00\xEB\x00\xEB\x00\x8B\x4D","xxx????x?x?xx");
DWORD dwKill	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8D\x84\x81\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x00\x00\x55\x8B\xEC\x83\xEC","xxx????xxxx??xxxxx");
DWORD dwPing		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8A\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x00\x00\xCC\x55\x8B\xEC\x51\x89\x4D\x00\x8B\x4D\x00","xx????xxxx??xxxxxxx?xx?");
DWORD dwScore		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8D\x84\x81\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x00\x00\x55\x8B\xEC\x51\x89\x4D\x00","xxx????xxxx??xxxxxx?");
DWORD dwQuick	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x89\x81\x00\x00\x00\x00\x8B\x55\x00\x83\xBA\x00\x00\x00\x00\x00\x75\x00\x6A\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x6A\x00","xx????xx?xx?????x?x?x????x????x?");
DWORD dwUnyuk	     = FindPattern(dwPBExe,0xA00000,(PBYTE)"\xBE\x00\x00\x00\x00\x65\x43\x68","x????xxx");
DWORD dwWTF			 = FindPattern(dwNxChara,i3NxChara,(PBYTE)"\x5E\x00\xD9\x46\x00\xD9\x44\x24\x00\xD9\xC0\xDE\xC2\xD9\xC9\xD9\x5E\x00\xD9\x46\x00\xD8\xC3\xD9\x5E\x00\xD9\x46\x00\xD8\xC2\xD9\x5E\x00\xD9\x46\x00","x?xx?xxx?xxxxxxxx?xx?xxxx?xx?xxxx?xx?");
DWORD dwUser		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\xC6\x81\x00\x00\x00\x00\x00\x8B\x55\xFC\x69\xD2\x00\x00\x00\x00\x8B\x45\xF8","xx???xxxxxxx????xxx");
DWORD dwCamPosition	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x61\x74\x29\x00\x6D\x5F\x70\x41\x6E\x69\x6D\x5B\x6D\x5F\x65\x52","xxx?xxxxxxxxxxxx");
DWORD DwDoLine	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xF4\xC6\x45\xFF\x00\x83\x7D\x00\x00\x75\x2A\x6A\x00","xxxxx?xxxxxx?xx??xxx?");
DWORD DwCamPos		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x53\x8B\xDC\x83\xEC\x00\x83\xE4\x00\x83\xC4\x00\x55\x8B\x6B\x00\x89\x6C\x24\x00\x8B\xEC\x81\xEC\x00\x00\x00\x00\x89\x4D\xFC\x83\x3D\x00\x00\x00\x00\x00\x75\x00","xxxxx?xx?xx?xxx?xxx?xxxx????xxxxx?????x?");
DWORD DwEventFire	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\x56\x89\x4D\xD8\x83\x7D\x00\x00\x75\x00\x6A\x00","xxxxx?xxxxxx??x?x?");
DWORD dwTeam		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x88\x00\x00\x00\x00\x51\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x8B\xE5\x5D\xC3","xxxxxxxxxxxx????xxx????x????xxx????xxxx");
DWORD dwPlayer	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x83\xC4\x14\x8B\x4D\xF4\x8B\x55\xF0\x89\x84\x8A\x00\x00\x00\x00","xxxxxxxxxxxx????");
DWORD dwName		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\x55\x08\x6B\xD2\x00\x8B\x45\xFC\x8D\x84\x10","xxxxx?xxxxxx");
DWORD DwGetButton    = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\x4D\xF0\xC7\x81\x00\x00\x00\x00\x00\x00\x00\x00\x8B\x4D\xF8\xFF\x15\x00\x00\x00\x00\x83\xE0\x01","xxxxx????????xxxxx????xxx");
DWORD dwInvincible	 = FindPattern(dwPBExe,0xA00000,(PBYTE)"\x6F\x12\x83\x3C","xxxx");
DWORD Magnet		 = FindPattern(dwFrameW,FrameW,(PBYTE)"\xC0\x30\xC3\x00","xxx?");
DWORD DwSetNetChara	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\xFF\xD0\xEB\x00\x8B\xE5\x5D\xC2\x04\x00\xCC\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xCC\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xD0\x83\x7D\x00\x00\x74\x00","xxx?xxxxx?x??????????xxxxxx?xxxxx??x?");
DWORD dwPrimary		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\x88\x00\x00\x00\x00\x51\xFF\x15\x00\x00\x00\x00\x83\xC4\x00\x8B\x55\x00\xC7\x82\x00\x00\x00\x00\x00\x00\x00\x00\x5E\x8B\xE5\x5D\xC3","xx????xxx????xx?xx?xx????????xxxxx");
DWORD dwWallShot	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x75\x00\xC7\x45\x00\x00\x00\x00\x00\xC7\x45\x00\x00\x00\x00\x00\x8D\x4D\x00\xFF\x15\x00\x00\x00\x00\x8B\x45\x00","x?xx?????xx?????xx?xx????xx?");
DWORD FakeReplac	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x83\xEC\x30\x89\x4D\xD0\x83\x7D\x08\x00\x74","xxxxxxxxxxxx?x");
DWORD DwPTRIdle		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\xE5\x5D\xC2\x04\x00\xCC\x00\x00\x00\x00\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80","xxxxx?x????xxxxxxxxxxxxx");
DWORD DwPTRpTarget2	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x83\xF8\xFF\x0F\x00\x00\x00\x00\x00\x8B\x55\xA0\x8B\x8A","xxxx?????xxxxx");
DWORD DwPTRRecoil	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8B\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC3\xCC\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xCC\x00\x00\x00\x00\x00\x00\x00\x8B\x45\xFC\x05\x00\x00\x00\x00\x8B\xE5\x5D\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x05\x00\x00\x00\x00\x8B\xE5\x5D\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xCC\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80","xx????xxxxx??????????x???????xxxx????xxxx????????????xxxxxxxxxxxx????xxxx????????????xxxxxxxxxxxxx");
DWORD DwSetEvent	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\x00\x56\x50\x8D\x45","x????x????xxxx?xxxx");
DWORD DwNames		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x8D\x84\x10\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x88","xxx????xxxxx?xxxxxxxxxxxx");
DWORD DwPTRCaclAmmo  = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x6A\x00\x8B\x4D\xE8\xE8\x00\x00\x00\x00\x8B\x55\xE8\xC7\x82","x?xxxx????xxxxx");
DWORD DwDeltaX	     = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xF8\x51\xD9\xEE\xD9\x1C\x24\x8B\x45\xF8\x8B\x88\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x51\xD9\x1C\x24","xxxxx?xxxxxxxxxxxxxx????xx????xxxx");
DWORD DwDeltaY		 = FindPattern(dwPBExe,i3PBExe,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\x89\x4D\xF8\x51\xD9\xEE\xD9\x1C\x24\x8B\x45\xF8\x8B\x88\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x51\xD9\x1C\x24","xxxxx?xxxxxxxxxxxxxx????xx????xxxx");
DWORD dwSuicide	     = FindPattern(ModulePB,ModuleSizePB,(PBYTE)Pattern_Suicide,Mask_Suicide);
DWORD SKILL	         = FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_SKILL,Mask_SKILL);
DWORD i3Damage		 = FindPattern((DWORD)ModulePB,(DWORD)ModuleSizePB,(PBYTE)Pattern_i3Damage,Mask_i3Damage);
DWORD i3NoRecoil1	 = FindPattern((DWORD)ModulePB,(DWORD)ModuleSizePB,(PBYTE)Pattern_NoRecoil,Mask_NoRecoil);
DWORD i3NoRecoil2	 = FindPattern((DWORD)i3NoRecoil1+1,(DWORD)ModuleSizePB,(PBYTE)Pattern_NoRecoil,Mask_NoRecoil);
//DWORD ci3AmmoStatus  = FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_AmmoStatus,Mask_AmmoStatus);
//DWORD gi3AmmoStatus	 = FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_AmmoStatus,Mask_AmmoStatus);
//DWORD DwAmmoStatus1	 = FindPattern(gi3AmmoStatus+1,i3PBExe,(PBYTE)Pattern_AmmoStatus,Mask_AmmoStatus);
//DWORD DwAmmoStatus2	 = FindPattern(DwAmmoStatus1+1,i3PBExe,(PBYTE)Pattern_AmmoStatus,Mask_AmmoStatus);
//DWORD DwAmmoStatus3	 = FindPattern(DwAmmoStatus2+1,i3PBExe,(PBYTE)Pattern_AmmoStatus,Mask_AmmoStatus);
DWORD i3RangeWeapon			= FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_Range,Mask_Range);
DWORD dwALLplayer			= FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_Plant,Mask_Plant);
DWORD dwBLUE				= FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_Defuse,Pattern_Defuse);
DWORD dwRED					= FindPattern(dwPBExe,i3PBExe,(PBYTE)Pattern_Stage,Maks_Stage);
/*-----------------------------------------------------------------------------------------------------------------------*/
DWORD ResultHook, ResultBaseAddress, ResultKill, ResultPing, ResultScore, ResultBullet, ResultRafid, ResultRafid2, ResultSKILL2, ResultRespawn, ResultMajor, ResultBugWeapon, ResultSuicide, ResultPlayerSpeed, ResultUserDeath, ResultSmoke, OFSBullet, ResultBomb, ResultHeadGear;
DWORD ResultBaseHealth, ResultBaseHealth2, ResultBasePlayer, ResultBasePlayer2, ResultBaseAmmo, ResultBaseAmmo2, ResultBaseMove, ResultBaseMove2, ResultBaseWinMode, ResultBaseWinMode2, ResultBaseIdle, ResultBaseIdle2, ResultPTRWeapon, ResultNorecoil, ResultPTRChara, ResultPTRQC;
DWORD ResultFireSpeed, RETNeoFireSpeed, ResultPTRFShot, ResultPTRRapid, ResultPTRFall, ResultPTRRepeat, ResultPTRJumper, ResultPTRAmmo, ResultMagnet;
DWORD ResultDoLine, ResultCamPos, ResultEventFire, ResultSetNetChara, ResultTEAM, ResultRespawn2, ResultPlayer, ResultPRIMARYSIZE,  ResultSECONDARYSIZE, ResultMALESIZE, ResultBOMBSIZE, ResultSMOKESIZE, NeoPTRProtectA, NeoPTRProtectB, NeoPTRProtectC, NeoPTRAmmoB, NeoPTRAmmoD;
DWORD OFSSkill, OFSHelmed, OFSReplace, WTF, WTW, ResultName, ResultHEALTH, ResultPLAYER1, ResultPLAYER, ResultBONE, ResultSKILL, ResultPlayer1, ResultGetButton, ResultInvincible, ResultPrimary, ResultSkillGM, ResultSecondary, ResultMelee, ResultWallShot, ResultBaret, ResultQuick;
DWORD PTR_Idle, ResultSetEvent, PTR_Idle2, ResultPTRIdle, ResultPTRpTarget, ResultPTRpTarget2, ResultPTRRecoil, ResultNAMES, ResultPTRCaclAmmo, ResultDeltaX, ResultDeltaY, ResultPTRCaclKnife, ResultHEALTHSIZE, ResultRANKSIZE, ResultNAMESIZE, NeoPTRAmmoC, NeoPTRProtectD;
DWORD NeoAmmoL, BackAmmoL, NeoAmmoR, BackAmmoR, NeoAmmoX, BackAmmoX, ResultPTRAmmoA, ResultPTRAmmoB, ResultPTRAmmoC, ResultGetAmmo, NeoPTRAmmoA, ResultPTRAddCharaHealth, NeoPTRProtectNew2, NeoPTRProtectNew1, RETNeoDamage, NeoDamage, NeoNoRecoil1, NeoNoRecoil2;
DWORD ResultHealth;
DWORD ResultALLplayer, ResultBLUE, ResultRED,NeoRangeWeapon,RETNeoRangeWeapon;
/*-----------------------------------------------------------------------------------------------------------------------*/
void SearchLogger(){
if(ChekLogPortal==false){
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwBaseAddress+0x2), &ResultBaseAddress, sizeof(ResultBaseAddress), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwBullet+0x9), &ResultBullet, sizeof(ResultBullet), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwSkill+0x4), &OFSSkill, sizeof(OFSSkill), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (SKILL+0x3), &ResultSKILL, sizeof(ResultSKILL), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPlayer+0xC)	,&ResultPlayer1,sizeof(ResultPlayer1), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwKill+0x3), &ResultKill, sizeof(ResultKill), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPing+0x2), &ResultPing, sizeof(ResultPing), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwScore+0x3), &ResultScore, sizeof(ResultScore), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwQuick+0x2), &ResultQuick, sizeof(ResultQuick), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwHook+0x2), &ResultHook, sizeof(ResultHook), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwUser+0x2), &ResultUserDeath, sizeof(ResultUserDeath), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwTeam+0xC), &ResultTEAM, sizeof(ResultTEAM), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwName+0xC), &ResultName, sizeof(ResultName), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwGetButton+0x12), &ResultGetButton, sizeof(ResultGetButton), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPrimary + 0x2), &OFSReplace, sizeof(OFSReplace), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRIdle+0x18), &ResultPTRIdle, sizeof(ResultPTRIdle), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRpTarget2+0xE), &ResultPTRpTarget2, sizeof(ResultPTRpTarget2), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRRecoil+0x2), &ResultPTRRecoil, sizeof(ResultPTRRecoil), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwNames+0x3), &ResultNAMES, sizeof(ResultNAMES), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRCaclAmmo+0xF), &ResultPTRCaclAmmo, sizeof(ResultPTRCaclAmmo), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwDeltaX+0x1A), &ResultDeltaX, sizeof(ResultDeltaX), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwDeltaY+0x3F), &ResultDeltaY, sizeof(ResultDeltaY), NULL);
//ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAmmoStatus1+0x11), &ResultPTRAmmoA, sizeof(ResultPTRAmmoA), NULL);
//ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAmmoStatus2+0x11), &ResultPTRAmmoB, sizeof(ResultPTRAmmoB), NULL);
//ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAmmoStatus3+0x11), &ResultPTRAmmoC, sizeof(ResultPTRAmmoC), NULL);
//----------------------------------------------------------------------------------------------------------//
                                       // Declaration Result //
//----------------------------------------------------------------------------------------------------------//
ResultBasePlayer	  = ResultBaseAddress - dwPBExe;
ResultBasePlayer2	  = ResultBaseAddress;
ResultBaseHealth	  = ResultBaseAddress - dwPBExe - 0x34;
ResultBaseHealth2	  = ResultBaseAddress - 0x34;
ResultBaseAmmo		  = ResultBaseAddress - dwPBExe - 0x38;
ResultBaseAmmo2		  = ResultBaseAddress - 0x38;
ResultBaseMove		  = ResultBasePlayer - 0x28;
ResultBaseMove2		  = ResultBasePlayer2 - 0x28;
ResultBaseWinMode	  = ResultBasePlayer - 0x794;
ResultBaseWinMode2	  = ResultBasePlayer2 - 0x794;
ResultBaseIdle		  = ResultBasePlayer - 0x8;
ResultBaseIdle2		  = ResultBasePlayer2 - 0x8;
ResultUserDeath		  = ResultUserDeath;
ResultPTRAmmo		  = ResultPTRRecoil - 0x4;
ResultPTRWeapon		  = ResultPTRRecoil - 0x14;
ResultNorecoil		  = ResultPTRRecoil - 0x18;
ResultPTRJumper		  = ResultPTRRecoil - 0x18 + 0x4C;
ResultPTRChara		  = ResultPTRRecoil - 0x18 + 0x1C;
ResultPTRQC			  = ResultPTRRecoil - 0x18;
ResultPTRFShot		  = ResultPTRRecoil - 0x54;
ResultPTRRapid	      = ResultPTRCaclAmmo - 0x6B4;
ResultPTRFall	      = ResultPTRRecoil - 0x48;
ResultPTRRepeat	      = ResultPTRFall + 0x3;
ResultRespawn2		  = ResultTEAM - 0x19B0;
ResultSKILL2		  = OFSSkill;
ResultSKILL			  = ResultSKILL2 - 0x1;
PTR_Idle			  = ResultPTRIdle - 0x1;
PTR_Idle2			  = ResultPTRIdle + 0x4;
ResultRespawn	      = ResultSKILL2 + 0x1;
ResultPrimary		  = OFSReplace + 0x5A0;
ResultSkillGM		  = ResultPLAYER + 0xAC;
ResultRafid			  = ResultNorecoil - 0x7C;
ResultRafid2		  = ResultNorecoil - 0x54;
ResultPTRpTarget	  = ResultPTRRecoil + 0x8;
ResultMelee			  = ResultPrimary + 0x8;
ResultSecondary		  = ResultPrimary + 0x4;
ResultBomb	          = ResultPrimary + 0xC;
ResultSmoke		      = ResultPrimary + 0x10;
ResultHeadGear	      = ResultPrimary - 0x12C;
ResultBaret			  = ResultPrimary - 0x128;
//NeoAmmoL			  = DwAmmoStatus1;
//BackAmmoL			  = DwAmmoStatus1 + 0x1B;
//NeoAmmoR			  = DwAmmoStatus2;
//BackAmmoR			  = DwAmmoStatus2 + 0x1B;
//NeoAmmoX			  = DwAmmoStatus3;
//BackAmmoX			  = DwAmmoStatus3 + 0x1B;
NeoPTRAmmoA			  = ResultPTRAmmoA;
NeoPTRAmmoB		   	  = ResultPTRAmmoB;
NeoPTRAmmoC			  = ResultPTRAmmoC - 0x4;
NeoPTRAmmoD			  = ResultPTRAmmoC;
NeoPTRProtectA		  = 0xA368;
NeoPTRProtectB		  = 0xA370;
NeoPTRProtectC		  = 0xA384;
NeoPTRProtectD		  = 0xA3EC;
NeoPTRProtectNew1     = 0xA358;
NeoPTRProtectNew2	  = 0xA36C;
NeoNoRecoil1		  = i3NoRecoil1;
NeoNoRecoil2	      = i3NoRecoil2;
ResultSetEvent	      = DwSetEvent - 0x16;
NeoDamage		      = i3Damage;
RETNeoDamage		  = i3Damage + 0x6;
ResultInvincible	  = dwInvincible - dwPBExe;
ResultMagnet          = Magnet - dwFrameW;
ResultWallShot		  = dwWallShot - dwPBExe;
ResultSuicide		  = dwSuicide - dwPBExe;
ResultSetNetChara	  = FakeReplac;
ResultPTRCaclKnife	  = ResultPTRCaclAmmo - 0xC;
ResultHEALTH		  = ResultPTRAddCharaHealth;
ResultPLAYER		  = ResultPlayer1;
ResultPLAYER1         = ResultPlayer1;
ResultBONE			  = ResultUserDeath;
ResultBugWeapon		  = dwUnyuk - dwPBExe;
ResultDoLine		  = DwDoLine;
ResultCamPos		  = DwCamPos;
ResultEventFire		  = DwEventFire;
ResultHEALTHSIZE      = 0x24;
ResultRANKSIZE        = 0x2B;
ResultNAMESIZE        = 0x21;
ResultPRIMARYSIZE	  = 0x1C;
ResultSECONDARYSIZE	  = 0x20;
ResultMALESIZE		  = 0x24;
ResultBOMBSIZE		  = 0x28;
ResultSMOKESIZE		  = 0x2C;
ResultHealth		  = 0x264;
WTF					  = dwWTF - dwNxChara - 0x1000;
HookBaseRender		  = HookBaseRender;
ResultHook			  = ResultHook;
NeoRangeWeapon		  = i3RangeWeapon;
RETNeoRangeWeapon	  = i3RangeWeapon+0x5;
ResultALLplayer		  = dwALLplayer;
ResultRED			  = dwRED;
ResultBLUE			  = dwBLUE;
ChekLogPortal=true;
Beep(500, 500);
}}
/*-----------------------------------------------------------------------------------------------------------------------*/
#define PTR_Player		    0x27B24
#define PlayerBody			0x548 
#define CoordinateX			0x11C
#define CoordinateZ			0x120
#define CoordinateY			0x124
#define CoordinateX2		0x110
#define CoordinateZ2		0x114
#define CoordinateY2		0x118
//------------------------------------------//