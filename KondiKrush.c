//címkép alsó fele
//creditsen billenytűkódo


#options
#define DB_TILT_EXTRA_WIDTH
#define DB_TILT_MIRROR
#endoptions

//{	Exportált sprite indexek
#pragma rem START_GFX_DEFINES		// NE VÁLTOZTASD!

#define SPR_IND_BLUE	0
#define SPR_IND_YELLOW	1
#define SPR_IND_RED	2
#define SPR_IND_BRAWN	3
#define SPR_IND_PURPLE	4
#define SPR_IND_GREEN	5
#define SPR_IND_DISCO	6
#define SPR_IND_CSIK	7
#define SPR_IND_STAR	8
#define SPR_IND_STAR2	9
#define SPR_IND_BOMB	10
#define SPR_IND_1	11
#define SPR_IND_2	12
#define SPR_IND_3	13
#define SPR_IND_4	14
#define SPR_IND_5	15
#define SPR_IND_6	16
#define SPR_IND_DISCO2	17
#define SPR_IND_CSIK2	18
#define SPR_IND_STAR22	19
#define SPR_IND_STAR23	20
#define SPR_IND_BOMB2	21
#define SPR_IND_PROBASPRITE	22
#define SPR_IND_KERET	23
#define SPR_IND_KERET2	24
#define SPR_IND_KERET3	25
#define SPR_IND_MINISTAR	26
#define SPR_IND_KEZDO3	27

#pragma rem END_GFX_DEFINES

//}

#define ROBOT_BACK_SIZE 66
char *backPtr;

//{ -------------------------- INIT --------------------------------
//https://youtu.be/EzG_4HVOxnQ
struct RECT
{
	unsigned char X,Y,Width,Height;	
};

struct VPORT
{
	unsigned char Left,Top,Right,Bottom;	
};

struct GOBJ
{
	int X,Y;			// (*) A sprite 16 bites előjeles koordinátája.
	unsigned char SprInd;		// (*) A sprite indexe az exportált munkamenetben
	unsigned char Flag;		// (*) 0. bit: jelzi, hogy a sprite be van-e kapcsolva, a 7. pedig, ha tükrözni kell
	char *SprBackAddr;		// (*) A sprite háttér mentése számára lefoglalt mem. blokk kezdőcíme. Ha nem kell menteni a hátteret akkor az értéke 0!
	char *SprPalAddr;		// (*) A sprite palettájának címe. Ha nincs paletta, akkor értéke 0!
	int (*spritefunc)();		// (*) A sprite kirajzoló rutin kezdőcíme
	unsigned char SprWidth;		// A sprite szélessége
	unsigned char SprHeight;	// A sprite magassága
	unsigned char SprIndRef;	// Sprite index referencia. Azért kell, hogy el tudjuk dönteni kell-e újra inicializálni a sprite alap adatait (pl RawAddr)
	char *SprRawAddr;		// Az adott sprite forrás adatai
	char *SprScrAddr;		// A sprite vágás utáni kezdőcíme a képernyőn v. háttér bufferben
	unsigned char SprClipSkipRow;	// A sprite felső vágásánál ezen a változón tárolódik, hogy hány sort kell felül kihagynia a sprite kirajzolónak
	struct RECT SprClip;		// A sprite vágás utáni dimenziói
	struct RECT SprPrevClip;	// A sprite előző fázisban értelmezett vágás utáni dimenziói
	unsigned char SprClipFlag;	// A sprite vágási állapotát tárolja le a sprite kirakónak
};

   struct SCNSPRITE
   {
 	        unsigned char SprInd;		// A sprite indexe (*)
 	        int X,Y;			// A sprite 16 bites előjeles koordinátája. (*)
 	        unsigned char SprWidth;		// A sprite szélessége. (*)
 	        unsigned char SprHeight;	// A sprite magassága. (*)
 	        unsigned char Tag;		// A scene editorban a sprite-hoz rendelt Tag (*)
 	        unsigned char Flag;		// A kirakott sprite Flag értéke. A 7. bit mondja meg, hogy a kirakandó sprite-ot kell-e tükrözni. (*)
 	        unsigned char *SprPalette;	// A sprite palettájának címe. Alapból 0, de a működés során tetszőlegesen megváltoztatható. Feltéve, ha a kirajzoló használja a sprite palettát.
 	        char Visible;			// Ezzel a tulajdonsággal kikapcsolhatjuk a sprite kirajzolását. Ha ezt a változót 0-ra állítjuk (false) akkor az adott sprite nem fog kirajzolódni
   };

struct GameLevel
{
	int score;
	int star1Score;
	int star2Score;
	int star3Score;
	int xSize;
	int ySize;
	int maxLap;
	int condyNumber;
	int extras;
};

#define      SN     30
#define      speed   1

struct GameLevel levels[37] = 	{
					{0,0,0,0,0,0,0,0,0},

					{0,1,10,30,3,3,10,4,0},
					{0,1,10,30,4,4,10,4,0},
					{0,20,50,100,5,3,20,5,0},
					{0,20,50,100,4,6,20,5,0},
					{0,20,50,100,5,5,20,6,0},
					{0,20,50,200,6,6,15,6,1},

					{0,20,50,100,4,6,20,6,1},
					{0,20,50,100,6,3,20,6,1},
					{0,20,50,100,5,5,20,6,1},
					{0,20,50,100,3,3,20,4,1},
					{0,20,50,100,2,6,20,4,1},
					{0,20,50,100,6,2,20,4,1},

					{0,20,50,500,5,4,20,3,1},
					{0,20,50,800,6,6,20,4,0},
					{0,20,50,100,4,4,10,6,1},
					{0,20,50,100,4,6,10,6,0},
					{0,20,50,100,2,4,20,4,1},
					{0,20,50,100,3,5,20,6,1},

					{0,20,50,100,4,6,20,6,1},
					{0,3,6,10,1,6,20,3,1},
					{0,20,50,100,4,4,20,5,1},
					{0,20,50,1000,6,6,20,3,1},
					{0,20,50,100,3,3,20,3,1},
					{0,20,50,100,3,6,20,5,1},

					{0,20,50,1000,5,4,20,3,1},
					{0,20,50,700,5,5,10,3,1},
					{0,20,50,50,4,2,20,5,1},
					{0,20,50,200,4,6,20,6,1},
					{0,20,50,400,5,5,30,6,1},
					{0,20,300,1000,3,4,20,2,1},

					{0,20,70,150,5,2,20,3,1},
					{0,20,50,200,4,6,20,4,1},
					{0,20,50,100,6,3,20,6,1},
					{0,20,50,100,4,4,20,6,1},
					{1000,20,50,100,5,5,20,5,1},
					{1000,20,50,300,6,6,30,6,1}
				};


struct GOBJ gameObjects[SN];
struct GOBJ *gIndex;
struct GOBJ *gIndex2[SN];


char actualLevel[40];
char lastDrawnlevel[40];


int posx = 0;
int posy = 0;
int lastposx = 0;
int lastposy = 0;
int selectedPosx = 0;
int selectedPosy = 0;
int moveMode = 0;

int maxSizeX;
int maxSizeY;

int startX;
int startY;

int gamemode=0;
int gotomain=1;

int lap;
int level;
int levelScore=0;


int levelCandyNumber = 0;
int levelExtras = 0;

int deep = 1;

int currentIndex;

struct GOBJ *ptr;

int plx=0;
int ply=0;

#define EFFECT_CH_COUNT 3

char effectBuffer[12];

#pragma mblock 0x200
char snowBack[620];
#pragma endmb

int music;

//}

//{-------------------------- MAIN --------------------------------
main()
{
	int i;

	music=1;	
	SetBorder(COLOR_DARKBLUE);
	DbInitFont(KKF);
	DbInitGameLib(2, gameObjects, SN);
	DbPageFullRamVid();
	DbAssignRenderToVideo();
	DbRandomize();
	DbSetFontParam(FNT_COLOR, COLOR_WHITE); 
	DbSetFontParam(FNT_BACKCOLOR, COLOR_DARKBLUE);  

	DbInitSoundSystem();
      	DbInitEffectChannels(effectBuffer,EFFECT_CH_COUNT);
	DbStopMusic();
	InitInterrupt(DefUserIT);
	DbSetTvcMusicParams(3, 1);

	DbStartMusic(TitleMusic,MUSIC_TVC,6 + MUSIC_LOOPED);


	ptr = gameObjects;

	while (1)  
	{
		if (gotomain==1) MainScreen();
		LevelSelector();
	};

	DbCloseGameLib();
}
//}


//{-------------------------- ClearScreen --------------------------------
ClearScreen()
{
	DbFillBox(0,0,64,255,COLOR_DARKBLUE);
}
//}

//{-------------------------- MainScreen --------------------------------
MainScreen()
{
	int c;
	int i;
	int y;
	int x;
	c=0;

	ClearScreen();

	DbAssignRenderToBuffer();

	ClearScreen();
	DrawSprite2(9,42,SPR_IND_KEZDO3,59);
	DrawSprite2(8,85,SPR_IND_BLUE+gamemode*11,59);
	DrawSprite2(16,85,SPR_IND_YELLOW+gamemode*11,59);
	DrawSprite2(24,85,SPR_IND_RED+gamemode*11,59);
	DrawSprite2(32,85,SPR_IND_BRAWN+gamemode*11,59);
	DrawSprite2(40,85,SPR_IND_PURPLE+gamemode*11,59);
	DrawSprite2(48,85,SPR_IND_GREEN+gamemode*11,59);
	DrawCoolString(4, 230, "C - CREDITS    SPACE - START", 5);

	ptr = gameObjects;
 
	DbCopyToFullScreen();
	/*
	backPtr = snowBack;
	for(i=0;i<10;i++)
	{
		DrawSprite3(Random(60),Random(40), 17,i);
	}
	*/
	while(1)
	{
		for(i=0;i<10;i++)
		{
			if(IsKeyDown(KEY_C)) {c=1; break;}
			if(IsKeyDown(KEY_SPACE)) {break;}
			/*
			y = gIndex2[i]->Y+Random(20)+5;
			x = gIndex2[i]->X+Random(6)-3;
			if(x<0) x = 0;
			if (x>60) x=60;
			gIndex2[i]->X=x;
			if(y>230) y=0;
			gIndex2[i]->Y=y;
			*/
		}
		if(IsKeyDown(KEY_C)) {c=1; break;}
		if(IsKeyDown(KEY_SPACE)) {break;}
		DbRender();
		if(IsKeyDown(KEY_C)) {c=1; break;}
		if(IsKeyDown(KEY_SPACE)) {break;}
	}

	DbSetRenderToVideo();
	if(c) Credits();

	ptr = gameObjects;

}
//}

