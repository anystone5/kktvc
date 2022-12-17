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
	unsigned char Flag;		// (*) 0. bit: jelzi, hogy a sprite be van-e kapcsolva, a 7. pedig, ha tükrözni kell.
	char *SprBackAddr;		// (*) A sprite háttér mentése számára lefoglalt mem. blokk kezdőcíme. Ha nem kell menteni a hátteret akkor az értéke 0!
	char *SprPalAddr;		// (*) A sprite palettájának címe. Ha nincs paletta, akkor értéke 0!
	int (*spritefunc)();		// (*) A sprite kirajzoló rutin kezdőcíme
	unsigned char SprWidth;		// A sprite szélessége
	unsigned char SprHeight;	// A sprite magassága
	unsigned char SprIndRef;	// Sprite index referencia. Azért kell, hogy el tudjuk dönteni kell-e újra inicializálni a sprite alap adatait (pl. RawAddr)
	char *SprRawAddr;		// Az adott sprite forrás adatai
	char *SprScrAddr;		// A sprite vágás utáni kezdőcíme a képernyőn v. háttér bufferben
	unsigned char SprClipSkipRow;	// A sprite felső vágásánál ezen a változón tárolódik, hogy hány sort kell felül kihagynia a sprite kirajzolónak
	struct RECT SprClip;		// A sprite vágás utáni dimenziói
	struct RECT SprPrevClip;	// A sprite előző fázisban értelmezett vágás utáni dimenziói
	unsigned char SprClipFlag;	// A sprite vágási állapotát tárolja le a sprite kirakónak
};



#define      SN     60
#define      speed   2


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
int fullScore=0;

int deep = 0;

struct GOBJ *ptr;


char level1[9] = {0,0,1,
                  2,2,1,
                  3,1,2};


//-------------------------- MAIN --------------------------------
main()
{
	DbInitGameLib(2, gameObjects, SN);
	DbPageFullRamVid();
	DbAssignRenderToVideo();
	DbRandomize();

	ptr = gameObjects;
	DrawSprite(0, 0, 0, 0);
	WaitForKeyDown(KEY_SPACE);
	//DrawSprite(8, 0, 1, 59);

	//StartLevel(3,3,3, level1, 0);
	//StartLevel(6,4,3, level1, 1);

	DbCloseGameLib();
	PrintStr(itos(fullScore));
}

//-------------------------- StartLevel --------------------------------
StartLevel(int lx, int ly, int maxLap, char currentLevel[], int randomLevel)
{
	int i;
	char key;

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
	ptr = gameObjects;
	
	DrawSprite(0, 0, 14, 59);

	maxSizeX = lx;
	maxSizeY = ly;
	
	startX = (60-maxSizeX*8)/2;
	startY = (240-maxSizeY*30)/2;

	for(i=0;i<maxSizeX*maxSizeY;i++)
	{
		lastDrawnlevel[i] = 10;
	}

	if(randomLevel)
	{
		for(i=0;i<maxSizeX*maxSizeY;i++)
		{
			actualLevel[i] = RandomColor();
		}
	}
	else
	{
		for(i=0;i<maxSizeX*maxSizeY;i++)
		{
			actualLevel[i] = currentLevel[i];
		}
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
		if(key!='P')
		{
			KeyDown(key);
			Sleep(10);
			key = 'P';
		}
	}

	fullScore+=levelScore;
}


//-------------------------- Level --------------------------------
Level(int x, int y)
{
	return actualLevel[y*maxSizeX+x];
}

//-------------------------- SetLevel --------------------------------
SetLevel(int x, int y, char c)
{
	actualLevel[y*maxSizeX+x] = c;
}

//-------------------------- LastDrawnlevel --------------------------------
LastDrawnlevel(int x, int y)
{
	return lastDrawnlevel[y*maxSizeX+x];
}

//-------------------------- DrawTable --------------------------------
DrawTable(char withWait, char fast );
{
   int x;
   int y;
   int i;
   int xonscreen;
   int yonscreen;

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
                    case 'C':
                        candy = 4;
                        break;
                    case ' ':
                        candy = 5;
                        break;
                }

		DrawSprite(x, y, candy, x+y*maxSizeX);

                if (x == lastposx && y == lastposy) { lastposx = -1; lastposx = -1; };
            }
        }

	DrawSprite(posx, posy, 6 + moveMode, 58);

	lastposx = posx;
	lastposy = posy;
	
	for(i=0;i<SN;i++)
	{
		lastDrawnlevel[i] = actualLevel[i];
	}
	
	if (withWait) Wait(fast);
}

