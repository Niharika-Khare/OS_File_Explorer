#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <time.h>
#include <stack>
#include <vector>
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
using namespace std;

stack <struct dirent> dir_struct;
vector <struct dirent *> directories; 
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

void NC_to_canon(struct termios term_p)
{
	tcsetattr( 1 , TCSANOW, &term_p);
}

int list_display(DIR *cur_dir,const char * path)
{
	struct dirent *next_dir;
	cur_dir = opendir (path); 
	int sno = 0;
	if (cur_dir != NULL)
	{
		while ( (next_dir=readdir(cur_dir) ) && sno <=19 )
		{
			struct stat file_info;
			directories.push_back(next_dir);
			stat(directories[sno-1]->d_name,&file_info);
			printf("\t%2d%-9s", ++sno,".");
			printf("%-40s", directories[sno-1]->d_name);
			printf("%-40ld", file_info.st_size);
			printf("%-40o", file_info.st_mode & 0777 );
			printf("%s", ctime(&file_info.st_mtime));
	    }
	    closedir(cur_dir);
	}
	else
		printf("Directory Not Found!");
 	return 1;
}

int main ()
{
	printf("\033[2J\033[H");
	printf("\t%-11s%-40s%-40s%-40s%-40s\n", "S.no", "File/Directory", "Size", "Permissions", "Last Modified");
	printf("_________________________________________________________________________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________________________________________________________________________\n\n");
	struct termios old_terminal = canon_to_NC();
	DIR *cur_dir;
	const char * path = "../";
	list_display(cur_dir,path);
	printf("_________________________________________________________________________________________________________________________________________________________________________\n");
	printf("_________________________________________________________________________________________________________________________________________________________________________\n\n");
	while(1) {
	printf("\033[5;10H");
	int k = 0;
	char c;
	while(1)
	{
		c = getchar();		
		if( c ==';' || c == 'q' )
			break;		
		else if( c== 10 )
		{
		 	printf("zvzdfgv");
		}
		else if( c == '\033')
			if(getchar() == '[')
			{	
				c = getchar();
				if( k == 0 && c == 'B' )
				{
					k++;
					printf("\033[B");
				}
				else if( k == 19 && c == 'A' )
				{
					k--;
					printf("\033[A"); 
				}
				else if( k>0 && k<19 )	
				{
					switch(c)
					{

					case 'A' : printf("\033[A"); 
							   k--;
							   break;
					case 'B' : printf("\033[B");
							   k++; 
							   break;
					default  : break;
					}
				}	
			}		
	}
	if( c == ';')
	{
		gotoxy(60,5);
		NC_to_canon(old_terminal);
		if(getchar()=='\033')
		{
			old_terminal = canon_to_NC();
			continue;
		}
		//
		//commands of command mode
		//
		//
	}
	else
	{
		printf("\033[2J\033[H");
		NC_to_canon(old_terminal);
		break;
	}
}
	return 0;
}