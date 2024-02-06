#options
#define DB_TILT_EXTRA_WIDTH
#define DB_TILT_MIRROR
#endoptions

//{	Exportált sprite indexek
#pragma rem START_GFX_DEFINES		// NE VÁLTOZTASD!

#define SPR_IND_ORNAMENT	0
#define SPR_IND_BELL	1
#define SPR_IND_SANTAHAT	2
#define SPR_IND_CANDYCANE	3
#define SPR_IND_SNOWMAN	4
#define SPR_IND_PRESENT	5
#define SPR_IND_DISCO	6
#define SPR_IND_CSIK	7
#define SPR_IND_STOCKINGS	8
#define SPR_IND_STOCKINGS2	9
#define SPR_IND_EXPLOSION	10
#define SPR_IND_PROBASPRITE	11
#define SPR_IND_KERET	12
#define SPR_IND_KERET2	13
#define SPR_IND_KERET3	14
#define SPR_IND_MINISTAR	15
#define SPR_IND_KEZDO2_2	16
#define SPR_IND_FLAKE1	17

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
char snowBack[1320];
#pragma endmb

int music;

//}

//{-------------------------- MAIN --------------------------------
main()
{
	int i;

	music=1;	

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

	MainScreen();

	while(1) LevelSelector();

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
	DrawSprite2(4,30,16,59);
	DrawSprite2(8,85,0,59);
	DrawSprite2(16,85,1,59);
	DrawSprite2(24,85,2,59);
	DrawSprite2(32,85,3,59);
	DrawSprite2(40,85,4,59);
	DrawSprite2(48,85,5,59);
	DrawCoolString(4, 230, "C - CREDITS    SPACE - START", 5);

	ptr = gameObjects;
 
	DbCopyToFullScreen();
	backPtr = snowBack;
	for(i=0;i<21;i++)
	{
		DrawSprite3(Random(60),Random(40), 17,i);
	}

	while(1)
	{
		for(i=0;i<21;i++)
		{
			if(IsKeyDown(KEY_C)) {c=1; break;}
			if(IsKeyDown(KEY_SPACE)) {break;}
			y = gIndex2[i]->Y+Random(20)+5;
			x = gIndex2[i]->X+Random(6)-3;
			if(x<0) x = 0;
			if (x>60) x=60;
			gIndex2[i]->X=x;
			if(y>230) y=0;
			gIndex2[i]->Y=y;
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

#pragma link forward
Credits()
{
	ClearScreen();
	
	DrawCoolString(22,0, "KONDI KRUSH!", 1);
	DrawCoolString(0,40, "MADE BY ANYSTONE", 1);
	DrawCoolString(0,80, "DEVTOOL HELPS: DOBERDO BROTHERS", 1);
	DrawCoolString(0,100, "MUSIC CONVERSATION: KISS KAROLY", 1);
	DrawCoolString(0,120, "LOT OF GFX: NORBICSEK", 1);

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

			if(levels[index].score >= levels[index].star1Score) DrawSprite2(10+lx*8,50+ly*30,15,59);
			if(levels[index].score >= levels[index].star2Score) DrawSprite2(12+lx*8,50+ly*30,15,59);
			if(levels[index].score >= levels[index].star3Score) DrawSprite2(14+lx*8,50+ly*30,15,59);

		}
	}

	DrawSprite(plx+1, ply+1, 12, 58);

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
				case 'I':
					index = ply*6+plx+1;
					if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
					{
					    LevelInfo(index);
					    return;
					}
				    //break;
				case ' ':
					index = ply*6+plx+1;
					if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
					{
						currentIndex = index;
						StartLevel(index);
						return;
					}
				    //break;
			}
			
			if (plx < 0) plx = 0;
			if (ply < 0) ply = 0;
			if (plx > 5) plx = 5;
			if (ply > 5) ply = 5;

			DrawSprite(olx+1, oly+1, 14, 58);
			DrawSprite(plx+1, ply+1, 12, 58);
			
			Sleep(7);
			key = 'P';
		}
	}
	
}
//}

