#ifndef LIST
#define LIST

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
//################################################################  DATA TYPES  ##################################################################
struct winsize w;
extern int rows, col;
extern DIR *cur_dir;
extern string path;
extern vector <vector<string> > directories;;
extern vector <string > path_vector;
extern int path_pos;
extern int upper, low;
extern int cursor;
//#########################################################  FUNCTION DECLARATION  ################################################################
vector<vector<string> > list_store(string path);
void list_display(int upper, int lower);
void list();
//#########################################################  FUNCTION DEFINITION  ################################################################
vector<vector<string> > list_store(string path)
{
	struct dirent* next_dir;
	cur_dir = opendir (path.c_str()); 
	if (cur_dir != NULL)
	{
		while ( (next_dir=readdir(cur_dir) ) )
		{
			struct stat file_info;
			string file_path = path + next_dir->d_name;
			stat(file_path.c_str(),&file_info);
			vector<string> fields;
			fields.push_back(next_dir->d_name); /////1
			fields.push_back(to_string(file_info.st_size)); ////2
			struct passwd *pwd = getpwuid(file_info.st_uid);
			if( pwd )
				fields.push_back(string(pwd->pw_name)); ////3
			else 
				fields.push_back("error");
			struct group *group_info = getgrgid(file_info.st_gid);
			if( group_info )
				fields.push_back(string(group_info->gr_name)); ////4
			else
				fields.push_back("error");
			fields.push_back(to_string(file_info.st_mode&0777)); /////5
			fields.push_back(string(ctime(&file_info.st_mtime))); ////6
			if(S_IFDIR & file_info.st_mode)
				fields.push_back("dir");
			else 
				fields.push_back("file");
			directories.push_back(fields);
		}
	    closedir(cur_dir);
	}
	else
		cout << "Directory Not Found!";
	return directories;
}
void list_display(int upper, int lower)
{
	printf("\033[2J\033[H");
	int sno = upper;
	while ( sno>=upper && sno <lower && sno<directories.size() )
	{
		cout << sno+1 << "." << "\t";
		cout << left << setw(50) << directories[sno][0];
		cout << left << setw(20) << directories[sno][1];
		cout << left << setw(20) << directories[sno][2]; 
		cout << left << setw(20) << directories[sno][3];
		cout << left << setw(20) << directories[sno][4];
		cout << left << setw(20) << directories[sno][5];
		sno++;
	}
}
void list()
{
	directories.clear();
	directories = list_store(path);
	upper = 0;
	low = rows;
	list_display(upper,low);
	cout << endl << endl << path << endl;
	gotoxy(0,0);
	cursor = 0;
}

#endif