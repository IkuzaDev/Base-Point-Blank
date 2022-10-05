//int Drawing			= 0;
//int Mpos			= 0;
//int Mmax			= 0;
//int DrawFont		= 1;
//int Mvisible		= 1;
//int Mysize			= 17;
//int Mxofs			= 165;
//int my				= 60;
//int	mx				= 150;


//int MenuFolder[100];
//int Drawing		= 0;
//int Mpos		= 0;	
//int Mmax		= 0;
//int DrawFont	= 1;
//int Mvisible	= 1;
//int	Mxofs		= 235; // Lebar Menu //
//int	Mysize      = 17;  // Mengatur Bawah Menu //
//int my			= 30;  // Up Down //
//int	mx			= 10;  // Right Left //
////int	Mxofs		= 150; // Lebar Menu //
////int	Mysize      = 18;  // Mengatur Bawah Menu //
//int ShowMenu = 1;
//char Mtitle[81]	= "";

int MenuFolder[100];
int Drawing		= 0;
int Mpos		= 0;	
int Mmax		= 0;
int DrawFont	= 1;
int Mvisible	= 1;
int Mxofs		= 25.0f;
int Mysize		= 15.0f;
int my			= 40; // Up Down
int	mx			= 140; // Right Left
char Mtitle[81]	= "";
#define MENUMAXINDEX	100
#define MENUFOLDER		1
#define MENUTEXT		2
#define HEADER			1
#define MENUITEM		3
#define	MENUCAT			4

//#define	MCOLOR_HEADER	RED
//#define	MCOLOR_CURRENT	ORANGE
//#define	MCOLOR_FOLDER	YELLOW
//#define	MCOLOR_TEXT		SKYBLUE
//#define	MCOLOR_INACTIVE	WHITE
//#define	MCOLOR_ACTIVE	GREEN
//#define MCOLOR_TITLE	RED

//#define			MCOLOR_TITLE	(RED)
//#define			MCOLOR_CURRENT	D3DCOLOR_ARGB(255, 000, 000, 255)//red
//#define			MCOLOR_FOLDER	(YELLOW)
//#define			MCOLOR_TEXT		(BLUE)
//#define			MCOLOR_INACTIVE	(GREEN)
//#define			MCOLOR_ACTIVE	(ORANGE)

#define			COLORFOLDER		D3DCOLOR_ARGB(255, 255, 255, 000)
#define			COLORTEXT		D3DCOLOR_ARGB(255, 255, 125, 000)
#define			COLORON			D3DCOLOR_ARGB(255, 000, 255, 000)
#define			COLOROFF		D3DCOLOR_ARGB(255, 245, 000, 000)
#define			COLORCURENT		D3DCOLOR_ARGB(255, 125, 160, 200)
//------------------------------

struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}
D3MENU[MENUMAXINDEX];
void AddItem(char *txt, char **opt, int *var, int maxvalue, int typ)
{
	D3MENU[Mmax].typ=typ;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=opt;
	D3MENU[Mmax].var=var;
	D3MENU[Mmax].maxvalue=maxvalue;
	Mmax++;
}

void AddText(char *txt, char *opt)
{
	D3MENU[Mmax].typ=MENUTEXT;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=(char **)opt;
	D3MENU[Mmax].var=0;
	D3MENU[Mmax].maxvalue=0;
	Mmax++;
}




#define cCallHeader /*Hooked*/XorStr<0x5F,20,0x42E2A6B8>("\x7F\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x2C\x0E\x0E\x1F\x07\x35\x19\x01"+0x42E2A6B8).s


