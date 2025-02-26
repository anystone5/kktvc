#options
#define DB_TILT_EXTRA_WIDTH
#define DB_TILT_MIRROR
#endoptions

//{	Exportált sprite indexek
#pragma rem START_GFX_DEFINES		// NE VÁLTOZTASD!

#define SPR_BLUE	0
#define SPR_YELLOW	1
#define SPR_RED	2
#define SPR_BRAWN	3
#define SPR_PURPLE	4
#define SPR_GREEN	5
#define SPR_DISZKO	6
#define SPR_CSIK	7
#define SPR_STAR	8
#define SPR_STAR2	9
#define SPR_BOMB	10
#define SPR_1	11
#define SPR_2	12
#define SPR_3	13
#define SPR_4	14
#define SPR_5	15
#define SPR_6	16
#define SPR_KONDIBOMB	17
#define SPR_KONDICSIK	18
#define SPR_KONDICSILL	19
#define SPR_KONDICSILLQ	20
#define SPR_BOMB2	21
#define SPR_PROBASPRITE	22
#define SPR_KERET	23
#define SPR_KERET2	24
#define SPR_KERET3	25
#define SPR_MINISTAR	26
#define SPR_KEZDO3	27

#pragma rem END_GFX_DEFINES

//}

#define ROBOT_BACK_SIZE 66
char *backPtr;

#ifdef EP128
	#define GFX_COLOR_RED 1
	#define GFX_COLOR_YELLOW 2
	#define GFX_COLOR_WHITE 7
	#define GFX_COLOR_BLACK 0
	#define GFX_COLOR_DARKRED 9 
	#define GFX_COLOR_DARKBLUE 12
	#define GFX_COLOR_GRAY 15
	#define GFX_COLOR_DARKPURPLE 5
#endif

#ifdef TVC
	#define GFX_COLOR_RED COLOR_RED
	#define GFX_COLOR_YELLOW COLOR_YELLOW
	#define GFX_COLOR_WHITE COLOR_WHITE
	#define GFX_COLOR_BLACK COLOR_BLACK
	#define GFX_COLOR_DARKRED COLOR_DARKRED
	#define GFX_COLOR_DARKBLUE COLOR_DARKBLUE
	#define GFX_COLOR_GRAY COLOR_GRAY
	#define GFX_COLOR_DARKPURPLE COLOR_DARKPURPLE
#endif

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
	int SprInd;		// (*) A sprite indexe az exportált munkamenetben
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
					{0,20,50,100,5,5,20,5,1},
					{0,20,50,300,6,6,30,6,1}
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

int music;

//}

//{-------------------------- MAIN --------------------------------
main()
{
	int i;

	//for (i=0;i<36;i++) levels[i].score=100;

	music=1;	
	SetBorder(GFX_COLOR_DARKBLUE);
	DbInitFont(KKF);
	DbInitGameLib(2, gameObjects, gIndex2, SN);
	DbPageFullRamVid();
	DbAssignRenderToVideo();
	DbRandomize();
	DbSetFontParam(FNT_COLOR, GFX_COLOR_WHITE); 
	DbSetFontParam(FNT_BACKCOLOR, GFX_COLOR_DARKBLUE);  

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
	DbFillBox(0,0,64,255,GFX_COLOR_DARKBLUE);
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
	DrawSprite2(9,42,SPR_KEZDO3,59);
	DrawSprite2(8,85,SPR_BLUE+gamemode*11,59);
	DrawSprite2(16,85,SPR_YELLOW+gamemode*11,59);
	DrawSprite2(24,85,SPR_RED+gamemode*11,59);
	DrawSprite2(32,85,SPR_BRAWN+gamemode*11,59);
	DrawSprite2(40,85,SPR_PURPLE+gamemode*11,59);
	DrawSprite2(48,85,SPR_GREEN+gamemode*11,59);
	DrawCoolString(4, 230, "C - CREDITS    SPACE - START", 5);

	ptr = gameObjects;
 
	DbCopyToFullScreen();
	//DrawCoolString(18, 75, "PORTED EDITION", 10);

	DbSetFontParam(FNT_COLOR, GFX_COLOR_DARKPURPLE); 
	DbDrawStrEx(18, 75, "PORTED EDITION");

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
		if(IsKeyDown(KEY_C) ) {c=1; break;}
		if(IsKeyDown(KEY_SPACE)) {break;}
		//DbRender();
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
	char cp,op,np,dp,ap;

	cp=0;
	op=0;
	np=0;
	dp=0;
	ap=0;

	ClearScreen();

	DrawCoolString(22,0, "KONDI KRUSH!", 1);
	DrawCoolString(0,40, "MADE BY ANYSTONE", 1);
	DrawCoolString(0,80, "GFX: NORBICSEK", 1);
	DrawCoolString(0,100, "MUSIC: REI AND ANYSTONE", 1);
	DrawCoolString(0,120, "POWERED BY DEVTOOL", 1);
	DrawCoolString(26,220, "ANYSTONE GAMES 2022", 1);
	DrawCoolString(40,230, "(2025.02.26)", 1);

	while(!IsKeyDown(KEY_SPACE)) 
	{
		if(IsKeyDown(KEY_C)) cp=1;
		if(IsKeyDown(KEY_O) && cp==1) op=1; 
		if(IsKeyDown(KEY_N) && op==1) np=1;
		if(IsKeyDown(KEY_D) && np==1) dp=1;
		if(IsKeyDown(KEY_I) && dp==1)  
		{
			gamemode=1;
			DrawCoolString(22,0, "KONDI KRUSH!", 1);
		};
		
		if(IsKeyDown(KEY_A) && cp==1) ap=1; 
		if(IsKeyDown(KEY_N) && ap==1) np=1;
		if(IsKeyDown(KEY_D) && np==1) dp=1;
		if(IsKeyDown(KEY_Y) && dp==1)  
		{
			gamemode=0;
			DrawCoolString(22,0, "KONDI KRUSH!", 1);
		};
	}

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
				DbSetFontParam(FNT_COLOR, GFX_COLOR_WHITE);
			}
			else
			{
				DbSetFontParam(FNT_COLOR, GFX_COLOR_GRAY);
			}

			DbDrawStrEx(11+lx*8,40+ly*30,itos(index));

			if(levels[index].score >= levels[index].star1Score) DrawSprite2(10+lx*8,50+ly*30,SPR_MINISTAR,59);
			if(levels[index].score >= levels[index].star2Score) DrawSprite2(12+lx*8,50+ly*30,SPR_MINISTAR,59);
			if(levels[index].score >= levels[index].star3Score) DrawSprite2(14+lx*8,50+ly*30,SPR_MINISTAR,59);

		}
	}

	DrawSprite(plx+1, ply+1, SPR_KERET, 58);

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

			DrawSprite(olx+1, oly+1, SPR_KERET3, 58);
			DrawSprite(plx+1, ply+1, SPR_KERET, 58);
			
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
		DrawSprite2(8,75,SPR_DISZKO+gamemode*11,59);
		DrawSprite2(18,75,SPR_CSIK+gamemode*11,59);
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
	DrawCooStringPart(x, y, text, textSpeed, GFX_COLOR_DARKBLUE); 
	DrawCooStringPart(x, y, text, textSpeed, GFX_COLOR_DARKRED); 
	DrawCooStringPart(x, y, text, textSpeed, GFX_COLOR_RED); 
	DrawCooStringPart(x, y, text, textSpeed, GFX_COLOR_YELLOW); 
	DrawCooStringPart(x, y, text, textSpeed, GFX_COLOR_WHITE); 
}
//}


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
	DrawSprite2(40, 0,  SPR_STAR2+gamemode*11, 59);
	DrawSprite2(48, 0,  SPR_STAR2+gamemode*11, 59);
	DrawSprite2(56, 0,  SPR_STAR2+gamemode*11, 59);

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
		DrawCoolString(0,0,   " CONDENSATOR (KONDI) MODE ACTIVE! ", 8);
		DrawCoolString(0,230, "   ON CREDITS TYPE CONDI/CANDY!   ", 8);
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
                        candy = SPR_BOMB;
                        break;
                    case ' ':
                        candy = SPR_PROBASPRITE;
                        break;
                    case 'D':
                        candy = SPR_DISZKO;
                        break;
                    case 'X':
                        candy = SPR_CSIK;
                        break;
                }

		if(candy!=SPR_PROBASPRITE) candy=candy+gamemode*11;

		DrawSprite(x, y, candy, x+y*maxSizeX);

                if (x == lastposx && y == lastposy) { lastposx = -1; lastposx = -1; };
            }
        }

	DrawSprite(posx, posy, SPR_KERET + moveMode, 58);

	lastposx = posx;
	lastposy = posy;
	
	for(i=0;i<40;i++)
	{
		lastDrawnlevel[i] = actualLevel[i];
	}
	
	//if (withWait) Wait(fast);

	if(levelScore>=levels[currentIndex].star1Score) DrawSprite2(40, 0,  SPR_STAR+gamemode*11, 59);
	if(levelScore>=levels[currentIndex].star2Score) DrawSprite2(48, 0,  SPR_STAR+gamemode*11, 59);
	if(levelScore>=levels[currentIndex].star3Score) DrawSprite2(56, 0,  SPR_STAR+gamemode*11, 59);
	DbDrawStrEx(12,0, itos(levelScore));
	space = itos(lap);
	DbDrawStrEx(33,0, strcat(space, " "));
}
//}


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


