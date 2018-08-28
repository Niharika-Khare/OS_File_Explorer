#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))

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

int main ()
{
	printf("\033[2J\033[H");
	printf("\t%-11s%-40s%-40s%-40s%-40s\n\n", "S.no", "File/Directory", "Size", "Permissions", "Last Modified");
	struct termios old_terminal = canon_to_NC();
	DIR *cur_dir;
	struct dirent *next_dir;
	cur_dir = opendir ("./");
	int sno = 0;
	if (cur_dir != NULL)
	{
		while (next_dir = readdir (cur_dir))
		{
			struct stat file_info;
			stat(next_dir->d_name,&file_info);
			printf("\t%2d%-9s", ++sno,".");
			printf("%-40s", next_dir->d_name);
			printf("%-40ld", file_info.st_size);
			//printf("%-40ld", file_info.st_mode);
			printf("%-40ld\n", file_info.st_mtime);
	    }
	    closedir(cur_dir);
	}
	else
		printf("Root Directory Not Found!");

	printf("\033[3;9H");
	char c;
	while(1)
	{
		c = getchar();		
		if( c ==';' || c == 'q' )
			break;		
		if( c == '\033')
			if(getchar() == '[')
			{	
				c = getchar();		
				switch(c)
				{

					case 'A' : printf("\033[A"); 
								break;
					case 'B' : printf("\033[B"); 
								break;
					default  :  break;
				}
			}		
	}
	if( c == ';')
	{
		NC_to_canon(old_terminal);
		gotoxy(3,60);
		while(1) {}
	}
	else
		printf("\033[2J\033[H");
	NC_to_canon(old_terminal);
	return 0;
}