/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------- Source Code Base Edition By Fahmi Santoso --------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include <windows.h>
/*-------------------------------------------------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
LPDIRECT3DTEXTURE9 Red,Green,texRed,texBlue,texGreen,texPink,texOrange = NULL;
/*-------------------------------------------------------------------------------------------------------------------*/
#define bodyred (((primCount==520&&NumVertices==348)||(primCount==346&&NumVertices==384)||(primCount==304&&NumVertices==472)||(primCount==590&&NumVertices==596)||((primCount==485||primCount==1737||primCount==1766)&&NumVertices==3487)||(primCount==157&&NumVertices==201)||(primCount==200&&NumVertices==224)||(primCount==166)||((primCount==1404)&&NumVertices==1353)||(NumVertices==92)||(primCount==84&&NumVertices==108)||(primCount==64&&NumVertices==114)||((primCount==114||primCount==526)&&NumVertices==611)))
// Keen Eyes
#define bodyayse (((primCount==270&&NumVertices==366)||((primCount==660||primCount==987||primCount==2442)&&NumVertices==4705)||(primCount==102&&NumVertices==141)||(primCount==1387&&NumVertices==1184)||(NumVertices==85)||(primCount==504&&NumVertices==490)))
// Tarantula
#define bodytar (((primCount==1344&&NumVertices==2728)||(primCount==406&&NumVertices==244)||(primCount==540&&NumVertices==528)||(primCount==1390&&NumVertices==1091)||(primCount==1460&&NumVertices==1095)||((primCount==414||primCount==2090)&&NumVertices==1846)||(primCount==128&&NumVertices==142)||(primCount==136&&NumVertices==90)||(primCount==322&&NumVertices==218)||((primCount==134||primCount==1574)&&NumVertices==1316)||(primCount==20&&NumVertices==26)||(primCount==52&&NumVertices==80)||(primCount==139&&NumVertices==113)||((primCount==44||primCount==740)&&NumVertices==684)))
// CT Hide
#define bodyhide (((primCount==150&&NumVertices==101)||(primCount==320&&NumVertices==307)||(primCount==400&&NumVertices==324)||(primCount==1494&&NumVertices==854)||(primCount==1946&&NumVertices==1619)||((primCount==254||primCount==320||primCount==3152)&&NumVertices==3796)||(primCount==102&&NumVertices==128)||(primCount==138&&NumVertices==158)||(primCount==373&&NumVertices==227)||(primCount==706&&NumVertices==654)||(primCount==1154&&NumVertices==998)||(NumVertices==78)||(primCount==78&&NumVertices==86)||(primCount==185&&NumVertices==125)||(primCount==240&&NumVertices==221)||(primCount==592&&NumVertices==520)))
// Viper Red
#define bodyviper (((primCount==66&&NumVertices==74)||(primCount==78&&NumVertices==71)||(primCount==254&&NumVertices==185)||(primCount==738&&NumVertices==934)||(primCount==1534&&NumVertices==1530)||(primCount==1561&&NumVertices==2041)||((primCount==278||primCount==341||primCount==1267)&&NumVertices==1831)||(primCount==30&&NumVertices==41)||(primCount==32&&NumVertices==35)||(primCount==67&&NumVertices==62)||(primCount==80&&NumVertices==114)||(primCount==95&&NumVertices==144)||(primCount==337&&NumVertices==516)||(primCount==395&&NumVertices==237)||(primCount==716&&NumVertices==647)||(primCount==936&&NumVertices==727)||(primCount==12&&NumVertices==18)||(primCount==13&&NumVertices==23)||(primCount==32&&NumVertices==66)||(primCount==38&&NumVertices==41)||(primCount==61&&NumVertices==99)||(primCount==276&&NumVertices==245)||(primCount==487&&NumVertices==398)))
// D-Fox
#define bodydfox (((primCount==76&&NumVertices==92)||(primCount==278&&NumVertices==370)||(primCount==390&&NumVertices==482)||(primCount==688&&NumVertices==734)||(primCount==1246&&NumVertices==812)||(primCount==1326&&NumVertices==1089)||((primCount==45||primCount==1023||primCount==1434)&&NumVertices==2263)||(primCount==40&&NumVertices==92)||(primCount==120&&NumVertices==165)||(primCount==158&&NumVertices==246)||(primCount==324&&NumVertices==381)||(primCount==700&&NumVertices==547)||((primCount==41||primCount==402||primCount==749)&&NumVertices==1348)||(primCount==20&&NumVertices==32)||(primCount==38&&NumVertices==71)||(primCount==86&&NumVertices==122)||(primCount==109&&NumVertices==195)||(primCount==360&&NumVertices==334)||((primCount==27||primCount==32||primCount==35||primCount==42||primCount==46||primCount==121||primCount==241)&&NumVertices==1204)))
// Leopard
#define bodyleo (((NumVertices==154&&primCount==114)||(NumVertices==338&&primCount==434)||(NumVertices==661&&primCount==664)||(NumVertices==1053&&primCount==1722)||((primCount==263||primCount==312||primCount==529||primCount==574||primCount==1132)&&NumVertices==3770)))
// Acid Pool
#define bodyacid (((NumVertices==40&&primCount==50)||(NumVertices==354&&primCount==270)||(NumVertices==988&&primCount==708)||(NumVertices==1253&&primCount==1660)||(NumVertices==3155&&(primCount==1134||primCount==1678))||(NumVertices==10&&primCount==10)||(NumVertices==134&&primCount==90)||(NumVertices==307&&primCount==183)||(NumVertices==595&&primCount==752)||(NumVertices==793&&primCount==885)||(NumVertices==68&&primCount==42)||(NumVertices==167&&primCount==100)||(NumVertices==223&&primCount==246)||(NumVertices==361&&primCount==406)))
// Rica
#define bodyr (((primCount==122&&NumVertices==65)||(primCount==186&&NumVertices==150)||(primCount==830&&NumVertices==650)||(primCount==1626&&NumVertices==923)||((primCount==523||primCount==1280||primCount==1502||primCount==1743)&&NumVertices==3952)||(primCount==44&&NumVertices==26)||(primCount==144&&NumVertices==124)||(primCount==504&&NumVertices==421)||(primCount==890&&NumVertices==549)||((primCount==895||primCount==1398)&&NumVertices==2197)||(primCount==8&&NumVertices==6)||(primCount==57&&NumVertices==68)||(primCount==116&&NumVertices==117)||(primCount==433&&NumVertices==257)||(primCount==437&&NumVertices==367)||((primCount==369||primCount==866)&&NumVertices==1271)))
// Helm
#define helmred (Stride==40&&((primCount==266&&NumVertices==142)||(primCount==120&&NumVertices==71)||(primCount==56&&NumVertices==45)))
#define hacidayse (Stride==32&&((primCount==52&&NumVertices==38)||(primCount==648&&NumVertices==638)||(primCount==212&&NumVertices==198)||(primCount==102&&NumVertices==95)))
#define helmtar (Stride==32&&((primCount==338&&NumVertices==224)||(primCount==170&&NumVertices==128)||(primCount==84&&NumVertices==67)))
#define helmhid (Stride==32&&((primCount==218&&NumVertices==186)||(primCount==150&&NumVertices==133)||(primCount==80&&NumVertices==70)))
#define helmvip (Stride==32&&((primCount==240&&NumVertices==184)||(primCount==42&&NumVertices==51)))
#define helmfox (Stride==32&&((primCount==242&&NumVertices==196)||(primCount==112&&NumVertices==73)||(primCount==54&&NumVertices==40)))
#define helmleo (Stride==32&&((NumVertices==818&&primCount==866)||(NumVertices==269&&primCount==272)||(NumVertices==115&&primCount==122)))
#define topeng1 (Stride==32&&((NumVertices==653&&primCount==902)||(NumVertices==404&&primCount==484)||((NumVertices==189||NumVertices==191)&&primCount==158)))
#define helmegg (Stride==32&&((NumVertices==575&&primCount==768)||(NumVertices==381&&primCount==434)||(NumVertices==177&&primCount==142)))
#define helmking1 (Stride==32&&((NumVertices==1049&&primCount==1492)||(NumVertices==673&&primCount==843)||(NumVertices==293&&primCount==302)))
#define prohead (helmred||hacidayse||helmtar||helmhid||helmvip||helmfox||helmleo||topeng1||helmegg||helmking1)