//{-------------------------- DrawSprite2 --------------------------------
DrawSprite2(int x, int y, int candy, int index)
{
	gIndex = DbInitGameObject(ptr,x,y,candy,GOFLG_VISIBLE, DbSprite16c16Mask,0,0);
	
	DbClipSprite(gIndex);
	DbDrawSprite(gIndex);
}
//}

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







//{	 Font adatok: qKKF
#asm	/* NE VÁLTOZTASD MEG! */
	qKKF
				db	2	; betű szélesség
				db	9	; betű magasság
				db	105+32	; karakter tábla mérete
	@FntAddrTable
				dw	@fnt1,@fnt2,@fnt3,@fnt4,@fnt5,@fnt6,@fnt7,@fnt8,@fnt9,@fnt10,@fnt11,@fnt12,@fnt13,@fnt14,@fnt15,@fnt16
				dw	@fnt17,@fnt18,@fnt19,@fnt20,@fnt21,@fnt22,@fnt23,@fnt24,@fnt25,@fnt26,@fnt27,@fnt28,@fnt29,@fnt30,@fnt31,@fnt32
				dw	@fnt33,@fnt34,@fnt35,@fnt36,@fnt37,@fnt38,@fnt39,@fnt40,@fnt41,@fnt42,@fnt43,@fnt44,@fnt45,@fnt46,@fnt47,@fnt48
				dw	@fnt49,@fnt50,@fnt51,@fnt52,@fnt53,@fnt54,@fnt55,@fnt56,@fnt57,@fnt58,@fnt59,@fnt60,@fnt61,@fnt62,@fnt63,0
				dw	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				dw	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				dw	@fnt97,@fnt98,@fnt99,@fnt100,@fnt101,@fnt102,@fnt103,@fnt104,@fnt105
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



#ifdef TVC
//{	A grafikus munkaasztalból importált adatok.
#pragma rem START_GFX_DATA

