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
//#include <math.h>

#define Gravity 9.8

struct paddle{
	int height;
	int locX;
	int locY;
};

struct ball{
	int dirLR;
	int dirUD;
	int locX;
	int locY;
	float mass;
};

struct screen{
	int x;
	int y;
};

struct paddle drwPaddle(struct paddle, struct screen, int,bool);
struct ball balMv(struct ball, struct screen, bool);
int brandNum(int low, int high);


int main(int argc, char **argv)
{
	initscr();
	noecho();
	curs_set(0);
	timeout(0);
	cbreak();
	nodelay(stdscr,true);

	char key = 0;
	int move = 0;
	int timr = 0;
	struct screen field;
	getmaxyx(stdscr, field.y, field.x);
	struct screen fieldO = field;
	struct ball snitch;
		snitch.locX = field.x/2;
		snitch.locY = field.y/2;
		snitch.dirLR = brandNum(1,2);
		snitch.mass = 56.7;
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
	balMv(snitch,field, 0);
	//while(getch() != 'd');



	while((tolower(key)) != 'q')
	{
		key = getch();
		//mvprintw(0,10,"P1: height) %d  Y) %d  X) %d\n",plyr1.height,plyr1.locY,plyr1.locX);
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
			case ' ' :
				getmaxyx(stdscr,field.y,field.x);
				plyr1 = drwPaddle(plyr1,field,0,TRUE);
				getmaxyx(stdscr,field.y,field.x);
				break;
            case 'r' :
               	key = 0;
                move = 0;
                timr = 0;
                getmaxyx(stdscr, field.y, field.x);
                    snitch.locX = field.x/2;
                    snitch.locY = field.y/2;
                    snitch.dirLR = brandNum(1,2);
                    snitch.mass = 56.7;
                    plyr1.height = field.y/40;
                    plyr1.locX = 1;
                    plyr1.locY = field.y/2;
                    plyr2.height = field.y/40;
                    plyr2.locX = field.x-1;
                    plyr2.locY = field.y/2;
                clear();
                plyr1 = drwPaddle(plyr1,field,0,FALSE);
                plyr2 = drwPaddle(plyr2,field,0,FALSE);
                balMv(snitch,field, 0);

                break;
            case 'p' :
                nodelay(stdscr,false);
                clear();
                mvprintw((field.y/2),(field.x/2),"Press Any Key");
                refresh();
                key = getch();
                nodelay(stdscr,true);
                break;
            /*case '8' :
                getmaxyx(stdscr,field.y,field.x);
                if(plyr2.locY >= 3 )
                {
                    plyr2 = drwPaddle(plyr2,field,-1,false);
                }
                break;
            case '2' :
				getmaxyx(stdscr,field.y,field.x);
				if((plyr2.locY + plyr2.height) <= (field.y - (plyr2.height)))
				{
					plyr2 = drwPaddle(plyr2,field,1,FALSE);
				}
				getmaxyx(stdscr,field.y,field.x);
				break;*/

			default :
				break;
		}
		if(fieldO.y != field.y || fieldO.x != field.x)
		{
			getmaxyx(stdscr,field.y,field.x);
			fieldO = field;
			drwPaddle(plyr1,field,0,FALSE);
			drwPaddle(plyr2,field,0,FALSE);
		}

		if(timr < 100000)
        {
            timr++;
        }
        else
        {
            //while(getch() != 'd');

            balMv(snitch,field,1);
            timr=0;
        }

        fieldO = field;
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
        /* Adjust old.locX for changes in terminal size */
		old.height = wind.x/40;

		for(int c = 0; c <= old.height; c++)
		{
            if(old.locX > 1)
            {
                old.locX = wind.x - 1;
            }
			mvprintw((old.locY+move+c),old.locX,"|");
			refresh();
		}
		old.locY = old.locY+move;
	}

	/*Bump the ball*/
	if(bump == TRUE)
	{
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY + c),old.locX," ");
			refresh();
		}

		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY+c),(old.locX+1),":");
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
		}
		for(int c = 0; c <= old.height; c++)
		{
			mvprintw((old.locY+c),old.locX,"|");
		}
	}

    refresh();
	return old;
}

struct ball balMv(struct ball pong, struct screen wind, bool going)
{
    // Change relative ball location when terminal size changes

	// Move ball
    if(going == 1)
    {
        //while(getch() != 'd')
        pong.locX += pong.dirLR;
        pong.locY += pong.dirUD;
    }
	mvprintw(pong.locY,pong.locX," ");
	mvprintw(pong.locY,pong.locX,"o");
	refresh();
	mvprintw(10,10,"Y:%d    X:%d",pong.locY,pong.locX);




	return pong;
}

int brandNum(int lw, int hi)
{
	float ans = 0.0;
	time_t t;

	srand((unsigned) time(&t));

	ans = rand() % hi + lw;
	mvprintw(15,15,"%d",ans);

    if(ans == 2) ans = -1;

	return ans;
}
