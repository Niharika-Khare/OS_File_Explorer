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

vector <string> commands;
char enter_cmd_mod(char escape, int rows);

char enter_cmd_mod(char escape, int rows)
{
	gotoxy(rows+2,0);
	escape = getchar();
	cout << escape;
	//string command_buff += string(escape);
	if( escape == 'q' )
		return escape;
	else
	{
		while( escape != '\033')
		{
			escape = getchar();
			if( escape != '\n')
			{
				cout << escape;
				//command_buff += to_string(escape);
			}
			else 
			{
				cout << "\033[2K";
				gotoxy(rows+2,0);
				// if( commands.find(command_buff) == commands.end())
				// {
					
				// 	cout << "Command not Found!";
				// }
				
			}
			if( escape == 'q' )
				break;
		}
	}
	return escape;
}

#endif