Credits()
{
	ClearScreen();

	DrawCoolString(22,0, "KONDI KRUSH!", 1);
	DrawCoolString(0,40, "MADE BY ANYSTONE", 1);
	DrawCoolString(0,80, "DEVTOOL HELPS: DOBERDO BROTHERS", 1);
	DrawCoolString(0,100, "MUSIC: REI AND ANYSTONE", 1);
	DrawCoolString(0,120, "GFX: NORBICSEK", 1);
	DrawCoolString(23, 230, "- SPACE -", 5);

	WaitForKeyPress(KEY_SPACE);
	MainScreen();
}

//{-------------------------- LevelSelector --------------------------------
LevelSelector()
{
	int lx;
	int ly;
	int olx;
	int oly;
	char key;
	int index;
	int i;
	int fullscore;
	int fullstars;

	ptr = gameObjects;
	startX=0;
	startY=0;

	ClearScreen();

	fullscore = 0;
	fullstars = 0;

	for(i=1;i<37;i++)
	{
		fullscore+=levels[i].score;
		if(levels[i].score >= levels[i].star1Score) fullstars++;
		if(levels[i].score >= levels[i].star2Score) fullstars++;
		if(levels[i].score >= levels[i].star3Score) fullstars++;
	}
	
	DrawCoolString(0,0, "FULLSCORE:", 4);
	DrawCoolString(20,0, itos(fullscore),2);
	DrawCoolString(36,0, "FULLSTARS:",4);
	DrawCoolString(56,0, itos(fullstars),2);
	
	DrawCoolString(0,230, "I-INFO                   M-MUSIC",1);

	for(lx=0;lx<6;lx++)
	{
		for(ly=0;ly<6;ly++)
		{
			index = ly*6+lx+1;
			if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
			{
				DbSetFontParam(FNT_COLOR, COLOR_WHITE);
			}
			else
			{
				DbSetFontParam(FNT_COLOR, COLOR_GRAY);
			}

			DbDrawStrEx(11+lx*8,40+ly*30,itos(index));

			if(levels[index].score >= levels[index].star1Score) DrawSprite2(10+lx*8,50+ly*30,SPR_IND_MINISTAR,59);
			if(levels[index].score >= levels[index].star2Score) DrawSprite2(12+lx*8,50+ly*30,SPR_IND_MINISTAR,59);
			if(levels[index].score >= levels[index].star3Score) DrawSprite2(14+lx*8,50+ly*30,SPR_IND_MINISTAR,59);

		}
	}

	DrawSprite(plx+1, ply+1, SPR_IND_KERET, 58);

	key = 'P';
	while(key!='Q')
	{
		if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_X)) key = 'Q';	
		if (IsKeyDown(KEY_I)) key = 'I';	
		if (IsKeyDown(JOY1_UP) || IsKeyDown(KEY_W)) key = 'W';	
		if (IsKeyDown(JOY1_LEFT) || IsKeyDown(KEY_A)) key = 'A';	
		if (IsKeyDown(JOY1_DOWN) || IsKeyDown(KEY_S)) key = 'S';	
		if (IsKeyDown(JOY1_RIGHT) || IsKeyDown(KEY_D)) key = 'D';	
		if (IsKeyDown(KEY_M)) key = 'M';	
		if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RET) || IsKeyDown(JOY1_FIRE)) key = ' ';	
		if(key!='P')
		{
			olx = plx;
			oly = ply;

			switch (key)
			{				
				case 'M':
				   	if(music==1)	
				    	{
						music = 0;
						DbStopMusic();
					}
					else
					{
						music = 1;
						DbStartMusic(TitleMusic,MUSIC_TVC,6 + MUSIC_LOOPED);
					}
					Sleep(30);
				    	break;
				case 'W':
				    ply--;
				    break;
				case 'S':
				    ply++;
				    break;
				case 'A':
				    plx--;
				    break;
				case 'D':
				    plx++;
				    break;
				case 'Q':
				    gotomain=1; 
                                    return;
				    break;
				case 'I':
					index = ply*6+plx+1;
					if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
					{
					    LevelInfo(index);
					    gotomain=0;
					    return;
					}
				    //break;
				case ' ':
					index = ply*6+plx+1;
					if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
					{
						currentIndex = index;
						StartLevel(index);
						gotomain=0;
						return;
					}
				    //break;
			}
			
			if (plx < 0) plx = 0;
			if (ply < 0) ply = 0;
			if (plx > 5) plx = 5;
			if (ply > 5) ply = 5;

			DrawSprite(olx+1, oly+1, SPR_IND_KERET3, 58);
			DrawSprite(plx+1, ply+1, SPR_IND_KERET, 58);
			
			Sleep(7);
			key = 'P';
		}
	}
	
}
//}

//{-------------------------- LevelInfo --------------------------------
LevelInfo(int index)
{
	int i;
	ClearScreen();
	DrawCoolString(10,30, "USABLE CONDENSERS:", 1);
	
	for(i=0;i<levels[index].condyNumber;i++)
	{
		DrawSprite2(8+i*7,44,i+gamemode*11,59);
	}

	if(levels[index].extras)
	{
		DrawSprite2(8,75,SPR_IND_DISCO+gamemode*11,59);
		DrawSprite2(18,75,SPR_IND_CSIK+gamemode*11,59);
	}

	DrawCoolString(10,110,"SIZE:  X", 1);
	DrawCoolString(21,110,itos(levels[index].xSize), 1);
	DrawCoolString(27,110,itos(levels[index].ySize), 1);

	DrawCoolString(10,130, "MAX LAP:" ,1); 
	DrawCoolString(27,130,itos(levels[index].maxLap), 1);

	DrawCoolString(10,150, "1 STAR:",1); 
	DrawCoolString(10,160, "2 STAR:",1); 
	DrawCoolString(10,170, "3 STAR:",1); 
	DrawCoolString(25,150,itos(levels[index].star1Score), 1);
	DrawCoolString(25,160,itos(levels[index].star2Score), 1);
	DrawCoolString(25,170,itos(levels[index].star3Score), 1);

	DrawCoolString(10,190, "MAX SCORE:" ,1); 
	DrawCoolString(30,190,itos(levels[index].score), 1);
	DrawCoolString(23, 230, "- SPACE -", 5);
	
	WaitForKeyPress(KEY_SPACE);
}
//}

//{-------------------------- DrawCoolString --------------------------------
DrawCoolString(int x, int y, char* text, int textSpeed)
{
	DrawCooStringPart(x, y, text, textSpeed, COLOR_BLACK); 
	DrawCooStringPart(x, y, text, textSpeed, COLOR_DARKRED); 
	DrawCooStringPart(x, y, text, textSpeed, COLOR_RED); 
	DrawCooStringPart(x, y, text, textSpeed, COLOR_YELLOW); 
	DrawCooStringPart(x, y, text, textSpeed, COLOR_WHITE); 
}
//}

#pragma link forward
//{-------------------------- DrawCooStringPart --------------------------------
DrawCooStringPart(int x, int y, char* text, int textSpeed, int textcolor)
{
	DbSetFontParam(FNT_COLOR, textcolor); 
	DbDrawStrEx(x,y,text);
	Sleep(textSpeed); 
}
//}

//{-------------------------- StartLevel --------------------------------
StartLevel(int index)
{
	int lx;
	int ly;
	int maxLap;
	int candyNumber;
	int extras;

	int i;
	char key;

	ptr = gameObjects;

	lx = levels[index].xSize;
	ly = levels[index].ySize;
	maxLap = levels[index].maxLap;
	candyNumber = levels[index].condyNumber;
	extras = levels[index].extras;

	posx = 0;
	posy = 0;
	lastposx = 0;
	lastposy = 0;
	selectedPosx = 0;
	selectedPosy = 0;
	moveMode = 0;
	levelScore = 0;

	lap = maxLap;
	lastDrawnlevel[0]=='S';
	levelCandyNumber = candyNumber;
	levelExtras = extras;
	ptr = gameObjects;

	ClearScreen();
	DrawSprite2(40, 0,  SPR_IND_STAR2+gamemode*11, 59);
	DrawSprite2(48, 0,  SPR_IND_STAR2+gamemode*11, 59);
	DrawSprite2(56, 0,  SPR_IND_STAR2+gamemode*11, 59);

	DrawCoolString(0,0, "SCORE:", 4);
	DrawCoolString(12,0, itos(levelScore),2);
	DrawCoolString(25,0, "LAP:",4);
	DrawCoolString(33,0, itos(lap),2);

	DrawCoolString(0,230, "                          Q-QUIT",1);

	maxSizeX = lx;
	maxSizeY = ly;
	
	startX = (64-maxSizeX*8)/2;
	startY = (250-maxSizeY*30)/2;

	for(i=0;i<maxSizeX*maxSizeY;i++)
	{
		lastDrawnlevel[i] = 10;
	}

	for(i=0;i<maxSizeX*maxSizeY;i++)
	{
		actualLevel[i] = RandomColor();
	}

	CheckTable(1);
	DrawTable(0, 0);
	
	key = 'P';
	
	while(key!='Q' && lap >0)
	{
		if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_X)) key = 'Q';	
		if (IsKeyDown(JOY1_UP) || IsKeyDown(KEY_W)) key = 'W';	
		if (IsKeyDown(JOY1_LEFT) || IsKeyDown(KEY_A)) key = 'A';	
		if (IsKeyDown(JOY1_DOWN) || IsKeyDown(KEY_S)) key = 'S';	
		if (IsKeyDown(JOY1_RIGHT) || IsKeyDown(KEY_D)) key = 'D';	
		if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RET) || IsKeyDown(JOY1_FIRE)) key = ' ';	

		if (IsKeyDown(KEY_M)) key = 'M';	
		if(key!='P' && key!='Q')
		{
			KeyDown(key);
			key = 'P';
		}
		Sleep(7);
	}

	if(levelScore > levels[index].score) levels[index].score = levelScore;

	if(index==36 && levelScore > levels[index].star1Score && gamemode==0)  
	{ 
		DrawCoolString(0,0,  "  CONDENSATOR (KONDI) MODE ACTIVATED!   ", 8);
		DrawCoolString(0,230, " ON CREDITS TYPE CONDI/CANDY TO CHANGE! ", 8);
		Sleep(200);
		gamemode=1;
	};
}
//}

