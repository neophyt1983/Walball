/*----------------------------------------------------------------------------------------------*/
/*					Character Graphics Library													*/
/*																								*/
/* Everything from maps to menus that deals with text in the game client.						*/
/*----------------------------------------------------------------------------------------------*/

#ifdef linux
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#endif



void dClock();


#ifdef _WIN32

#elif linux

void sizeUpdate()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
}
#endif


void dClock(int x, int y)
{
	curs_set(0);
	time_t T= time(NULL);
	struct tm tm = *localtime(&T);
	
	int hour = 0;
	if(tm.tm_hour > 12)
		hour = tm.tm_hour - 12;
	else
		hour = tm.tm_hour;
	
	move((y-1),0);
	clrtoeol();
	move((y+1),0);
	clrtoeol();
	
	mvprintw(y,x,"%02d/%02d/%04d\n%02d:%02d:%02d",tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, hour, tm.tm_min, tm.tm_sec);
	mvprintw(y,x," ");
	refresh();
		
	curs_set(0);
}
