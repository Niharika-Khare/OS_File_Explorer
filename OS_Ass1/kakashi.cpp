#include <iostream>
#include <iomanip>
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

int rows, col;
DIR *cur_dir;
string path;
vector <vector<string> > directories;;
vector <string > path_vector;
int path_pos;
int upper, low;
int cursor;

int main ()
{
	struct termios old_terminal = canon_to_NC();
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row - 3;
    col = w.ws_col;
	path = "./";
	path_pos = 0;
	path_vector.push_back(path);
	path_pos++;
	while(1)
	{
		list();
		char c;
		while(1)
		{
			c = getchar();		
			if( c == ':' )
				break;	
			else if( c == 'q')
			{
				break;
			}
			else if( c == 'h' || c == 'H')
			{
				path = "./";
				path_vector.resize(path_pos+1);
				path_vector.push_back(path);
				path_pos++;
				list();
			}	
			else if( c == 127 )
			{
				path = path.substr(0,path.length()-1);
				int last_pos = path.find_last_of("/");
  				path =  path.substr(0,last_pos);
  				path = path + "/";
  				path_vector.push_back(path);
				path_pos++;
				list();
  			}
			else if( c == 10 && directories[upper + cursor][6] == "file") /// OPEN FILE
			{
				pid_t pid = fork();
				if (pid == 0)
    			{
    				string file = "xdg-open " + path + directories[upper + cursor][0];
        			int err_no = system( (file + " >> error.txt").c_str());
           			exit(0);
    			}
    			else if (pid > 0)
        			continue;
    			else
    			{
        			cout << "fork() failed!\n";
        			return 1;
    			}
			}
			else if( c == 10 && directories[upper + cursor][6] == "dir") /// ENTER INTO A DIRECTORY
			{
				string new_path = directories[upper + cursor][0];
				if( new_path == "..")
				{
					path = path.substr(0, path.length()-1);
					int last_pos = path.find_last_of("/");
  					path =  path.substr(0,last_pos);
  					path = path + "/";
				}
				else if( new_path == "." )
				{
					gotoxy(0,0);
				}
				else
				{
					path = path.append(new_path);
					path = path.append("/");
				}
				path_vector.resize(path_pos+1);
				path_vector.push_back(path);
				path_pos++;
				list();
			}
			else if( c == '\033')
			{
				if(getchar() == '[')
				{	
					c = getchar();
					if( c == 'D')
					{
						if(path_pos >0 )
						{
							path_pos--;
							path = path_vector[path_pos];
							list();
						}
					}
					else if ( c == 'C')
					{
						if(path_pos < path_vector.size()-1 )
						{
							path_pos++;
							path = path_vector[path_pos];
							list();
						}
					}
					else if( cursor == 0  )
					{
						if( c == 'B' )
						{
							cursor++;
							printf("\033[B");	
						}
						else if( c == 'A' && upper >0 )
						{
							upper--;
							low--;
							list_display(upper,low);
							cout << endl << endl << path << endl;	
							gotoxy(0,0);
						}
					}
					else if( cursor == rows-1 || cursor == directories.size()-1 )
					{
						if( c == 'A')
						{
							cursor--;
							printf("\033[A"); 
						}
						else if( c == 'B' && low < directories.size())
						{
							upper++;
							low++;
							list_display(upper, low);
							cout << endl << endl << path << endl;
							int list_length = (rows-1) > directories.size() ? directories.size() : (rows-1);
							gotoxy(list_length,0);
						}	
					}
					else if( cursor > 0 && cursor < rows-1 && cursor <directories.size()-1)	
					{
						switch(c)
						{	
						case 'A' : printf("\033[A"); 
								   cursor--;
								   break;
						case 'B' : printf("\033[B");
								   cursor++; 
								   break;
						default  : break;
						}
					}	
				}	
			}
		}
		char escape;
		if( c == ':')
			escape = enter_cmd_mod(escape,rows);
		else			
			break;
		if( escape == 'q' )
			break;	
	}
	printf("\033[2J\033[H");
	NC_to_canon(old_terminal);
	return 0;
}