#pragma link forward
//{-------------------------- LevelInfo --------------------------------
LevelInfo(int index)
{
	int i;
	ClearScreen();
	DrawCoolString(10,30, "USABLE CONDENSERS:", 1);
	
	for(i=0;i<levels[index].condyNumber;i++)
	{
		DrawSprite2(8+i*7,44,i,59);
	}

	if(levels[index].extras)
	{
		DrawSprite2(8,75,6,59);
		DrawSprite2(18,75,7,59);
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
	DrawSprite2(40, 0,  9, 59);
	DrawSprite2(48, 0,  9, 59);
	DrawSprite2(56, 0,  9, 59);

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
                        candy = 10;
                        break;
                    case ' ':
                        candy = 11;
                        break;
                    case 'D':
                        candy = 6;
                        break;
                    case 'X':
                        candy = 7;
                        break;
                }

		DrawSprite(x, y, candy, x+y*maxSizeX);

                if (x == lastposx && y == lastposy) { lastposx = -1; lastposx = -1; };
            }
        }

	DrawSprite(posx, posy, 12 + moveMode, 58);

	lastposx = posx;
	lastposy = posy;
	
	for(i=0;i<SN;i++)
	{
		lastDrawnlevel[i] = actualLevel[i];
	}
	
	if (withWait) Wait(fast);

	if(levelScore>=levels[currentIndex].star1Score) DrawSprite2(40, 0,  8, 59);
	if(levelScore>=levels[currentIndex].star2Score) DrawSprite2(48, 0,  8, 59);
	if(levelScore>=levels[currentIndex].star3Score) DrawSprite2(56, 0,  8, 59);
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


DrawSprite3(int x, int y, int obj, int index)
{
	gIndex2[index] = DbInitGameObject(ptr++,x,y,obj,GOFLG_VISIBLE, DbSprite16c16Mask,backPtr,0);
	backPtr+=88;
}


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

//{-------------------------- Wait --------------------------------
Wait(int fast)
{
    int wait;
    wait = speed;
    //if (fast) wait = speed / 2;
    //Sleep(wait);
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
	DbStartSoundEffect(ch, soundSample);
}
//}

#pragma link forward
//{-------------------------- ItCallBack -------------------------- 
ItCallBack()
{
    	IncTimer();
    	ReadKeyMatrix();
	DbMusicPlayer_IT();
	DbSoundEffect_IT();
}
//}

#pragma link backward


