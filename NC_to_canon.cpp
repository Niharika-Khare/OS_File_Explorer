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

using namespace std;

void NC_to_canon(struct termios term_p)
{
	tcsetattr( 1 , TCSANOW, &term_p);
}