//-------------------------- DrawSprite --------------------------------
DrawSprite(int x, int y, int candy, int index)
{
	int xonscreen;
	int yonscreen;

	xonscreen= x*8 + startX;
	yonscreen= y*30 + startY;
	
	goIndex[index] = DbInitGameObject(++ptr,xonscreen,yonscreen,candy,GOFLG_VISIBLE, DbSprite16c8,0,0);
	
	DbClipSprite(goIndex[index]);
	DbDrawSprite(goIndex[index]);
}

//-------------------------- ChangeMoveMode --------------------------------
ChangeMoveMode()
{
    char temp;
    if(moveMode)
    {
        selectedPosx = posx;
        selectedPosy = posy;
    }
    else
    {
        if(posx==selectedPosx && posy==selectedPosy)
        {
            //Do nthing
        }
        else if (Level(posx, posy) == Level(selectedPosx, selectedPosy))
        {	
            if(moveMode){ moveMode = 0;} else {moveMode=1;}
        }
        else
        {
            temp = Level(selectedPosx, selectedPosy);
            SetLevel(selectedPosx, selectedPosy, Level(posx, posy));
            SetLevel(posx, posy, temp);
	    deep=0;
	    lap--;

            CheckTable(1);
        }
    }
}

//-------------------------- CheckTable --------------------------------
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

//-------------------------- Wait --------------------------------
Wait(int fast)
{
    int wait;
    wait = speed;
    //if (fast) wait = speed / 2;
    Sleep(wait);
}

//-------------------------- Crush --------------------------------
Crush (int cx1, int cy1, int cx2, int cy2, int cx3, int cy3, int cx4, int cy4, int cx5, int cy5, int draw)
{
    SetLevel(cx1, cy1, 'C');
    SetLevel(cx2, cy2, 'C');
    SetLevel(cx3, cy3, 'C');
    if (cx4 != -1 && cy4!=-1) SetLevel(cx4, cy4, 'C');
    if (cx5 != -1 && cy5 != -1) SetLevel(cx5, cy5, 'C');

    if (draw) DrawTable(true, false);

    SetLevel(cx1, cy1, ' ');
    SetLevel(cx2, cy2, ' ');
    SetLevel(cx3, cy3, ' ');
    if (cx4 != -1) SetLevel(cx4, cy4,  ' ');
    if (cx5 != -1) SetLevel(cx5, cy5, ' ');

    if (draw) DrawTable(true, false);

    levelScore+=deep*3;
    if (cx4 != -1 && cy4!=-1) levelScore+=deep*2;
    if (cx5 != -1 && cy5 != -1) levelScore+=deep*4;
	
    deep++;

    Fall(draw);

    CheckTable(draw);
}

//-------------------------- Fall --------------------------------
Fall(int draw)
{
    int fall;
    int x;
    int y;

    fall = 1;

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

//-------------------------- RandomColor --------------------------------
RandomColor()
{
    int rng;
    char color;

    color = ' ';

    rng = DbRndRange(0)*6/256;

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
    }

    return color;
}

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

    DrawTable(false, false);
}

//{	A grafikus munkaasztalból importált adatok.
#asm   /* A grafikus munkaasztalból importált adatok. NE VÁLTOZTASD MEG! */
		;{	Enumerált sprite indexek. Célszerű a főprogram elejére másolni!
				enum	SPR_IND_GREEN, //0
					SPR_IND_ORANGE2, //139
					SPR_IND_PURPLE2, //322
					SPR_IND_BLUE2

		;}

	qGraphicsBaseAddr
	GfxBaseAddr		dw	SpriteCount-GfxBaseAddr,0,0

	;{   Sprite-ok adatai (Automatikusan beemelve!)
	SpriteCount		db 4
	SpriteIndexArray
				dw	0,139,322,473

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

	;}
#endasm
//}
