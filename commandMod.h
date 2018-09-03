#include <iostream>
#include <iomanip>
#ifndef COMMAND 
#define COMMAND

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <stack>
#include <cstddef>
#include <pwd.h>
#include <grp.h>
#include "list.h"
#include "termSet.h"
#include "commandMod.h"
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
using namespace std;

char enter_cmd_mod(char escape, int rows);


char enter_cmd_mod(char escape, int rows)
{
	gotoxy(rows+2,0);
	struct termios old_terminal;
	tcgetattr ( 1 , &old_terminal);
	struct termios new_terminal = old_terminal;
	new_terminal.c_lflag &= ECHO;
	tcsetattr( 1 , TCSANOW, &new_terminal);
	escape = getchar();
	if( escape == 'q' )
		return escape;
	else
	{
		while( escape != '\033')
		{
			escape = getchar();
			if( escape == 'q' )
			{
				cout << escape;
				break;
			}
		}
	}
	return escape;
}

#endif