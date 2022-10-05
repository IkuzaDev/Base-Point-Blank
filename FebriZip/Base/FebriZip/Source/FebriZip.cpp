#include "FebriZip Main.h"
#include "FebriZip Class.h"
#include "FebriZip.h"
#include <math.h>
#include "Connect HDSN.h"
#include "FebriZip Connect.h"
#include "FebriZip Bone.h"
#include "Include Dubeta.h"
#include "XPORT.h"

#include "FebriZip D3D.h"
#include "Text.h"
typedef HRESULT(WINAPI* oPresent)(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
typedef HRESULT(WINAPI* oReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(WINAPI* oQuery)(LPDIRECT3DDEVICE9 pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);
typedef HRESULT(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oQuery pQuery;
oReset pReset;
BOOL Create;

inline void ReleaseHook()
{
	LPDIRECT3DDEVICE9 pD3DDevice = i3RenderContext::Singleton()->pDevice;
	if (pFont)pFont->OnLostDevice();
	if(i_pFont)i_pFont->OnLostDevice();
	if(g_pFont)g_pFont->OnLostDevice();
	if (fName)pFont->OnLostDevice();
	if (pLine)pLine->OnLostDevice();
	if (pFonts)pFonts->OnLostDevice();
	if (pReset == D3D_OK)
	{
		if (pFont)pFont->OnResetDevice();
		if (fName)pFont->OnResetDevice();
		if (pLine)pLine->OnResetDevice();
		if (pFonts)pFonts->OnResetDevice();
		if (i_pFont)i_pFont->OnResetDevice();
		if(g_pFont)g_pFont->OnResetDevice();
	}
	if (!Create)
	{
		D3DXCreateFont(pD3DDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, "Tahoma", &pFont);
		D3DXCreateFont(pD3DDevice, 15, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, "Franklin Ghotic", &pFonts);
		D3DXCreateLine(pD3DDevice, &pLine);
		Create = TRUE;
	}
}
bool bRenderText = true;
LPD3DXFONT fSmall	= NULL;
LPD3DXFONT Title    = NULL;



LPD3DXFONT fTime	= NULL;
LPDIRECT3DDEVICE9 pDevice;
HRESULT APIENTRY i3SceneCreatess() {
	__try {
		pDevice = i3RenderContext::Singleton()->pDevice;
		pDevice->GetViewport(&g_ViewPort);
		if (pDevice && pDevice->TestCooperativeLevel() != D3DERR_DEVICELOST) {
			if(!pLine)	D3DXCreateLine( pDevice, &pLine );
			if ( bRenderText == true )
			{
				//======================================================= Draw Font & Color ========================================================//
				if(!fName)  D3DXCreateFont(pDevice, 11, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &fName);//15
if(!fSmall) D3DXCreateFont(pDevice, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &fSmall);//18
if(!Title)	D3DXCreateFont(pDevice, 40, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Monotype Corsiva", &Title);//13
if(!fTime) D3DXCreateFont(pDevice, 40, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &fTime);
				//D3DXCreateFontA(pDevice, 14, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghotic", &fName);//15
				//D3DXCreateFontA(pDevice, 14, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghotic", &fSmall);//18
				//D3DXCreateFontA(pDevice, 14, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghotic", &Title);//13
				//D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &g_pFont);//15
				D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghotic", &pFont);
				D3DXCreateSprite(pDevice, &textSprite);
				D3DXCreateLine(pDevice, &pLine);
				bRenderText = false;
				}
			{
		    if(IsKeyPressed(VK_F12, 0)&1){ExitProcess(0);}
			RainBow();
			DrawDirect3D(pDevice);
			DrawMenuD3D(pDevice);
			ReleaseHook();
			/*if (*(DWORD*)(ResultBasePlayer) == NULL)
				{}else{*/
            CrossHair(pDevice);
			DrawESP22(pDevice);
			DrawEsp2(pDevice);
			DoAimBot(pDevice);
			//AutoShot2(pDevice);
			//CallAimVischeck(pDevice);
			//CallAimTarget();
			//SUUPÉRFLY();
			//AutoHS();
//			AutoHS();
			//DoAimBot1(pDevice);
			//CallGBMode(pDevice);
			FastReload();
			WeaponFastSwitch();
			Agilidade();
			RespawnVoid();
			//CuchilloRapido();
			/*	if(FastShoot == 1)
			{
				*(DWORD*)(*(DWORD*)(ResultBasePlayer)+0x120) = 0;
			}*/
			if (Skeleto)
					DesenhaWall2(GREEN, pDevice);
				}
			if (*(DWORD*)(ResultBasePlayer) == NULL)
			{
				ResetMatrixSystem();
			}	
			/*if(NoRecoil == 1)
			{
				if(GetAsyncKeyState(VK_LBUTTON))
				{
					*(BYTE*)(ResultGetNoRecoil+0x2) = 0x01;
				}else{
					*(BYTE*)(ResultGetNoRecoil+0x2) = 0xFC;
				}
			}else{
				*(BYTE*)(ResultGetNoRecoil+0x2) = 0xFC;
			}*/
		}
//	}		
}
	__except (EXCEPTION_EXECUTE_HANDLER) {}
return true;
}		


//----------------------------------------------------------------------------------
void  EraseHeaders(HINSTANCE hModule)
{

	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;

	pDoH = (PIMAGE_DOS_HEADER)(hModule);

	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

void HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax
		InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]
		LoopInLoadOrderModuleList :
								  lodsd
								  mov esi, eax
								  mov ecx, [eax + 18h]
								  cmp ecx, hModule
								  jne SkipA
								  mov ebx, [eax]
								  mov ecx, [eax + 4]
								  mov[ecx], ebx
								  mov[ebx + 4], ecx
								  jmp InMemoryOrderModuleList
							  SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList
		InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]
		LoopInMemoryOrderModuleList :
									lodsd
									mov esi, eax
									mov ecx, [eax + 10h]
									cmp ecx, hModule
									jne SkipB
									mov ebx, [eax]
									mov ecx, [eax + 4]
									mov[ecx], ebx
									mov[ebx + 4], ecx
									jmp InInitializationOrderModuleList
								SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList
		InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]
		LoopInInitializationOrderModuleList :
											lodsd
											mov esi, eax
											mov ecx, [eax + 08h]
											cmp ecx, hModule
											jne SkipC
											mov ebx, [eax]
											mov ecx, [eax + 4]
											mov[ecx], ebx
											mov[ebx + 4], ecx
											jmp Finished
										SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList
		Finished :
		popfd;
		popad;
	}
}