//{	TitleMusic
#asm
	qTitleMusic

	;ChannelNr
				db	4
	;InsturmentNr
				db	4
	;TrackSize
				db	4
	;PatternSize
				db	64
	;CardFlag
				db	0
	;PatternOffs
				dw	25
	;InstrumentOffs
				dw	57
	;Track0
				db	0,4,8,12
	;Track1
				db	1,5,9,13
	;Track2
				db	2,6,10,14
	;Track3
				db	3,3,3,3
	;PatternOffset
				dw	65,181,309,373,374,494,618,682,683,807,935,999,1000,1124,1252,1316
	;InstrumentOffset
				dw	1317,1322,1327,1332

	;Patterns
				db	50,16,50,16,59,16,59,16,57,16,57,16,55,16,55,16,50,16,50,16,50,16,50,16,255,255,50,16,50,16
				db	50,16,50,16,59,16,59,16,57,16,57,16,55,16,55,16,52,16,52,16,52,16,52,16,255,255,255,255,52,16
				db	52,16,60,16,60,16,59,16,59,16,57,16,57,16,54,16,54,16,54,16,54,16,255,255,255,255,54,16,54,16
				db	62,16,62,16,60,16,60,16,57,16,57,16,59,16,59,16,59,16,59,16,59,16,59,16,255,255

				db	31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17
				db	43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,36,17,36,17,48,17,48,17,40,17,40,17
				db	48,17,48,17,36,17,36,17,48,17,48,17,40,17,40,17,48,17,48,17,38,17,38,17,50,17,50,17,42,17
				db	42,17,50,17,50,17,38,17,38,17,50,17,50,17,42,17,42,17,50,17,50,17,31,17,31,17,43,17,43,17
				db	35,17,35,17,43,17,43,17

				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255

				db	192

				db	50,16,50,16,59,16,59,16,57,16,57,16,55,16,55,16,50,16,50,16,50,16,50,16,255,255,255,255,50,16
				db	50,16,59,16,59,16,57,16,57,16,55,16,55,16,52,16,52,16,52,16,52,16,255,255,255,255,52,16,52,16
				db	60,16,60,16,59,16,59,16,57,16,57,16,54,16,54,16,62,16,62,16,61,16,61,16,62,16,62,16,64,16
				db	64,16,62,16,62,16,60,16,60,16,57,16,57,16,55,16,55,16,55,16,55,16,62,16,62,16,62,16,62,16


				db	31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17
				db	43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,36,17,36,17,48,17,48,17,40,17,40,17
				db	48,17,48,17,36,17,36,17,48,17,48,17,40,17,40,17,48,17,48,17,38,17,38,17,50,17,50,17,42,17
				db	42,17,50,17,50,17,38,17,38,17,50,17,50,17,42,17,42,17,50,17,50,17,43,17,43,17,43,17,43,17
				db	255,255,255,255

				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255

				db	192

				db	59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16
				db	59,16,59,16,59,16,62,16,62,16,55,16,55,16,55,16,57,16,59,16,59,16,59,16,59,16,255,255,255,255
				db	60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,59,16,59,16,59,16,59,16,59,16
				db	59,16,59,16,59,16,57,16,57,16,57,16,57,16,59,16,59,16,57,16,57,16,57,16,57,16,62,16,62,16
				db	62,16,62,16

				db	31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17
				db	43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17
				db	43,17,43,17,36,17,36,17,48,17,48,17,40,17,40,17,48,17,48,17,31,17,31,17,43,17,43,17,35,17
				db	35,17,43,17,43,17,33,17,33,17,45,17,45,17,37,17,37,17,45,17,45,17,38,17,38,17,45,17,45,17
				db	42,17,42,17,42,17,42,17

				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255

				db	192

				db	59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16,59,16
				db	59,16,59,16,59,16,62,16,62,16,55,16,55,16,55,16,57,16,59,16,59,16,59,16,59,16,255,255,255,255
				db	60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,60,16,59,16,59,16,59,16,59,16,59,16
				db	59,16,62,16,62,16,62,16,62,16,60,16,60,16,57,16,57,16,55,16,55,16,55,16,55,16,55,16,55,16
				db	55,16,55,16

				db	31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17
				db	43,17,31,17,31,17,43,17,43,17,35,17,35,17,43,17,43,17,31,17,31,17,43,17,43,17,35,17,35,17
				db	43,17,43,17,36,17,36,17,48,17,48,17,40,17,40,17,48,17,48,17,31,17,31,17,43,17,43,17,35,17
				db	35,17,43,17,43,17,38,17,38,17,50,17,50,17,42,17,42,17,50,17,50,17,43,17,43,17,35,17,35,17
				db	43,17,43,17,43,17,43,17

				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
				db	255,255,255,255

				db	192


	;Instruments
				db	15,10,5,0,128

				db	15,10,5,0,128

				db	15,10,5,0,128

				db	128



			; Exportálva 1333 byte

