

#pragma once
#ifndef _DETOURS_H_
#define _DETOURS_H_

#pragma comment(lib, "detours")

//////////////////////////////////////////////////////////////////////////////
//
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct  _GUID
{
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[ 8 ];
} GUID;
#endif // !GUID_DEFINED

#if defined(__cplusplus)
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID &
#endif // !_REFGUID_DEFINED
#else // !__cplusplus
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID * const
#endif // !_REFGUID_DEFINED
#endif // !__cplusplus
//
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/////////////////////////////////////////////////// Instruction Target Macros.
//
#define DETOUR_INSTRUCTION_TARGET_NONE          ((PBYTE)0)
#define DETOUR_INSTRUCTION_TARGET_DYNAMIC       ((PBYTE)~0ul)

/////////////////////////////////////////////////////////// Trampoline Macros.
//
// DETOUR_TRAMPOLINE(trampoline_prototype, target_name)
//
// The naked trampoline must be at least DETOUR_TRAMPOLINE_SIZE bytes.
//
#define DETOUR_TRAMPOLINE_SIZE          32
#define DETOUR_SECTION_HEADER_SIGNATURE 0x00727444   // "Dtr\0"

#define DETOUR_TRAMPOLINE(trampoline,target) \
static PVOID __fastcall _Detours_GetVA_##target(VOID) \
{ \
    return &target; \
} \
\
__declspec(naked) trampoline \
{ \
    __asm { nop };\
    __asm { nop };\
    __asm { call _Detours_GetVA_##target };\
    __asm { jmp eax };\
    __asm { ret };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
}

#define DETOUR_TRAMPOLINE_EMPTY(trampoline) \
__declspec(naked) trampoline \
{ \
    __asm { nop };\
    __asm { nop };\
    __asm { xor eax, eax };\
    __asm { mov eax, [eax] };\
    __asm { ret };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
    __asm { nop };\
}

/////////////////////////////////////////////////////////// Binary Structures.
//
#pragma pack(push, 8)
typedef struct _DETOUR_SECTION_HEADER
{
    DWORD       cbHeaderSize;
    DWORD       nSignature;
    DWORD       nDataOffset;
    DWORD       cbDataSize;
    
    DWORD       nOriginalImportVirtualAddress;
    DWORD       nOriginalImportSize;
    DWORD       nOriginalBoundImportVirtualAddress;
    DWORD       nOriginalBoundImportSize;
    
    DWORD       nOriginalIatVirtualAddress;
    DWORD       nOriginalIatSize;
    DWORD       nOriginalSizeOfImage;
    DWORD       nReserve;
} DETOUR_SECTION_HEADER, *PDETOUR_SECTION_HEADER;

typedef struct _DETOUR_SECTION_RECORD
{
    DWORD       cbBytes;
    DWORD       nReserved;
    GUID        guid;
} DETOUR_SECTION_RECORD, *PDETOUR_SECTION_RECORD;
#pragma pack(pop)

#define DETOUR_SECTION_HEADER_DECLARE(cbSectionSize) \
{ \
      sizeof(DETOUR_SECTION_HEADER),\
      DETOUR_SECTION_HEADER_SIGNATURE,\
      sizeof(DETOUR_SECTION_HEADER),\
      (cbSectionSize),\
      \
      0,\
      0,\
      0,\
      0,\
      \
      0,\
      0,\
      0,\
      0,\
}

///////////////////////////////////////////////////////////// Binary Typedefs.
//
typedef BOOL (CALLBACK *PF_DETOUR_BINARY_BYWAY_CALLBACK)(PVOID pContext,
                                                         PCHAR pszFile,
                                                         PCHAR *ppszOutFile);
typedef BOOL (CALLBACK *PF_DETOUR_BINARY_FILE_CALLBACK)(PVOID pContext,
                                                        PCHAR pszOrigFile,
                                                        PCHAR pszFile,
                                                        PCHAR *ppszOutFile);
typedef BOOL (CALLBACK *PF_DETOUR_BINARY_SYMBOL_CALLBACK)(PVOID pContext,
                                                          DWORD nOrdinal,
                                                          PCHAR pszOrigSymbol,
                                                          PCHAR pszSymbol,
                                                          PCHAR *ppszOutSymbol);
typedef BOOL (CALLBACK *PF_DETOUR_BINARY_FINAL_CALLBACK)(PVOID pContext);
typedef BOOL (CALLBACK *PF_DETOUR_BINARY_EXPORT_CALLBACK)(PVOID pContext,
                                                          DWORD nOrdinal,
                                                          PCHAR pszName,
                                                          PBYTE pbCode);

typedef VOID * PDETOUR_BINARY;
typedef VOID * PDETOUR_LOADED_BINARY;

//////////////////////////////////////////////////////// Trampoline Functions.
//
void *DetourFunction (BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp;
    DWORD dwback;
    DWORD jumpto, newjump;

    VirtualProtect(src,len,PAGE_READWRITE,&dwback);
    
    if(src[0] == 0xE9)
    {
        jmp = (BYTE*)malloc(10);
        jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
        newjump = (jumpto-(DWORD)(jmp+5));
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = newjump;
        jmp += 5;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
    }
    else
    {
        jmp = (BYTE*)malloc(5+len);
        memcpy(jmp,src,len);
        jmp += len;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
    }
    src[0] = 0xE9;
   *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

    for(int i = 5; i < len; i++)
        src[i] = 0x90;
    VirtualProtect(src,len,dwback,&dwback);
    return (jmp-len);
} 
//PBYTE WINAPI DetourFunction(PBYTE pbTargetFunction,
//                            PBYTE pbDetourFunction);

BOOL WINAPI DetourFunctionWithEmptyTrampoline(PBYTE pbTrampoline,
                                              PBYTE pbTarget,
                                              PBYTE pbDetour);

BOOL WINAPI DetourFunctionWithEmptyTrampolineEx(PBYTE pbTrampoline,
                                                PBYTE pbTarget,
                                                PBYTE pbDetour,
                                                PBYTE *ppbRealTrampoline,
                                                PBYTE *ppbRealTarget,
                                                PBYTE *ppbRealDetour);

BOOL  WINAPI DetourFunctionWithTrampoline(PBYTE pbTrampoline,
                                          PBYTE pbDetour);

BOOL  WINAPI DetourFunctionWithTrampolineEx(PBYTE pbTrampoline,
                                            PBYTE pbDetour,
                                            PBYTE *ppbRealTrampoline,
                                            PBYTE *ppbRealTarget);

BOOL  WINAPI DetourRemove(PBYTE pbTrampoline, PBYTE pbDetour);

////////////////////////////////////////////////////////////// Code Functions.
//
PBYTE WINAPI DetourFindFunction(PCHAR pszModule, PCHAR pszFunction);
PBYTE WINAPI DetourGetFinalCode(PBYTE pbCode, BOOL fSkipJmp);

PBYTE WINAPI DetourCopyInstruction(PBYTE pbDst, PBYTE pbSrc, PBYTE *ppbTarget);
PBYTE WINAPI DetourCopyInstructionEx(PBYTE pbDst,
                                     PBYTE pbSrc,
                                     PBYTE *ppbTarget,
                                     LONG *plExtra);

///////////////////////////////////////////////////// Loaded Binary Functions.
//
HMODULE WINAPI DetourEnumerateModules(HMODULE hModuleLast);
PBYTE WINAPI DetourGetEntryPoint(HMODULE hModule);
BOOL WINAPI DetourEnumerateExports(HMODULE hModule,
                                   PVOID pContext,
                                   PF_DETOUR_BINARY_EXPORT_CALLBACK pfExport);

PBYTE WINAPI DetourFindPayload(HMODULE hModule, REFGUID rguid, DWORD *pcbData);
DWORD WINAPI DetourGetSizeOfPayloads(HMODULE hModule);

///////////////////////////////////////////////// Persistent Binary Functions.
//
BOOL WINAPI DetourBinaryBindA(PCHAR pszFile, PCHAR pszDll, PCHAR pszPath);
BOOL WINAPI DetourBinaryBindW(PWCHAR pwzFile, PWCHAR pwzDll, PWCHAR pwzPath);
#ifdef UNICODE
#define DetourBinaryBind  DetourBinaryBindW
#else
#define DetourBinaryBind  DetourBinaryBindA
#endif // !UNICODE

PDETOUR_BINARY WINAPI DetourBinaryOpen(HANDLE hFile);
PBYTE WINAPI DetourBinaryEnumeratePayloads(PDETOUR_BINARY pBinary,
                                           GUID *pGuid,
                                           DWORD *pcbData,
                                           DWORD *pnIterator);
PBYTE WINAPI DetourBinaryFindPayload(PDETOUR_BINARY pBinary,
                                     REFGUID rguid,
                                     DWORD *pcbData);
PBYTE WINAPI DetourBinarySetPayload(PDETOUR_BINARY pBinary,
                                    REFGUID rguid,
                                    PBYTE pbData,
                                    DWORD cbData);
BOOL WINAPI DetourBinaryDeletePayload(PDETOUR_BINARY pBinary, REFGUID rguid);
BOOL WINAPI DetourBinaryPurgePayloads(PDETOUR_BINARY pBinary);
BOOL WINAPI DetourBinaryResetImports(PDETOUR_BINARY pBinary);
BOOL WINAPI DetourBinaryEditImports(PDETOUR_BINARY pBinary,
                                    PVOID pContext,
                                    PF_DETOUR_BINARY_BYWAY_CALLBACK pfByway,
                                    PF_DETOUR_BINARY_FILE_CALLBACK pfFile,
                                    PF_DETOUR_BINARY_SYMBOL_CALLBACK pfSymbol,
                                    PF_DETOUR_BINARY_FINAL_CALLBACK pfFinal);
BOOL WINAPI DetourBinaryWrite(PDETOUR_BINARY pBinary, HANDLE hFile);
BOOL WINAPI DetourBinaryClose(PDETOUR_BINARY pBinary);

/////////////////////////////////////////////// First Chance Exception Filter.
//
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI
DetourFirstChanceExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelFilter);