#define Ni3SceneCall XorStr<0xE6,44,0xA757ACAE>("\xD9\xB5\x8D\x9A\x8F\x9F\xB4\x9F\x8F\x96\xA2\x94\x9C\x97\x91\x87\xB7\x83\x8C\xB5\x93\x88\x88\xBD\x97\xCC\x58\x73\x63\x7A\x57\x66\x63\x69\x6D\x49\x4A\x5A\x4D\x48\x56\x57\x4A"+0xA757ACAE).s
#define Di3SceneDx XorStr<0x21,14,0x212D5558>("\x48\x11\x70\x47\x40\x48\x42\x6C\x51\x04\x4F\x40\x41"+0x212D5558).s
#define Ni3SceneTracer XorStr<0xFD,29,0x65C43F96>("\xC2\xAC\x9A\x73\x64\x76\x43\x6D\x36\x55\x64\x6D\x67\x6F\x5F\x7E\x6C\x6D\x6A\x62\x51\x52\x42\x55\x50\x4E\x4F\x42"+0x65C43F96).s
DWORD Call_i3Scene = (DWORD)GetProcAddress(GetModuleHandleA(Di3SceneDx), Ni3SceneCall);
DWORD Reti_3Scene = (DWORD)GetProcAddress(GetModuleHandleA(Di3SceneDx), Ni3SceneTracer) + 0xC;
DWORD Dll_i3Scene = (DWORD)GetProcAddress(GetModuleHandleA(Di3SceneDx), Ni3SceneTracer);
void MyResetFont()
{  pFonts->OnLostDevice();
	textSprite->OnLostDevice();
	g_pFont->OnLostDevice();
	Title->OnLostDevice();
	fName->OnLostDevice();
	pFont->OnLostDevice();
	pLine->OnLostDevice();
	Title->OnResetDevice();
	pFont->OnResetDevice();
	pLine->OnResetDevice();
	fName->OnResetDevice();
	g_pFont->OnResetDevice();
	textSprite->OnResetDevice();
	pFonts->OnResetDevice();
}
__declspec (naked) void Calli3Scene(void)//myhook
{//?Reset@i3SceneTracer@@QAEXXZ
	
	__asm
	{
		pushad
		call[i3SceneCreatess]
		call MyResetFont
		popad
		push	    ebp
		mov     ebp, esp
		push    ecx
		push    esi
		mov     esi, ecx
		mov     ecx, [esi + 2Ch]
		test    ecx, ecx
		jmp[Reti_3Scene]
		mov     ecx, [ecx + 0D0h]
		call[Call_i3Scene]
	}
	}

void MakeJMP2(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{

    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}

void Detour(void* dwAddress, void* dwJmp, int Size)
{
	DWORD dwOldProtect, dwRelAddr;
	DWORD dwJumpTo = (DWORD)dwJmp;
	BYTE* pAddress = (BYTE*)dwAddress;
	VirtualProtect((LPVOID)pAddress, sizeof(dwAddress), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*(BYTE*)pAddress = 0xE9;
	*(DWORD*)(pAddress + 0x1) = dwRelAddr;
	for (DWORD x = 0x5; x < Size; x++)*(BYTE*)(pAddress + x) = 0x90;
	VirtualProtect((LPVOID)pAddress, sizeof(dwAddress), dwOldProtect, &dwOldProtect);
}
DWORD HookBone = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)GetModuleHandleA("i3BaseDx.dll")+0xB42CC) + 0xD8) + 0x68) + 0x20) + 0x1fc) -0x7A954B);
inline void myVirtualProtect(void* dwAddress, void* dwJmp, int dwLen)
{
	DWORD dwRelAddr;
	DWORD dwOldProtect;
	DWORD dwJumpTo = (DWORD)dwJmp;
	BYTE* pAddress = (BYTE*)dwAddress;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*(BYTE*)pAddress = 0xE9;
	*(DWORD*)(pAddress + 0x1) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++)
	{
		*(BYTE*)(pAddress + x) = 0x90;
	}
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwOldProtect);
}