void DrawTextL(int x,int y,DWORD color,char *text)
{
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
void DrawTextR(int x,int y,DWORD color,char *text)
{
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
struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};
D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
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
//-------------------------------------------------------------------------------
#define PISSS 3.14159265
void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice)
{
	const int NUMPOINTS = 34;

	if(!center)
	{
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
	for( i=0; i<=NUMPOINTS; i++ )
	{
		Theta = i * WedgeAngle;
		X = (float)( x + rad * cos(Theta) );
		Y = (float)( y - rad * sin(Theta) );
		Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
	}
	pDevice	->	SetFVF			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	pDevice	->	SetTexture		( 0, NULL );
	pDevice	->	DrawPrimitiveUP	( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}
//-------------------------------------------------------------------------------
VOID FillGradients(int x, int y, int h, int w, DWORD color1, DWORD color2, LPDIRECT3DDEVICE9 pDevice)
{
float alpha = 5;
     float step;
	DWORD r1 = (color1>>16)&0xff;
	DWORD g1 = (color1>>8)&0xff;
	DWORD b1 = (color1)&0xff;
	DWORD r2 = (color2>>16)&0xff;
	DWORD g2 = (color2>>8)&0xff;
	DWORD b2 = (color2)&0xff;
	float /*aDif,*/rDif,gDif,bDif;
	rDif = ((float)r2-(float)r1)/h;
	gDif = ((float)g2-(int)g1)/h;
	bDif = ((float)b2-(float)b1)/h;
	DWORD DrawCol;
	 step  = ((255 - alpha) / h);
	for(int i = 0;i<h;i++)
	{
	alpha = alpha + step;
		DrawCol = (r1+(int)(rDif * i) << 16) | (g1+(int)(gDif * i) << 8) | (b1+(int)(bDif*i));
		FillRGB(x,y+i,w,1,DrawCol, pDevice);
	}
}
void DrawBox12(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
} 
void  DrawBox13(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
/*------------------------------------------- Declaration DrawBorder ------------------------------------------------------*/
void DrawBorder12(int x, int y, int w, int h, int px,D3DCOLOR col ,LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x,(y + h - px), w, px,col);
	DrawBox12(pDevice,x, y, px, h,col);
	DrawBox12(pDevice,x, y, w, px,col);
	DrawBox12(pDevice,(x + w - px), y, px, h,col);


/*------------------------------------------- Declaration DrawBorder ------------------------------------------------------*/

	DrawBox12(pDevice,x,(y + h - px), w, px+1,col);
	DrawBox12(pDevice,x, y, px+1, h+1,col);
	//DrawBox12(pDevice,x+px, y, w, px,col);// ini ori
	DrawBox12(pDevice,(x + w - px), y, px+1, h+1,col);
}
void  DrawBorder13(int x, int y, int w, int h, int px,D3DCOLOR col ,LPDIRECT3DDEVICE9 pDevice)
{
DrawBox13(pDevice,x+px,y+h-px,w-px-px,px,col);// Bottom
DrawBox13(pDevice,x,y,px,h,col); // Left
//DrawBox13(pDevice,x+px,y,w-px-px,px,col); // TOP
DrawBox13(pDevice,x+w-px,y,px,h,col); // RIGHT
}

/*------------------------------------------- Declaration DrawBorder ------------------------------------------------------*/
//void DrawBorder12(int x, int y, int w, int h, int px,D3DCOLOR col ,LPDIRECT3DDEVICE9 pDevice)
//{
//	DrawBox12(pDevice,x+px,y+h-px,w-px-px,px,col);
//	DrawBox12(pDevice,x,y,px,h,col);
//	DrawBox12(pDevice,x+px,y,w-px-px,px,col);
//	DrawBox12(pDevice,x+w-px,y,px,h,col);
//}
/*------------------------------------------- Declaration DrawMenu ------------------------------------------------------*/
void DrawMenu12(int x, int y, int w, int h, int px,D3DCOLOR col1,D3DCOLOR col2, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x,y,w,h,col1);
    DrawBorder12 ( x,y,w,h,px,col2,pDevice);
}
void  DrawMenu13(int x, int y, int w, int h, int px,D3DCOLOR col1,D3DCOLOR col2, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox13(pDevice,x,y,w,h,col1);
    DrawBorder13 ( x,y,w,h,px,col2,pDevice);
}
void  DrawMenu11(int x, int y, int w, int h, int px,D3DCOLOR col1,D3DCOLOR col2, LPDIRECT3DDEVICE9 pDevice)
{
	//DrawBox12(pDevice,x,y,w,h,col1);
    DrawBorder12 ( x,y,w,h,px,col2,pDevice);
}

VOID __stdcall CMenuItem_DrawCronersBox(INT xx,INT yy,INT hh,INT ww,LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec;
	FLOAT x,y,w,h;
	    
	struct vertex 
	{
		FLOAT x,y,z,t;
		DWORD Color;
	};

	vertex V[8];

	x = (float)xx; y = (float)yy; h = (float)hh; w = (float)ww;

	V[0].Color = V[1].Color = V[2].Color = V[3].Color = BLACK;
	V[4].Color = V[5].Color = V[6].Color = V[7].Color = BLACK;

	V[0].z  = V[1].z = V[2].z  = V[3].z  = 0;
	V[4].z  = V[5].z = V[6].z  = V[7].z  = 0;
	V[0].t  = V[1].t = V[2].t  = V[3].t  = 0;
	V[4].t  = V[5].t = V[6].t  = V[7].t  = 0;

	V[0].x = V[1].x = x;
	V[0].y = V[2].y = y + h;
	V[1].y = V[3].y = y;
	V[2].x = V[3].x = x + w;
	V[4].x = V[5].x = x;
	V[4].y = V[6].y = y + h;
	V[5].y = V[7].y = y;
	V[6].x = V[7].x = x + w;

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader( NULL );
	pDevice->SetRenderState(D3DRS_CLIPPING,FALSE); 
	pDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,2,V,sizeof(vertex));

	rec.x1 = xx;rec.y1 = yy;rec.x2 = xx+ww;rec.y2 = yy+1;
	pDevice->Clear(1,&rec,D3DCLEAR_TARGET,WHITE,0,0);
	rec.x1 = xx;rec.y1 = hh+yy;rec.x2 = xx+ww;rec.y2 = hh+yy+1;
	pDevice->Clear(1,&rec,D3DCLEAR_TARGET,WHITE,0,0);
	rec.x1 = xx;rec.y1 = yy;rec.x2 = xx+1;rec.y2 = yy+hh;
	pDevice->Clear(1,&rec,D3DCLEAR_TARGET,WHITE,0,0);
	rec.x1 = xx+ww;rec.y1 = yy;rec.x2 = xx+ww+1;rec.y2 = yy+hh;
	pDevice->Clear(1,&rec,D3DCLEAR_TARGET,WHITE,0,0);

	return;
}
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	DWORD texty;
	char text[100];
	if (!Mvisible) return;
	for (i=0; i<Mmax; i++) 
	{
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		sprintf(text, "%s", D3MENU[i].txt);
		if (i==Mpos){
			if(RainbowTexts!=100)
			{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
			if(RainbowTexts!=255)
			{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
			color=RainbowTextTest;
			texty=RainbowTextTest;
			sprintf(text, "~> %s", D3MENU[i].txt);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=COLORFOLDER;
			texty=COLORFOLDER;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=COLORTEXT;
			texty=COLORTEXT;
		}
		else{
			color=(val)?COLORON:COLOROFF;
			texty=(val)?COLORCURENT:COLORCURENT;
		}
		if (D3MENU[i].opt)
		{
			if (D3MENU[i].typ==MENUITEM){
				DrawTextL(x+3, y, texty,text);
				y = y + 2;
			}else{
				DrawTextL(x+3, y, texty,text);
			}
		}
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt);
			else
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt[val]);
		}
		y+=Mysize;
	}
}
#define BlueNEW	D3DCOLOR_ARGB(00, 000, 000, 100)
//void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
//{
//	int i, val;
//	DWORD color;
//	SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
//	if (!Mvisible) return;
//	if (Mtitle[0]) 
//	{
//		DrawMenu13(x-2, y-2, 242/*<wigth*/, 19/*<heigt*/, 1, WHITE, SKYBLUE, pDevice);// Warna dan lebar tinggi line
//		pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_CENTER, RainbowTextTest);
//		y+=Mysize;
//	}
//	for (i=0; i<Mmax; i++) 
//	{
//		DrawMenu13(x-2, y-2, 242/*<wigth*/, 18/*<heigt*/, 1, TransBlack2, SKYBLUE, pDevice);// Warna dan tinggi line
//		//DrawMenu13(x+Mxofs-170, y-2, Mxofs+38, Mysize+2, 2,dBlack,GREEN , pDevice);
//		val=(D3MENU[i].var)?(*D3MENU[i].var):0;// determine color
//		if (i==Mpos){
//		//	DrawMenu11(x+Mxofs-240, y, Mxofs+5, 15, 2,color,WHITE , pDevice);//select
//			DrawMenu11(x+Mxofs-238, y, Mxofs+5, 15, 2,color,WHITE , pDevice);//select
//		}
//		else if (D3MENU[i].typ==MENUFOLDER){
//			color=MCOLOR_FOLDER;
//		}
//		else if (D3MENU[i].typ==MENUTEXT){
//			color=MCOLOR_TEXT;
//		}
//		else
//			color=(val)?SKYBLUE:WHITE;
//		SetRect( &rect3, x, y, x , y );
//		SetRect( &rect2, x+Mxofs, y, x+Mxofs , y );
//		pFont->DrawText(NULL,D3MENU[i].txt,-1,&rect3, DT_NOCLIP,color);
//		if (D3MENU[i].opt) {
//			if (D3MENU[i].typ==MENUTEXT)
//				pFont->DrawText(NULL,(char *)D3MENU[i].opt,-1,&rect2, DT_NOCLIP | DT_RIGHT, color);
//			else
//				pFont->DrawText(NULL,(char *)D3MENU[i].opt[val],-1,&rect2, DT_NOCLIP | DT_RIGHT, color);
//
//		}
//		y+=Mysize;
//	}
//   	if (Mtitle[0]) 
//	{
//		//DrawMenu12(x-1, y+4, 242/*<wigth*/, 18/*<heigt*/, 1, WHITE, WHITE, pDevice);// Warna dan lebar tinggi line
//		pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_CENTER, MCOLOR_TITLE);
//		y+=Mysize;
//	}
//}
char* cDATE(void)
{
	struct tm * current_tm;
	time_t current_time;time (&current_time);
	current_tm = localtime (&current_time);
	char *month	[]={"Jan.","Feb.","Mar.","Apr.","May","June","July","Aug.","Sept.","Oct.","Nov.","Dec."};
	char *logbuf = new char[ 256 ];
	sprintf( logbuf, "%s %02d, 20%d",month[current_tm->tm_mon],current_tm->tm_mday,current_tm->tm_year-100);
	return logbuf;
}
char* cTIME(void)
{
	static char ctime[20] = "" ;
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	if(current_tm->tm_hour>12)
		sprintf( ctime, "%d:%02d:%02d PM", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec );
	else
		sprintf( ctime, "%d:%02d:%02d AM", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return ctime;
}

int MoveD3D9;
void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1){
		Mvisible=(!Mvisible);
	}
	if (!Mvisible) return;
	if(MoveD3D9 && GetAsyncKeyState(VK_LCONTROL))
	{
		POINT Mpos;
		GetCursorPos(&Mpos);
		ScreenToClient(GetForegroundWindow(), &Mpos);
		mx = Mpos.x;
		my = Mpos.y+2;
	}
	if (IsKeyPressed(VK_UP, 0)&1)
	{
		do{
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		}
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}
	else if (IsKeyPressed(VK_DOWN, 0)&1)
	{
		do{
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
		}
		while (D3MENU[Mpos].typ==MENUTEXT);		
	}
	else if (D3MENU[Mpos].var)
	{
		int dir=0;
		if((IsKeyPressed(VK_LEFT, 0)&1) && *D3MENU[Mpos].var > 0) dir=-1;
		if((IsKeyPressed(VK_RIGHT, 0)&1) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if(dir)
		{
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}
char *Moptfolder          []   = {"Open", "Close"}; 
char *Moptonoff           []   = {"Off", "On"};
char *Moptmulty		[]	= {"Off", "50%", "100%"};
char *Moptmd3d9		[]	= {"Off", " Press L-CTRL"};
char *Moptbullet	[]	= {"Head", " Body"};
char *Moptspeed	[]	= {" •", " 1x", " 2x","3x","4x","5x","6x","7x","8x","9x","10"};
char *MoptKeys              []   = {" •","Auto", "L-Click", "R-Click", "Ctrl", "Shift", "Alt"};
char *MoptBrust              []   = { " •","5", "10", "25", "50", "100"};
int HACK;
int ESP;
int PLAYER;
int WEAPON;
int AIM;
int GB;
int INFORMATION;
int HS;

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	//AddItem("Menu Information", Moptfolder, &INFORMATION, 2, MENUFOLDER);
	 //if(INFORMATION)
	// {
	// }
//	AddText("[ Waktu   :", cTIME());

//	AddText("[ Tanggal :", cDATE());
	//strcpy(Mtitle,"");
	AddText("FebriZip.net","Point Blank Beyond Limits");
	AddItem("[Visual Hack]", Moptfolder, &HACK, 2, MENUFOLDER);
	if(HACK)
	{
		//AddItem("[<->]Move D3D9", Moptmd3d9, &MoveD3D9, 2, MENUCAT);
		AddItem("CrossHair", Moptonoff, &Cross, 2, MENUCAT);
		AddItem("ESP Bone", Moptonoff, &Skeleto, 2, MENUCAT);
		AddItem("ESP Box ", Moptonoff, &Box3s, 2, MENUCAT);
		AddItem("ESP Line", Moptonoff, &Linia, 2, MENUCAT);
		AddItem("ESP Name", Moptonoff, &Espname, 2, MENUCAT);
		AddItem("ESP Distance", Moptonoff, &EspDistance, 2, MENUCAT);
	//	AddItem("[<->]ESP Vicible", Moptonoff, &Visible, 2, MENUCAT);
	//	AddItem("[<->]ESP Spanw", Moptonoff, &Spanw, 2, MENUCAT);
	}
AddItem("[Aim Hack]", Moptfolder, &AIM, 2, MENUFOLDER);
	if(AIM)
	{
		AddItem("Aim Bot", Moptonoff, &AimBot, 2,MENUCAT);
		AddItem("Target", Moptbullet, &TargetLock, 2,MENUCAT);
		/*if(AimBot)
		{
		AddItem("[<->]Target Lock", Moptbullet, &TargetLock, 3,MENUCAT);
		}
		AddItem("[<->]Aim Bone", Moptonoff, &AimBone, 2,MENUCAT);
		AddItem("[<->]Aim Bot Keys", MoptKeys,&AimKey			, 6,  MENUCAT);
		AddItem("[<->]Aim Target", Moptonoff, &Target, 2,MENUCAT);
		AddItem("[<->]Aim Vischeck", Moptonoff, &AimVischeck, 2,MENUCAT);
		AddItem("[<->]Hotkey Mode", Moptonoff, &Mode, 2,MENUCAT);*/
	}
	//AddItem("[ Auto HS Hacks", Moptfolder, &HS, 2, MENUFOLDER);
	//if(HS)
	//{
	//	AddItem("[<->]Fast Shot", Moptonoff, &FastShoot, 2,MENUCAT);
	////	AddItem("[<->]Auto HS", Moptonoff, &AutoHeadshot, 2,MENUCAT);
	////	AddItem("[<->]Auto Shot", Moptonoff, &AutoShot, 2,MENUCAT);
	//}
	AddItem("[Waepon Hack]", Moptfolder, &PLAYER, 2, MENUFOLDER);
	if(PLAYER)
	{
		//AddItem("Aim Bot", Moptonoff, &AimBot, 2,MENUCAT);
		//AddItem("Target", Moptbullet, &TargetLock, 2,MENUCAT);
		//AddItem("Speed Hack", Moptonoff, &agilidadfunc, 2,MENUCAT);	
	//	AddItem("NoFalldamge", Moptonoff, &fallfunc, 2, MENUCAT);
		AddItem("Fast Respawn", Moptmulty, &RespawnFunc, 3, MENUCAT);
		AddItem("Quick Change", Moptmulty, &FastSwith, 3, MENUCAT);
		AddItem("Quick Reload", Moptmulty, &Reloadnew, 3, MENUCAT);
	}
	//AddItem("[ Weapon Hacks", Moptfolder, &WEAPON, 2, MENUFOLDER);
	if(WEAPON)
	{
	//	AddItem("• No Recoil V", Moptonoff, &NoRecoil, 2, MENUCAT);
		////AddItem("• No Recoil H", Moptonoff, &NoRecoil1, 2, MENUCAT);
		//AddItem("• Auto Macro", Moptonoff, &macro, 2, MENUCAT);
	   // AddItem("• Quick Change", Moptmulty, &FastSwith, 3, MENUCAT);
	   // AddItem("• Quick Reload", Moptmulty, &Reloadnew, 3, MENUCAT);
	//	//AddItem("[<->]Fast Knife", Moptonoff, &MultiSnife, 2, MENUCAT);
	//	//AddItem("[<->]Set  Brust", MoptBrust, &SetBrust, 2, MENUCAT);
	}
	//AddItem("AutoGB Hack", Moptfolder, &GB, 2, MENUFOLDER);
	if(GB)
	{
		AddItem("Auto Ready"			    , Moptonoff,  &AutoReady				, 3,  MENUCAT);
		AddItem("Auto Bundir"			, Moptonoff,  &AutoBundi				, 3,  MENUCAT);
	}
}
void DrawDirect3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1) 
	{
		D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Franklin Ghoti", &pFont);
		D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghoti", &pFont);
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Franklin Ghoti", &g_pFont);
//		D3DXCreateFontA(pDevice, 14, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &mFont);
		//D3DXCreateFontA(pDevice, 13, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Time New Roman", &pFont2 );
		//D3DXCreateFontA(pDevice, 13, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fName);
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Franklin Ghoti", &g_pFont);
//		D3DXCreateLine(pDevice,&g_pLine);
		D3DXCreateSprite(pDevice, &textSprite);
		DrawFont = 0;
	}
}

void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (Drawing == 0)
	{
		if(Mmax==0) 
		RebuildMenu(pDevice);
		MenuShow(mx,my,pDevice);
		MenuNav();
	}
}