///////////////////////////////////////////////// Create Process & Inject Dll.
//
typedef BOOL (WINAPI *PDETOUR_CREATE_PROCESS_ROUTINEA)
    (LPCSTR lpApplicationName,
     LPSTR lpCommandLine,
     LPSECURITY_ATTRIBUTES lpProcessAttributes,
     LPSECURITY_ATTRIBUTES lpThreadAttributes,
     BOOL bInheritHandles,
     DWORD dwCreationFlags,
     LPVOID lpEnvironment,
     LPCSTR lpCurrentDirectory,
     LPSTARTUPINFOA lpStartupInfo,
     LPPROCESS_INFORMATION lpProcessInformation);

typedef BOOL (WINAPI *PDETOUR_CREATE_PROCESS_ROUTINEW)
    (LPCWSTR lpApplicationName,
     LPWSTR lpCommandLine,
     LPSECURITY_ATTRIBUTES lpProcessAttributes,
     LPSECURITY_ATTRIBUTES lpThreadAttributes,
     BOOL bInheritHandles,
     DWORD dwCreationFlags,
     LPVOID lpEnvironment,
     LPCWSTR lpCurrentDirectory,
     LPSTARTUPINFOW lpStartupInfo,
     LPPROCESS_INFORMATION lpProcessInformation);
                                  
BOOL WINAPI DetourCreateProcessWithDllA(LPCSTR lpApplicationName,
                                        LPSTR lpCommandLine,
                                        LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                        LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                        BOOL bInheritHandles,
                                        DWORD dwCreationFlags,
                                        LPVOID lpEnvironment,
                                        LPCSTR lpCurrentDirectory,
                                        LPSTARTUPINFOA lpStartupInfo,
                                        LPPROCESS_INFORMATION lpProcessInformation,
                                        LPCSTR lpDllName,
                                        PDETOUR_CREATE_PROCESS_ROUTINEA
                                        pfCreateProcessA);

BOOL WINAPI DetourCreateProcessWithDllW(LPCWSTR lpApplicationName,
                                        LPWSTR lpCommandLine,
                                        LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                        LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                        BOOL bInheritHandles,
                                        DWORD dwCreationFlags,
                                        LPVOID lpEnvironment,
                                        LPCWSTR lpCurrentDirectory,
                                        LPSTARTUPINFOW lpStartupInfo,
                                        LPPROCESS_INFORMATION lpProcessInformation,
                                        LPCWSTR lpDllName,
                                        PDETOUR_CREATE_PROCESS_ROUTINEW
                                        pfCreateProcessW);
                  