void i3SceneHK()
{
	VirtualProtect((PVOID*)Dll_i3Scene, 12, PAGE_EXECUTE_READWRITE, NULL);
	myVirtualProtect((void*)Dll_i3Scene, (void*)Calli3Scene, 5);
	retuna = HookBone + 6;
	Detour((void*)HookBone, (void*)GetEax, 5);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&WriteHooking_Macro, 0, 0, 0);
}

bool bClient = true;
DWORD APIENTRY StartProtection(PVOID Thread)
{

	{
		__try
		{
			while (bClient)
			{
			
				
					if (bClient == true)
					{
						i3SceneHK();
						bClient = false;
					}
				
			}
		}
		__except (TRUE){}
	}
	return bClient;
}


void TrialStarter(){
	ThreadTrial("https://pastebin.com/raw/apMWSgua"/*XorStr<0x89,34,0xC6BAC551>("\xE1\xFE\xFF\xFC\xFE\xB4\xA0\xBF\xE1\xF3\xE0\xE0\xF0\xF4\xFE\xF6\xB7\xF9\xF4\xF1\xB2\xEC\xFE\xD7\x8E\x97\xEB\xD5\xD3\xC5\x90\xCD\xED"+0xC6BAC551).s*/);
	Beep(1000, 100);
}

void Read_HDSN8()
{
	while (1)
	{
		bool IsVerify = false;
		OpenServer();
		DWORD ReadSize; DWORD ReadSize2; BOOL bResult; BOOL bResult2;
		ReadSize = 6;
		ReadSize2 = 10;
		//ReadSize3 = 10;
		Sleep(10);
		bResult = InternetReadFile(hFile1, output, 6, &ReadSize);
		bResult2 = InternetReadFile(hFile2, output2, 10, &ReadSize2);
		//bResult3 = InternetReadFile(hFile3, outputt, 10, &ReadSize3);
		output[ReadSize] = '\0';
		if (strcmp("aktif", output) == 0){
			IsVerify = true;
		}
		if (IsVerify){
			Beep(1000,100);
		}
		else {
		  int StaticModule = MessageBoxA(0, "Maaf anda belom terdaftar di cheat prabayar kami atau trial cheat sudah habis.\nsilahkan kontak Admin untuk membeli Cheat!", "Info", MB_OK|MB_ICONERROR|MB_TOPMOST);
			ExitProcess(0);
		}
		goto end;
	}
  end: return;
}

#define cryptui7		/*cryptui7.dll*/XorStr<0x14,13,0x89CA489D>("\x77\x67\x6F\x67\x6C\x6C\x73\x2C\x32\x79\x72\x73"+0x89CA489D).s
#define cryptui71		/*vfx.dll*/XorStr<0x03,8,0xEC703B4D>("\x75\x62\x7D\x28\x63\x64\x65"+0xEC703B4D).s

#define hid		/*hid.dll*/XorStr<0x05,8,0xF359A315>("\x6D\x6F\x63\x26\x6D\x66\x67"+0xF359A315).s
#define hid1	/*gfx.dll*/XorStr<0x41,8,0x43B6FACE>("\x26\x24\x3B\x6A\x21\x2A\x2B"+0x43B6FACE).s

inline bool file_exists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void RenameDll()
{
	if(file_exists("vfx.dll") && file_exists("gfx.dll"))
	{
		DeleteFileA("vfx.dll");
		DeleteFileA("gfx.dll");
	}
	else{
		rename(hid, hid1);
		rename(cryptui7, cryptui71);
		SetFileAttributes(hid1, FILE_ATTRIBUTE_HIDDEN);
		SetFileAttributes(cryptui7, FILE_ATTRIBUTE_HIDDEN);
	}
}

HMODULE hPointBlank = NULL;
BOOL WINAPI DllMain(HMODULE XTrap, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{

		hPointBlank = GetModuleHandleA("PointBlank.exe");

		if (hPointBlank){
			Beep(2000, 100);
			if (dwReason == DLL_PROCESS_ATTACH)
			{
				//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&TrialStarter, 0, 0, 0);
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&StartProtection, 0, 0, 0);
				MessageBox(0, "Cheat Active", "FebriZip.net",MB_ICONINFORMATION | MB_OK);
				//MessageBox(0, "Cheat Telah Aktif", "Information", MB_ICONWARNING | MB_OK);
				//RenameDll();
			}
		}
	}
	return TRUE;
}