#endasm
//}
#pragma link

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
	SpriteCount		db 18
	SpriteIndexArray
				dw	0,242,484,726,968,1210,1452,1694,1936,2178,2420,2662,2904,3146,3388,3630,3636,6500

	SpriteDataBuffer	ds	0,0
	DecompressBuffer	ds	0,0

	SpriteBaseAddr
	qornament
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,43,3,3,3,3,3,3,23,3,3,3,3,3,3,3,3,43,3,3,3
				db	3,3,3,23,63,3,3,3,3,3,3,133,207,3,3,3,3,3,66,79,207,139,3,3,3,3,66,79,255,139,3,3
				db	3,3,133,79,223,207,3,3,3,3,133,207,223,239,3,3,3,3,133,207,207,239,3,3,3,3,133,207,207,239,3,3
				db	3,3,133,79,207,207,3,3,3,3,133,79,207,207,3,3,3,3,133,15,207,143,3,3,3,3,192,15,207,74,3,3
				db	3,3,66,15,15,11,3,3,3,3,66,133,15,129,3,3,3,3,3,192,74,3,3,3,3,3,3,66,129,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qbell
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,205,139,71,139,3,3,3,3,204,205,204,137,3,3
				db	3,3,70,76,12,137,3,3,3,3,70,76,204,3,3,3,3,3,3,140,204,3,3,3,3,3,70,92,236,3,3,3
				db	3,3,70,252,172,139,3,3,3,3,12,252,252,137,3,3,3,3,22,252,254,3,3,3,3,3,22,252,254,169,3,3
				db	3,3,86,252,254,169,3,3,3,3,86,252,253,169,3,3,3,3,124,252,253,188,3,3,3,3,124,252,253,252,3,3
				db	3,3,124,252,252,252,3,3,3,3,124,252,252,252,3,3,3,3,124,252,252,252,3,3,3,3,252,253,254,252,3,3
				db	3,3,188,252,255,252,3,3,3,3,124,252,252,188,3,3,3,22,252,60,60,252,41,3,3,22,188,124,188,124,41,3
				db	3,3,60,124,188,60,3,3,3,3,3,124,190,3,3,3,3,3,3,86,169,3,3,3,3,3,3,22,41,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qsantahat
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,71,207,3,3,3,3,3,71,207,204,3,3,3,3,3,71,204,204,139,3,3
				db	3,3,204,204,204,205,3,3,3,70,204,204,204,204,3,3,87,238,204,204,204,204,3,3,127,238,76,204,76,204,139,3
				db	255,174,6,12,76,204,139,3,255,43,6,12,204,204,137,3,127,43,6,76,204,204,139,3,23,3,6,204,204,204,137,3
				db	3,3,12,204,204,204,137,3,3,3,76,204,12,140,137,3,3,3,76,140,93,191,9,3,3,3,12,29,255,255,43,3
				db	3,3,93,255,255,255,191,3,3,3,127,255,255,255,191,3,3,23,255,255,255,127,191,3,3,23,255,255,191,63,43,3
				db	3,23,127,255,43,3,3,3,3,3,63,63,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qcandycane
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,93,171,3,3,3,3,3,6,221,171,3,3,3,3,3,46,221,238,3
				db	3,3,3,6,238,204,238,137,3,3,3,70,255,204,238,137,3,3,3,76,255,12,255,137,3,3,3,76,191,3,127,137
				db	3,3,3,204,171,3,127,137,3,3,23,204,171,3,127,137,3,3,23,204,3,3,127,3,3,3,23,204,3,6,255,3
				db	3,3,87,238,3,6,157,3,3,3,93,238,3,70,137,3,3,3,93,171,3,6,9,3,3,3,93,171,3,3,3,3
				db	3,3,204,171,3,3,3,3,3,6,204,137,3,3,3,3,3,23,204,3,3,3,3,3,3,23,204,3,3,3,3,3
				db	3,87,238,3,3,3,3,3,3,127,238,3,3,3,3,3,3,127,171,3,3,3,3,3,3,23,171,3,3,3,3,3
				db	3,23,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qsnowman
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,243,163,3,3,3
				db	3,3,3,255,171,3,3,3,3,3,87,255,251,3,3,3,3,3,87,213,213,3,3,3,3,3,87,255,255,3,3,3
				db	3,3,87,255,255,3,3,3,3,3,87,213,213,3,3,3,3,3,23,234,255,3,3,3,3,3,3,127,171,3,9,9
				db	3,3,3,110,137,3,6,3,3,3,6,140,140,3,9,3,3,3,6,221,251,6,3,3,3,3,110,221,255,9,3,3
				db	3,3,238,221,255,43,3,3,3,23,238,93,255,163,3,3,3,87,238,255,255,251,3,3,3,87,238,255,255,255,3,3
				db	3,23,174,255,255,251,3,3,3,87,255,255,255,255,3,3,3,23,255,255,255,255,3,3,3,23,255,255,255,191,3,3
				db	3,3,127,255,255,43,3,3,3,3,63,255,191,3,3,3,3,3,3,63,171,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qpresent
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,207,3,3,3,3,3,3,3,204,3,71,139,3,3,3,3,76,218,204,139,3,3
				db	3,3,76,204,140,137,3,3,3,3,164,76,12,137,3,3,3,82,164,204,204,240,3,3,3,82,206,88,12,152,33,3
				db	3,82,205,216,204,24,33,3,3,82,204,218,164,12,129,3,3,18,204,240,36,72,33,3,3,82,76,240,48,132,33,3
				db	3,82,140,240,96,12,33,3,3,82,204,112,144,12,33,3,3,82,204,176,48,12,33,3,3,82,204,240,48,12,33,3
				db	3,82,204,240,48,12,33,3,3,82,204,240,48,12,33,3,3,82,204,240,48,12,33,3,3,3,204,240,48,12,3,3
				db	3,3,70,240,48,9,3,3,3,3,3,240,48,3,3,3,3,3,3,82,33,3,3,3,3,3,3,3,3,3,3,3
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
	qstockings
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,3,3,3,3,23,255,3,137,137
				db	3,3,3,23,255,63,3,9,3,3,3,23,127,255,174,3,3,3,3,18,117,255,171,3,3,3,3,18,176,63,171,3
				db	3,3,3,18,240,245,43,3,3,3,3,18,240,245,3,3,3,3,3,18,240,245,3,3,3,3,3,112,240,240,3,3
				db	3,3,3,112,240,245,3,3,3,3,3,112,240,240,3,3,3,3,3,112,240,245,3,3,3,3,18,112,240,240,3,3
				db	3,6,88,48,240,240,3,3,3,76,216,240,240,240,3,3,3,76,216,240,240,140,3,3,3,76,216,240,240,204,3,3
				db	3,76,204,240,240,140,3,3,3,6,12,112,228,140,3,3,3,3,3,18,36,9,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qstockings2
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,0,21,63,0,63,42
				db	0,0,0,21,63,63,63,42,0,0,0,21,63,63,63,0,0,0,0,21,63,63,42,0,0,0,0,21,63,63,42,0
				db	0,0,0,21,63,63,42,0,0,0,0,21,63,63,0,0,0,0,0,21,63,63,0,0,0,0,0,63,63,63,0,0
				db	0,0,0,63,63,63,0,0,0,0,0,63,63,63,0,0,0,0,0,63,63,63,0,0,0,0,21,63,63,63,0,0
				db	0,21,63,63,63,63,0,0,0,63,63,63,63,63,0,0,0,63,63,63,63,63,0,0,0,63,63,63,63,63,0,0
				db	0,63,63,63,63,63,0,0,0,21,63,63,63,63,0,0,0,0,0,21,63,42,0,0,0,0,0,0,0,0,0,0
				db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	qexplosion
				db	8			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,87,3,3,3,3,3,87,3,3,3,3,87,3,3,3,3,87,3,23,86,3
				db	3,86,3,3,3,3,3,3,3,87,3,86,3,87,43,3,43,253,171,86,3,86,3,3,3,86,3,86,3,169,3,23
				db	3,86,3,86,3,171,3,43,3,3,3,252,169,3,3,3,3,23,3,253,169,3,3,3,3,3,3,253,169,3,3,3
				db	3,3,86,253,254,3,3,3,23,86,252,255,255,254,87,3,3,3,23,253,254,3,3,3,3,3,3,253,169,3,3,3
				db	3,86,169,253,169,3,3,3,3,254,3,126,169,3,3,171,3,169,3,86,3,87,3,169,23,3,3,86,3,3,3,3
				db	3,87,3,86,23,3,169,3,3,169,3,86,3,253,3,3,43,3,87,3,3,126,3,3,3,3,86,86,3,3,169,3
				db	3,3,3,23,3,3,87,3,3,3,169,3,3,43,3,3,3,23,3,3,3,3,3,171,3,3,3,23,3,3,3,3
				db	23,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
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
	qkezdo2_2
				db	54			; A sprite szélessége byte-okban
				db	53			; A sprite magassága
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,238,171,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	204,221,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,87,204,204,171,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,70,140,204,204,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,76,12,204,140,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,204,76,204,255,171,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,6,140,76,221,234,129,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,70,137,76,255,186,96,255,171,3,204,255,3,208,245,66,245,234,204,221,255,3,208,255,171,3,196,255,234,255,234
				db	240,245,255,3,196,255,70,255,171,66,245,171,3,196,255,196,255,82,255,171,3,3,3,3,70,9,76,255,208,96,240,171
				db	70,204,204,171,208,240,66,240,234,204,204,204,171,208,245,171,3,196,204,200,204,234,240,240,240,171,196,221,70,221,171,144
				db	240,255,3,196,204,196,221,82,245,171,3,3,3,3,255,3,76,255,112,48,240,161,196,204,204,171,208,240,234,240,234,204
				db	204,204,171,208,240,171,3,132,204,12,204,200,240,240,240,161,196,221,70,204,171,112,240,240,171,196,204,196,221,18,240,171
				db	3,3,3,3,255,3,76,255,240,176,240,224,204,204,204,137,208,240,234,240,234,76,221,204,221,208,240,171,3,132,204,140
				db	204,200,240,240,240,161,196,221,70,204,234,112,240,240,161,196,204,196,221,18,112,171,3,3,3,3,234,3,93,234,240,176
				db	240,66,204,221,204,221,144,240,234,112,234,204,171,204,221,208,240,171,3,132,204,140,204,66,112,240,112,245,196,221,70,204
				db	234,240,240,240,161,196,204,196,221,66,112,171,3,3,3,3,192,3,93,186,240,240,240,66,204,171,204,221,144,240,234,112
				db	234,76,171,204,221,208,240,171,3,132,204,204,204,66,240,224,144,245,196,221,70,204,234,240,161,112,161,196,204,196,204,66
				db	112,171,3,3,3,3,3,3,66,186,240,240,240,66,204,171,76,221,144,240,176,112,234,76,137,204,221,144,240,171,3,132
				db	204,204,204,66,112,234,144,245,196,221,70,204,234,112,161,112,161,132,204,213,221,66,240,161,3,3,3,3,3,3,66,144
				db	240,240,176,66,204,137,76,204,144,240,176,240,234,204,137,76,204,208,240,161,3,132,204,204,204,66,240,234,144,240,196,204
				db	6,204,234,240,161,48,161,196,204,213,204,66,240,161,3,3,3,3,3,3,3,144,240,240,161,66,204,137,76,221,144,240
				db	240,240,234,76,137,76,221,144,240,161,3,132,204,204,137,66,112,234,208,240,196,221,70,204,200,112,245,3,3,132,204,213
				db	204,66,240,161,3,3,3,3,3,3,3,144,240,240,33,66,76,137,76,204,144,240,240,240,234,76,137,76,221,208,240,171
				db	3,132,204,204,3,66,112,245,240,240,196,204,6,204,200,112,240,3,3,132,204,238,204,66,240,161,3,3,3,3,3,3
				db	3,144,240,240,3,66,76,137,76,204,144,240,240,240,234,76,137,76,204,144,240,161,3,132,204,204,3,66,112,240,240,161
				db	196,204,6,204,137,112,240,171,3,132,204,204,204,66,240,161,3,3,3,3,3,3,3,144,240,240,3,66,76,137,76,204
				db	144,240,240,240,234,76,137,76,221,144,240,171,3,132,204,137,3,66,112,240,240,33,196,204,6,204,137,144,240,245,3,132
				db	204,204,204,66,240,161,3,3,3,3,3,3,3,144,240,240,3,66,76,137,76,204,144,240,240,240,234,76,137,76,204,144
				db	240,161,3,132,204,137,3,66,112,240,240,3,132,204,6,204,137,66,240,240,171,132,204,204,204,66,240,161,3,3,3,3
				db	3,3,3,144,240,240,171,66,76,137,76,204,144,240,240,240,234,76,137,76,204,144,240,161,3,132,204,221,3,66,112,240
				db	240,171,196,204,6,204,137,3,112,240,171,132,204,238,204,66,112,161,3,3,3,3,3,3,3,144,240,240,245,66,76,137
				db	76,204,144,240,240,240,234,76,137,76,204,144,240,161,3,132,204,204,3,66,112,240,240,161,132,204,6,204,137,3,144,240
				db	161,132,221,132,204,66,112,161,3,3,3,3,3,3,3,144,240,240,245,66,76,137,76,204,144,240,240,240,234,76,137,76
				db	204,144,240,161,3,132,204,204,171,66,112,240,240,245,196,204,6,204,137,3,66,112,171,132,204,132,204,66,112,161,3,3
				db	3,3,3,3,3,144,240,240,240,66,76,137,76,204,144,240,240,240,224,76,137,76,204,144,240,161,3,132,204,204,221,66
				db	112,240,240,240,132,204,6,204,137,245,234,240,161,132,204,132,204,66,112,161,3,3,3,3,3,3,3,144,240,240,240,66
				db	76,137,76,204,144,240,240,240,224,76,137,76,204,144,240,161,3,132,204,204,221,66,112,240,112,240,132,204,6,204,200,240
				db	234,240,171,132,204,132,204,3,48,161,3,3,3,3,3,3,3,144,240,240,240,66,76,137,76,204,144,240,112,240,224,76
				db	137,76,204,144,240,161,3,132,204,204,204,66,112,245,82,240,132,204,6,204,200,240,224,240,161,132,204,132,204,3,48,33
				db	3,3,3,3,3,3,3,144,240,240,240,234,76,9,76,204,144,240,208,240,224,76,9,76,204,144,240,161,3,132,204,204
				db	204,234,112,161,82,240,132,140,6,204,200,240,96,240,161,132,204,132,204,3,3,3,3,3,3,3,3,3,3,144,240,240
				db	240,224,76,140,204,140,144,240,144,240,224,76,140,204,204,144,240,161,3,132,204,204,204,200,112,161,18,240,6,204,76,204
				db	72,240,224,240,161,132,204,132,204,66,245,171,3,3,3,3,3,3,3,144,240,176,240,161,12,204,204,137,144,240,18,240
				db	224,76,204,204,140,144,240,161,3,132,204,140,204,200,112,161,18,240,6,76,204,204,66,112,176,240,171,132,204,132,204,66
				db	112,171,3,3,3,3,3,3,3,144,240,176,240,161,132,204,204,137,144,112,18,240,224,76,204,204,137,144,240,161,3,132
				db	204,140,204,200,112,161,82,240,66,76,204,204,3,48,240,240,171,132,204,132,204,66,112,161,3,3,3,3,3,3,3,144
				db	112,224,112,161,6,76,204,9,144,112,18,112,224,12,204,204,9,144,112,161,3,132,76,200,76,200,48,161,18,240,3,12
				db	204,140,3,18,240,240,171,132,204,132,204,66,48,161,3,3,3,3,3,3,3,144,48,224,48,161,3,12,76,3,144,48
				db	18,48,224,12,12,76,3,144,48,161,3,132,12,200,12,200,48,33,18,112,3,6,76,137,3,3,48,112,3,132,76,132
				db	76,66,48,33,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
				db	3,3,3,3,3,3,3,3,3,3,3,3,3,3
	qflake1
				db	3			; A sprite szélessége byte-okban
				db	11			; A sprite magassága
				db	0,0,0,0,85,0,85,85,81,0,43,170,0,81,0,85,43,251,0,85,0,0,43,170,21,85,81,0,85,0,0,0
				db	0

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

