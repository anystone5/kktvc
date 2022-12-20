//{ -------------------------- INIT --------------------------------
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

struct GameLevel levels[37];


#define      SN     38
#define      speed   1


struct GOBJ gameObjects[SN];
struct GOBJ *goIndex[SN];

char actualLevel[SN];
char lastDrawnlevel[SN];

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

//}

//{-------------------------- MAIN --------------------------------
main()
{
	DbInitGameLib(2, gameObjects, SN);
	DbPageFullRamVid();
	DbAssignRenderToVideo();
	DbRandomize();
	DbInitFont(KKF);
	DbSetFontParam(FNT_COLOR, COLOR_WHITE); 
	DbSetFontParam(FNT_BACKCOLOR, COLOR_DARKBLUE);  

	ptr = gameObjects;

	MainScreen();
	CreateLevels();
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

//{-------------------------- CreateLevels --------------------------------
CreateLevels()
{
	int i;

	for(i=1;i<37;i++)
	{	
		levels[i].score = 0; levels[i].star1Score = 20; levels[i].star2Score = 50; levels[i].star3Score = 100; levels[i].maxLap = 20; levels[i].condyNumber = 6; levels[i].extras = 1;
	}
	
	i=1; levels[i].star1Score = 1;	levels[i].star2Score = 10;	levels[i].star3Score = 30;	levels[i].xSize = 3;	levels[i].ySize = 3;	levels[i].maxLap = 10;	levels[i].condyNumber = 4;	levels[i].extras = 0;
	i=2; levels[i].star1Score = 1;	levels[i].star2Score = 10;	levels[i].star3Score = 30;	levels[i].xSize = 4;	levels[i].ySize = 4;	levels[i].maxLap = 10;	levels[i].condyNumber = 4;	levels[i].extras = 0;
	i=3; levels[i].xSize = 5;	levels[i].ySize = 3;	levels[i].condyNumber = 5;	levels[i].extras = 0;
	i=4; levels[i].xSize = 4;	levels[i].ySize = 6;	levels[i].condyNumber = 5;	levels[i].extras = 0;
	i=5; levels[i].xSize = 5;	levels[i].ySize = 5;    levels[i].extras = 0;
	i=6; levels[i].xSize = 6;	levels[i].ySize = 6;	levels[i].maxLap = 15;  levels[i].star3Score = 200;	

	i=7; levels[i].xSize = 4;	levels[i].ySize = 6;
	i=8; levels[i].xSize = 6;	levels[i].ySize = 3;
	i=9; levels[i].xSize = 5;	levels[i].ySize = 5;

	i=10; levels[i].xSize = 3;	levels[i].ySize = 3; levels[i].condyNumber = 4;
	i=11; levels[i].xSize = 2;	levels[i].ySize = 6; levels[i].condyNumber = 4;
	i=12; levels[i].xSize = 6;	levels[i].ySize = 2; levels[i].condyNumber = 4;
	i=13; levels[i].xSize = 5;	levels[i].ySize = 4; levels[i].condyNumber = 3; levels[i].star3Score = 500;
	i=14; levels[i].xSize = 6;	levels[i].ySize = 6; levels[i].condyNumber = 4; levels[i].extras = 0; levels[i].star3Score = 1000;
	i=15; levels[i].xSize = 4;	levels[i].ySize = 4; levels[i].maxLap = 10;
	i=16; levels[i].xSize = 4;	levels[i].ySize = 6; levels[i].maxLap = 10; levels[i].extras = 0; 
	i=17; levels[i].xSize = 2;	levels[i].ySize = 4;
	i=18; levels[i].xSize = 3;	levels[i].ySize = 5;
	i=19; levels[i].xSize = 4;	levels[i].ySize = 6;

	i=20; levels[i].xSize = 1;	levels[i].ySize = 6; levels[i].condyNumber = 3; levels[i].star1Score = 3; levels[i].star2Score = 6; levels[i].star3Score = 10;
	i=21; levels[i].xSize = 4;	levels[i].ySize = 4; levels[i].condyNumber = 5;
	i=22; levels[i].xSize = 6;	levels[i].ySize = 6; levels[i].condyNumber = 3; levels[i].star3Score = 1000;
	i=23; levels[i].xSize = 3;	levels[i].ySize = 3; levels[i].condyNumber = 3;
	i=24; levels[i].xSize = 3;	levels[i].ySize = 6; levels[i].condyNumber = 5;
	i=25; levels[i].xSize = 5;	levels[i].ySize = 4; levels[i].condyNumber = 3;
	i=26; levels[i].xSize = 5;	levels[i].ySize = 5; levels[i].condyNumber = 3; levels[i].maxLap = 10;  levels[i].star3Score = 1000;
	i=27; levels[i].xSize = 4;	levels[i].ySize = 2; levels[i].condyNumber = 5;
	i=28; levels[i].xSize = 4;	levels[i].ySize = 6; levels[i].star3Score = 200;
	i=29; levels[i].xSize = 5;	levels[i].ySize = 5; levels[i].maxLap = 30; levels[i].star3Score = 400;

	i=30; levels[i].xSize = 3;	levels[i].ySize = 4; levels[i].condyNumber = 2; levels[i].star2Score = 300; levels[i].star3Score = 1000;
	i=31; levels[i].xSize = 5;	levels[i].ySize = 2; levels[i].condyNumber = 3; levels[i].star2Score = 300; levels[i].star3Score = 1000;
	i=32; levels[i].xSize = 4;	levels[i].ySize = 6; levels[i].condyNumber = 4; levels[i].star3Score = 900;
	i=33; levels[i].xSize = 6;	levels[i].ySize = 3;
	i=34; levels[i].xSize = 4;	levels[i].ySize = 4;
	i=35; levels[i].xSize = 5;	levels[i].ySize = 5; levels[i].condyNumber = 5; 
	i=36; levels[i].xSize = 6;	levels[i].ySize = 6; levels[i].maxLap = 30; levels[i].star3Score = 300;	

}
//}

//{-------------------------- MainScreen --------------------------------
MainScreen()
{
	ClearScreen();
	DrawSprite2(4,30,16,59);
	DrawSprite2(8,85,0,59);
	DrawSprite2(16,85,1,59);
	DrawSprite2(24,85,2,59);
	DrawSprite2(32,85,3,59);
	DrawSprite2(40,85,4,59);
	DrawSprite2(48,85,5,59);
	DrawCoolString(5,190,"MADE BY: ANYSTONE", 7);
	DrawCoolString(5,210,"POWERED BY: DEVTTOOLS", 5);
	DrawCoolString(5,220,"FROM DOBERDO BBROTHERS", 5);
	WaitForKeyPress(KEY_SPACE);
}
//}

//{-------------------------- LevelSelector --------------------------------
LevelSelector()
{
	int lx;
	int ly;
	int plx;
	int ply;
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

	plx = 0;
	ply = 0;

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
		if (IsKeyDown(JOY1_UP) || IsKeyDown(KEY_W)) key = 'W';	
		if (IsKeyDown(JOY1_LEFT) || IsKeyDown(KEY_A)) key = 'A';	
		if (IsKeyDown(JOY1_DOWN) || IsKeyDown(KEY_S)) key = 'S';	
		if (IsKeyDown(JOY1_RIGHT) || IsKeyDown(KEY_D)) key = 'D';	
		if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RET) || IsKeyDown(JOY1_FIRE)) key = ' ';	
		if(key!='P')
		{
			olx = plx;
			oly = ply;

			switch (key)
			{
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
			
			Sleep(5);
			key = 'P';
		}
	}
	
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
		if(key!='P' && key!='Q')
		{
			KeyDown(key);
			key = 'P';
		}
		Sleep(5);
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
DrawTable(char withWait, char fast );
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
	
	goIndex[index] = DbInitGameObject(ptr,xonscreen,yonscreen,candy,GOFLG_VISIBLE, DbSprite16c8,0,0);
	
	DbClipSprite(goIndex[index]);
	DbDrawSprite(goIndex[index]);
}
//}