#ifdef UNICODE
#define DetourCreateProcessWithDll  DetourCreateProcessWithDllW
#define PDETOUR_CREATE_PROCESS_ROUTINE     PDETOUR_CREATE_PROCESS_ROUTINEW
#else
#define DetourCreateProcessWithDll  DetourCreateProcessWithDllA
#define PDETOUR_CREATE_PROCESS_ROUTINE     PDETOUR_CREATE_PROCESS_ROUTINEA
#endif // !UNICODE

BOOL WINAPI DetourContinueProcessWithDllA(HANDLE hProcess, LPCSTR lpDllName);
BOOL WINAPI DetourContinueProcessWithDllW(HANDLE hProcess, LPCWSTR lpDllName);

#ifdef UNICODE
#define DetourContinueProcessWithDll    DetourContinueProcessWithDllW
#else
#define DetourContinueProcessWithDll    DetourContinueProcessWithDllA
#endif // !UNICODE
//
//////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif // __cplusplus

/////////////////////////////////////////////////////////////////// Old Names.
//
#define ContinueProcessWithDll            DetourContinueProcessWithDll 
#define ContinueProcessWithDllA           DetourContinueProcessWithDllA
#define ContinueProcessWithDllW           DetourContinueProcessWithDllW
#define CreateProcessWithDll              DetourCreateProcessWithDll 
#define CreateProcessWithDllA             DetourCreateProcessWithDllA
#define CreateProcessWithDllW             DetourCreateProcessWithDllW
#define DETOUR_TRAMPOLINE_WO_TARGET       DETOUR_TRAMPOLINE_EMPTY
#define DetourBinaryPurgePayload          DetourBinaryPurgePayloads
#define DetourEnumerateExportsForInstance DetourEnumerateExports
#define DetourEnumerateInstances          DetourEnumerateModules
#define DetourFindEntryPointForInstance   DetourGetEntryPoint
#define DetourFindFinalCode               DetourGetFinalCode
#define DetourFindPayloadInBinary         DetourFindPayload
#define DetourGetSizeOfBinary             DetourGetSizeOfPayloads
#define DetourRemoveWithTrampoline        DetourRemove
#define PCREATE_PROCESS_ROUTINE           PDETOUR_CREATE_PROCESS_ROUTINE
#define PCREATE_PROCESS_ROUTINEA          PDETOUR_CREATE_PROCESS_ROUTINEA
#define PCREATE_PROCESS_ROUTINEW          PDETOUR_CREATE_PROCESS_ROUTINEW
//

//////////////////////////////////////////////// Detours Internal Definitions.
//
#ifdef __cplusplus
#ifdef DETOURS_INTERNAL

//////////////////////////////////////////////////////////////////////////////
//
#ifdef IMAGEAPI // defined by IMAGEHLP.H
typedef LPAPI_VERSION (NTAPI *PF_ImagehlpApiVersionEx)(LPAPI_VERSION AppVersion);

typedef BOOL (NTAPI *PF_SymInitialize)(IN HANDLE hProcess,
                                       IN LPSTR UserSearchPath,
                                       IN BOOL fInvadeProcess);
typedef DWORD (NTAPI *PF_SymSetOptions)(IN DWORD SymOptions);
typedef DWORD (NTAPI *PF_SymGetOptions)(VOID);
typedef BOOL (NTAPI *PF_SymLoadModule)(IN HANDLE hProcess,
                                       IN HANDLE hFile,
                                       IN PSTR ImageName,
                                       IN PSTR ModuleName,
                                       IN DWORD BaseOfDll,
                                       IN DWORD SizeOfDll);
typedef BOOL (NTAPI *PF_SymGetModuleInfo)(IN HANDLE hProcess,
                                          IN DWORD dwAddr,
                                          OUT PIMAGEHLP_MODULE ModuleInfo);
typedef BOOL (NTAPI *PF_SymGetSymFromName)(IN HANDLE hProcess,
                                           IN LPSTR Name,
                                           OUT PIMAGEHLP_SYMBOL Symbol);
typedef BOOL (NTAPI *PF_BindImage)(IN LPSTR pszImageName,
                                   IN LPSTR pszDllPath,
                                   IN LPSTR pszSymbolPath);

typedef struct _DETOUR_SYM_INFO
{
    HANDLE                   hProcess;
    HMODULE                  hImageHlp;
    PF_ImagehlpApiVersionEx  pfImagehlpApiVersionEx;
    PF_SymInitialize         pfSymInitialize;
    PF_SymSetOptions         pfSymSetOptions;
    PF_SymGetOptions         pfSymGetOptions;
    PF_SymLoadModule         pfSymLoadModule;
    PF_SymGetModuleInfo      pfSymGetModuleInfo;
    PF_SymGetSymFromName     pfSymGetSymFromName;
    PF_BindImage             pfBindImage;
} DETOUR_SYM_INFO, *PDETOUR_SYM_INFO;

PDETOUR_SYM_INFO DetourLoadImageHlp(VOID);

#endif // IMAGEAPI

//////////////////////////////////////////////////////////////////////////////
//
class CDetourEnableWriteOnCodePage
{
public:
    CDetourEnableWriteOnCodePage(PBYTE pbCode, LONG cbCode = DETOUR_TRAMPOLINE_SIZE)
    {
        m_pbCode = pbCode;
        m_cbCode = cbCode;
        m_dwOldPerm = 0;
        m_hProcess = GetCurrentProcess();

        if (m_pbCode && m_cbCode) {
            if (!FlushInstructionCache(m_hProcess, pbCode, cbCode)) {
                return;
            }
            if (!VirtualProtect(pbCode,
                                cbCode,
                                PAGE_EXECUTE_READWRITE,
                                &m_dwOldPerm)) {
                return;
            }
        }
    }

    ~CDetourEnableWriteOnCodePage()
    {
        if (m_dwOldPerm && m_pbCode && m_cbCode) {
            DWORD dwTemp = 0;
            if (!FlushInstructionCache(m_hProcess, m_pbCode, m_cbCode)) {
                return;
            }
            if (!VirtualProtect(m_pbCode, m_cbCode, m_dwOldPerm, &dwTemp)) {
                return;
            }
        }
    }

    BOOL SetPermission(DWORD dwPerms)
    {
        if (m_dwOldPerm && m_pbCode && m_cbCode) {
            m_dwOldPerm = dwPerms;
            return TRUE;
        }
        return FALSE;
    }

