/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
class GM;
class PlayerInfo;
class RenderContext;
class RenderData;
class CGameBase;
class CBonesContext;
class CBone;
class cGameStageInfo;
//-------------------------------------------------------------------------------//
LPD3DXFONT pFonts;
DWORD dwGFX			= (DWORD)GetModuleHandle("i3GfxDx.dll");
RenderContext *pRC	= (RenderContext*)(dwGFX + HookBaseRender);
//-------------------------------------------------------------------------------//
class RenderData{
public:
char _0x0000[32];
D3DXMATRIX ViewMatrix;
D3DXMATRIX ProjMatrix;
char _0x00A0[4800];
D3DXMATRIX World;
};
//-------------------------------------------------------------------------------//
class RenderContext{
public:
RenderData* pRenderData; 
char unknown4[912];
D3DXVECTOR3 bone;
D3DXVECTOR3 bone1;
D3DXVECTOR3 bone2;
};
//-------------------------------------------------------------------------------//
extern RenderContext *pRC;
//-------------------------------------------------------------------------------//
class CBone{
public:
D3DXMATRIX BoneMatrix;
};
//-------------------------------------------------------------------------------//
class CBonesContext{
public:
char   Unk[0xD8];
CBone* BoneData;
};
//-------------------------------------------------------------------------------//
struct D3DTLVERTEX{
float fX;
float fY;
float fZ;
float fRHW;
D3DCOLOR Color;
float fU;
float fV;
};
//-------------------------------------------------------------------------------//
class CGameBase{
public:
char Unk[0x558];
CBonesContext* Bones;
};
//-------------------------------------------------------------------------------//
struct CHealth{
float CurHP;
};
//-------------------------------------------------------------------------------//
struct CPlayers{
float yaw;
float pitch;
D3DXVECTOR3 pos;
char unkno8[2304];
};
//-------------------------------------------------------------------------------//
class Bone{
public:
D3DXMATRIX m_Bone;
};
//-------------------------------------------------------------------------------//
struct CRank{
BYTE iRank;
};
//-------------------------------------------------------------------------------//
struct CNames{
char szNames[33];
};
//-------------------------------------------------------------------------------//
class GM;
class GM{
public:
BYTE iRank;
char _0x0001[15];
WORD iHack;
};
//-------------------------------------------------------------------------------//
struct CTeam{
BYTE iTeam;
};
//-------------------------------------------------------------------------------//
class CLog;
class CLog{
public:
BYTE iLog;
};
//-------------------------------------------------------------------------------//
class CNick{
public:
BYTE bVal;
};
//-------------------------------------------------------------------------------//
class Gendeng{
public:
DWORD Module;
};
//-------------------------------------------------------------------------------//
class CDWORD{
public:
DWORD dwRes;
};
//-------------------------------------------------------------------------------//
class CWORD{
public:
WORD wRes;
};
//-------------------------------------------------------------------------------//
class CBYTE{
public:
BYTE bRes;
};
//-------------------------------------------------------------------------------//
class CSlotz;
class CSlotz{
public:
DWORD Host;
DWORD Slot;
};
//-------------------------------------------------------------------------------//
class HackName{
public:
DWORD iName1;
};
//-------------------------------------------------------------------------------//
class HackName2{
public:
DWORD iName2;
};
//-------------------------------------------------------------------------------//
class HackName3{
public:
DWORD iName3;
};
//-------------------------------------------------------------------------------//
class HackName4{
public:
DWORD iName4;
};
//-------------------------------------------------------------------------------//
class cGameStageInfo{
public:
char _pad1[0x230];
D3DXVECTOR3 BombPositionA; 
D3DXVECTOR3 BombPositionB;
char _pad2[0x248];
float BombFloorOnMiniMap_A;
float BombFloorOnMiniMap_B;
};
//-------------------------------------------------------------------------------//
class cGameBases{
public:
char _pad1[0x3C1E8];
cGameStageInfo* StageInfo;
};
//-------------------------------------------------------------------------------//
class CDeathPlayer{
public:
BYTE Death[16];
};
//-------------------------------------------------------------------------------//
class CLocalPlayerID{
public:
BYTE ID;
};
//-------------------------------------------------------------------------------//
class CGameCharaBoneContext{
public:
char nop[0xD8];
Bone* m_Bone;
};
//-------------------------------------------------------------------------------//
class CGameCharaBase{
public:
char nop[0x558];
CGameCharaBoneContext* m_BoneContext;
};
//-------------------------------------------------------------------------------//
DWORD CGameContextPointer(void) {
unsigned long dwBase = *(DWORD*)ResultBasePlayer2;
return dwBase;
}
//-------------------------------------------------------------------------------//
CNames		*oNames(UINT i)	{
return (CNames*)((CGameContextPointer() + ResultName) + i * ResultNAMESIZE);
}
//-------------------------------------------------------------------------------//
CLog		*pPing(UINT i)	{
return (CLog*)((CGameContextPointer() + ResultPing) + i * 1);
}