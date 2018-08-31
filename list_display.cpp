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

int list_display(int upper, int lower, vector <struct dirent*> directories)
{
	printf("\033[2J");
	gotoxy(1,1);
	//printf("\t%-11s%-40s%-40s%-40s%-40s\n", "S.no", "File/Directory", "Size", "Permissions", "Last Modified");
	//printf("_________________________________________________________________________________________________________________________________________________________________________\n");
	//printf("_________________________________________________________________________________________________________________________________________________________________________\n\n");
	for(int i = upper; i<lower ; i++ )	
	{
		struct stat file_info;
		stat(directories[i]->d_name,&file_info);
		printf("\t%2d%-9s", i+1,".");
		printf("%-40s", directories[i]->d_name);
 		printf("%-40ld", file_info.st_size);
 		printf("%-40o", file_info.st_mode & 0777 );
 		printf("%s", ctime(&file_info.st_mtime));
	}
	gotoxy(1,1);
	//gotoxy(upper,10);
	//printf("_________________________________________________________________________________________________________________________________________________________________________\n");
	//printf("_________________________________________________________________________________________________________________________________________________________________________\n\n");
	
	return 0;
}