    BOOL IsValid(VOID)
    {
        return m_pbCode && m_cbCode && m_dwOldPerm;
    }

private:
    HANDLE  m_hProcess;
    PBYTE   m_pbCode;
    LONG    m_cbCode;
    DWORD   m_dwOldPerm;
};

//////////////////////////////////////////////////////////////////////////////
//
inline PBYTE DetourGenMovEax(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xB8;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEbx(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBB;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEcx(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xB9;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEdx(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBA;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEsi(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBE;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEdi(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBF;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEbp(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBD;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenMovEsp(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0xBC;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenPush(PBYTE pbCode, UINT32 nValue)
{
    *pbCode++ = 0x68;
    *((UINT32*&)pbCode)++ = nValue;
    return pbCode;
}

inline PBYTE DetourGenPushad(PBYTE pbCode)
{
    *pbCode++ = 0x60;
    return pbCode;
}

inline PBYTE DetourGenPopad(PBYTE pbCode)
{
    *pbCode++ = 0x61;
    return pbCode;
}

inline PBYTE DetourGenJmp(PBYTE pbCode, PBYTE pbJmpDst, PBYTE pbJmpSrc = 0)
{
    if (pbJmpSrc == 0) {
        pbJmpSrc = pbCode;
    }
    *pbCode++ = 0xE9;
    *((INT32*&)pbCode)++ = pbJmpDst - (pbJmpSrc + 5);
    return pbCode;
}

inline PBYTE DetourGenCall(PBYTE pbCode, PBYTE pbJmpDst, PBYTE pbJmpSrc = 0)
{
    if (pbJmpSrc == 0) {
        pbJmpSrc = pbCode;
    }
    *pbCode++ = 0xE8;
    *((INT32*&)pbCode)++ = pbJmpDst - (pbJmpSrc + 5);
    return pbCode;
}

inline PBYTE DetourGenBreak(PBYTE pbCode)
{
    *pbCode++ = 0xcc;
    return pbCode;
}

inline PBYTE DetourGenRet(PBYTE pbCode)
{
    *pbCode++ = 0xc3;
    return pbCode;
}

inline PBYTE DetourGenNop(PBYTE pbCode)
{
    *pbCode++ = 0x90;
    return pbCode;
}
#endif DETOURS_INTERAL
#endif // __cplusplus

#endif // _DETOURS_H_



//#define NATIVE_CODE
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <stddef.h>
//#include <string.h>
//#include <windows.h>
//#include <winioctl.h>
//
//#pragma warning(disable:4996)
//   //  Required to ensure correct PhysicalDrive IOCTL structure setup
//#pragma pack(1)
//
//#define  IDENTIFY_BUFFER_SIZE  512
//
//
//   //  IOCTL commands
//#define  DFP_GET_VERSION          0x00074080
//#define  DFP_SEND_DRIVE_COMMAND   0x0007c084
//#define  DFP_RECEIVE_DRIVE_DATA   0x0007c088
//
//#define  FILE_DEVICE_SCSI              0x0000001b
//#define  IOCTL_SCSI_MINIPORT_IDENTIFY  ((FILE_DEVICE_SCSI << 16) + 0x0501)
//#define  IOCTL_SCSI_MINIPORT 0x0004D008  //  see NTDDSCSI.H for definition
//
//
//#define SMART_GET_VERSION               CTL_CODE(IOCTL_DISK_BASE, 0x0020, METHOD_BUFFERED, FILE_READ_ACCESS)
//#define SMART_SEND_DRIVE_COMMAND        CTL_CODE(IOCTL_DISK_BASE, 0x0021, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
//#define SMART_RCV_DRIVE_DATA            CTL_CODE(IOCTL_DISK_BASE, 0x0022, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
//
//   //  GETVERSIONOUTPARAMS contains the data returned from the 
//   //  Get Driver Version function.
//typedef struct _GETVERSIONOUTPARAMS
//{
//   BYTE bVersion;      // Binary driver version.
//   BYTE bRevision;     // Binary driver revision.
//   BYTE bReserved;     // Not used.
//   BYTE bIDEDeviceMap; // Bit map of IDE devices.
//   DWORD fCapabilities; // Bit mask of driver capabilities.
//   DWORD dwReserved[4]; // For future use.
//} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;
//
//
//   //  Bits returned in the fCapabilities member of GETVERSIONOUTPARAMS 
//#define  CAP_IDE_ID_FUNCTION             1  // ATA ID command supported
//#define  CAP_IDE_ATAPI_ID                2  // ATAPI ID command supported
//#define  CAP_IDE_EXECUTE_SMART_FUNCTION  4  // SMART commannds supported
//
//
//
//   //  Valid values for the bCommandReg member of IDEREGS.
//#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
//#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.
//
//   // The following struct defines the interesting part of the IDENTIFY
//   // buffer:
//typedef struct _IDSECTOR
//{
//   USHORT  wGenConfig;
//   USHORT  wNumCyls;
//   USHORT  wReserved;
//   USHORT  wNumHeads;
//   USHORT  wBytesPerTrack;
//   USHORT  wBytesPerSector;
//   USHORT  wSectorsPerTrack;
//   USHORT  wVendorUnique[3];
//   CHAR    sSerialNumber[20];
//   USHORT  wBufferType;
//   USHORT  wBufferSize;
//   USHORT  wECCSize;
//   CHAR    sFirmwareRev[8];
//   CHAR    sModelNumber[40];
//   USHORT  wMoreVendorUnique;
//   USHORT  wDoubleWordIO;
//   USHORT  wCapabilities;
//   USHORT  wReserved1;
//   USHORT  wPIOTiming;
//   USHORT  wDMATiming;
//   USHORT  wBS;
//   USHORT  wNumCurrentCyls;
//   USHORT  wNumCurrentHeads;
//   USHORT  wNumCurrentSectorsPerTrack;
//   ULONG   ulCurrentSectorCapacity;
//   USHORT  wMultSectorStuff;
//   ULONG   ulTotalAddressableSectors;
//   USHORT  wSingleWordDMA;
//   USHORT  wMultiWordDMA;
//   BYTE    bReserved[128];
//} IDSECTOR, *PIDSECTOR;
//
////
//// IDENTIFY data (from ATAPI driver source)
////
//
//#pragma pack(1)
//
//typedef struct _IDENTIFY_DATA {
//    USHORT GeneralConfiguration;            // 00 00
//    USHORT NumberOfCylinders;               // 02  1
//    USHORT Reserved1;                       // 04  2
//    USHORT NumberOfHeads;                   // 06  3
//    USHORT UnformattedBytesPerTrack;        // 08  4
//    USHORT UnformattedBytesPerSector;       // 0A  5
//    USHORT SectorsPerTrack;                 // 0C  6
//    USHORT VendorUnique1[3];                // 0E  7-9
//    USHORT SerialNumber[10];                // 14  10-19
//    USHORT BufferType;                      // 28  20
//    USHORT BufferSectorSize;                // 2A  21
//    USHORT NumberOfEccBytes;                // 2C  22
//    USHORT FirmwareRevision[4];             // 2E  23-26
//    USHORT ModelNumber[20];                 // 36  27-46
//    UCHAR  MaximumBlockTransfer;            // 5E  47
//    UCHAR  VendorUnique2;                   // 5F
//    USHORT DoubleWordIo;                    // 60  48
//    USHORT Capabilities;                    // 62  49
//    USHORT Reserved2;                       // 64  50
//    UCHAR  VendorUnique3;                   // 66  51
//    UCHAR  PioCycleTimingMode;              // 67
//    UCHAR  VendorUnique4;                   // 68  52
//    UCHAR  DmaCycleTimingMode;              // 69
//    USHORT TranslationFieldsValid:1;        // 6A  53
//    USHORT Reserved3:15;
//    USHORT NumberOfCurrentCylinders;        // 6C  54
//    USHORT NumberOfCurrentHeads;            // 6E  55
//    USHORT CurrentSectorsPerTrack;          // 70  56
//    ULONG  CurrentSectorCapacity;           // 72  57-58
//    USHORT CurrentMultiSectorSetting;       //     59
//    ULONG  UserAddressableSectors;          //     60-61
//    USHORT SingleWordDMASupport : 8;        //     62
//    USHORT SingleWordDMAActive : 8;
//    USHORT MultiWordDMASupport : 8;         //     63
//    USHORT MultiWordDMAActive : 8;
//    USHORT AdvancedPIOModes : 8;            //     64
//    USHORT Reserved4 : 8;
//    USHORT MinimumMWXferCycleTime;          //     65
//    USHORT RecommendedMWXferCycleTime;      //     66
//    USHORT MinimumPIOCycleTime;             //     67
//    USHORT MinimumPIOCycleTimeIORDY;        //     68
//    USHORT Reserved5[2];                    //     69-70
//    USHORT ReleaseTimeOverlapped;           //     71
//    USHORT ReleaseTimeServiceCommand;       //     72
//    USHORT MajorRevision;                   //     73
//    USHORT MinorRevision;                   //     74
//    USHORT Reserved6[50];                   //     75-126
//    USHORT SpecialFunctionsEnabled;         //     127
//    USHORT Reserved7[128];                  //     128-255
//} IDENTIFY_DATA, *PIDENTIFY_DATA;
//
//#pragma pack()
//
//typedef struct _SRB_IO_CONTROL
//{
//   ULONG HeaderLength;
//   UCHAR Signature[8];
//   ULONG Timeout;
//   ULONG ControlCode;
//   ULONG ReturnCode;
//   ULONG Length;
//} SRB_IO_CONTROL, *PSRB_IO_CONTROL;
//#define SMART_RCV_DRIVE_DATA            CTL_CODE(IOCTL_DISK_BASE, 0x0022, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
//
//class DiskInfo
//{
//	static char VI[1024];
//	static char SN[1024];
//	static char MN[1024];
//	static char RN[1024];
//public:
//	DiskInfo(UINT driveNum);
//	void Destroy()
//	{
//	};
//	~DiskInfo(void);
//	int DriveReadAsSCSI (void);
//	long LoadDiskInfo();
//	int DriveReadAdmin (void);
//	int DriveReadNoAdmin (void);
//	int DriveReadPort9x (void);
//	int DriveReadSMART (void);
//
//	unsigned __int64 DriveSize ();
//	UINT BufferSize ();
//	char* ModelNumber ();
//	char* SerialNumber ();
//	char* RevisionNumber ();
//	char* DriveType ();
//private:
//	UINT uDriveNum;
//	DWORD diskdata[256];
//
//   __int64 Sectors;
//   __int64 Bytes;
//
//	static char * flipAndCodeBytes (char * str);
//	static char * ConvertToString (DWORD diskdata [256], int firstIndex, int lastIndex);
//	void getIDEInfo();
//	static BOOL DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
//                 PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
//                 PDWORD lpcbBytesReturned);
//};
//
//
//#pragma warning(disable: 4172)
//using namespace std;
//char DiskInfo::VI [1024];
//char DiskInfo::SN [1024];
//char DiskInfo::MN [1024];
//char DiskInfo::RN [1024];
//
//void DiskInfo::getIDEInfo()
//{
//	strcpy( MN, ConvertToString(diskdata, 27, 46));
//	strcpy( SN, ConvertToString(diskdata, 10, 19));
//	strcpy( RN, ConvertToString(diskdata, 23, 26));
//}
//
//int DiskInfo::DriveReadSMART (void)
//{
//   int done = FALSE;
//   //int drive = uDriveNum;
//   HANDLE hPhysicalDriveIOCTL = 0;
//   char driveName [256];
//   sprintf  (driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);
//   //  Windows NT, Windows 2000, Windows Server 2003, Vista
//   hPhysicalDriveIOCTL = CreateFile (driveName,GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
//   if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
//   {
//   }else{
//	   GETVERSIONINPARAMS GetVersionParams;
//	   DWORD cbBytesReturned = 0;
//	   memset ((void*) & GetVersionParams, 0, sizeof(GetVersionParams));
//	   if (DeviceIoControl (hPhysicalDriveIOCTL, SMART_GET_VERSION,NULL, 0,&GetVersionParams, sizeof (GETVERSIONINPARAMS),&cbBytesReturned, NULL) )
//	   {         
//		   ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
//		   PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS) malloc (CommandSize);
//
//#define ID_CMD          0xEC            // Returns ID sector for ATA
//
//		   Command -> irDriveRegs.bCommandReg = ID_CMD;
//		   DWORD BytesReturned = 0;
//		   if ( DeviceIoControl (hPhysicalDriveIOCTL, SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),Command, CommandSize,&BytesReturned, NULL) )
//		   {
//			   USHORT *pIdSector = (USHORT *)(PIDENTIFY_DATA) ((PSENDCMDOUTPARAMS) Command) -> bBuffer;
//			   for (int haa = 0; haa < 256; haa++) diskdata [haa] = pIdSector [haa];
//			   getIDEInfo();
//			   done = TRUE;
//		   }
//		   CloseHandle (hPhysicalDriveIOCTL);
//		   free (Command);
//	   }
//   }
//   return done;
//}
//
//int DiskInfo::DriveReadAdmin (void)
//{
//	int done = FALSE;
//	BYTE IdOutCmd [sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
//	HANDLE hPhysicalDriveIOCTL = 0;
//
//	TCHAR driveName [256];
//
//	sprintf (driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);
//
//	//  Windows NT, Windows 2000, run as admin 
//	hPhysicalDriveIOCTL = CreateFile (driveName,GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL);
//
//	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
//	{
//		GETVERSIONOUTPARAMS VersionParams;
//		DWORD               cbBytesReturned = 0;
//
//		memset ((void*) &VersionParams, 0, sizeof(VersionParams));
//
//		if (  DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,NULL, 0,&VersionParams,sizeof(VersionParams),&cbBytesReturned, NULL) )
//		{         
//			if (VersionParams.bIDEDeviceMap > 0)
//			{
//				BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
//				SENDCMDINPARAMS  scip;
//				bIDCmd = (VersionParams.bIDEDeviceMap >> uDriveNum & 0x10) ? \
//IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
//
//				memset (&scip, 0, sizeof(scip));
//				memset (IdOutCmd, 0, sizeof(IdOutCmd));
//
//				if ( DoIDENTIFY (hPhysicalDriveIOCTL, &scip, (PSENDCMDOUTPARAMS)&IdOutCmd, (BYTE) bIDCmd,(BYTE) uDriveNum,&cbBytesReturned))
//				{
//					USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;
//					for (int aa = 0; aa < 256; aa++) diskdata [aa] = pIdSector [aa];  
//					getIDEInfo();
//					done = TRUE;
//				}
//			}
//		}
//		CloseHandle (hPhysicalDriveIOCTL);
//	}
//	return done;
//}
//
//#pragma pack(4)
///*
//typedef enum _STORAGE_QUERY_TYPE {
//	PropertyStandardQuery = 0,          // Retrieves the descriptor
//	PropertyExistsQuery,                // Used to test whether the descriptor is supported
//	PropertyMaskQuery,                  // Used to retrieve a mask of writeable fields in the descriptor
//	PropertyQueryMaxDefined     // use to validate the value
//} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;
//*/
//
///*
//typedef enum _STORAGE_PROPERTY_ID {
//	StorageDeviceProperty = 0,
//	StorageAdapterProperty
//} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;
//*/
//
///*
//typedef struct _STORAGE_PROPERTY_QUERY {
//	STORAGE_PROPERTY_ID PropertyId;
//	STORAGE_QUERY_TYPE QueryType;
//	UCHAR AdditionalParameters[1];
//
//} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;
//*/
//#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)
//
//char * DiskInfo::flipAndCodeBytes (char * str)
//{
//	static char flipped [1000];
//	int num = strlen (str);
//	strcpy (flipped, "");
//	for (int i = 0; i < num; i += 4)
//	{
//		for (int j = 1; j >= 0; j--)
//		{
//			int sum = 0;
//			for (int k = 0; k < 2; k++)
//			{
//				sum *= 16;
//				switch (str [i + j * 2 + k])
//				{
//				case '0': sum += 0; break;
//				case '1': sum += 1; break;
//				case '2': sum += 2; break;
//				case '3': sum += 3; break;
//				case '4': sum += 4; break;
//				case '5': sum += 5; break;
//				case '6': sum += 6; break;
//				case '7': sum += 7; break;
//				case '8': sum += 8; break;
//				case '9': sum += 9; break;
//				case 'a': sum += 10; break;
//				case 'b': sum += 11; break;
//				case 'c': sum += 12; break;
//				case 'd': sum += 13; break;
//				case 'e': sum += 14; break;
//				case 'f': sum += 15; break;
//				}
//			}
//			if (sum > 0) 
//			{
//				char sub [2];
//				sub [0] = (char) sum;
//				sub [1] = 0;
//				strcat (flipped, sub);
//			}
//		}
//	}
//
//	return flipped;
//}
//
//char * flipAndCodeBytes2 (const char * str,int pos,int flip,char * buf)
//{
//	int i;
//	int j = 0;
//	int k = 0;
//
//	buf [0] = '\0';
//	if (pos <= 0) return buf;
//	if ( ! j)
//	{
//		char p = 0;
//
//		// First try to gather all characters representing hex digits only.
//		j = 1;
//		k = 0;
//		buf[k] = 0;
//		for (i = pos; j && str[i] != '\0'; ++i)
//		{
//
//			char c = tolower(str[i]);
//			if (isspace(c))	    c = '0';
//			++p;
//			buf[k] <<= 4;
//
//			if (c >= '0' && c <= '9')
//				buf[k] |= (unsigned char) (c - '0');
//			else if (c >= 'a' && c <= 'f')
//				buf[k] |= (unsigned char) (c - 'a' + 10);
//			else
//			{
//				j = 0;
//				break;
//			}
//
//			if (p == 2)
//			{
//				if (buf[k] != '\0' && ! isprint(buf[k]))
//				{
//					j = 0;
//					break;
//				}
//				++k;
//				p = 0;
//				buf[k] = 0;
//			}
//
//		}
//	}
//
//	if ( ! j)
//	{
//		// There are non-digit characters, gather them as is.
//		j = 1;
//		k = 0;
//		for (i = pos; j && str[i] != '\0'; ++i)
//		{
//			char c = str[i];
//
//			if ( ! isprint(c))
//			{
//				j = 0;
//				break;
//			}
//
//			buf[k++] = c;
//		}
//	}
//
//	if ( ! j)
//	{
//		// The characters are not there or are not printable.
//		k = 0;
//	}
//
//	buf[k] = '\0';
//
//	if (flip)
//		// Flip adjacent characters
//		for (j = 0; j < k; j += 2)
//		{
//			char t = buf[j];
//			buf[j] = buf[j + 1];
//			buf[j + 1] = t;
//		}
//		// Trim any beginning and end space
//		i = j = -1;
//		for (k = 0; buf[k] != '\0'; ++k)
//		{
//			if (! isspace(buf[k]))
//			{
//				if (i < 0)
//					i = k;
//				j = k;
//			}
//		}
//
//		if ((i >= 0) && (j >= 0))
//		{
//			for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
//				buf[k - i] = buf[k];
//			buf[k - i] = '\0';
//		}
//		return buf;
//}
//
//
//typedef struct _MEDIA_SERAL_NUMBER_DATA {
//  ULONG  SerialNumberLength; 
//  ULONG  Result;
//  ULONG  Reserved[2];
//  UCHAR  SerialNumberData[1];
//} MEDIA_SERIAL_NUMBER_DATA, *PMEDIA_SERIAL_NUMBER_DATA;
//
//int DiskInfo::DriveReadNoAdmin (void)
//{
//	int done = FALSE;
//	//int drive = 0;
//	HANDLE hPhysicalDriveIOCTL = 0;
//	char driveName [256];
//	sprintf_s(driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);
//
//	//  Windows NT, Windows 2000, Windows XP - admin rights not required
//	hPhysicalDriveIOCTL = CreateFile (driveName, 0,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL);
//	if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
//	{
//	}
//	else
//	{
//		STORAGE_PROPERTY_QUERY query;
//		DWORD cbBytesReturned = 0;
//		char buffer [10000];
//
//		memset ((void *) & query, 0, sizeof (query));
//		query.PropertyId = StorageDeviceProperty;
//		query.QueryType = PropertyStandardQuery;
//
//		memset (buffer, 0, sizeof (buffer));
//
//
//		if ( DeviceIoControl (hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,& query,sizeof (query),& buffer,sizeof (buffer),& cbBytesReturned, (LPOVERLAPPED)NULL) )
//		{         
//			STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) & buffer;
//			char serialNumber [1000];
//			char modelNumber [1000];
//			char vendorId [1000];
//			char productRevision [1000];
//			flipAndCodeBytes2 (buffer, descrip -> VendorIdOffset,0, vendorId );
//			flipAndCodeBytes2 (buffer,descrip -> ProductIdOffset,0, modelNumber );
//			flipAndCodeBytes2 (buffer,descrip -> ProductRevisionOffset,0, productRevision );
//
//			flipAndCodeBytes2 (buffer,descrip -> SerialNumberOffset,1, serialNumber );
//
//			if (0 == SN [0] &&(isalnum (serialNumber [0]) || isalnum (serialNumber [19])))
//			{
//				strcpy (VI, vendorId);
//				strcpy (MN, modelNumber);
//				strcpy (SN, serialNumber);
//				strcpy (RN, productRevision);
//				done = TRUE;
//			}
//			memset (buffer, 0, sizeof(buffer));
//			if ( ! DeviceIoControl (hPhysicalDriveIOCTL,IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,NULL,0,&buffer,sizeof(buffer),&cbBytesReturned,NULL))
//			{
//
//			}
//			else
//			{         
//				DISK_GEOMETRY_EX* geom = (DISK_GEOMETRY_EX*) &buffer;
//				int fixed = (geom->Geometry.MediaType == FixedMedia);
//				__int64 size = geom->DiskSize.QuadPart;
//
//			}
//		}
//		else
//		{
//			DWORD err = GetLastError ();
//
//		}
//
//		CloseHandle (hPhysicalDriveIOCTL);
//	}
//
//	return done;
//}
//
//
//   // DoIDENTIFY
//   // FUNCTION: Send an IDENTIFY command to the drive
//   // bDriveNum = 0-3
//   // bIDCmd = IDE_ATA_IDENTIFY or IDE_ATAPI_IDENTIFY
//BOOL DiskInfo::DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,PDWORD lpcbBytesReturned)
//{
//      // Set up data structures for IDENTIFY command.
//   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
//   pSCIP -> irDriveRegs.bFeaturesReg = 0;
//   pSCIP -> irDriveRegs.bSectorCountReg = 1;
//   pSCIP -> irDriveRegs.bSectorNumberReg = 1;
//   pSCIP -> irDriveRegs.bCylLowReg = 0;
//   pSCIP -> irDriveRegs.bCylHighReg = 0;
//
//      // Compute the drive number.
//   pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);
//
//      // The command can either be IDE identify or ATAPI identify.
//   pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
//   pSCIP -> bDriveNumber = bDriveNum;
//   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
//
//   return ( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,(LPVOID) pSCIP,sizeof(SENDCMDINPARAMS) - 1,(LPVOID) pSCOP,sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,lpcbBytesReturned, NULL) );
//}
////  ---------------------------------------------------
//   // (* Output Bbuffer for the VxD (rt_IdeDinfo record) *)
//typedef struct _rt_IdeDInfo_
//{
//    BYTE IDEExists[4];
//    BYTE DiskExists[8];
//    WORD DisksRawInfo[8*256];
//} rt_IdeDInfo, *pt_IdeDInfo;
//
//
//   // (* IdeDinfo "data fields" *)
//typedef struct _rt_DiskInfo_
//{
//   BOOL DiskExists;
//   BOOL ATAdevice;
//   BOOL RemovableDevice;
//   WORD TotLogCyl;
//   WORD TotLogHeads;
//   WORD TotLogSPT;
//   char SerialNumber[20];
//   char FirmwareRevision[8];
//   char ModelNumber[40];
//   WORD CurLogCyl;
//   WORD CurLogHeads;
//   WORD CurLogSPT;
//} rt_DiskInfo;
//
//
//#define  m_cVxDFunctionIdesDInfo  1
//
////  ---------------------------------------------------
//
//int DiskInfo::DriveReadPort9x (void)
//{
//   int done = FALSE;
//   unsigned long int i = 0;
//
//   HANDLE VxDHandle = 0;
//   pt_IdeDInfo pOutBufVxD = 0;
//   DWORD lpBytesReturned = 0;
//
//   BOOL status = SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
//
//   rt_IdeDInfo info;
//   pOutBufVxD = &info;
//
//
//   ZeroMemory (&info, sizeof(info));
// 
//   VxDHandle = CreateFile ("\\\\.\\IDE21201.VXD", 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);
//
//   if (VxDHandle != INVALID_HANDLE_VALUE)
//   {
//      DeviceIoControl (VxDHandle, m_cVxDFunctionIdesDInfo,0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);
//      CloseHandle (VxDHandle);
//   }
//   else
//   for (i=0; i<8; i++)
//   {
//      if((pOutBufVxD->DiskExists[i]) && (pOutBufVxD->IDEExists[i/2]))
//      {
//			for (int j = 0; j < 256; j++) diskdata [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];
//			getIDEInfo();
//			done = TRUE;
//      }
//   }
//
//   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);
//
//   return done;
//}
//
//#define  SENDIDLENGTH  sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE
//
//
//int DiskInfo::DriveReadAsSCSI (void)
//{
//   int done = FALSE;
//   int controller = 0;
//
//   for (controller = 0; controller < 16; controller++)
//   {
//      HANDLE hScsiDriveIOCTL = 0;
//      TCHAR   driveName [256];
//
//      sprintf (driveName, "\\\\.\\Scsi%d:", controller);
//      //  Windows NT, Windows 2000
//      hScsiDriveIOCTL = CreateFile (driveName,GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL);
//
//      if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
//      {
//         int drive = 0;
//
//         for (drive = 0; drive < 2; drive++)
//         {
//            char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
//            SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
//            SENDCMDINPARAMS *pin =
//                   (SENDCMDINPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
//            DWORD dummy;
//   
//            memset (buffer, 0, sizeof (buffer));
//            p -> HeaderLength = sizeof (SRB_IO_CONTROL);
//            p -> Timeout = 10000;
//            p -> Length = SENDIDLENGTH;
//            p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
//            strncpy ((char *) p -> Signature, "SCSIDISK", 8);
//  
//            pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
//            pin -> bDriveNumber = drive;
//
//            if (DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
//                                 buffer,
//                                 sizeof (SRB_IO_CONTROL) +
//                                         sizeof (SENDCMDINPARAMS) - 1,
//                                 buffer,
//                                 sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
//                                 &dummy, NULL))
//            {
//               SENDCMDOUTPARAMS *pOut =
//                    (SENDCMDOUTPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
//               IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
//               if (pId -> sModelNumber [0])
//               {
//                  USHORT *pIdSector = (USHORT *) pId;
//                  for (int ii = 0; ii < 256; ii++) diskdata [ii] = pIdSector [ii];
//				  getIDEInfo();
//                  done = TRUE;
//               }
//            }
//         }
//         CloseHandle (hScsiDriveIOCTL);
//      }
//   }
//
//   return done;
//}
//
//char* DiskInfo::ModelNumber ()
//{
//	//return ConvertToString(diskdata, 27, 46);
//	return MN;
//}
//
//char* DiskInfo::SerialNumber ()
//{
//	//return ConvertToString(diskdata, 10, 19);
//	return SN;
//}
//
//char* DiskInfo::RevisionNumber ()
//{
//	//return ConvertToString(diskdata, 23, 26);
//	return RN;
//}
//
//char* DiskInfo::DriveType ()
//{
//   if (diskdata[0] & 0x0080)
//      return "Removable";
//   else if (diskdata[0] & 0x0040)
//      return "Fixed";
//   else return "Unknown";
//}
//
//
//
//char * DiskInfo::ConvertToString (DWORD diskdatax [256], int firstIndex, int lastIndex)
//{
//   char string [1024];
//   int index = 0;
//   int position = 0;
//
//   for (index = firstIndex; index <= lastIndex; index++)
//   {
//      string [position] = (unsigned char) (diskdatax [index] / 256);
//      position++;
//
//      string [position] = (unsigned char) (diskdatax [index] % 256);
//      position++;
//   }
//   string [position] = '\0';
//   
//   for (index = position - 1; index > 0 && isspace(string [index]); index--)
//      string [index] = '\0';
//   
//   return string;
//}
//
//unsigned __int64 DiskInfo::DriveSize ()
//{
//	unsigned __int64 bytes = 0,sectors =0;
//	if (diskdata [83] & 0x400) 
//		sectors = diskdata[103] * 65536I64 * 65536I64 * 65536I64 + 
//					diskdata[102] * 65536I64 * 65536I64 + 
//					diskdata[101] * 65536I64 + 
//					diskdata[100];
//	else
//		sectors = diskdata[61] * 65536 +diskdata[60];
//		//  there are 512 bytes in a sector
//		bytes = sectors * 512;
//	return bytes;
//}
//
//DiskInfo::DiskInfo(UINT driveNum)
//{
//	//m_DriveCount = 0;
//	uDriveNum = driveNum;
//}
//
//DiskInfo::~DiskInfo(void)
//{
//}
//
//long DiskInfo::LoadDiskInfo ()
//{
//	int done = FALSE;
//	__int64 id = 0;
//	OSVERSIONINFO version;
//	memset (&version, 0, sizeof (version));
//	version.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
//	GetVersionEx (&version);
//	if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
//	{
//		if (!done)
//		{
//			printf("\nTes 1. Admin: ");//
//			done = DriveReadAdmin ();
//		}
//		//  this should work in WinNT or Win2K if previous did not work
//		//  this is kind of a backdoor via the SCSI mini port driver into
//		//     the IDE drives
//		
//		if (!done)
//		{
//			printf("FAILED.\n");//
//			printf("\nTes 2. SCSI: ");//
//			done = DriveReadAsSCSI ();
//		}
//		//this works under WinNT4 or Win2K or WinXP if you have any rights
//		
//		if (!done) 
//		{
//			printf("FAILED.\n");//
//			printf("\nTes 3. No Admin/XP :");//
//			done = DriveReadNoAdmin ();
//		}
//		if (!done)
//		{
//			printf("FAILED.\n");//
//			printf("\nTes 4. Smart :");//
//			done = DriveReadSMART();
//			if (!done) printf("FAILED.");//
//		}
//	}
//	else
//	{
//		int attempt = 0;
//		for (attempt = 0;
//			attempt < 10 && !done ;
//			attempt++)
//			done = DriveReadPort9x ();
//	}
//	return (long) done;
//}
//
//UINT DiskInfo::BufferSize ()
//{
//	return diskdata[21] * 512;
//}

void PactJumper(DWORD Base,DWORD Ofs1, BYTE Value){
DWORD Temp=NULL;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
*(PBYTE)Temp=Value;
}
}
}



/*CNames	*oNames(UINT i)
{
return (CNames*)((CGameContextPointer()+ResultName)+i * 0x21);
}

#define   RainbowTextTest     D3DCOLOR_ARGB(255,RainbowR,RainbowG, RainbowB)*/
//------------------------------------------------------------------------------	