//{-------------------------- Level --------------------------------
Level(int x, int y)
{
	return actualLevel[y*maxSizeX+x];
}
//}

//{-------------------------- SetLevel --------------------------------
SetLevel(int x, int y, char c)
{
	actualLevel[y*maxSizeX+x] = c;
}
//}

//{-------------------------- LastDrawnlevel --------------------------------
LastDrawnlevel(int x, int y)
{
	return lastDrawnlevel[y*maxSizeX+x];
}
//}

#pragma link forward
//{-------------------------- DrawTable --------------------------------
DrawTable(char withWait, char fast )
{
   int x;
   int y;
   int i;
   int xonscreen;
   int yonscreen;
   char* space;
   space = "   ";

   ptr = gameObjects;

    for(x=0;x< maxSizeX;x++)
        for(y=0;y< maxSizeY;y++)
        {
            if (lastDrawnlevel[0]=='S' || Level(x, y) != LastDrawnlevel(x, y) || (lastposx==x && lastposy==y && (posx != lastposx || posy != lastposy) )  )
            {
                int candy;
                candy = 0;

                switch (Level(x, y))
                {
                    case 'B':
                        candy = 0;
                        break;
                    case 'P':
                        candy = 1;
                        break;
                    case 'O':
                        candy = 2;
                        break;
                    case 'G':
                        candy = 3;
                        break;
                    case 'Y':
                        candy = 4;
                        break;
                    case 'R':
                        candy = 5;
                        break;
                    case 'C':
                        candy = SPR_IND_BOMB;
                        break;
                    case ' ':
                        candy = SPR_IND_PROBASPRITE;
                        break;
                    case 'D':
                        candy = SPR_IND_DISCO;
                        break;
                    case 'X':
                        candy = SPR_IND_CSIK;
                        break;
                }

		if(candy!=SPR_IND_PROBASPRITE) candy=candy+gamemode*11;

		DrawSprite(x, y, candy, x+y*maxSizeX);

                if (x == lastposx && y == lastposy) { lastposx = -1; lastposx = -1; };
            }
        }

	DrawSprite(posx, posy, SPR_IND_KERET + moveMode, 58);

	lastposx = posx;
	lastposy = posy;
	
	for(i=0;i<SN;i++)
	{
		lastDrawnlevel[i] = actualLevel[i];
	}
	
	//if (withWait) Wait(fast);

	if(levelScore>=levels[currentIndex].star1Score) DrawSprite2(40, 0,  SPR_IND_STAR+gamemode*11, 59);
	if(levelScore>=levels[currentIndex].star2Score) DrawSprite2(48, 0,  SPR_IND_STAR+gamemode*11, 59);
	if(levelScore>=levels[currentIndex].star3Score) DrawSprite2(56, 0,  SPR_IND_STAR+gamemode*11, 59);
	DbDrawStrEx(12,0, itos(levelScore));
	space = itos(lap);
	DbDrawStrEx(33,0, strcat(space, " "));
}
//}

#pragma link forward
//{-------------------------- DrawSprite --------------------------------
DrawSprite(int x, int y, int candy, int index)
{
	int xonscreen;
	int yonscreen;

	xonscreen= x*8 + startX;
	yonscreen= y*30 + startY;
	
	gIndex = DbInitGameObject(ptr,xonscreen,yonscreen,candy,GOFLG_VISIBLE, DbSprite16c16Mask,0,0);
	
	DbClipSprite(gIndex);
	DbDrawSprite(gIndex);
}
//}

#pragma link forward
//{-------------------------- DrawSprite2 --------------------------------
DrawSprite2(int x, int y, int candy, int index)
{
	gIndex = DbInitGameObject(ptr,x,y,candy,GOFLG_VISIBLE, DbSprite16c16Mask,0,0);
	
	DbClipSprite(gIndex);
	DbDrawSprite(gIndex);
}

/*
#pragma link forward
DrawSprite3(int x, int y, int obj, int index)
{
	gIndex2[index] = DbInitGameObject(ptr++,x,y,obj,GOFLG_VISIBLE, DbSprite16c16Mask,backPtr,0);
	backPtr+=88;
}
*/

//{-------------------------- ChangeMoveMode --------------------------------
ChangeMoveMode()
{
 	char temp;
	int xx;
	int yy;
   
	if(moveMode)
	{
		selectedPosx = posx;
		selectedPosy = posy;
	}
	else
	{
		if(posx==selectedPosx && posy==selectedPosy)
		{
		    //Do nothing
		}
		else if (Level(posx, posy) == Level(selectedPosx, selectedPosy))
		{	
			if(moveMode){ moveMode = 0;} else {moveMode=1;}
		}
		else
		{
			if (Level(posx,posy)=='D')
			{
				temp = Level(selectedPosx, selectedPosy);
				for(xx=0;xx<maxSizeX;xx++)
				{
					for(yy=0;yy<maxSizeY;yy++)
					{
						if(temp==Level(xx, yy))
						{
							SetLevel(xx, yy, 'C');
							levelScore+=2;
						}
					}
				}
				SetLevel(posx,posy, 'C' );
				levelScore+=2;
			        
				SoundEffect(0, CrushSound);
			}
			else if (Level(selectedPosx,selectedPosy)=='D')
			{
				temp = Level(posx, posy);
				for(xx=0;xx<maxSizeX;xx++)
				{
					for(yy=0;yy<maxSizeY;yy++)
					{
						if(temp==Level(xx, yy)) 
						{
							SetLevel(xx, yy, 'C');
							levelScore+=2;
						}
					}
				}
				
				SetLevel(selectedPosx,selectedPosy, 'C');
				levelScore+=2;
				SoundEffect(0, CrushSound);
			}
			else if (Level(posx,posy)=='X')
			{	
				if(posx!=selectedPosx)
				{
					for(xx=0;xx<maxSizeX;xx++)
					{
						SetLevel(xx, selectedPosy, 'C');
						levelScore+=2;
					}
				}
				if(posy!=selectedPosy)
				{
					for(yy=0;yy<maxSizeY;yy++)
					{
						SetLevel(selectedPosx, yy, 'C');
						levelScore+=2;
					}
				}

				SoundEffect(0, CrushSound);
			}
			else if (Level(selectedPosx,selectedPosy)=='X')
			{
				if(posx!=selectedPosx)
				{
					for(xx=0;xx<maxSizeX;xx++)
					{
						SetLevel(xx, posy, 'C');
						levelScore+=2;
					}
				}
				if(posy!=selectedPosy)
				{
					for(yy=0;yy<maxSizeY;yy++)
					{
						SetLevel(posx, yy, 'C');
						levelScore+=2;
					}
				}
				SoundEffect(0, CrushSound);
			}
			else
			{
				temp = Level(selectedPosx, selectedPosy);
		    		SetLevel(selectedPosx, selectedPosy, Level(posx, posy));
		    		SetLevel(posx, posy, temp);
			}
		
		    	deep=1;
		    	lap--;
			
			DrawTable(1,1);
			for(xx=0;xx<maxSizeX;xx++)
			{
				for(yy=0;yy<maxSizeY;yy++)
				{
					if(Level(xx, yy)=='C') SetLevel(xx, yy, ' ');
				}
			}
		    	Fall(1);
			CheckTable(1);
		}
	}
}
//}

