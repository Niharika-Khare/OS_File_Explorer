#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <termios.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <stack>
#include <cstddef>
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
using namespace std;
stack <struct dirent> dir_struct;
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
//#########################################################################################################################################################
//##########################################################################################################################################################
vector<vector<string> > list_store(DIR *cur_dir, const char * path, vector<vector<string> > directories)
{
	struct dirent* next_dir;
	cur_dir = opendir (path); 
	int sno = 0;
	if (cur_dir != NULL)
	{
		while ( (next_dir=readdir(cur_dir) ) )
		{
			struct stat file_info;
			stat(next_dir->d_name,&file_info);
			vector<string> fields;
			fields.push_back(next_dir->d_name);
			directories.push_back(fields);
			//directories[sno][1] = file_info.st_size;
			//directories[sno][2] = permission(file_info.st_mode&0777);
			sno++;
	    }
	    closedir(cur_dir);
	}
	else
		printf("Directory Not Found!");
	return directories;
}
void list_display( vector < vector <string> > directories, int upper, int lower)
{
	printf("\033[2J\033[H");
	int sno = upper;
	while ( sno>=upper && sno <lower && sno<directories.size() )
	{
		cout << sno+1 << "." << "\t";
		cout << directories[sno][0] << right << setw(30) << "\n" ;
		//cout << directories[sno][1] << endl;
		sno++;
	}
}
//#############################################################################################################################################################
//##############################################################################################################################################################
int main ()
{
	while(1)
	{
		struct winsize w;
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    	int rows = w.ws_row;
    	int col = w.ws_col;
		struct termios old_terminal = canon_to_NC();
		DIR *cur_dir;
		string path = "..";
		vector < vector <string> > directories;
		directories = list_store(cur_dir, (path+'/').c_str(), directories);
		int upper = 0, low = 20;
		list_display(directories,upper,low);
		gotoxy(0,0);
		int k = 0;
		char c;
		while(1)
		{
			c = getchar();		
			if( c ==':' || c == 'q' )
				break;		
			else if( c == 10 )
			{
				string new_path = directories[upper + k][0];
				if( new_path == "..")
				{
					int last_pos = path.find_last_of("/");
  					path =  path.substr(0,last_pos);
				}
				else if( new_path == "." )
				{
					gotoxy(0,0);
				}
				else
				{
					path = path.append("/");
					path = path.append(new_path);
					path = path.append("\0");
				}
				directories.clear();
				directories = list_store(cur_dir, path.c_str(), directories);
				upper = 0;
				low = 20;
				list_display(directories,upper,low);
				cout << endl << endl << path << endl;
				gotoxy(0,0);
				k = 0;
			}
			else if( c == '\033')
			{
				if(getchar() == '[')
				{	
					c = getchar();
					if( k == 0  )
					{
						if( c == 'B' )
						{
							k++;
							printf("\033[B");	
						}
						else if( c == 'A' && upper >0 )
						{
							upper--;
							low--;
							list_display(directories, upper,low);	
							gotoxy(0,0);
						}
					}
					else if( k == 19 || k == directories.size()-1 )
					{
						if( c == 'A')
						{
							k--;
							printf("\033[A"); 
						}
						else if( c == 'B' && low < directories.size())
						{
							upper++;
							low++;
							list_display(directories, upper, low);
							int list_length = 20 > directories.size() ? directories.size() : 20;
							gotoxy(list_length,0);
						}	
					}
					else if( k>0 && k<19 && k<directories.size()-1)	
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
		}
		if( c == ':')
		{
			//gotoxy(0,70);
			cout << "zdf";
			NC_to_canon(old_terminal);
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