#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <time.h>
#include <stack>
#include <vector>
#include "explorerFunc.h"
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
using namespace std;

struct termios canon_to_NC()
{
	struct termios old_terminal;
	tcgetattr ( 1 , &old_terminal);
	struct termios new_terminal = old_terminal;
	new_terminal.c_lflag &= ~ICANON;
	new_terminal.c_lflag &= ~ECHO;
	new_terminal.c_cc[VMIN] = 1;
	new_terminal.c_cc[VTIME] = 0;
	tcsetattr( 1 , TCSANOW, &new_terminal);
	return old_terminal;
}