//{-------------------------- DrawSprite2 --------------------------------
DrawSprite2(int x, int y, int candy, int index)
{
	goIndex[index] = DbInitGameObject(ptr,x,y,candy,GOFLG_VISIBLE, DbSprite16c8,0,0);
	
	DbClipSprite(goIndex[index]);
	DbDrawSprite(goIndex[index]);
}
//}

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
			        
				Sound(2000,3,15);
			        Sound(1000,3,15);
			        Sound(500,3,15);
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
				Sound(2000,3,15);
			        Sound(1000,3,15);
			        Sound(500,3,15);

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

				Sound(2000,3,15);
			        Sound(1000,3,15);
			        Sound(500,3,15);
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
				Sound(2000,3,15);
			        Sound(1000,3,15);
			        Sound(500,3,15);
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
    Sound(2000,3,15);
    Sound(1000,3,15);

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
		    	Sound(3723,2,15);
	 	        pair=0;
		    }
                    else
		    {
		    	Sound(3823,2,15);
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

//{-------------------------- KeyDown --------------------------------
KeyDown(char KeyCode)
{
    int oldposx;
    int oldposy;
    oldposx = posx;
    oldposy = posy;

    switch (KeyCode)
    {
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

//{	A grafikus munkaasztalból importált adatok.
#asm   /* A grafikus munkaasztalból importált adatok. NE VÁLTOZTASD MEG! */
		;{	Enumerált sprite indexek. Célszerű a főprogram elejére másolni!
				enum	SPR_IND_GREEN, //0
					SPR_IND_ORANGE2, //139
					SPR_IND_PURPLE2, //322
					SPR_IND_BLUE2, //473
					SPR_IND_YELLOW32, //639    (0,156,286,476,565,719)
					SPR_IND_RED, //795
					SPR_IND_DISCO, //925
					SPR_IND_CSIK, //1115
					SPR_IND_STAR, //1204
					SPR_IND_EMPTYSTAR //1366 (121)
					SPR_IND_CRUSH2, //1487
					SPR_IND_SPACE2, //1697
					SPR_IND_KERET, //1737
					SPR_IND_KERET2, //1821
					SPR_IND_KERET3, //1905
					SPR_IND_MINISTAR, //1989
					SPR_IND_KEZDO //2003

		;}

	qGraphicsBaseAddr
	GfxBaseAddr		dw	SpriteCount-GfxBaseAddr,0,0

	;{   Sprite-ok adatai (Automatikusan beemelve!)
	SpriteCount		db 17
	SpriteIndexArray
				dw	0,139,322,473,639,795,925,1115,1204,1366,1487,1697,1737,1821,1905,1989,2003

	SpriteDataBuffer	ds	0,0
	DecompressBuffer	ds	0,0

	SpriteBaseAddr
	green
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,240,255,48,0,60,0			; A sprite szín adatai
				db	193,193,17,20,66,34,66,68,65,17,17,66,146,36,148,17,17,156,146,36,17,17,148,66,146,36,17,17,148,66,146,68
				db	17,17,180,17,17,36,172,17,17,36,51,164,17,17,36,51,52,156,17,17,36,70,156,66,17,17,36,164,66,17,17,36
				db	164,66,17,17,36,164,66,17,17,36,164,66,17,17,36,164,66,17,17,36,164,66,17,17,34,164,66,17,17,146,156,66
				db	17,17,154,66,146,17,17,178,17,17,178,17,17,178,17,17,178,17,17,178,17,17,178,17,17,178,17,17,18,162,33,17
				db	193
	orange2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,252,0,60,0			; A sprite szín adatai
				db	193,193,153,38,33,153,145,18,68,70,153,145,20,68,70,33,145,145,34,50,52,65,145,145,52,148,66,145,145,36,67,68
				db	66,145,17,18,70,51,52,67,145,17,18,67,50,35,52,145,17,19,68,35,51,54,145,17,19,68,147,68,145,17,19,68
				db	147,52,33,17,17,19,70,35,51,52,33,17,17,19,70,35,51,38,33,17,17,19,70,35,51,36,33,17,17,19,70,35
				db	51,68,33,17,17,19,70,35,51,68,33,17,17,19,68,35,35,67,145,17,19,70,148,67,145,17,19,54,68,70,99,145
				db	17,18,52,68,102,66,145,17,18,52,68,100,66,145,145,51,68,67,50,145,145,51,148,49,145,145,35,51,67,33,145,145
				db	19,147,33,145,145,18,146,153,153,34,33,153,193
	purple2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,207,15,0,0,0,0			; A sprite szín adatai
				db	193,193,145,50,35,50,35,145,145,162,145,17,18,162,49,17,17,18,50,154,33,17,17,18,35,34,51,34,33,17,17,18
				db	50,35,50,34,33,17,17,50,34,50,146,33,17,17,146,51,146,35,17,17,178,17,18,162,50,34,49,18,146,50,35,146
				db	33,18,162,35,34,33,18,50,154,35,35,33,18,34,50,34,35,51,34,49,18,178,33,19,178,33,18,34,50,35,154,33
				db	17,178,17,17,178,17,17,146,50,50,34,33,17,17,50,162,33,17,17,18,162,33,17,17,18,162,33,17,17,19,162,49
				db	17,17,19,162,145,145,154,35,145,169,49,145,193
	blue2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,195,243,255,51,0,0			; A sprite szín adatai
				db	193,193,153,18,33,153,153,146,33,145,145,154,33,145,17,18,154,33,145,17,18,162,33,17,17,170,145,17,34,33,154,33
				db	17,17,34,33,18,154,17,17,34,35,51,83,146,17,18,34,20,83,51,146,17,17,34,21,19,51,50,145,18,146,35,51
				db	53,18,17,17,34,33,35,147,34,17,18,34,37,35,51,85,34,17,18,18,17,18,51,81,18,17,18,17,21,50,81,19
				db	18,17,19,18,33,19,147,50,17,17,33,34,35,51,82,34,17,17,18,162,33,17,17,49,18,153,33,17,17,50,17,154
				db	145,17,18,17,18,34,18,145,17,19,33,145,81,145,145,82,145,81,145,145,21,33,161,153,149,153,193,193
	yellow32
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,252,0,0,60,0			; A sprite szín adatai
				db	193,193,193,153,22,102,33,145,153,19,51,49,145,153,99,51,50,145,153,147,54,145,145,18,54,147,145,145,22,155,97,17
				db	145,19,99,147,97,17,145,99,99,51,54,49,17,145,99,147,54,50,17,145,163,54,17,145,163,99,17,17,22,163,99,17
				db	17,22,99,163,17,17,22,99,54,155,33,17,19,99,155,54,97,17,22,102,155,54,33,17,22,38,147,54,102,17,17,22
				db	38,99,51,54,102,17,17,18,34,99,51,54,35,17,145,98,35,51,98,38,17,145,98,34,102,34,98,17,145,38,154,97
				db	17,145,22,98,34,38,33,17,153,38,102,98,145,161,18,153,193,193
	red
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,204,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,145,18,33,161,145,146,161,145,34,50,161,145,35,50,33,153,17,18,35,51,33,153,17,18,35,51,33,153
				db	17,18,35,50,33,153,145,35,50,50,153,145,34,51,50,153,145,34,51,50,33,145,145,34,147,34,145,145,34,35,51,50
				db	145,145,18,35,147,33,17,145,18,35,51,35,49,17,145,18,34,51,35,34,17,153,34,35,51,50,17,153,34,35,51,50
				db	17,153,18,34,35,34,17,161,34,35,34,17,161,146,33,17,169,34,145,193,193,193,193,193
	disco
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,48,255,60,63			; A sprite szín adatai
				db	193,145,48,51,48,49,145,145,51,67,48,51,145,17,19,51,67,147,49,17,17,19,147,3,83,51,17,17,51,50,51,19
				db	35,51,17,17,51,50,50,51,3,51,17,17,147,54,34,52,80,49,19,147,3,50,52,48,49,19,52,51,35,147,50,49
				db	19,52,51,19,163,19,163,3,147,147,35,51,34,3,35,51,51,50,50,99,35,83,34,51,51,50,54,99,51,35,35,51
				db	54,50,35,99,51,53,147,54,53,155,48,53,51,54,53,147,35,50,53,51,155,35,19,51,48,51,155,35,51,34,147,19
				db	163,34,51,49,19,49,147,35,51,19,49,19,49,147,87,99,19,49,19,147,35,83,99,19,49,17,179,17,17,19,54,51
				db	48,147,17,17,19,51,50,155,17,17,19,163,49,17,145,163,145,145,163,145
	csik
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,192,240,255,0,0			; A sprite szín adatai
				db	193,145,16,144,1,145,145,160,145,17,16,160,1,17,193,193,17,176,17,17,176,17,17,180,17,17,180,17,16,176,1,16
				db	176,1,18,178,33,18,178,33,192,192,197,197,192,192,18,178,33,18,178,33,16,168,3,1,16,176,1,17,180,17,17,180
				db	17,17,176,17,17,16,160,1,17,145,160,145,145,160,145
	star
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,252,0,0,0,60,63			; A sprite szín adatai
				db	161,97,153,161,97,153,161,103,153,153,22,102,153,153,22,102,153,153,118,102,153,153,38,34,97,145,153,38,39,33,145,145
				db	118,102,146,113,17,17,18,34,102,34,38,98,113,17,158,34,38,34,33,17,150,98,146,38,97,17,114,102,98,34,38,102
				db	97,17,22,150,98,150,113,17,22,38,166,17,17,23,166,103,17,145,158,98,97,17,145,118,150,98,145,145,114,150,98,145
				db	145,114,150,98,113,17,145,114,150,98,113,17,145,98,98,98,98,33,17,145,34,38,98,102,33,17,145,34,102,118,102,33
				db	17,145,38,103,23,102,97,17,145,102,113,17,118,97,17,145,119,145,23,113,17,193,193,193
	emptystar
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,0,0,0,0,0,0			; A sprite szín adatai
				db	161,113,153,161,113,153,161,119,153,153,23,119,153,153,23,119,153,153,151,153,153,151,113,145,153,151,113,145,145,167,113,17
				db	17,23,175,113,17,183,113,17,183,113,17,183,113,17,23,175,113,17,23,175,17,17,23,175,17,145,167,113,17,145,23,159
				db	145,145,23,159,145,145,167,113,17,145,167,113,17,145,167,113,17,145,167,113,17,145,167,113,17,145,151,23,119,113,17,145
				db	119,113,17,119,113,17,145,119,145,23,113,17,193,193,193

	crush2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,12,252,255,0,60,0			; A sprite szín adatai
				db	193,153,34,33,153,145,22,50,98,153,18,33,102,34,102,98,97,17,35,38,102,38,51,99,34,17,38,38,150,51,54,34
				db	17,98,38,102,35,99,54,98,17,34,150,98,99,51,98,17,38,102,99,102,38,51,98,17,102,99,51,102,34,99,98,17
				db	34,99,51,54,98,102,98,17,102,99,51,54,102,54,98,17,102,99,51,54,98,34,35,17,34,102,51,54,158,17,34,174
				db	99,17,38,38,150,38,54,99,17,99,102,38,99,38,54,98,17,38,102,98,34,38,54,102,17,18,102,38,102,38,51,99
				db	17,22,34,51,102,38,98,98,17,22,34,99,54,38,102,54,17,19,150,54,98,98,35,33,22,50,158,34,36,33,22,102
				db	38,102,98,98,102,33,17,102,98,102,38,98,38,33,17,22,54,102,70,98,18,17,17,19,99,67,102,38,145,145,158,97
				db	145,145,98,38,97,33,145,193
	space2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193,193

	Keret
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,204,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193

	Keret2
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,255,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193

	Keret3
				db	8+128			; A sprite szélessége byte-okban
				db	30			; A sprite magassága
				db	0,3,0,0,0,0,0,0			; A sprite szín adatai
				db	193,193,193,193,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17
				db	176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17,17,176,17
				db	17,176,17,17,176,17,193,193,193,193

				db	1+128			; A sprite szélessége byte-okban
				db	4			; A sprite magassága
				db	0,3,252,0,0,0,0,0			; A sprite szín adatai
				db	17,33,33,17

	kezdo
				db	54+128			; A sprite szélessége byte-okban
				db	53			; A sprite magassága
				db	0,3,12,192,0,0,0,0			; A sprite szín adatai
				db	249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201
				db	249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201
				db	169,50,34,35,34,33,17,146,17,50,34,3,34,35,154,17,50,34,33,17,50,34,35,34,35,154,17,50,34,18,34,33
				db	19,34,33,17,50,34,50,34,18,34,33,145,169,50,34,35,34,33,18,146,33,50,34,3,34,35,154,33,50,34,33,17
				db	50,34,35,34,35,154,33,50,34,18,34,33,50,146,17,50,34,50,34,18,34,33,145,169,50,154,33,50,146,33,50,34
				db	35,34,35,154,33,50,34,33,17,50,34,32,34,35,154,33,50,34,18,34,33,154,33,50,34,50,34,18,34,33,145,169
				db	50,154,35,154,33,50,34,35,34,35,162,50,34,33,17,50,154,35,154,33,50,34,18,34,35,154,33,50,34,50,34,18
				db	34,33,145,169,50,154,19,162,50,34,35,34,35,34,33,146,50,34,33,17,50,154,19,162,50,34,18,34,35,154,33,50
				db	34,50,34,19,34,33,145,169,50,154,19,34,33,146,50,34,35,34,35,34,33,146,50,34,33,17,50,154,19,34,35,50
				db	34,50,34,18,34,35,34,33,34,33,50,34,50,34,19,34,33,145,169,50,154,19,34,33,146,50,154,35,34,33,146,50
				db	34,33,17,50,154,19,34,35,50,34,50,34,18,34,35,34,33,34,33,50,34,50,34,19,34,33,145,169,50,154,19,34
				db	33,146,50,154,35,34,33,146,50,34,33,17,50,154,19,34,35,50,34,50,34,18,34,35,34,33,34,33,50,34,50,34
				db	19,34,33,145,169,50,146,33,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,146,33,19,34,35,50,34,50,34
				db	18,34,35,146,145,50,34,50,34,19,34,33,145,169,50,146,33,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50
				db	146,17,19,162,50,34,18,34,35,146,145,50,154,19,34,33,145,169,50,146,17,19,34,33,146,50,154,35,34,33,146,50
				db	34,33,17,50,146,17,19,154,33,50,34,18,34,33,146,33,17,50,154,19,34,33,145,169,50,146,17,19,34,33,146,50
				db	154,35,34,33,146,50,34,33,17,50,34,33,17,19,154,33,50,34,18,34,33,50,146,17,50,154,19,34,33,145,169,50
				db	146,17,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,34,33,17,19,154,17,50,34,18,34,33,19,146,33,50
				db	154,19,34,33,145,169,50,146,33,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,146,17,19,154,33,50,34,18
				db	34,33,17,146,33,50,154,19,34,33,145,169,50,154,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,146,17,19
				db	154,33,50,34,18,34,33,17,50,34,33,50,34,50,34,19,34,33,145,169,50,154,19,34,33,146,50,154,35,34,33,146
				db	50,34,33,17,50,146,33,19,162,50,34,18,34,33,17,19,34,33,50,34,50,34,19,34,33,145,169,50,154,19,34,33
				db	146,50,154,35,34,33,146,50,34,33,17,50,154,19,162,50,34,18,34,33,34,35,34,33,50,34,50,34,19,34,33,145
				db	169,50,154,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,154,19,162,50,34,18,34,35,34,35,34,33,50,34
				db	50,34,17,34,33,145,169,50,154,19,34,33,146,50,154,35,34,33,146,50,34,33,17,50,154,19,146,18,34,50,34,18
				db	34,35,34,35,34,33,50,34,50,34,17,34,33,145,169,50,154,35,34,33,146,50,34,50,34,35,34,33,146,50,34,33
				db	17,50,154,35,34,33,18,34,50,34,18,34,35,34,33,34,33,50,34,50,34,169,169,50,154,35,162,50,34,50,34,35
				db	162,50,34,33,17,50,154,35,34,33,18,34,18,154,35,34,33,34,33,50,34,50,34,19,34,33,145,169,50,154,33,154
				db	33,50,34,18,34,35,162,50,34,33,17,50,154,35,34,33,18,34,18,154,19,154,33,50,34,50,34,19,34,33,145,169
				db	50,154,33,50,146,33,50,34,18,34,35,154,33,50,34,33,17,50,34,32,34,35,34,33,18,34,19,154,17,154,33,50
				db	34,50,34,19,34,33,145,169,50,34,35,34,33,18,146,33,50,34,18,34,35,154,33,50,34,33,17,50,34,35,34,35
				db	34,33,18,34,17,154,17,18,146,33,50,34,50,34,19,34,33,145,169,50,34,35,34,33,17,146,17,50,34,18,34,35
				db	154,17,50,34,33,17,50,34,35,34,35,34,33,18,34,17,18,34,33,145,146,17,50,34,50,34,19,34,33,145,249,249
				db	249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249,249,201,249,249
				db	249,201,249,249,249,201,249,249,249,201,249,249,249,201

	;}


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
