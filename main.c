/************************************************************************/
/*				walbal					*/
/*			(c)2019 Creative Commons			*/
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

struct paddle{
	int height;
	int locX;
	int locY;
};

struct ball{
	float dirLR;
	float dirUD;
	int locX;
	int locY;
};

struct screen{
	int x;
	int y;
};

struct paddle drwPaddle(struct paddle, struct screen, int,bool);
struct ball balMv(struct ball, struct screen);
int brandNum();


int main(int argc, char **argv)
{
	initscr();
	noecho();
	curs_set(0);
	timeout(0);

	char key = 0;
	int move = 0;
	int timr = 0;
	struct screen field;
	getmaxyx(stdscr, field.y, field.x);
	struct screen fieldO = field;
	struct ball snitch;
		snitch.locX = brandNum();
		snitch.locY = brandNum();
		snitch.locX = roundf(field.x/2);
		snitch.locY = roundf(field.y/2);
	struct paddle plyr1;
		plyr1.height = field.y/40;
		plyr1.locX = 1;
		plyr1.locY = field.y/2;
	struct paddle plyr2;
		plyr2.height = field.y/40;
		plyr2.locX = field.x-1;
		plyr2.locY = field.y/2;
		
	plyr1 = drwPaddle(plyr1,field,0,FALSE);
	plyr2 = drwPaddle(plyr2,field,0,FALSE);
	balMv(snitch,field);


	while((tolower(key)) != 'q')
	{
		key = getch();
		mvprintw(0,10,"P1: height) %d  Y) %d  X) %d\n",plyr1.height,plyr1.locY,plyr1.locX);
		refresh();

		switch(tolower(key)){
			case 'w' :
				getmaxyx(stdscr,field.y,field.x);
				if(plyr1.locY >= 3 )
				{
					plyr1 = drwPaddle(plyr1,field,-1,FALSE);
				}
				getmaxyx(stdscr,field.y,field.x);
				break;
			case 's' :
				getmaxyx(stdscr,field.y,field.x);
				if((plyr1.locY + plyr1.height) <= (field.y - (plyr1.height)))
				{
					plyr1 = drwPaddle(plyr1,field,1,FALSE);
				}
				getmaxyx(stdscr,field.y,field.x);
				break;
			/*case ' ' :
				getmaxyx(stdscr,field.y,field.x);
				plyr1 = drwPaddle(plyr1,field,0,TRUE);
				getmaxyx(stdscr,field.y,field.x);
				break;*/
			default :
				break;
		}
		if(fieldO.y != field.y || fieldO.x != field.x)
		{
			getmaxyx(stdscr,field.y,field.x);
			fieldO = field;
			plyr1.height = field.y/40;
			plyr2.height = field.y/40;
			drwPaddle(plyr1,field,0,FALSE);
			drwPaddle(plyr2,field,0,FALSE);
		}
		if(timr == 100000)
		{
			balMv(snitch,field);
			timr = 0;
		}
		timr++;
		plyr2 = drwPaddle(plyr2,field,0,FALSE);
	}


	endwin();
	return 0;
}

struct paddle drwPaddle(struct paddle old, struct screen wind, int move,bool bump)
{

	


	/*Erase the old paddle*/
	if(move != 0 && bump == FALSE)
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY + c),old.locX," ");
			refresh();
		}
	
	/*Draw Paddle*/
	if(bump == FALSE)
	{
		old.height = wind.x/40;
	
		for(int c = 0; c <= old.height; c++)
		{
				mvprintw((old.locY+move+c),old.locX,"|");
				refresh();
		}
		old.locY = old.locY+move;
	}
	
	/*Bump the ball*/
	/*if(bump == TRUE)
	{
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY + c),old.locX," ");
			refresh();
		}
	
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY+c),(old.locX+1),"|");
			refresh();
		}
		int n = 0;
		char key = 0;
		while(key == -1)
		{
			key = getch();
			n++;
		}
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY + c),(old.locX+1)," ");
			refresh();
		}
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY+c),old.locX,"|");
			refresh();
		}
	}*/

	
	return old;
}

struct ball balMv(struct ball pong, struct screen wind)
{
	srand(time(NULL));
	/*Draw the ball*/
	mvprintw(pong.locY,pong.locX,"o");
	refresh();
	
	/*Move ball*/
	mvprintw(roundf(pong.locY+pong.dirUD),roundf(pong.locX+pong.dirLR),"o");
	mvprintw(pong.locY,pong.locX," ");
	refresh();
	pong.locY += roundf(pong.dirUD);
	pong.locX += roundf(pong.dirLR);
	mvprintw(10,10,"Y:%d    X:%d",pong.locY,pong.locX);
	
	return pong;
}

int brandNum()
{
	float ans = 0.0;
	
	srand(time(0));
	
	ans = rand() % 3 + (-1);
	
	return ans;
}