//{-------------------------- CheckTable --------------------------------
CheckTable(int draw)
{
    int x;
    int y;
    char currchar;

    int crush;
    int cx1;
    int cy1;
    int cx2;
    int cy2;
    int cx3;
    int cy3;
    int cx4;
    int cy4;

    crush = 0;
    cx1 = -1;
    cy1 = -1;
    cx2 = -1;
    cy2 = -1;
    cx3 = -1;
    cy3 = -1;
    cx4 = -1;
    cy4 = -1;

    for (x = 0; x < maxSizeX; x++)
    {
        for (y = 0; y < maxSizeY; y++)
        {
             currchar = Level(x, y);
             //TODO: bomba L ,vagy nyalóka alakban

            //Vízszintes 5-ös
            if (x < maxSizeX - 4 && Level(x + 4, y) == currchar && Level(x + 3, y) == currchar && Level(x + 2, y) == currchar && Level(x + 1, y) == currchar)
            {
                cx1 = x + 1;
                cy1 = y;
                cx2 = x + 2;
                cy2 = y;
                cx3 = x + 3;
                cy3 = y;
                cx4 = x + 4;
                cy4 = y;
                crush = 1;
            }                    
            //Vízszintes 4-es
            else if (x < maxSizeX - 3 && Level(x + 3, y) == currchar && Level(x + 2, y) == currchar && Level(x + 1, y) == currchar)
            {
                cx1 = x + 1;
                cy1 = y;
                cx2 = x + 2;
                cy2 = y;
                cx3 = x + 3;
                cy3 = y;
                crush = 1;
            }
            //Vízszintes 3-as
            else if (x < maxSizeX - 2 && Level(x + 2, y) == currchar && Level(x + 1, y) == currchar)
            {
                cx1 = x + 1;
                cy1 = y;
                cx2 = x + 2;
                cy2 = y;
                crush = 1;
            }
            //Függőleges 5-ös
            else if (y < maxSizeY - 4 && Level(x, y + 4) == currchar && Level(x, y + 3) == currchar && Level(x, y + 2) == currchar && Level(x, y + 1) == currchar)
            {
                cx1 = x;
                cy1 = y + 1;
                cx2 = x;
                cy2 = y + 2;
                cx3 = x;
                cy3 = y + 3;
                cx4 = x;
                cy4 = y + 4;
                crush = 1;
            }
            //Függőleges 4-es
            else if (y < maxSizeY - 3 && Level(x, y + 3) == currchar && Level(x, y + 2) == currchar && Level(x, y + 1) == currchar)
            {
                cx1 = x;
                cy1 = y + 1;
                cx2 = x;
                cy2 = y + 2;
                cx3 = x;
                cy3 = y + 3;
                crush = 1;
            }
            //Függőleges 3-as
            else if (y < maxSizeY - 2 && Level(x, y+2) == currchar && Level(x, y+1) == currchar)
            {
                cx1 = x;
                cy1 = y + 1;
                cx2 = x;
                cy2 = y + 2;
                crush = 1;
            }

            if (crush)
            {
                Crush(x, y, cx1, cy1, cx2, cy2, cx3, cy3, cx4, cy4, draw);
                break;
            }
        }
        if (crush) break;
    }
}
//}

//{-------------------------- Crush --------------------------------
Crush (int cx1, int cy1, int cx2, int cy2, int cx3, int cy3, int cx4, int cy4, int cx5, int cy5, int draw)
{
    SoundEffect(0, Crush2Sound);

    SetLevel(cx1, cy1, 'C');
    SetLevel(cx2, cy2, 'C');
    SetLevel(cx3, cy3, 'C');
    if (levelExtras)
    {
	    if (cx5 != -1 && cy5 != -1) SetLevel(cx5, cy5, 'D');
	    else
	    {	
		    if (cx4 != -1 && cy4!=-1) 
			if (cx5 != -1 && cy5 != -1)	
			{
				SetLevel(cx4, cy4, 'C');
			}
		    	else
			{
				SetLevel(cx4, cy4, 'X');
			}
	    }
    }
    else
    {
	    if (cx4 != -1 && cy4 != -1) SetLevel(cx4, cy4, 'C');
	    if (cx5 != -1 && cy5 != -1) SetLevel(cx5, cy5, 'C');
    }

    if (draw) DrawTable(true, false);

    SetLevel(cx1, cy1, ' ');
    SetLevel(cx2, cy2, ' ');
    SetLevel(cx3, cy3, ' ');
    if (cx4 != -1 && Level(cx4,cy4)=='C') SetLevel(cx4, cy4,  ' ');
    if (cx5 != -1 && Level(cx5,cy5)=='C') SetLevel(cx5, cy5, ' ');

    if (draw) DrawTable(true, false);

    levelScore+=deep*3;
    if (cx4 != -1 && cy4!=-1) levelScore+=deep*2;
    if (cx5 != -1 && cy5 != -1) levelScore+=deep*4;
	
    deep++;

    Fall(draw);

    CheckTable(draw);
}
//}

//{-------------------------- Fall --------------------------------
Fall(int draw)
{
    int fall;
    int x;
    int y;
    int pair;

    fall = 1;
    pair = 0;

    while(fall)
    {
        fall = 0;
        for(y=maxSizeY-1;y>0;y--)
        {
            for (x = 0; x < maxSizeX; x++)
            {
                if(Level(x,y)==' ')
                {
                    SetLevel(x, y, Level(x, y - 1));
                    SetLevel(x, y - 1, ' ');
                    fall = 1;
		    
		    if(pair)
                    {
			SoundEffect(1, Fall1Sound);
	 	        pair=0;
		    }
                    else
		    {
			SoundEffect(2, Fall2Sound);
                        pair=1;
	            }
                }
            }
        }

        for (x = 0; x < maxSizeX; x++)
        {
            if (Level(x, 0) == ' ')
            {
                SetLevel(x, 0, RandomColor());
            }
        }

        if (draw) DrawTable(1, 1);
    }
}
//}

//{-------------------------- RandomColor --------------------------------
RandomColor()
{
    int rng;
    char color;

    color = ' ';

    //rng = DbRndRange(0)*levelCandyNumber/256;
    rng = DbRndRange(levelCandyNumber-1);


    switch (rng)
    {
        case 0:
            color = 'B';
            break;
        case 1:
            color = 'G';
            break;
        case 2:
            color = 'O';
            break;
        case 3:
            color = 'P';
            break;
        case 4:
            color = 'Y';
            break;
        case 5:
            color = 'R';
            break;
    }

    return color;
}
//}

//{-------------------------- Random --------------------------------
Random(int maxNumber)
{
    	int rng;

	rng = DbRndRange(maxNumber);
/*
	if(maxNumber>15)
	{
		rng = DbRndRange(maxNumber);
	}
	else
	{	 
    		rng = DbRndRange(maxNumber)*maxNumber/256;
	}
	*/
    	return rng;
}
//}

//{-------------------------- KeyDown --------------------------------
KeyDown(char KeyCode)
{
    int oldposx;
    int oldposy;
    oldposx = posx;
    oldposy = posy;

    switch (KeyCode)
    {
	case 'M':
	   	if(music==1)	
	    	{
			music = 0;
			DbStopMusic();
		}
		else
		{
			music = 1;
			DbStartMusic(TitleMusic,MUSIC_TVC,6 + MUSIC_LOOPED);
		}
		Sleep(30);
	    	break;
        case 'W':
            posy--;
            break;
        case 'S':
            posy++;
            break;
        case 'A':
            posx--;
            break;
        case 'D':
            posx++;
            break;
        case ' ':
            moveMode = !moveMode;
            ChangeMoveMode();
	    Sleep(3);
            break;
    }

    if (posx < 0) posx = oldposx;
    if (posy < 0) posy = oldposy;
    if (posx > maxSizeX - 1) posx = oldposx;
    if (posy > maxSizeY - 1) posy = oldposy;
    if (moveMode)
    {
        if (posx > selectedPosx + 1) posx = oldposx;
        if (posx < selectedPosx - 1) posx = oldposx;
        if (posy > selectedPosy + 1) posy = oldposy;
        if (posy < selectedPosy - 1) posy = oldposy;
        if (posx != selectedPosx && posy != selectedPosy) { posx = oldposx; posy = oldposy; }
    }

    DrawTable(0, 0);
}
//}


//{-------------------------- SoundEffect -------------------------- 
SoundEffect(int ch, char *soundSample)
{
	if(music==0) DbStartSoundEffect(ch, soundSample);
}
//}

//{-------------------------- ItCallBack -------------------------- 
ItCallBack()
{
    	IncTimer();
    	ReadKeyMatrix();
	DbMusicPlayer_IT();
	DbSoundEffect_IT();
}
//}