/*-------------------------------------------------------------------------------------------------------------------*/
#define cTeroH (bodytar || bodyred || bodyviper || bodydfox || bodyr || topeng1 || helmegg || helmking1 || helmred || helmtar || helmvip || helmfox)
#define cPoliceH (bodyayse || bodyhide || bodyleo || bodyacid || topeng1 || helmegg ||helmking1 || helmhid || helmleo)
#define allp (bodyred||bodyayse||bodytar||bodyhide||bodyviper||bodyleo||bodydfox||bodyacid||bodyr||prohead)
/*-------------------------------------------------------------------------------------------------------------------*/
#define cTeroH (bodytar || bodyred || bodyviper || bodydfox || bodyr || topeng1 || helmegg || helmking1 || helmred || helmtar || helmvip || helmfox)
#define cPoliceH (bodyayse || bodyhide || bodyleo || bodyacid || topeng1 || helmegg ||helmking1 || helmhid || helmleo)
#define allp (bodyred||bodyayse||bodytar||bodyhide||bodyviper||bodyleo||bodydfox||bodyacid||bodyr||prohead)
#define SMOKE ( Stride == 24 && NumVertices == 256 ||(Stride == 24 && NumVertices == 192))
#define Dino ((primCount == 57) || (primCount == 161) || (primCount == 186) || (primCount == 197) || (primCount == 349) || (primCount == 495) || (primCount == 955) || (NumVertices == 2517 && primCount == 57) || (NumVertices == 3721 && primCount == 275) || (NumVertices == 0 && primCount == 52) || (NumVertices == 0 && primCount == 105) || (NumVertices ==0 && primCount == 186) || (NumVertices == 0 && primCount == 197) || (primCount == 579) || (primCount == 488))
#define K400 ((NumVertices == 1002 && primCount == 980))
#define C5 ((NumVertices == 772 && primCount == 849))
#define Police ( NumVertices == 490 || NumVertices == 221 || NumVertices == 611|| NumVertices == 102 ||(primCount == 526) || (primCount == 84) || (primCount == 64) || NumVertices == 67 || NumVertices == 92 || NumVertices == 95 || NumVertices == 114 || NumVertices == 504 || NumVertices == 108 || NumVertices == 398 || NumVertices == 520 || NumVertices == 684 || (primCount == 56) || (primCount == 93) )
#define Boddy ((primCount == 16 || primCount == 28 || primCount == 50 || primCount == 52 || primCount == 76 || primCount == 130))
#define Teroris ((NumVertices == 88 && primCount == 130) || (NumVertices == 142 && primCount == 266)|| (NumVertices == 472 && primCount == 304) || (NumVertices == 384 && primCount == 346) || (NumVertices == 348 && primCount == 520) || (NumVertices == 596 && primCount == 590)|| (NumVertices == 628 && primCount == 748) || (NumVertices == 3487 && primCount == 1737)|| (NumVertices == 3487 && primCount == 1766) || (NumVertices == 262 && primCount == 196) || (NumVertices == 142 && primCount == 266) || (NumVertices == 244 && primCount == 406) || (NumVertices == 1846 && primCount == 414) || (NumVertices == 528 && primCount == 540) || (NumVertices == 520 && primCount == 593) || (NumVertices == 2728 && primCount == 1344) || (NumVertices == 1091 && primCount == 1390) || (NumVertices == 1095 && primCount == 1460) || (NumVertices == 1846 && primCount == 2090) || (NumVertices == 2263 && primCount == 45) || (NumVertices == 370 && primCount == 278) || (NumVertices == 482 && primCount == 390) || (NumVertices == 734 && primCount == 688) || (NumVertices == 2263 && primCount == 1023) || (NumVertices == 812 && primCount == 1246) || (NumVertices == 2263 && primCount == 1434) || (NumVertices == 2041 && primCount == 1561) || (NumVertices == 1530 && primCount == 1534) || (NumVertices == 749 && primCount == 1374) || (NumVertices == 1831 && primCount == 1267) || (NumVertices == 2010 && primCount == 426) || (NumVertices == 287 && primCount == 396) || (NumVertices == 1831 && primCount == 341) || (NumVertices == 1831 && primCount == 278) || (NumVertices == 185 && primCount == 254) || (NumVertices == 74 && primCount == 66) || (NumVertices == 56 && primCount == 40) || (NumVertices == 185 && primCount == 271) || (NumVertices == 45 && primCount == 56) || (NumVertices == 92 && primCount == 56) || (NumVertices == 611 && primCount == 114) || (NumVertices == 611 && primCount == 526) || (NumVertices == 18 && primCount == 12) || (NumVertices == 96 && primCount == 92) || (NumVertices == 99 && primCount == 61) || (NumVertices == 133 && primCount == 205)|| (NumVertices == 245 && primCount == 276) || (NumVertices == 398 && primCount == 487) || (NumVertices == 26 && primCount == 20) || (NumVertices == 1204 && primCount == 241) || (NumVertices == 80 && primCount == 52) || (NumVertices == 1204 && primCount == 124) || (NumVertices == 113 && primCount == 139) || (NumVertices == 1204 && primCount == 56) || (NumVertices == 684 && primCount == 740) || (NumVertices == 1204 && primCount == 42) || (NumVertices == 45 && primCount == 56) || (NumVertices == 1204 && primCount == 35) || (NumVertices == 334 && primCount == 360) || (NumVertices == 175 && primCount == 246) || (NumVertices == 195 && primCount == 109) || (NumVertices == 71 && primCount == 120) || (NumVertices == 88 && primCount == 130) || (NumVertices == 201 && primCount == 157) || (NumVertices == 224 && primCount == 200) || (NumVertices == 296 && primCount == 166) || (NumVertices == 1353 && primCount == 386) || (NumVertices == 18 && primCount == 20) || (NumVertices == 41 && primCount == 30) || (NumVertices == 62 && primCount == 67) || (NumVertices == 152 && primCount == 168) || (NumVertices == 202 && primCount == 174) || (NumVertices == 237 && primCount == 395) || (NumVertices == 647 && primCount == 716) || (NumVertices == 727 && primCount == 936) || (NumVertices == 90 && primCount == 136) || (NumVertices == 120 && primCount == 170) || (NumVertices == 142 && primCount == 128) || (NumVertices == 218 && primCount == 322) || (NumVertices == 285 && primCount == 94) || (NumVertices == 1316 && primCount == 1574) || (NumVertices == 1316 && primCount == 134) || (NumVertices == 56 && primCount == 158) || (NumVertices == 73 && primCount == 112) || (NumVertices == 143 && primCount == 94) || (NumVertices == 246 && primCount == 120) || (NumVertices == 353 && primCount == 464) || (NumVertices == 381 && primCount == 234) || (NumVertices == 547 && primCount == 700) || (NumVertices == 1353 && primCount == 1404))
/*-------------------------------------------------------------------------------------------------------------------*/
const BYTE bRed[60] ={
0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
};
/*-------------------------------------------------------------------------------------------------------------------*/
const BYTE bBlue[60] ={
0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
};
/*-------------------------------------------------------------------------------------------------------------------*/
const BYTE bGreen[60] ={
0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x9E, 0x00, 0x00, 0x00, 0x00
};
/*-------------------------------------------------------------------------------------------------------------------*/
const BYTE bPink[58] ={
0x42, 0x4D, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x00, 0xFF, 0x00
};
/*-------------------------------------------------------------------------------------------------------------------*/
const BYTE bOrange[60] ={
0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x10, 0x80, 0xF0, 0xB0, 0x00, 0x00
};
/*-------------------------------------------------------------------------------------------------------------------*/