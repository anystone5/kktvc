 
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


#define      SN     30
#define      speed   1


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

char robotBack[528];

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
	DbSetTvcMusicParams(1, 1);

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
	DrawCoolString(5, 230, "C - CREDITS    SPACE - START", 5);

	ptr = gameObjects;
 
	DbCopyToFullScreen();
	backPtr = robotBack;
	for(i=0;i<8;i++)
	{
		DrawSprite3(Random(60),Random(40), 17,i);
	}

	while(1)
	{
		for(i=0;i<8;i++)
		{
			if(IsKeyDown(KEY_C)) {c=1; break;}
			if(IsKeyDown(KEY_SPACE)) {break;}
			y = gIndex2[i]->Y+=Random(20)+5;
			x = gIndex2[i]->X+=Random(7)-3;
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
				    break;
				case ' ':
					index = ply*6+plx+1;
					if(index<2 || levels[index-1].score>=levels[index-1].star1Score)
					{
						currentIndex = index;
						StartLevel(index);
						return;
					}
				    break;
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
	
	gIndex = DbInitGameObject(ptr,xonscreen,yonscreen,candy,GOFLG_VISIBLE, DbSprite16c8,0,0);
	
	DbClipSprite(gIndex);
	DbDrawSprite(gIndex);
}
//}

//{-------------------------- DrawSprite2 --------------------------------
DrawSprite2(int x, int y, int candy, int index)
{
	gIndex = DbInitGameObject(ptr,x,y,candy,GOFLG_VISIBLE, DbSprite16c8,0,0);
	
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

    rng = DbRndRange(0)*levelCandyNumber/256;
    //rng = DbRndRange(levelCandyNumber);


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

	if(maxNumber>15)
	{
		rng = DbRndRange(maxNumber);
	}
	else
	{	 
    		rng = DbRndRange(maxNumber)*maxNumber/256;
	}
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
				dw	0,113,267,405,546,686,853,1043,1132,1264,1364,1530,1570,1654,1738,1822,1836,3122

	SpriteDataBuffer	ds	0,0
	DecompressBuffer	ds	0,0

	SpriteBaseAddr
	qornament
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,192,15,207,255,0,63			; A sprite szín adatai
				db	193,193,193,193,193,161,113,153,153,23,161,161,113,153,153,23,119,153,153,35,68,153,145,18,52,68,65,145,145,18,52,85
				db	65,145,145,35,52,69,68,145,145,35,68,69,84,145,145,35,148,84,145,145,35,148,84,145,145,35,52,148,145,145,35,52
				db	148,145,145,35,51,68,67,145,145,34,51,68,50,145,145,18,147,49,145,145,18,35,51,33,145,153,34,50,153,153,18,33
				db	153,193,193,193,193,193,193
	qbell
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,207,252,60,255			; A sprite szín adatai
				db	193,193,145,52,65,20,65,145,145,51,52,51,49,145,145,19,35,34,49,145,145,19,35,51,153,153,50,51,153,145,19,37
				db	83,153,145,19,85,82,65,145,145,34,149,49,145,145,22,85,117,153,145,22,85,117,81,145,145,21,85,117,81,145,145,21
				db	85,87,81,145,145,101,85,87,86,145,145,101,85,87,85,145,145,101,157,145,145,101,157,145,145,101,157,145,145,85,87,117
				db	85,145,145,86,85,119,85,145,145,101,149,86,145,17,22,85,150,85,97,17,17,22,86,101,86,101,97,17,145,102,101,86
				db	102,145,153,101,118,153,153,21,81,153,153,22,97,153,193,193
	qsantahat
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,207,255,0,63			; A sprite szín adatai
				db	193,193,193,193,193,153,20,68,153,145,20,68,51,153,145,20,147,65,145,145,155,52,145,17,19,163,145,21,83,163,145,117
				db	83,35,51,35,51,65,17,85,82,18,34,35,51,65,17,85,113,18,34,147,49,17,117,113,18,35,147,65,17,23,17,18
				db	155,49,17,145,34,155,49,17,145,35,51,34,50,49,17,145,35,50,37,87,33,17,145,34,39,149,113,17,145,37,157,87
				db	17,145,117,157,87,17,17,23,157,117,87,17,17,23,149,87,119,113,17,17,23,117,85,113,153,145,151,161,193,193,193,193

	qcandycane
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,255,0,0,63			; A sprite szín adatai
				db	193,193,193,193,193,169,36,65,17,161,18,52,65,17,161,114,52,67,17,153,18,67,51,67,49,153,19,68,51,67,49,153
				db	35,68,34,68,49,153,35,71,17,116,49,153,51,65,17,116,49,145,23,51,65,17,116,49,145,23,51,145,116,17,145,23
				db	51,17,18,68,17,145,20,67,17,18,55,17,145,36,67,17,19,49,17,145,36,65,17,18,33,17,145,36,65,161,145,51
				db	65,161,17,18,51,49,161,17,23,51,169,17,23,51,169,17,20,67,169,17,116,67,169,17,116,65,169,17,23,65,169,17
				db	23,177,193
	qsnowman
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,204,243,255,63			; A sprite szín adatai
				db	193,193,193,153,85,81,153,153,102,97,153,145,22,102,101,153,145,22,54,54,153,145,22,150,153,145,22,150,153,145,22,54
				db	54,153,145,23,99,102,153,153,118,97,17,33,33,153,116,65,17,18,17,145,18,66,66,17,33,17,145,18,70,101,18,145
				db	145,116,70,102,33,145,145,100,70,102,113,145,17,23,100,38,102,81,145,17,22,100,150,101,145,17,22,100,158,145,17,23
				db	98,150,101,145,17,22,166,145,17,23,166,145,17,23,158,103,145,145,118,150,113,145,145,119,102,103,153,153,119,97,153,193
				db	193,193
	qpresent
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,48,204,207,240			; A sprite szín adatai
				db	193,193,193,193,193,145,102,169,145,85,17,22,97,145,145,37,103,85,97,145,145,37,85,82,81,145,145,114,37,34,81,145
				db	17,23,114,149,119,145,17,23,101,39,34,84,65,17,17,23,86,87,85,36,65,17,17,23,85,103,114,34,49,17,17,20
				db	85,119,66,35,65,17,17,23,37,119,68,50,65,17,17,23,82,119,67,34,65,17,17,23,85,71,52,34,65,17,17,23
				db	85,116,68,34,65,17,17,23,85,119,68,34,65,17,17,23,85,119,68,34,65,17,17,23,85,119,68,34,65,17,17,23
				db	85,119,68,34,65,17,145,85,119,68,34,145,145,21,119,68,33,145,153,119,68,153,153,23,65,153,193,193,193
	qdisco
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,48,255,60,63			; A sprite szín adatai
				db	193,145,48,51,48,49,145,145,51,67,48,51,145,17,19,51,67,147,49,17,17,19,147,3,83,51,17,17,51,50,51,19
				db	35,51,17,17,51,50,50,51,3,51,17,17,147,54,34,52,80,49,19,147,3,50,52,48,49,19,52,51,35,147,50,49
				db	19,52,51,19,163,19,163,3,147,147,35,51,34,3,35,51,51,50,50,99,35,83,34,51,51,50,54,99,51,35,35,51
				db	54,50,35,99,51,53,147,54,53,155,48,53,51,54,53,147,35,50,53,51,155,35,19,51,48,51,155,35,51,34,147,19
				db	163,34,51,49,19,49,147,35,51,19,49,19,49,147,87,99,19,49,19,147,35,83,99,19,49,17,179,17,17,19,54,51
				db	48,147,17,17,19,51,50,155,17,17,19,163,49,17,145,163,145,145,163,145
	qcsik
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,240,255,0,0			; A sprite szín adatai
				db	193,145,16,144,1,145,145,160,145,17,16,160,1,17,193,193,17,176,17,17,176,17,17,180,17,17,180,17,16,176,1,16
				db	176,1,18,178,33,18,178,33,192,192,197,197,192,192,18,178,33,18,178,33,16,168,3,1,16,176,1,17,180,17,17,180
				db	17,17,176,17,17,16,160,1,17,145,160,145,145,160,145
	qstockings
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,48,240,255,63			; A sprite szín adatai
				db	193,193,193,193,193,193,177,18,17,153,23,102,17,49,49,153,23,102,119,17,33,153,23,118,102,98,17,153,20,70,102,97
				db	17,153,20,84,119,97,17,153,20,85,86,113,17,153,20,85,86,145,153,20,85,86,145,153,69,149,145,153,69,85,86,145
				db	153,69,149,145,153,69,85,86,145,145,20,69,149,145,17,18,37,68,149,145,17,35,53,157,145,17,35,53,149,50,145,17
				db	35,53,149,51,145,17,35,51,149,50,145,17,18,34,69,83,50,145,153,20,66,33,145,193,193,193
	qstockings2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,0,0,0,0,0,0,0			; A sprite szín adatai
				db	192,192,192,192,192,192,176,7,0,152,7,119,0,119,112,152,7,159,112,152,7,159,0,152,7,151,112,0,152,7,151,112
				db	0,152,7,151,112,0,152,7,151,144,152,7,151,144,152,159,144,152,159,144,152,159,144,152,159,144,144,7,159,144,0,7
				db	167,144,0,175,144,0,175,144,0,175,144,0,175,144,0,7,167,144,152,7,119,112,144,192,192,192
	qexplosion
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,252,255,0,0,0,63			; A sprite szín adatai
				db	193,153,19,161,17,19,161,19,17,153,19,17,23,18,17,17,18,177,17,19,17,18,17,19,113,17,113,35,49,18,17,18
				db	145,17,18,17,18,17,33,17,23,17,18,17,18,17,49,17,113,153,34,33,153,17,23,17,35,33,153,153,35,33,153,145
				db	18,35,50,153,23,18,34,147,50,19,17,145,23,35,50,153,153,35,33,153,17,18,33,35,33,153,17,50,17,114,33,145
				db	49,17,33,17,18,17,19,17,33,23,145,18,161,17,19,17,18,23,17,33,17,17,33,17,18,17,35,145,113,17,19,145
				db	114,145,145,18,18,145,33,17,153,23,145,19,17,145,33,145,113,145,17,23,169,49,153,23,161,23,185,193
	qProbaSprite
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,0,0,0,0,0,0,0			; A sprite szín adatai
				db	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192
	qkeret
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,204,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193
	qkeret2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,255,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193
	qkeret3
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193

	qministar
				db	1+128			; A sprite szélessége byte-okban
				db	4			; A sprite magassága
				db	0,252,0,0,0,0,0,0			; A sprite szín adatai
				db	17,17,17,17
	qkezdo2_2
				db	54+128			; A sprite szélessége byte-okban
				db	53			; A sprite magassága
				db	0,3,12,192,48,204,240,255			; A sprite szín adatai
				db	249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201
				db	249,249,249,201,161,117,113,249,249,249,153,161,85,87,249,249,249,153,153,23,149,113,249,249,249,145,153,21,82,149,249,249
				db	249,145,153,37,34,85,82,249,249,249,145,153,85,37,85,119,113,249,249,249,17,145,18,82,37,87,115,49,249,249,249,17
				db	145,21,81,37,119,116,67,119,113,17,85,119,17,54,103,19,103,115,85,87,119,17,54,119,113,17,53,119,115,119,115,102
				db	103,119,17,53,119,21,119,113,19,103,113,17,53,119,53,119,22,119,113,145,145,21,33,37,119,54,67,102,113,21,149,113
				db	54,102,19,102,115,157,113,54,103,113,17,53,85,83,85,115,158,113,53,87,21,87,113,52,102,119,17,53,85,53,87,22
				db	103,113,145,145,119,17,37,119,70,68,102,97,53,149,113,54,102,115,102,115,157,113,54,102,113,17,50,85,34,85,83,158
				db	97,53,87,21,85,113,70,150,113,53,85,53,87,20,102,113,145,145,119,17,37,119,102,100,102,99,157,81,54,102,115,102
				db	115,37,87,85,87,54,102,113,17,50,85,82,85,83,158,97,53,87,21,85,115,70,150,97,53,85,53,87,20,70,113,145
				db	145,115,17,39,115,102,100,102,19,85,87,85,87,52,102,115,70,115,85,113,85,87,54,102,113,17,50,85,82,85,19,70
				db	102,70,103,53,87,21,85,115,158,97,53,85,53,87,19,70,113,145,145,51,17,39,116,158,19,85,113,85,87,52,102,115
				db	70,115,37,113,85,87,54,102,113,17,50,157,19,102,99,52,103,53,87,21,85,115,102,97,70,97,53,85,53,85,19,70
				db	113,145,161,19,116,158,19,85,113,37,87,52,102,100,70,115,37,81,85,87,52,102,113,17,50,157,19,70,115,52,103,53
				db	87,21,85,115,70,97,70,97,50,85,55,87,19,102,97,145,161,19,52,150,100,19,85,81,37,85,52,102,100,102,115,85
				db	81,37,85,54,102,97,17,50,157,19,102,115,52,102,53,85,18,85,115,102,97,68,97,53,85,55,85,19,102,97,145,169
				db	52,150,97,19,85,81,37,87,52,158,115,37,81,37,87,52,102,97,17,50,149,81,19,70,115,54,102,53,87,21,85,83
				db	70,103,145,50,85,55,85,19,102,97,145,169,52,150,65,19,37,81,37,85,52,158,115,37,81,37,87,54,102,113,17,50
				db	149,17,19,70,103,150,53,85,18,85,83,70,102,145,50,85,117,85,19,102,97,145,169,52,150,17,19,37,81,37,85,52
				db	158,115,37,81,37,85,52,102,97,17,50,149,17,19,70,150,97,53,85,18,85,81,70,102,113,17,50,157,19,102,97,145
				db	169,52,150,17,19,37,81,37,85,52,158,115,37,81,37,87,52,102,113,17,50,85,81,17,19,70,150,65,53,85,18,85
				db	81,52,102,103,17,50,157,19,102,97,145,169,52,150,17,19,37,81,37,85,52,158,115,37,81,37,85,52,102,97,17,50
				db	85,81,17,19,70,150,17,50,85,18,85,81,19,150,113,50,157,19,102,97,145,169,52,150,113,19,37,81,37,85,52,158
				db	115,37,81,37,85,52,102,97,17,50,85,87,17,19,70,150,113,53,85,18,85,81,17,70,102,113,50,85,117,85,19,70
				db	97,145,169,52,150,103,19,37,81,37,85,52,158,115,37,81,37,85,52,102,97,17,50,149,17,19,70,150,97,50,85,18
				db	85,81,17,52,102,97,50,87,50,85,19,70,97,145,169,52,150,103,19,37,81,37,85,52,158,115,37,81,37,85,52,102
				db	97,17,50,149,113,19,70,150,103,53,85,18,85,81,17,19,70,113,50,85,50,85,19,70,97,145,169,52,158,19,37,81
				db	37,85,52,158,99,37,81,37,85,52,102,97,17,50,149,87,19,70,158,50,85,18,85,81,103,115,102,97,50,85,50,85
				db	19,70,97,145,169,52,158,19,37,81,37,85,52,158,99,37,81,37,85,52,102,97,17,50,149,87,19,70,102,70,102,50
				db	85,18,85,83,102,115,102,113,50,85,50,85,17,68,97,145,169,52,158,19,37,81,37,85,52,102,70,102,99,37,81,37
				db	85,52,102,97,17,50,157,19,70,103,22,102,50,85,18,85,83,102,99,102,97,50,85,50,85,17,68,65,145,169,52,158
				db	115,37,33,37,85,52,102,54,102,99,37,33,37,85,52,102,97,17,50,157,115,70,97,22,102,50,82,18,85,83,102,67
				db	102,97,50,85,50,85,169,169,52,158,99,37,82,85,82,52,102,52,102,99,37,82,149,52,102,97,17,50,157,83,70,97
				db	20,102,18,85,37,85,35,102,99,102,97,50,85,50,85,19,103,113,145,169,52,102,100,102,97,34,149,81,52,102,20,102
				db	99,37,149,82,52,102,97,17,50,85,82,85,83,70,97,20,102,18,37,149,19,70,100,102,113,50,85,50,85,19,70,113
				db	145,169,52,102,100,102,97,50,149,81,52,70,20,102,99,37,149,81,52,102,97,17,50,85,82,85,83,70,97,22,102,19
				db	37,149,17,68,150,113,50,85,50,85,19,70,97,145,169,52,70,99,70,97,18,37,85,33,52,70,20,70,99,34,149,33
				db	52,70,97,17,50,37,83,37,83,68,97,20,102,17,34,85,82,17,20,150,113,50,85,50,85,19,68,97,145,169,52,68
				db	99,68,97,17,34,37,17,52,68,20,68,99,146,37,17,52,68,97,17,50,34,83,34,83,68,65,20,70,17,18,37,81
				db	145,68,70,17,50,37,50,37,19,68,65,145,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201
				db	249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201
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