//{	TitleMusic
#asm
	qTitleMusic

	;ChannelNr
				db	4
	;InsturmentNr
				db	2
	;TrackSize
				db	10
	;PatternSize
				db	64
	;CardFlag
				db	0
	;PatternOffs
				dw	49
	;InstrumentOffs
				dw	105
	;Track0
				db	16,4,4,12,12,4,4,24,24,4
	;Track1
				db	1,5,5,9,9,5,5,13,13,5
	;Track2
				db	2,6,6,10,10,6,6,14,14,6
	;Track3
				db	3,7,7,11,11,7,7,15,15,7
	;PatternOffset
				dw	109,166,167,168,169,297,425,426,427,430,431,432,433,561,689,690,691,813,814,815,816,819,820,821,822,894,895,896
	;InstrumentOffset
				dw	897,900

	;Patterns
				db	25,16,27,16,30,16,32,16,34,16,37,16,255,16,45,16,26,16,28,16,29,16,31,16,33,16,35,16,36,16
				db	38,32,49,16,50,16,48,16,47,16,47,16,47,16,47,16,48,16,48,16,48,16,48,16,49,16,163

				db	192

				db	192

				db	192

				db	55,16,48,16,48,16,55,16,48,16,48,16,55,16,48,16,52,16,48,16,48,16,52,16,48,16,48,16,52,16
				db	48,16,53,16,48,16,48,16,53,16,48,16,48,16,53,16,48,16,50,16,43,16,43,16,50,16,43,16,43,16
				db	50,16,43,16,55,16,48,16,48,16,55,16,48,16,48,16,55,16,48,16,52,16,48,16,48,16,52,16,48,16
				db	48,16,52,16,48,16,53,16,48,16,48,16,53,16,48,16,48,16,53,16,48,16,50,16,43,16,43,16,50,16
				db	43,16,43,16,50,16,53,16

				db	36,16,43,16,43,16,36,16,43,16,43,16,36,16,43,16,36,16,40,16,40,16,36,16,40,16,40,16,36,16
				db	40,16,36,16,41,16,41,16,36,16,41,16,41,16,36,16,41,16,43,16,38,16,38,16,43,16,38,16,38,16
				db	43,16,38,16,36,16,43,16,43,16,36,16,43,16,43,16,36,16,43,16,36,16,40,16,40,16,36,16,40,16
				db	40,16,36,16,40,16,36,16,41,16,41,16,36,16,41,16,41,16,36,16,41,16,43,16,38,16,38,16,43,16
				db	38,16,38,16,43,16,38,16

				db	192

				db	192

				db	30,16,191

				db	192

				db	192

				db	192

				db	48,16,43,16,43,16,48,16,43,16,43,16,48,16,52,16,50,16,43,16,43,16,50,16,43,16,43,16,50,16
				db	53,16,52,16,43,16,43,16,52,16,43,16,43,16,52,16,43,16,50,16,43,16,43,16,50,16,53,16,52,16
				db	50,16,52,16,48,16,43,16,43,16,48,16,43,16,43,16,48,16,52,16,50,16,43,16,43,16,50,16,43,16
				db	43,16,50,16,53,16,52,16,43,16,43,16,52,16,43,16,43,16,52,16,55,16,57,16,55,16,53,16,52,16
				db	50,16,52,16,53,16,50,16

				db	36,16,43,16,43,16,36,16,43,16,43,16,36,16,43,16,36,16,40,16,40,16,36,16,40,16,40,16,36,16
				db	40,16,36,16,41,16,41,16,36,16,41,16,41,16,36,16,41,16,43,16,38,16,38,16,43,16,38,16,38,16
				db	43,16,38,16,36,16,43,16,43,16,36,16,43,16,43,16,36,16,43,16,36,16,40,16,40,16,36,16,40,16
				db	40,16,36,16,40,16,36,16,41,16,41,16,36,16,41,16,41,16,36,16,41,16,43,16,38,16,38,16,43,16
				db	38,16,38,16,43,16,38,16

				db	192

				db	192

				db	55,16,48,16,48,16,55,16,48,16,48,16,55,16,48,16,52,16,48,16,48,16,52,16,48,16,48,16,52,16
				db	48,16,53,16,48,16,48,16,53,16,48,16,48,16,53,16,48,16,50,16,43,16,43,16,50,16,43,16,43,16
				db	50,16,43,16,55,16,48,16,48,16,55,16,48,16,48,16,55,16,48,16,52,16,48,16,48,16,52,16,48,16
				db	48,16,52,16,48,16,53,16,48,16,48,16,53,16,48,16,48,16,53,16,48,16,50,16,43,16,43,16,50,16
				db	43,64

				db	192

				db	192

				db	192

				db	30,16,191

				db	192

				db	192

				db	192

				db	55,32,55,32,55,32,55,32,55,32,55,16,55,32,57,32,55,16,53,32,53,32,53,32,53,32,53,32,53,16
				db	53,32,52,32,50,16,55,32,55,32,55,32,55,32,55,32,55,16,55,32,57,32,55,16,53,32,52,16,50,32
				db	52,32,50,16,55,32,52,32,50,32,52,32

				db	192

				db	192

				db	192


	;Instruments
				db	15,9,128

				db	128



			; Exportálva 901 byte

#endasm
//}

#pragma link forward
//{-------------------------- font -------------------------- 
#asm
	qKKF
				db	2	; betű szélesség
				db	9	; betű magasság
	@FntAddrTable
				dw	@fnt1,@fnt2,@fnt3,@fnt4,@fnt5,@fnt6,@fnt7,@fnt8,@fnt9,@fnt10,@fnt11,@fnt12,@fnt13,@fnt14,@fnt15,@fnt16
				dw	@fnt17,@fnt18,@fnt19,@fnt20,@fnt21,@fnt22,@fnt23,@fnt24,@fnt25,@fnt26,@fnt27,@fnt28,@fnt29,@fnt30,@fnt31,@fnt32
				dw	@fnt33,@fnt34,@fnt35,@fnt36,@fnt37,@fnt38,@fnt39,@fnt40,@fnt41,@fnt42,@fnt43,@fnt44,@fnt45,@fnt46,@fnt47,@fnt48
				dw	@fnt49,@fnt50,@fnt51,@fnt52,@fnt53,@fnt54,@fnt55,@fnt56,@fnt57,@fnt58,@fnt59,@fnt60,@fnt61,@fnt62,@fnt63,0
				dw	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				dw	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				dw	@fnt97,@fnt98,@fnt99,@fnt100,@fnt101,@fnt102,@fnt103,@fnt104,@fnt105,0,0,0,0,0,0,0
	@fnt1				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	@fnt2				db	0,0,0,0,0,0,85,0,85,0,85,0,0,0,85,0,0,0
	@fnt3				db	0,0,0,0,170,170,170,170,0,0,0,0,0,0,0,0,0,0
	@fnt4				db	0,0,0,0,0,0,170,170,255,170,170,170,255,170,170,170,0,0
	@fnt5				db	0,0,0,0,85,0,255,170,170,0,255,170,0,170,255,170,85,0
	@fnt6				db	0,0,0,0,170,170,0,170,85,0,85,0,170,0,170,170,0,0
	@fnt7				db	0,0,0,0,85,0,170,170,255,0,170,255,170,170,85,85,0,0
	@fnt8				db	0,0,0,0,0,0,85,0,85,0,0,0,0,0,0,0,0,0
	@fnt9				db	0,0,0,0,0,0,0,170,85,0,85,0,85,0,0,170,0,0
	@fnt10				db	0,0,0,0,0,0,85,0,0,170,0,170,0,170,85,0,0,0
	@fnt11				db	0,0,0,0,0,0,0,0,170,170,85,0,170,170,0,0,0,0
	@fnt12				db	0,0,0,0,0,0,0,0,85,0,255,170,85,0,0,0,0,0
	@fnt13				db	0,0,0,0,0,0,0,0,0,0,0,0,85,0,85,0,0,0
	@fnt14				db	0,0,0,0,0,0,0,0,0,0,255,170,0,0,0,0,0,0
	@fnt15				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,85,0,0,0
	@fnt16				db	0,0,0,0,0,0,0,0,0,170,85,0,170,0,0,0,0,0
	@fnt17				db	0,0,0,0,0,0,255,170,170,170,170,170,170,170,255,170,0,0
	@fnt18				db	0,0,0,0,0,0,85,0,255,0,85,0,85,0,255,170,0,0
	@fnt19				db	0,0,0,0,0,0,255,170,0,170,255,170,170,0,255,170,0,0
	@fnt20				db	0,0,0,0,0,0,255,170,0,170,85,170,0,170,255,170,0,0
	@fnt21				db	0,0,0,0,0,0,170,170,170,170,255,170,0,170,0,170,0,0
	@fnt22				db	0,0,0,0,0,0,255,170,170,0,255,170,0,170,255,170,0,0
	@fnt23				db	0,0,0,0,0,0,255,170,170,0,255,170,170,170,255,170,0,0
	@fnt24				db	0,0,0,0,0,0,255,170,170,170,0,170,0,170,0,170,0,0
	@fnt25				db	0,0,0,0,0,0,255,170,170,170,255,170,170,170,255,170,0,0
	@fnt26				db	0,0,0,0,0,0,255,170,170,170,255,170,0,170,255,170,0,0
	@fnt27				db	0,0,0,0,0,0,0,0,85,0,0,0,85,0,0,0,0,0
	@fnt28				db	0,0,0,0,0,0,0,0,85,0,0,0,85,0,85,0,0,0
	@fnt29				db	0,0,0,0,0,0,0,0,0,170,85,0,0,170,0,0,0,0
	@fnt30				db	0,0,0,0,0,0,0,0,255,170,0,0,255,170,0,0,0,0
	@fnt31				db	0,0,0,0,0,0,0,0,85,0,0,170,85,0,0,0,0,0
	@fnt32				db	0,0,0,0,0,0,255,170,0,170,85,170,0,0,85,0,0,0
	@fnt33				db	0,0,0,0,85,0,170,170,170,170,255,170,170,0,255,170,0,0
	@fnt34				db	0,0,0,0,0,0,255,170,170,170,255,170,170,170,170,170,0,0
	@fnt35				db	0,0,0,0,0,0,255,170,170,170,255,0,170,170,255,170,0,0
	@fnt36				db	0,0,0,0,0,0,255,170,170,170,170,0,170,170,255,170,0,0
	@fnt37				db	0,0,0,0,0,0,255,0,170,170,170,170,170,170,255,170,0,0
	@fnt38				db	0,0,0,0,0,0,255,170,170,0,255,0,170,0,255,170,0,0
	@fnt39				db	0,0,0,0,0,0,255,170,170,0,255,0,170,0,170,0,0,0
	@fnt40				db	0,0,0,0,0,0,255,170,170,0,170,170,170,170,255,170,0,0
	@fnt41				db	0,0,0,0,0,0,170,170,170,170,255,170,170,170,170,170,0,0
	@fnt42				db	0,0,0,0,0,0,85,0,85,0,85,0,85,0,85,0,0,0
	@fnt43				db	0,0,0,0,0,0,0,170,0,170,0,170,170,170,255,0,0,0
	@fnt44				db	0,0,0,0,0,0,170,170,170,170,255,0,170,170,170,170,0,0
	@fnt45				db	0,0,0,0,0,0,170,0,170,0,170,0,170,0,255,170,0,0
	@fnt46				db	0,0,0,0,0,0,170,170,255,170,170,170,170,170,170,170,0,0
	@fnt47				db	0,0,0,0,0,0,255,170,170,170,170,170,170,170,170,170,0,0
	@fnt48				db	0,0,0,0,0,0,255,170,170,170,170,170,170,170,255,170,0,0
	@fnt49				db	0,0,0,0,0,0,255,170,170,170,255,170,170,0,170,0,0,0
	@fnt50				db	0,0,0,0,0,0,255,170,170,170,255,170,0,170,0,170,0,0
	@fnt51				db	0,0,0,0,0,0,255,170,170,170,255,0,170,170,170,170,0,0
	@fnt52				db	0,0,0,0,0,0,255,170,170,0,255,170,0,170,255,170,0,0
	@fnt53				db	0,0,0,0,0,0,255,170,85,0,85,0,85,0,85,0,0,0
	@fnt54				db	0,0,0,0,0,0,170,170,170,170,170,170,170,170,255,170,0,0
	@fnt55				db	0,0,0,0,0,0,170,170,170,170,170,170,170,170,255,0,0,0
	@fnt56				db	0,0,0,0,0,0,170,170,170,170,170,170,255,170,170,170,0,0
	@fnt57				db	0,0,0,0,0,0,170,170,170,170,85,0,170,170,170,170,0,0
	@fnt58				db	0,0,0,0,0,0,170,170,170,170,255,170,85,0,85,0,0,0
	@fnt59				db	0,0,0,0,0,0,255,170,0,170,255,170,170,0,255,170,0,0
	@fnt60				db	0,0,0,0,0,0,85,170,85,0,85,0,85,0,85,170,0,0
	@fnt61				db	0,0,0,0,0,0,0,0,170,0,85,0,0,170,0,0,0,0
	@fnt62				db	0,0,0,0,0,0,85,170,0,170,0,170,0,170,85,170,0,0
	@fnt63				db	0,0,0,0,85,0,170,170,170,170,0,0,0,0,0,0,0,0
	@fnt97				db	85,0,85,0,0,0,255,170,170,170,255,170,170,170,170,170,0,0
	@fnt98				db	85,0,85,0,0,0,255,170,170,0,255,0,170,0,255,170,0,0
	@fnt99				db	85,0,85,0,0,0,85,0,85,0,85,0,85,0,85,0,0,0
	@fnt100				db	85,0,85,0,0,0,255,170,170,170,170,170,170,170,255,170,0,0
	@fnt101				db	0,0,170,170,0,0,255,170,170,170,170,170,170,170,255,170,0,0
	@fnt102				db	170,170,170,170,0,0,255,170,170,170,170,170,170,170,255,170,0,0
	@fnt103				db	85,0,85,0,0,0,170,170,170,170,170,170,170,170,255,170,0,0
	@fnt104				db	0,0,170,170,0,0,170,170,170,170,170,170,170,170,255,170,0,0
	@fnt105				db	170,170,170,170,0,0,170,170,170,170,170,170,170,170,255,170,0,0
				endp

