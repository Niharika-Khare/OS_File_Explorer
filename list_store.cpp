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

int list_store(DIR *cur_dir,const char * path, vector <struct dirent*> directories)
{
	struct dirent *next_dir;
	cur_dir = opendir (path); 
	if (cur_dir != NULL)
	{
		while ( next_dir=readdir(cur_dir) )
		{
			directories.push_back(next_dir);
		}
	    closedir(cur_dir);
	}
	else
		printf("Directory Not Found!");
 	return 1;
}