#asm   /* A grafikus munkaasztalból importált adatok. NE VÁLTOZTASD MEG! */

	qGraphicsBaseAddr
	qGfxBaseAddr
	GfxBaseAddr		dw	SpriteCount-GfxBaseAddr,0,0

	;{   Sprite-ok adatai (Automatikusan beemelve!)
	SpriteCount		dw	28
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
				db	67,195,243,243,247,251,211,3,66,211,243,251,243,243,211,3,66,195,243,247,251,227,211,3,66,195,211,243,243,211,243,3
				db	3,193,195,195,195,211,163,3,3,192,195,211,243,243,163,3,3,192,192,195,211,227,163,3,3,66,193,193,227,211,3,3
				db	3,3,192,195,195,163,3,3,3,3,66,193,194,3,3,3,3,3,3,192,129,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qyellow
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,255,3,3,3,3,3,3,87,254,171,3,3,3,3,3,87,252,188,3,3,3,3,3,255,252,188,3,3,3
				db	3,3,254,253,252,41,3,3,3,3,254,124,254,41,3,3,3,22,252,252,254,41,3,3,3,22,188,124,254,169,3,3
				db	3,22,252,252,254,188,3,3,3,22,188,252,253,188,3,3,3,124,188,252,253,252,41,3,3,124,124,252,253,252,9,3
				db	3,124,60,252,252,254,41,3,3,92,124,252,252,252,41,3,3,92,124,252,252,124,9,3,3,92,60,252,188,252,41,3
				db	3,92,60,60,60,252,9,3,3,92,188,60,60,252,41,3,3,28,188,60,124,188,9,3,3,22,252,252,252,60,9,3
				db	3,6,124,252,252,44,3,3,3,3,60,60,60,9,3,3,3,3,6,12,12,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qred
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,77,3,3,3,3,3,3,6,76,139,3,3,3,3,3,6,204,139,3,3,3,3,3,12,205,137,3,3,3,3
				db	3,76,204,205,3,3,3,3,3,76,206,204,3,3,3,3,3,76,207,205,3,3,3,3,3,12,205,204,139,3,3,3
				db	3,12,204,204,139,3,3,3,3,6,76,204,205,3,3,3,3,6,76,204,206,139,3,3,3,6,12,204,204,207,3,3
				db	3,3,12,76,204,204,3,3,3,3,6,76,204,204,139,3,3,3,6,12,204,204,142,3,3,3,3,12,76,207,142,3
				db	3,3,3,12,76,205,140,3,3,3,3,6,12,204,12,3,3,3,3,3,12,12,12,3,3,3,3,3,6,12,12,3
				db	3,3,3,3,3,12,9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qbrawn
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,86,169,3,3,3
				db	3,3,3,252,60,9,3,3,3,3,3,60,60,41,3,3,3,3,86,60,188,41,3,3,3,3,22,60,60,44,3,3
				db	3,3,22,188,188,60,3,3,3,3,188,124,252,44,3,3,3,3,60,172,92,60,3,3,3,3,60,188,12,188,3,3
				db	3,3,60,188,44,124,3,3,3,3,28,28,44,188,3,3,3,3,60,60,44,124,3,3,3,3,28,28,44,60,3,3
				db	3,3,60,12,12,188,3,3,3,3,28,172,12,188,3,3,3,3,28,252,252,44,3,3,3,3,12,124,188,60,3,3
				db	3,3,22,60,124,44,3,3,3,3,6,60,60,44,3,3,3,3,6,12,28,9,3,3,3,3,3,28,60,9,3,3
				db	3,3,3,6,9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qpurple
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,195,131,67,131,3,3
				db	3,67,199,15,195,195,3,3,3,67,143,135,215,75,3,3,3,67,15,75,159,75,3,3,3,67,31,195,75,75,131,3
				db	3,15,15,75,135,47,131,3,3,195,195,195,195,75,135,3,3,135,15,215,235,195,203,11,67,135,195,143,31,199,15,131
				db	67,143,107,47,15,195,175,131,67,15,195,135,15,135,31,131,67,15,75,15,107,135,15,131,67,15,135,135,135,135,15,131
				db	7,135,75,75,195,135,195,11,3,195,195,135,135,75,195,3,3,195,223,195,95,47,75,3,3,75,135,107,31,31,75,3
				db	3,75,75,75,75,135,75,3,3,67,15,75,15,15,195,3,3,67,15,75,135,135,131,3,3,67,15,75,75,195,11,3
				db	3,7,195,135,195,135,11,3,3,3,15,11,75,135,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qgreen
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,48,48,48,48,33,3,3,18,112,240,240,240,176,3,3,18,240,240,240,240,176,3
				db	3,18,112,240,240,240,48,3,3,18,48,240,48,48,48,3,3,18,176,240,240,176,176,3,3,18,112,240,240,240,48,3
				db	3,18,112,240,240,240,176,3,3,18,112,255,255,240,176,3,3,18,48,255,240,240,176,3,3,18,117,112,240,240,176,3
				db	3,18,48,240,240,245,186,3,3,18,48,112,240,240,176,3,3,18,112,240,240,240,176,3,3,66,48,112,176,240,176,3
				db	3,18,112,240,240,48,48,3,3,18,48,48,48,112,48,3,3,66,112,112,240,48,48,3,3,18,48,48,48,48,48,3
				db	3,66,48,48,48,48,96,3,3,66,144,144,96,48,192,3,3,3,192,192,192,192,129,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qdiszko
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,70,204,204,3,3,3,3,3,140,89,204,137,3,3,3,66,12,89,76,76,3,3,3,132,12,12,12,36,137,3
				db	3,132,134,12,12,36,137,3,3,12,134,12,12,12,9,3,3,4,12,12,12,140,76,3,66,13,12,36,12,12,140,3
				db	66,13,12,36,73,12,12,3,66,132,12,12,73,12,134,137,132,12,12,12,12,12,134,137,132,166,12,13,12,12,12,9
				db	128,166,12,13,24,12,12,9,132,12,12,12,24,12,140,137,66,132,12,12,12,12,12,3,66,12,36,12,12,89,76,3
				db	66,132,36,14,12,89,12,3,66,12,12,14,12,12,76,3,3,132,12,12,12,12,9,3,3,132,132,12,14,12,9,3
				db	3,192,12,12,14,12,9,3,3,66,192,132,4,12,3,3,3,3,192,12,12,129,3,3,3,3,66,192,192,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qcsik
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,127,3,3,3,3,3,3,23,255,43,3,3,3,3
				db	3,23,255,171,3,3,3,3,3,29,255,191,3,3,3,3,3,76,204,140,3,3,3,3,3,76,205,204,3,3,3,3
				db	3,76,207,204,3,3,3,3,3,29,255,255,43,3,3,3,3,12,255,255,171,3,3,3,3,6,255,255,191,3,3,3
				db	3,6,76,204,204,9,3,3,3,6,76,204,204,140,3,3,3,3,12,204,204,140,3,3,3,3,6,127,255,255,43,3
				db	3,3,6,63,255,255,191,3,3,3,3,29,127,255,191,3,3,3,3,12,204,205,142,3,3,3,3,6,76,205,142,3
				db	3,3,3,3,12,204,140,3,3,3,3,3,6,255,191,3,3,3,3,3,3,29,43,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
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
				db	3,7,63,59,39,63,43,3,3,7,47,59,15,3,3,3,3,7,15,15,15,3,3,3,3,7,47,15,15,63,43,3
				db	3,7,15,15,39,3,3,3,3,23,63,63,23,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
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
				db	3,3,124,60,60,60,3,3,3,3,22,41,22,41,3,3,3,3,2,3,3,1,3,3,3,3,23,3,3,43,3,3
				db	3,3,23,3,3,43,3,3,3,3,23,3,3,43,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q3
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,9,3,3,3,3,3,3,6,205,3,3,3
				db	3,3,3,12,204,139,3,3,3,3,3,76,204,137,3,3,3,3,3,12,204,137,3,3,3,3,3,12,76,139,3,3
				db	3,3,6,12,204,206,3,3,3,3,6,12,76,204,3,3,3,3,2,9,9,136,3,3,3,3,23,3,3,23,3,3
				db	3,3,43,3,3,3,43,3,3,23,3,3,3,3,23,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q4
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,66,129,3,3,3,3,3,3,66,43,3,3,3,3,3,3,23,43,3,3,3
				db	3,3,3,23,129,3,3,3,3,3,3,63,63,3,3,3,3,3,66,192,192,129,3,3,3,3,66,192,192,129,3,3
				db	3,3,3,63,63,3,3,3,3,3,3,127,63,3,3,3,3,3,3,127,63,3,3,3,3,3,3,127,63,3,3,3
				db	3,3,3,127,63,3,3,3,3,3,3,63,63,3,3,3,3,3,3,191,63,3,3,3,3,3,87,255,191,43,3,3
				db	3,3,66,192,192,129,3,3,3,3,3,63,63,3,3,3,3,3,3,66,129,3,3,3,3,3,3,23,129,3,3,3
				db	3,3,3,23,129,3,3,3,3,3,3,23,129,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q5
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,66,3,192,23,3,3
				db	3,3,66,192,63,192,3,3,3,3,66,149,192,106,3,3,3,63,192,192,192,192,149,3,3,3,66,98,192,192,3,3
				db	3,3,66,145,192,145,3,3,3,3,66,3,192,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	q6
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,87,252,104,63,3,3
				db	3,3,87,184,33,3,3,3,3,3,86,48,33,3,3,3,3,3,86,184,33,3,3,3,3,3,86,48,33,3,3,3
				db	3,3,86,184,41,3,3,3,3,3,86,48,33,3,3,3,3,3,18,48,41,3,3,3,3,3,86,48,33,3,3,3
				db	3,3,18,48,41,3,3,3,3,3,18,48,41,3,3,3,3,3,18,254,33,3,3,3,3,3,22,48,104,63,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qkondibomb
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,23,255,3,3,3,3,3,3,243,83,163,3,3
				db	3,3,43,3,3,43,3,3,3,3,243,3,3,23,3,3,3,87,3,3,3,23,3,3,3,83,3,3,3,3,171,3
				db	3,251,3,3,3,3,163,3,3,3,3,3,9,3,251,3,3,3,3,6,205,3,83,3,3,3,3,12,204,139,3,3
				db	23,163,3,76,204,137,3,163,83,3,3,12,204,137,3,171,87,3,3,12,76,139,3,163,83,3,6,12,204,206,83,171
				db	3,171,6,12,76,204,3,171,3,163,2,9,9,136,3,163,3,3,23,3,3,23,3,3,3,3,43,3,3,3,43,3
				db	3,23,3,3,3,3,23,3,83,3,3,3,3,3,3,3,23,171,87,3,3,83,183,3,3,163,163,247,23,255,3,3
				db	3,23,3,247,243,183,3,3,3,3,3,23,171,243,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qkondicsik
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,123,171,3,3,3,3,3,3,163,127,83,247,43,251,163,3,3,83,247,43,243,243,3
				db	3,3,3,3,3,3,43,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,66,3,192,23,3,3
				db	3,3,66,192,63,192,3,3,3,3,66,149,192,106,3,3,3,63,192,192,192,192,149,3,3,3,66,98,192,192,3,3
				db	3,3,66,145,192,145,3,3,3,3,66,3,192,66,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,251,183,83,23,183,3,3,3,171,251,255,251,83,251,3,3,3,3,23,3,3,43,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qkondicsill
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,14,76,3,3,3,3,3,7,12,12,137,3,3
				db	3,3,15,12,12,76,3,3,3,3,15,12,12,204,3,3,3,3,14,14,204,76,3,3,3,3,14,12,12,140,3,3
				db	3,3,14,12,12,12,3,3,3,3,14,12,12,140,3,3,3,3,14,12,12,140,3,3,3,3,12,12,12,12,3,3
				db	3,3,14,12,12,12,3,3,3,3,12,12,12,204,3,3,3,3,6,12,76,137,3,3,3,3,6,12,12,9,3,3
				db	3,3,14,12,12,76,3,3,3,3,15,14,12,12,3,3,3,3,14,12,12,12,3,3,3,3,7,12,12,11,3,3
				db	3,3,3,14,13,3,3,3,3,3,3,129,66,3,3,3,3,3,3,43,23,3,3,3,3,3,3,43,23,3,3,3
				db	3,3,3,43,23,3,3,3,3,3,3,43,23,3,3,3,3,3,3,43,23,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qkondicsillq
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,66,192,129,3,3,3,3,3,149,63,106,3,3
				db	3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3
				db	3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3
				db	3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3
				db	3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,66,63,63,63,129,3,3,3,3,149,63,106,3,3
				db	3,3,3,66,192,192,3,3,3,3,3,66,3,129,3,3,3,3,3,66,3,129,3,3,3,3,3,66,3,129,3,3
				db	3,3,3,66,3,129,3,3,3,3,3,66,3,129,3,3,3,3,3,66,3,129,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
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
				db	194,3,66,195,195,3,66,195,66,193,66,131,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
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
#endif


#ifdef EP128
//{	A grafikus munkaasztalból importált adatok.

#pragma rem START_GFX_DATA

#asm   /* A grafikus munkaasztalból importált adatok. NE VÁLTOZTASD MEG! */

	qGraphicsBaseAddr
	qGfxBaseAddr
	GfxBaseAddr		dw	SpriteCount-GfxBaseAddr,0,0

	;{   Sprite-ok adatai (Automatikusan beemelve!)
	SpriteCount		dw	28
	SpriteIndexArray
				dw	0,242,484,726,968,1210,1452,1694,1936,2178,2420,2662,2904,3146,3388,3630,3872,4114,4356,4598,4840,5082,5324,5566,5808,6050,6292,6298

	SpriteDataBuffer	ds	0,0
	DecompressBuffer	ds	0,0

	SpriteBaseAddr
	qblue
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,54,57,51,51,51,51,51,50,48,52,51,51,51
				db	51,51,18,48,48,57,51,51,51,50,48,48,48,52,51,51,51,18,48,48,48,48,57,51,51,48,48,60,60,48,57,51
				db	51,48,52,60,60,56,57,51,35,48,116,188,60,56,60,51,50,48,252,188,60,60,52,51,35,48,124,188,124,188,52,51
				db	50,48,60,60,124,188,52,51,35,52,60,188,60,60,52,51,35,48,60,124,188,56,52,51,35,48,52,60,60,52,60,51
				db	51,18,48,48,48,52,57,51,51,3,48,52,60,60,57,51,51,3,3,48,52,56,57,51,51,35,18,18,56,52,51,51
				db	51,51,3,48,48,57,51,51,51,51,35,18,33,51,51,51,51,51,51,3,19,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qyellow
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,252,51,51,51,51,51,51,118,236,185,51,51,51,51,51,118,204,205,51,51,51,51,51,252,204,205,51,51,51
				db	51,51,236,220,204,155,51,51,51,51,236,206,236,155,51,51,51,103,204,204,236,155,51,51,51,103,205,206,236,153,51,51
				db	51,103,204,204,236,205,51,51,51,103,205,204,220,205,51,51,51,206,205,204,220,204,155,51,51,206,206,204,220,204,147,51
				db	51,206,207,204,204,236,155,51,51,198,206,204,204,204,155,51,51,198,206,204,204,206,147,51,51,198,207,204,205,204,155,51
				db	51,198,207,207,207,204,147,51,51,198,205,207,207,204,155,51,51,199,205,207,206,205,147,51,51,103,204,204,204,207,147,51
				db	51,99,206,204,204,203,51,51,51,51,207,207,207,147,51,51,51,51,99,195,195,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qred
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,210,51,51,51,51,51,51,99,194,177,51,51,51,51,51,99,192,177,51,51,51,51,51,195,208,145,51,51,51,51
				db	51,194,192,208,51,51,51,51,51,194,224,192,51,51,51,51,51,194,240,208,51,51,51,51,51,195,208,192,177,51,51,51
				db	51,195,192,192,177,51,51,51,51,99,194,192,208,51,51,51,51,99,194,192,224,177,51,51,51,99,195,192,192,240,51,51
				db	51,51,195,194,192,192,51,51,51,51,99,194,192,192,177,51,51,51,99,195,192,192,225,51,51,51,51,195,194,240,225,51
				db	51,51,51,195,194,208,193,51,51,51,51,99,195,192,195,51,51,51,51,51,195,195,195,51,51,51,51,51,99,195,195,51
				db	51,51,51,51,51,195,147,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qbrawn
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,102,153,51,51,51
				db	51,51,51,204,207,147,51,51,51,51,51,207,207,155,51,51,51,51,102,207,205,155,51,51,51,51,103,207,207,203,51,51
				db	51,51,103,205,205,207,51,51,51,51,205,206,204,203,51,51,51,51,207,201,198,207,51,51,51,51,207,205,195,205,51,51
				db	51,51,207,205,203,206,51,51,51,51,199,199,203,205,51,51,51,51,207,207,203,206,51,51,51,51,199,199,203,207,51,51
				db	51,51,207,195,195,205,51,51,51,51,199,201,195,205,51,51,51,51,199,204,204,203,51,51,51,51,195,206,205,207,51,51
				db	51,51,103,207,206,203,51,51,51,51,99,207,207,203,51,51,51,51,99,195,199,147,51,51,51,51,51,199,207,147,51,51
				db	51,51,51,99,147,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qpurple
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,48,49,50,49,51,51
				db	51,50,112,243,48,48,51,51,51,50,241,113,116,178,51,51,51,50,243,178,245,178,51,51,51,50,247,48,178,178,49,51
				db	51,243,243,178,113,251,49,51,51,48,48,48,48,178,113,51,51,113,243,116,184,48,176,179,50,113,48,241,247,112,243,49
				db	50,241,186,251,243,48,249,49,50,243,48,113,243,113,247,49,50,243,178,243,186,113,243,49,50,243,113,113,113,113,243,49
				db	115,113,178,178,48,113,48,179,51,48,48,113,113,178,48,51,51,48,244,48,246,251,178,51,51,178,113,186,247,247,178,51
				db	51,178,178,178,178,113,178,51,51,50,243,178,243,243,48,51,51,50,243,178,113,113,49,51,51,50,243,178,178,48,179,51
				db	51,115,48,113,48,113,179,51,51,51,243,179,178,113,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qgreen
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,15,15,15,15,27,51,51,39,14,12,12,12,13,51,51,39,12,12,12,12,13,51
				db	51,39,14,12,12,12,15,51,51,39,15,12,15,15,15,51,51,39,13,12,12,13,13,51,51,39,14,12,12,12,15,51
				db	51,39,14,12,12,12,13,51,51,39,14,252,252,12,13,51,51,39,15,252,12,12,13,51,51,39,94,14,12,12,13,51
				db	51,39,15,12,12,92,173,51,51,39,15,14,12,12,13,51,51,39,14,12,12,12,13,51,51,35,15,14,13,12,13,51
				db	51,39,14,12,12,15,15,51,51,39,15,15,15,14,15,51,51,35,14,14,12,15,15,51,51,39,15,15,15,15,15,51
				db	51,35,15,15,15,15,11,51,51,35,7,7,11,15,3,51,51,51,3,3,3,3,19,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qdiszko
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,98,192,192,51,51,51,51,51,193,150,192,145,51,51,51,35,195,150,194,194,51,51,51,67,195,195,195,75,145,51
				db	51,67,97,195,195,75,145,51,51,195,97,195,195,195,147,51,51,65,195,195,195,193,194,51,35,211,195,75,195,195,193,51
				db	35,211,195,75,146,195,195,51,35,67,195,195,146,195,97,145,67,195,195,195,195,195,97,145,67,105,195,211,195,195,195,147
				db	2,105,195,211,135,195,195,147,67,195,195,195,135,195,193,145,35,67,195,195,195,195,195,51,35,195,75,195,195,150,194,51
				db	35,67,75,227,195,150,195,51,35,195,195,227,195,195,194,51,51,67,195,195,195,195,147,51,51,67,67,195,227,195,147,51
				db	51,3,195,195,227,195,147,51,51,35,3,67,65,195,51,51,51,51,3,195,195,19,51,51,51,51,35,3,3,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qcsik
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,254,51,51,51,51,51,51,119,252,187,51,51,51,51
				db	51,119,252,185,51,51,51,51,51,215,252,253,51,51,51,51,51,194,192,193,51,51,51,51,51,194,208,192,51,51,51,51
				db	51,194,240,192,51,51,51,51,51,215,252,252,187,51,51,51,51,195,252,252,185,51,51,51,51,99,252,252,253,51,51,51
				db	51,99,194,192,192,147,51,51,51,99,194,192,192,193,51,51,51,51,195,192,192,193,51,51,51,51,99,254,252,252,187,51
				db	51,51,99,255,252,252,253,51,51,51,51,215,254,252,253,51,51,51,51,195,192,208,225,51,51,51,51,99,194,208,225,51
				db	51,51,51,51,195,192,193,51,51,51,51,51,99,252,253,51,51,51,51,51,51,215,187,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qstar
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,185,51,51,51,51,51,51,51,153,51,51,51,51,51,51,51,222,51,51,51
				db	51,51,51,102,206,51,51,51,51,51,51,102,206,51,51,51,51,51,51,205,206,51,51,51,51,51,51,205,204,185,51,51
				db	51,51,51,205,204,153,51,51,51,51,238,207,205,220,185,51,51,102,204,207,205,204,204,185,51,238,205,207,205,207,204,153
				db	51,205,207,206,204,204,204,153,51,204,239,206,204,204,204,187,51,102,255,207,204,204,204,51,51,102,205,207,206,204,221,51
				db	51,51,207,207,223,204,221,51,51,51,207,207,206,238,187,51,51,51,205,207,206,221,51,51,51,51,119,207,206,204,51,51
				db	51,51,238,207,207,204,187,51,51,51,238,207,207,204,187,51,51,51,236,206,206,204,153,51,51,51,204,205,206,206,153,51
				db	51,51,204,222,205,207,153,51,51,51,205,206,102,207,153,51,51,51,205,153,51,239,153,51,51,51,236,51,51,119,187,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qstar2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,153,51,51,51,51,51,51,51,153,51,51,51
				db	51,51,51,51,204,51,51,51,51,51,51,102,238,51,51,51,51,51,51,102,238,51,51,51,51,51,51,221,238,51,51,51
				db	51,51,51,221,255,153,51,51,51,51,51,221,255,153,51,51,51,51,221,255,255,255,153,51,51,102,255,255,255,255,255,153
				db	51,221,255,255,255,255,255,153,51,221,255,255,255,255,255,153,51,221,255,255,255,255,255,153,51,102,255,255,255,255,255,153
				db	51,102,255,255,255,255,238,51,51,102,255,255,255,255,238,51,51,51,221,255,255,255,153,51,51,51,102,255,255,238,51,51
				db	51,51,102,255,255,238,51,51,51,51,221,255,255,255,153,51,51,51,221,255,255,255,153,51,51,51,221,255,255,255,153,51
				db	51,51,221,255,255,255,153,51,51,51,221,255,255,255,153,51,51,51,221,238,102,255,153,51,51,51,221,153,51,221,153,51
				db	51,51,204,51,51,102,153,51,51,51,51,51,51,51,51,51
	qbomb
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,103,199,51,51,51,51,51,51,206,198,153,51,51,51,207,102,203,199,207,237,51
				db	99,201,199,203,206,204,205,155,103,201,199,207,206,204,207,155,102,195,207,203,204,204,207,155,103,199,207,207,199,252,237,155
				db	99,207,207,205,203,222,237,153,102,207,204,205,203,199,237,155,99,199,204,220,207,252,207,153,102,207,220,236,207,222,207,153
				db	103,207,220,236,207,214,204,153,103,199,206,236,252,207,207,153,99,199,207,222,252,207,207,153,103,201,207,206,233,214,207,153
				db	99,205,206,204,201,198,207,147,195,207,206,204,201,198,207,153,51,199,206,204,201,198,201,153,51,201,198,204,201,195,198,155
				db	51,201,198,204,204,195,206,155,51,205,206,206,195,198,195,201,51,204,199,207,195,195,195,201,51,205,206,207,207,198,199,207
				db	51,103,207,207,203,207,195,201,51,99,206,207,207,206,155,147,51,51,204,204,205,203,155,51,51,51,102,207,207,207,51,51
				db	51,51,102,203,199,205,51,51,51,51,99,195,51,51,51,51
	q1
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,115,243,243,115,51,51,51
				db	51,115,255,191,123,255,187,51,51,115,251,191,243,51,51,51,51,115,243,243,243,51,51,51,51,115,251,243,243,255,187,51
				db	51,115,243,243,123,51,51,51,51,119,255,255,119,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	q2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,204,236,252,252,51,51,51,51,204,204,204,220,51,51,51,51,206,204,204,204,51,51,51,51,204,204,204,205,51,51
				db	51,51,206,204,207,204,51,51,51,51,206,204,204,205,51,51,51,51,206,205,207,205,51,51,51,51,207,204,204,205,51,51
				db	51,51,206,207,207,207,51,51,51,51,103,155,103,155,51,51,51,51,34,51,51,17,51,51,51,51,119,51,51,187,51,51
				db	51,51,119,51,51,187,51,51,51,51,119,51,51,187,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	q3
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,147,51,51,51,51,51,51,99,208,51,51,51
				db	51,51,51,195,192,177,51,51,51,51,51,194,192,145,51,51,51,51,51,195,192,145,51,51,51,51,51,195,194,177,51,51
				db	51,51,99,195,192,224,51,51,51,51,99,195,194,192,51,51,51,51,34,147,147,128,51,51,51,51,119,51,51,119,51,51
				db	51,51,187,51,51,51,187,51,51,119,51,51,51,51,119,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	q4
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,35,19,51,51,51,51,51,51,35,187,51,51,51,51,51,51,119,187,51,51,51
				db	51,51,51,119,19,51,51,51,51,51,51,255,255,51,51,51,51,51,35,3,3,19,51,51,51,51,35,3,3,19,51,51
				db	51,51,51,255,255,51,51,51,51,51,51,254,255,51,51,51,51,51,51,254,255,51,51,51,51,51,51,254,255,51,51,51
				db	51,51,51,254,255,51,51,51,51,51,51,255,255,51,51,51,51,51,51,253,255,51,51,51,51,51,118,252,253,187,51,51
				db	51,51,35,3,3,19,51,51,51,51,51,255,255,51,51,51,51,51,51,35,19,51,51,51,51,51,51,119,19,51,51,51
				db	51,51,51,119,19,51,51,51,51,51,51,119,19,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	q5
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,35,51,3,119,51,51
				db	51,51,35,3,255,3,51,51,51,51,35,87,3,171,51,51,51,255,3,3,3,3,87,51,51,51,35,43,3,3,51,51
				db	51,51,35,23,3,23,51,51,51,51,35,51,3,34,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	q6
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,118,204,139,255,51,51
				db	51,51,118,141,27,51,51,51,51,51,102,15,27,51,51,51,51,51,102,141,27,51,51,51,51,51,102,15,27,51,51,51
				db	51,51,102,141,155,51,51,51,51,51,102,15,27,51,51,51,51,51,39,15,155,51,51,51,51,51,102,15,27,51,51,51
				db	51,51,39,15,155,51,51,51,51,51,39,15,155,51,51,51,51,51,39,236,27,51,51,51,51,51,103,15,139,255,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qkondibomb
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,119,252,51,51,51,51,51,51,60,54,57,51,51
				db	51,51,187,51,51,187,51,51,51,51,60,51,51,119,51,51,51,118,51,51,51,119,51,51,51,54,51,51,51,51,185,51
				db	51,188,51,51,51,51,57,51,51,51,51,51,147,51,188,51,51,51,51,99,208,51,54,51,51,51,51,195,192,177,51,51
				db	119,57,51,194,192,145,51,57,54,51,51,195,192,145,51,185,118,51,51,195,194,177,51,57,54,51,99,195,192,224,54,185
				db	51,185,99,195,194,192,51,185,51,57,34,147,147,128,51,57,51,51,119,51,51,119,51,51,51,51,187,51,51,51,187,51
				db	51,119,51,51,51,51,119,51,54,51,51,51,51,51,51,51,119,185,118,51,51,54,125,51,51,57,57,124,119,252,51,51
				db	51,119,51,124,60,125,51,51,51,51,51,119,185,60,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qkondicsik
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,190,185,51,51,51,51,51,51,57,254,54,124,187,188,57,51,51,54,124,187,60,60,51
				db	51,51,51,51,51,51,187,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,35,51,3,119,51,51
				db	51,51,35,3,255,3,51,51,51,51,35,87,3,171,51,51,51,255,3,3,3,3,87,51,51,51,35,43,3,3,51,51
				db	51,51,35,23,3,23,51,51,51,51,35,51,3,35,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,188,125,54,119,125,51,51,51,185,188,252,188,54,188,51,51,51,51,119,51,51,187,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qkondicsill
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,227,194,51,51,51,51,51,115,195,195,145,51,51
				db	51,51,243,195,195,194,51,51,51,51,243,195,195,192,51,51,51,51,227,227,192,194,51,51,51,51,227,195,195,193,51,51
				db	51,51,227,195,195,195,51,51,51,51,227,195,195,193,51,51,51,51,227,195,195,193,51,51,51,51,195,195,195,195,51,51
				db	51,51,227,195,195,195,51,51,51,51,195,195,195,192,51,51,51,51,99,195,194,145,51,51,51,51,99,195,195,147,51,51
				db	51,51,227,195,195,194,51,51,51,51,243,227,195,195,51,51,51,51,227,195,195,195,51,51,51,51,115,195,195,179,51,51
				db	51,51,51,227,211,51,51,51,51,51,51,19,35,51,51,51,51,51,51,187,119,51,51,51,51,51,51,187,119,51,51,51
				db	51,51,51,187,119,51,51,51,51,51,51,187,119,51,51,51,51,51,51,187,119,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qkondicsillq
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,35,3,19,51,51,51,51,51,87,255,171,51,51
				db	51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51
				db	51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51
				db	51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51
				db	51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,35,255,255,255,19,51,51,51,51,87,255,171,51,51
				db	51,51,51,35,3,3,51,51,51,51,51,35,51,19,51,51,51,51,51,35,51,19,51,51,51,51,51,35,51,19,51,51
				db	51,51,51,35,51,19,51,51,51,51,51,35,51,19,51,51,51,51,51,35,51,19,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qbomb2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,54,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,54,51,51,57,51
				db	119,51,51,54,51,51,57,51,54,185,51,60,51,119,57,51,51,57,51,60,51,118,51,51,51,51,54,188,51,124,51,51
				db	51,51,54,188,51,125,51,51,51,51,118,125,51,54,57,51,51,51,124,57,51,51,57,51,51,51,124,57,57,51,57,51
				db	185,54,252,60,57,51,57,51,51,54,252,124,185,51,51,51,51,54,252,252,57,51,51,51,51,119,60,124,254,51,51,51
				db	51,51,51,124,124,51,51,51,51,51,54,188,54,51,187,51,51,54,54,188,54,185,57,51,54,57,54,185,51,57,51,51
				db	54,51,118,57,51,51,51,51,54,51,124,51,51,51,51,51,119,51,124,54,185,51,51,51,51,51,124,54,185,51,118,51
				db	51,51,60,54,185,51,54,51,51,51,57,118,187,51,54,51,51,54,51,54,51,51,51,51,51,54,51,54,51,51,51,51
				db	51,54,51,51,51,51,51,51,51,125,51,51,51,51,51,51
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
				db	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192
				db	192,0,0,0,0,0,0,192,192,0,0,0,0,0,0,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192
				db	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192
	qkeret2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252
				db	252,0,0,0,0,0,0,252,252,0,0,0,0,0,0,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252
				db	252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252
	qkeret3
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51
				db	51,0,0,0,0,0,0,51,51,0,0,0,0,0,0,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
	qministar
				db	1			; A sprite szélessége byte-okban
				db	4			; A sprite magassága
				db	204,204,204,204
	qkezdo3
				db	46			; A sprite szélessége byte-okban
				db	29			; A sprite magassága
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,50,116,185,116
				db	185,51,48,252,51,50,116,51,116,185,48,116,252,51,50,252,185,51,50,116,185,252,185,48,116,252,51,50,252,50,252,185
				db	51,116,185,51,50,252,50,252,50,185,50,48,49,48,185,50,48,48,185,50,48,185,48,185,48,48,48,185,50,116,185,51
				db	50,48,49,48,185,48,48,48,185,50,116,50,116,185,50,48,252,51,50,48,50,116,50,49,50,48,33,48,49,50,48,48
				db	185,50,48,185,48,185,48,48,48,185,50,48,185,51,35,48,33,48,49,48,48,48,49,50,116,50,48,185,48,48,48,185
				db	50,48,50,116,50,49,50,48,33,48,49,48,48,48,49,50,48,185,48,185,48,116,48,116,50,48,185,51,35,48,33,48
				db	49,48,48,48,116,50,116,50,48,185,48,48,48,49,50,48,50,116,50,49,50,48,33,48,51,48,116,48,116,50,48,185
				db	48,185,48,185,48,116,50,48,49,51,35,48,48,48,51,48,48,50,48,50,116,50,48,185,18,48,48,49,50,48,50,116
				db	35,49,50,48,48,48,51,48,49,18,116,50,48,185,48,185,48,185,48,116,50,48,49,51,35,48,48,48,51,48,49,50
				db	48,50,116,50,48,185,48,49,48,49,50,48,50,48,35,49,35,48,48,48,51,48,49,48,116,50,48,49,18,185,48,49
				db	48,116,50,48,49,51,35,48,48,48,51,48,185,50,48,50,116,35,48,185,48,49,48,49,50,48,35,116,35,49,35,48
				db	48,48,51,48,49,18,48,50,48,33,48,185,48,49,48,48,35,48,49,51,35,48,48,33,51,48,185,50,48,50,48,50
				db	48,185,18,49,49,49,50,48,35,48,35,49,35,48,48,49,51,48,49,18,116,50,48,48,48,185,48,49,48,116,50,48
				db	49,51,35,48,48,49,51,18,185,50,48,50,48,35,48,49,18,116,51,51,35,48,35,48,35,49,35,48,48,49,51,18
				db	49,18,48,50,48,48,48,185,48,49,48,116,35,48,49,51,35,48,48,51,51,48,116,48,48,50,48,35,48,49,18,48
				db	51,51,50,48,48,48,35,49,35,48,48,51,51,18,49,18,48,50,48,48,48,185,48,49,48,48,50,48,49,51,35,48
				db	33,51,51,48,48,48,49,50,48,35,48,49,18,48,185,51,35,48,48,48,35,49,35,48,48,51,51,18,49,18,48,50
				db	48,48,48,185,48,49,48,116,35,48,49,51,35,48,49,51,51,18,48,48,19,50,48,50,48,49,35,48,116,51,35,48
				db	48,48,35,49,35,48,48,51,51,18,49,18,48,50,48,48,48,185,48,49,18,48,35,48,49,51,35,48,49,51,51,48
				db	48,48,51,50,48,35,48,49,51,48,48,185,35,48,48,48,35,49,35,48,48,185,51,18,49,18,48,50,48,48,48,185
				db	48,49,18,48,35,48,49,51,35,48,116,51,51,48,48,48,49,50,48,35,48,49,51,18,48,185,35,48,48,48,35,49
				db	35,48,48,116,51,18,49,18,48,35,48,48,48,185,48,49,18,48,35,48,49,51,35,48,48,51,51,18,48,48,49,50
				db	48,35,48,49,51,50,48,49,35,48,35,48,35,49,35,48,48,116,51,18,49,18,48,35,48,48,48,185,48,49,18,48
				db	35,48,49,51,35,48,48,48,51,18,48,48,48,50,48,35,48,49,51,51,48,185,35,48,35,48,35,49,35,48,48,48
				db	51,18,49,18,48,50,48,48,48,49,48,49,18,48,35,48,49,51,35,48,48,48,51,18,48,48,48,50,48,35,48,49
				db	116,185,48,49,35,48,35,48,35,49,35,48,48,48,51,18,19,18,48,35,48,48,48,49,48,49,18,48,35,48,49,51
				db	35,48,48,48,51,18,33,48,48,50,33,35,48,49,48,185,48,185,35,48,35,48,35,49,35,48,48,48,51,18,49,18
				db	48,35,48,18,48,49,48,49,18,48,35,48,49,51,35,48,48,48,51,18,33,18,48,50,48,35,48,49,48,49,48,49
				db	35,48,35,48,35,49,35,48,48,48,49,18,19,18,48,50,48,50,48,49,48,19,18,48,35,48,49,51,35,48,48,48
				db	49,18,49,35,48,50,33,35,48,49,48,49,48,49,35,48,35,48,51,51,35,48,48,48,49,18,33,48,48,35,48,35
				db	48,49,48,33,48,48,35,48,49,51,35,48,48,48,49,18,49,35,48,35,48,18,48,19,18,49,48,49,35,48,35,48
				db	50,185,35,48,33,48,49,3,48,48,49,35,48,35,48,49,48,48,48,33,35,48,49,51,35,48,33,48,49,18,49,35
				db	48,35,18,48,48,51,18,49,48,185,35,48,35,48,50,49,35,48,33,48,49,35,48,48,49,35,48,35,48,49,48,48
				db	48,49,35,48,49,51,35,48,33,48,49,18,49,50,48,51,18,48,48,51,18,48,48,185,35,48,35,48,35,49,35,18
				db	49,18,49,35,18,48,19,35,48,35,18,49,33,48,48,19,35,18,49,51,35,18,49,18,49,3,49,35,48,51,3,48
				db	33,51,35,48,48,51,35,48,35,18,35,49,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
				db	51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51

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

#endif