#endasm
//}
#pragma link 



//{	Crush_Sound
#asm
	qCrushSound
				db	3
				dw	3000+(15*4096)
				db	3
				dw	1000+(15*4096)
				db	3
				dw	500+(15*4096)
				db	0
#endasm
//}

//{	Crush2_Sound
#asm
	qCrush2Sound
				db	3
				dw	3000+(15*4096)
				db	3
				dw	1000+(15*4096)
				db	0
#endasm
//}


//{	Fall1_Sound
#asm
	qFall1Sound
				db	2
				dw	3723+(15*4096)
				db	0
#endasm
//}

//{	Fall2_Sound
#asm
	qFall2Sound
				db	2
				dw	3823+(15*4096)
				db	0
#endasm
//}

//{	A grafikus munkaasztalból importált adatok.
#pragma rem START_GFX_DATA

#asm   /* A grafikus munkaasztalból importált adatok. NE VÁLTOZTASD MEG! */

	qGraphicsBaseAddr
	GfxBaseAddr		dw	SpriteCount-GfxBaseAddr,0,0

	;{   Sprite-ok adatai (Automatikusan beemelve!)
	SpriteCount		db 28
	SpriteIndexArray
				dw	0,242,484,726,968,1210,1452,1694,1936,2178,2420,2662,2904,3146,3388,3630,3872,4114,4356,4598,4840,5082,5324,5566,5808,6050,6292,6298

	SpriteDataBuffer	ds	0,0
	DecompressBuffer	ds	0,0

	SpriteBaseAddr
	qblue
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,83,163,3,3,3,3,3,67,195,211,3,3,3
				db	3,3,193,195,195,163,3,3,3,67,195,195,195,211,3,3,3,193,195,195,195,195,163,3,3,195,195,243,243,195,163,3
				db	3,195,211,243,243,227,163,3,66,195,215,251,243,227,243,3,67,195,255,251,243,243,211,3,66,195,247,251,247,251,211,3
				db	67,211,243,243,247,251,211,3,66,211,243,243,243,243,211,3,66,195,243,243,243,227,211,3,66,195,211,243,243,211,243,3
				db	3,193,195,195,195,211,163,3,3,192,195,211,243,243,163,3,3,192,192,195,211,227,163,3,3,66,193,193,227,211,3,3
				db	3,3,192,195,195,163,3,3,3,3,66,193,194,3,3,3,3,3,3,192,129,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qyellow
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,255,3,3,3,3,3,3,87,254,171,3,3,3,3,3,87,252,188,3,3,3,3,3,255,252,188,3,3,3
				db	3,3,254,253,252,41,3,3,3,3,254,252,254,41,3,3,3,22,252,252,254,41,3,3,3,22,188,252,254,41,3,3
				db	3,22,252,252,254,188,3,3,3,22,188,252,253,188,3,3,3,124,188,252,253,188,41,3,3,124,124,252,253,188,9,3
				db	3,124,124,252,252,252,41,3,3,92,124,252,252,252,41,3,3,92,124,252,252,124,9,3,3,92,60,252,188,252,41,3
				db	3,92,60,60,60,252,9,3,3,92,188,60,60,252,41,3,3,28,188,60,124,188,9,3,3,22,252,252,252,60,9,3
				db	3,6,124,252,252,44,3,3,3,3,60,60,60,9,3,3,3,3,6,12,12,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qred
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,13,3,3,3,3,3,3,6,76,11,3,3,3,3,3,6,204,137,3,3,3,3,3,12,141,141,3,3,3,3
				db	3,12,204,141,3,3,3,3,3,12,78,204,3,3,3,3,3,12,15,141,3,3,3,3,3,12,141,204,11,3,3,3
				db	3,12,204,204,11,3,3,3,3,6,76,204,141,3,3,3,3,6,76,204,78,11,3,3,3,6,12,204,204,15,3,3
				db	3,3,12,76,204,204,3,3,3,3,6,76,204,204,11,3,3,3,6,12,204,204,14,3,3,3,3,12,12,204,14,3
				db	3,3,3,12,76,76,14,3,3,3,3,6,12,76,12,3,3,3,3,3,12,12,12,3,3,3,3,3,6,12,12,3
				db	3,3,3,3,3,12,9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qbrawn
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,86,169,3,3,3
				db	3,3,3,252,60,9,3,3,3,3,3,188,60,41,3,3,3,3,86,60,60,41,3,3,3,3,86,60,60,44,3,3
				db	3,3,22,60,188,60,3,3,3,3,188,124,252,44,3,3,3,3,60,172,92,60,3,3,3,3,60,188,12,188,3,3
				db	3,3,60,188,44,60,3,3,3,3,28,28,44,188,3,3,3,3,60,60,44,60,3,3,3,3,28,28,44,60,3,3
				db	3,3,60,12,12,188,3,3,3,3,28,172,12,188,3,3,3,3,28,252,252,60,3,3,3,3,28,124,188,60,3,3
				db	3,3,22,60,60,44,3,3,3,3,22,60,60,44,3,3,3,3,6,60,60,9,3,3,3,3,3,60,60,9,3,3
				db	3,3,3,22,41,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qpurple
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,195,131,67,131,3,3
				db	3,67,135,15,195,195,3,3,3,67,15,135,135,75,3,3,3,67,15,75,15,75,3,3,3,67,31,195,75,75,131,3
				db	3,15,15,75,135,15,131,3,3,195,195,195,195,75,135,3,3,135,15,151,107,195,75,11,67,135,195,15,31,135,15,131
				db	67,15,107,15,15,195,135,131,67,15,195,135,15,135,31,131,67,15,75,15,107,135,15,131,67,15,135,135,135,135,15,131
				db	7,135,75,75,195,135,195,11,3,195,195,135,135,75,195,3,3,195,31,195,15,47,75,3,3,75,135,107,31,31,75,3
				db	3,75,75,75,75,135,75,3,3,67,15,75,15,15,195,3,3,67,15,75,135,135,131,3,3,67,15,75,75,195,11,3
				db	3,7,195,135,195,135,11,3,3,3,15,11,75,135,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qgreen
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,48,48,48,48,33,3,3,18,240,240,240,240,176,3,3,18,240,240,240,240,176,3
				db	3,18,112,240,240,240,48,3,3,18,48,240,48,48,48,3,3,18,58,240,240,176,58,3,3,18,112,240,240,240,48,3
				db	3,18,112,240,240,240,176,3,3,18,112,255,255,240,176,3,3,18,48,255,240,240,176,3,3,18,53,112,240,240,176,3
				db	3,18,48,240,240,255,176,3,3,18,48,112,240,240,176,3,3,18,112,240,240,240,176,3,3,66,48,112,176,240,176,3
				db	3,18,112,240,240,48,48,3,3,18,48,48,48,53,48,3,3,66,53,53,63,48,48,3,3,18,48,48,48,48,48,3
				db	3,66,48,48,48,48,96,3,3,66,144,144,96,48,192,3,3,3,192,192,192,192,129,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qdisco
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,128,192,128,129,3,3,3,3,192,96,128,192,3,3,3,66,192,96,192,192,129,3
				db	3,66,192,192,64,234,192,3,3,192,132,192,66,72,192,3,3,192,132,132,192,64,192,3,3,192,192,148,12,144,170,129
				db	66,192,192,64,132,144,128,129,66,144,192,72,192,192,132,129,66,144,192,66,192,192,192,192,66,192,192,192,192,64,192,192
				db	192,192,72,192,12,64,72,192,192,132,132,104,72,234,12,192,192,132,148,104,192,72,72,192,148,132,72,104,192,213,192,192
				db	148,213,192,192,192,128,213,192,148,213,192,192,72,132,213,192,192,192,192,72,66,192,128,192,192,192,192,72,192,12,192,192
				db	66,192,192,192,192,12,192,129,66,129,192,192,72,192,66,129,66,129,192,192,191,104,66,129,66,192,192,72,234,104,66,129
				db	3,192,192,192,192,192,192,3,3,66,148,192,128,192,192,3,3,66,192,132,192,192,192,3,3,66,192,192,192,192,129,3
				db	3,3,192,192,192,192,3,3,3,3,192,192,192,192,3,3
	qcsik
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,2,0,0,1,3,3,3,3,0,0,0,0,3,3,3,2,0,0,0,0,1,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,240,240,240,240,240,240,3,3,240,240,240,240,240,240,3,2,0,0,0,0,0,0,1,2,0,0,0,0,0,0,1
				db	6,12,12,12,12,12,12,9,6,12,12,12,12,12,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	6,12,12,12,12,12,12,9,6,12,12,12,12,12,12,9,2,0,0,0,0,0,64,1,2,0,0,0,0,0,0,1
				db	3,240,240,240,240,240,240,3,3,240,240,240,240,240,240,3,3,0,0,0,0,0,0,3,3,2,0,0,0,0,1,3
				db	3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3
	qstar
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,171,3,3,3,3,3,3,3,169,3,3,3,3,3,3,3,125,3,3,3
				db	3,3,3,86,124,3,3,3,3,3,3,86,124,3,3,3,3,3,3,188,124,3,3,3,3,3,3,188,252,171,3,3
				db	3,3,3,188,252,169,3,3,3,3,126,60,188,253,171,3,3,86,252,60,188,252,252,171,3,126,188,60,188,60,252,169
				db	3,188,60,124,252,252,252,169,3,252,62,124,252,252,252,43,3,86,63,60,252,252,252,3,3,86,188,60,124,252,189,3
				db	3,3,60,60,61,252,189,3,3,3,60,60,124,126,43,3,3,3,188,60,124,189,3,3,3,3,23,60,124,252,3,3
				db	3,3,126,60,60,252,43,3,3,3,126,60,60,252,43,3,3,3,254,124,124,252,169,3,3,3,252,188,124,124,169,3
				db	3,3,252,125,188,60,169,3,3,3,188,124,86,60,169,3,3,3,188,169,3,62,169,3,3,3,254,3,3,23,43,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qstar2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,169,3,3,3,3,3,3,3,169,3,3,3
				db	3,3,3,3,252,3,3,3,3,3,3,86,126,3,3,3,3,3,3,86,126,3,3,3,3,3,3,189,126,3,3,3
				db	3,3,3,189,63,169,3,3,3,3,3,189,63,169,3,3,3,3,189,63,63,63,169,3,3,86,63,63,63,63,63,169
				db	3,189,63,63,63,63,63,169,3,189,63,63,63,63,63,169,3,189,63,63,63,63,63,169,3,86,63,63,63,63,63,169
				db	3,86,63,63,63,63,126,3,3,86,63,63,63,63,126,3,3,3,189,63,63,63,169,3,3,3,86,63,63,126,3,3
				db	3,3,86,63,63,126,3,3,3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3
				db	3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3,3,3,189,126,86,63,169,3,3,3,189,169,3,189,169,3
				db	3,3,252,3,3,86,169,3,3,3,3,3,3,3,3,3
	qbomb
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,22,28,3,3,3,3,3,3,124,92,169,3,3,3,60,86,44,28,60,190,3
				db	6,172,28,44,124,252,188,41,22,172,28,60,124,252,60,41,86,12,60,44,252,252,60,41,22,28,60,60,28,255,190,41
				db	6,60,60,188,44,125,190,169,86,60,252,188,44,28,190,41,6,28,252,253,60,255,60,169,86,60,253,254,60,125,60,169
				db	22,60,253,254,60,93,252,169,22,28,124,254,255,60,60,169,6,28,60,125,255,60,60,169,22,172,60,124,174,93,60,169
				db	6,188,124,252,172,92,60,9,12,60,124,252,172,92,60,169,3,28,124,252,172,92,172,169,3,172,92,252,172,12,92,41
				db	3,172,92,252,252,12,124,41,3,188,124,124,12,92,12,172,3,252,28,60,12,12,12,172,3,188,124,60,60,92,28,60
				db	3,22,60,60,44,60,12,172,3,6,124,60,60,124,41,9,3,3,252,252,188,44,41,3,3,3,86,60,60,60,3,3
				db	3,3,86,44,28,188,3,3,3,3,6,12,3,3,3,3
	q1
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,15,15,7,3,3,3
				db	3,7,63,107,135,63,43,3,3,7,47,107,15,3,3,3,3,7,15,15,15,3,3,3,3,7,47,15,15,63,43,3
				db	3,7,15,15,135,3,3,3,3,23,63,63,23,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,252,254,255,255,3,3,3,3,252,252,252,253,3,3,3,3,124,252,252,252,3,3,3,3,252,252,252,188,3,3
				db	3,3,124,252,60,252,3,3,3,3,124,252,252,188,3,3,3,3,124,188,60,188,3,3,3,3,60,252,252,188,3,3
				db	3,3,124,60,60,60,3,3,3,3,22,41,22,41,3,3,3,3,23,3,3,43,3,3,3,3,23,3,3,43,3,3
				db	3,3,23,3,3,43,3,3,3,3,23,3,3,43,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q3
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,9,3,3,3,3,3,3,6,61,3,3,3
				db	3,3,3,12,60,43,3,3,3,3,3,28,60,41,3,3,3,3,3,12,60,41,3,3,3,3,3,12,28,43,3,3
				db	3,3,6,12,60,62,3,3,3,3,6,12,28,60,3,3,3,3,23,9,9,61,3,3,3,3,23,3,3,23,3,3
				db	3,3,43,3,3,3,43,3,3,23,3,3,3,3,23,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q4
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,66,129,3,3,3,3,3,3,66,43,3,3,3,3,3,3,23,43,3,3,3
				db	3,3,3,23,129,3,3,3,3,3,3,63,63,3,3,3,3,3,66,192,192,129,3,3,3,3,66,192,192,129,3,3
				db	3,3,3,63,63,3,3,3,3,3,3,63,63,3,3,3,3,3,3,63,63,3,3,3,3,3,3,63,63,3,3,3
				db	3,3,3,63,63,3,3,3,3,3,3,63,63,3,3,3,3,3,3,63,63,3,3,3,3,3,23,63,63,43,3,3
				db	3,3,66,192,192,129,3,3,3,3,3,63,63,3,3,3,3,3,3,66,129,3,3,3,3,3,3,23,129,3,3,3
				db	3,3,3,23,129,3,3,3,3,3,3,23,129,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q5
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,66,3,192,23,3,3
				db	3,3,66,192,63,192,3,3,3,3,66,149,192,106,3,3,3,192,192,192,192,192,192,3,3,3,66,192,192,192,3,3
				db	3,3,66,192,192,192,3,3,3,3,66,3,192,66,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q6
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,23,63,53,63,3,3
				db	3,3,23,58,33,3,3,3,3,3,23,48,33,3,3,3,3,3,23,58,33,3,3,3,3,3,23,48,33,3,3,3
				db	3,3,23,58,33,3,3,3,3,3,23,48,33,3,3,3,3,3,18,48,33,3,3,3,3,3,23,48,33,3,3,3
				db	3,3,18,48,33,3,3,3,3,3,18,48,33,3,3,3,3,3,18,63,33,3,3,3,3,3,18,48,53,63,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qdisco2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,128,192,128,129,3,3,3,3,192,96,128,192,3,3,3,66,192,96,192,192,129,3
				db	3,66,192,192,64,234,192,3,3,192,132,192,66,72,192,3,3,192,132,132,192,64,192,3,3,192,192,148,12,144,170,129
				db	66,192,192,64,132,144,128,129,66,144,192,72,192,192,132,129,66,144,192,66,192,192,192,192,66,192,192,192,192,64,192,192
				db	192,192,72,192,12,64,72,192,192,132,132,104,72,234,12,192,192,132,148,104,192,72,72,192,148,132,72,104,192,213,192,192
				db	148,213,192,192,192,128,213,192,148,213,192,192,72,132,213,192,192,192,192,72,66,192,128,192,192,192,192,72,192,12,192,192
				db	66,192,192,192,192,12,192,129,66,129,192,192,72,192,66,129,66,129,192,192,191,104,66,129,66,192,192,72,234,104,66,129
				db	3,192,192,192,192,192,192,3,3,66,148,192,128,192,192,3,3,66,192,132,192,192,192,3,3,66,192,192,192,192,129,3
				db	3,3,192,192,192,192,3,3,3,3,192,192,192,192,3,3
	qcsik2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,2,0,0,1,3,3,3,3,0,0,0,0,3,3,3,2,0,0,0,0,1,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,240,240,240,240,240,240,3,3,240,240,240,240,240,240,3,2,0,0,0,0,0,0,1,2,0,0,0,0,0,0,1
				db	6,12,12,12,12,12,12,9,6,12,12,12,12,12,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	6,12,12,12,12,12,12,9,6,12,12,12,12,12,12,9,2,0,0,0,0,0,64,1,2,0,0,0,0,0,0,1
				db	3,240,240,240,240,240,240,3,3,240,240,240,240,240,240,3,3,0,0,0,0,0,0,3,3,2,0,0,0,0,1,3
				db	3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3
	qstar22
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,171,3,3,3,3,3,3,3,169,3,3,3,3,3,3,3,125,3,3,3
				db	3,3,3,86,124,3,3,3,3,3,3,86,124,3,3,3,3,3,3,188,124,3,3,3,3,3,3,188,252,171,3,3
				db	3,3,3,188,252,169,3,3,3,3,126,60,188,253,171,3,3,86,252,60,188,252,252,171,3,126,188,60,188,60,252,169
				db	3,188,60,124,252,252,252,169,3,252,62,124,252,252,252,43,3,86,63,60,252,252,252,3,3,86,188,60,124,252,189,3
				db	3,3,60,60,61,252,189,3,3,3,60,60,124,126,43,3,3,3,188,60,124,189,3,3,3,3,23,60,124,252,3,3
				db	3,3,126,60,60,252,43,3,3,3,126,60,60,252,43,3,3,3,254,124,124,252,169,3,3,3,252,188,124,124,169,3
				db	3,3,252,125,188,60,169,3,3,3,188,124,86,60,169,3,3,3,188,169,3,62,169,3,3,3,254,3,3,23,43,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qstar23
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,169,3,3,3,3,3,3,3,169,3,3,3
				db	3,3,3,3,252,3,3,3,3,3,3,86,126,3,3,3,3,3,3,86,126,3,3,3,3,3,3,189,126,3,3,3
				db	3,3,3,189,63,169,3,3,3,3,3,189,63,169,3,3,3,3,189,63,63,63,169,3,3,86,63,63,63,63,63,169
				db	3,189,63,63,63,63,63,169,3,189,63,63,63,63,63,169,3,189,63,63,63,63,63,169,3,86,63,63,63,63,63,169
				db	3,86,63,63,63,63,126,3,3,86,63,63,63,63,126,3,3,3,189,63,63,63,169,3,3,3,86,63,63,126,3,3
				db	3,3,86,63,63,126,3,3,3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3
				db	3,3,189,63,63,63,169,3,3,3,189,63,63,63,169,3,3,3,189,126,86,63,169,3,3,3,189,169,3,189,169,3
				db	3,3,252,3,3,86,169,3,3,3,3,3,3,3,3,3
	qbomb2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,83,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,83,3,3,163,3
				db	23,3,3,83,3,3,163,3,83,171,3,243,3,23,163,3,3,163,3,243,3,87,3,3,3,3,83,251,3,247,3,3
				db	3,3,83,251,3,183,3,3,3,3,87,183,3,83,163,3,3,3,247,163,3,3,163,3,3,3,247,163,163,3,163,3
				db	171,83,255,243,163,3,163,3,3,83,255,247,171,3,3,3,3,83,255,255,163,3,3,3,3,23,243,247,127,3,3,3
				db	3,3,3,247,247,3,3,3,3,3,83,251,83,3,43,3,3,83,83,251,83,171,163,3,83,163,83,171,3,163,3,3
				db	83,3,87,163,3,3,3,3,83,3,247,3,3,3,3,3,23,3,247,83,171,3,3,3,3,3,247,83,171,3,87,3
				db	3,3,243,83,171,3,83,3,3,3,163,87,43,3,83,3,3,83,3,83,3,3,3,3,3,83,3,83,3,3,3,3
				db	3,83,3,3,3,3,3,3,3,183,3,3,3,3,3,3
	qProbaSprite
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	qkeret
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204
				db	204,0,0,0,0,0,0,204,204,0,0,0,0,0,0,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204
				db	204,204,204,204,204,204,204,204,204,204,204,204,204,204,204,204
	qkeret2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255
				db	255,0,0,0,0,0,0,255,255,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
	qkeret3
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3
				db	3,0,0,0,0,0,0,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qministar
				db	1			; A sprite szélessége byte-okban
				db	4			; A sprite magassága
				db	252,252,252,252
	qkezdo3
				db	46			; A sprite szélessége byte-okban
				db	29			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,67,215,171,215
				db	171,3,195,255,3,67,215,3,215,171,195,215,255,3,67,255,171,3,67,215,171,255,171,195,215,255,3,67,255,67,255,171
				db	3,215,171,3,67,255,67,255,67,171,67,195,131,195,171,67,195,195,171,67,195,171,195,171,195,195,195,171,67,215,171,3
				db	67,195,131,195,171,195,195,195,171,67,215,67,215,171,67,195,255,3,67,195,67,215,67,131,67,195,194,195,131,67,195,195
				db	171,67,195,171,195,171,195,195,195,171,67,195,171,3,66,195,194,195,131,195,195,195,131,67,215,67,195,171,195,195,195,171
				db	67,195,67,215,67,131,67,195,194,195,131,195,195,195,131,67,195,171,195,171,195,215,195,215,67,195,171,3,66,195,194,195
				db	131,195,195,195,215,67,215,67,195,171,195,195,195,131,67,195,67,215,67,131,67,195,194,195,3,195,215,195,215,67,195,171
				db	195,171,195,171,195,215,67,195,131,3,66,195,195,195,3,195,195,67,195,67,215,67,195,171,193,195,195,131,67,195,67,215
				db	66,131,67,195,195,195,3,195,131,193,215,67,195,171,195,171,195,171,195,215,67,195,131,3,66,195,195,195,3,195,131,67
				db	195,67,215,67,195,171,195,131,195,131,67,195,67,195,66,131,66,195,195,195,3,195,131,195,215,67,195,131,193,171,195,131
				db	195,215,67,195,131,3,66,195,195,195,3,195,171,67,195,67,215,66,195,171,195,131,195,131,67,195,66,215,66,131,66,195
				db	195,195,3,195,131,193,195,67,195,194,195,171,195,131,195,195,66,195,131,3,66,195,195,194,3,195,171,67,195,67,195,67
				db	195,171,193,131,131,131,67,195,66,195,66,131,66,195,195,131,3,195,131,193,215,67,195,195,195,171,195,131,195,215,67,195
				db	131,3,66,195,195,131,3,193,171,67,195,67,195,66,195,131,193,215,3,3,66,195,66,195,66,131,66,195,195,131,3,193
				db	131,193,195,67,195,195,195,171,195,131,195,215,66,195,131,3,66,195,195,3,3,195,215,195,195,67,195,66,195,131,193,195
				db	3,3,67,195,195,195,66,131,66,195,195,3,3,193,131,193,195,67,195,195,195,171,195,131,195,195,67,195,131,3,66,195
				db	194,3,3,195,195,195,131,67,195,66,195,131,193,195,171,3,66,195,195,195,66,131,66,195,195,3,3,193,131,193,195,67
				db	195,195,195,171,195,131,195,215,66,195,131,3,66,195,131,3,3,193,195,195,129,67,195,67,195,131,66,195,215,3,66,195
				db	195,195,66,131,66,195,195,3,3,193,131,193,195,67,195,195,195,171,195,131,193,195,66,195,131,3,66,195,131,3,3,195
				db	195,195,3,67,195,66,195,131,3,195,195,171,66,195,195,195,66,131,66,195,195,171,3,193,131,193,195,67,195,195,195,171
				db	195,131,193,195,66,195,131,3,66,195,215,3,3,195,195,195,131,67,195,66,195,131,3,193,195,171,66,195,195,195,66,131
				db	66,195,195,215,3,193,131,193,195,66,195,195,195,171,195,131,193,195,66,195,131,3,66,195,195,3,3,193,195,195,131,67
				db	195,66,195,131,3,67,195,131,66,195,66,195,66,131,66,195,195,215,3,193,131,193,195,66,195,195,195,171,195,131,193,195
				db	66,195,131,3,66,195,195,195,3,193,195,195,195,67,195,66,195,131,3,3,195,171,66,195,66,195,66,131,66,195,195,195
				db	3,193,131,193,195,67,195,195,195,131,195,131,193,195,66,195,131,3,66,195,195,195,3,193,195,195,195,67,195,66,195,131
				db	215,171,195,131,66,195,66,195,66,131,66,195,195,195,3,193,129,193,195,66,195,195,195,131,195,131,193,195,66,195,131,3
				db	66,195,195,195,3,193,194,195,195,67,194,66,195,131,195,171,195,171,66,195,66,195,66,131,66,195,195,195,3,193,131,193
				db	195,66,195,193,195,131,195,131,193,195,66,195,131,3,66,195,195,195,3,193,194,193,195,67,195,66,195,131,195,131,195,131
				db	66,195,66,195,66,131,66,195,195,195,131,193,129,193,195,67,195,67,195,131,195,129,193,195,66,195,131,3,66,195,195,195
				db	131,193,131,66,195,67,194,66,195,131,195,131,195,131,66,195,66,195,3,3,66,195,195,195,131,193,194,195,195,66,195,66
				db	195,131,195,194,195,195,66,195,131,3,66,195,195,195,131,193,131,66,195,66,195,193,195,129,193,131,195,131,66,195,66,195
				db	67,171,66,195,194,195,131,192,195,195,131,66,195,66,195,131,195,195,195,194,66,195,131,3,66,195,194,195,131,193,131,66
				db	195,66,193,195,195,3,193,131,195,171,66,195,66,195,67,131,66,195,194,195,131,66,195,195,131,66,195,66,195,131,195,195
				db	195,131,66,195,131,3,66,195,194,195,131,193,131,67,195,3,193,195,195,3,193,195,195,171,66,195,66,195,66,131,66,193
				db	131,193,131,66,193,195,129,66,195,66,193,131,194,195,195,129,66,193,131,3,66,193,131,193,131,192,131,66,195,3,192,195
				db	194,3,66,195,195,171,66,195,66,193,66,131,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3

	;}
	;{   A Scene-ek adatai (Automatikusan beemelve!)
	SceneCount		db 	0		; Érvénytelen adatok, csak azért kellenek, hogy a dt_80lib beforduljon
	SceneIndexArray
				dw	0
	SceneBaseAddr
				db	0
	;}


#endasm
#pragma rem END_GFX_DATA
//}


