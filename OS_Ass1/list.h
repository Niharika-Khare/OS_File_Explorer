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
extern vector <vector<string> > directories;
extern vector <string > path_vector;
extern int path_pos;
extern int upper, low;
extern int cursor;
//#########################################################  FUNCTION DECLARATION  ################################################################
string size_of_file(off_t size);
vector<vector<string> > list_store(string path);
void list_display(int upper, int lower);
void list();
//#########################################################  FUNCTION DEFINITION  ################################################################
string size_of_file(off_t size)
{
	long int KB = 1024;
	long int MB = 1024*1024;
	long int GB = 1024*1024*1024;
	if(size < KB )
		return to_string(size) + " B";
	else if( size < MB )
	{
		size = size/KB;
		return to_string(size) + " KB";
	}
	else if( size < GB )
	{
		size = size/MB;
		return to_string(size) + " MB";
	}
	else 
	{
		size = size/GB;
		return to_string(size) + " GB";
	}
}
string permission(mode_t mod)
{
	string perm;
	if( mod & S_IFDIR)  perm += 'd';
	else 			    perm += '-';
	if( mod & 0400)     perm += 'r';
	else                perm += '-';
	if( mod & 0200) 	perm += 'w';
	else				perm += '-';
	if( mod & 0100)		perm += 'x';
	else				perm += '-';
	if( mod & 0040)		perm += 'r';
	else				perm += '-';
	if( mod & 0020)		perm += 'w';
	else				perm += '-';
	if( mod & 0010)		perm += 'x';
	else				perm += '-';
	if( mod & 0004)		perm += 'r';
	else				perm += '-';
	if( mod & 0002)		perm += 'w';
	else				perm += '-';
	if( mod & 0001)		perm += 'x';
	else				perm += '-';
	return perm;
}
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
			fields.push_back(next_dir->d_name); 
			fields.push_back(size_of_file(file_info.st_size)); 
			struct passwd *pwd = getpwuid(file_info.st_uid);
			if( pwd )
				fields.push_back(string(pwd->pw_name)); 
			else 
				fields.push_back("error");
			struct group *group_info = getgrgid(file_info.st_gid);
			if( group_info )
				fields.push_back(string(group_info->gr_name)); 
			else
				fields.push_back("error");
			fields.push_back(permission(file_info.st_mode)); 
			fields.push_back(string(ctime(&file_info.st_mtime))); 
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
		cout << right << setw(2) << sno+1 <<left << setw(3) << ".";
		cout << left << setw(32) << directories[sno][0];
		cout << left << setw(10) << directories[sno][1];
		cout << left << setw(11) << directories[sno][2]; 
		cout << left << setw(11) << directories[sno][3];
		cout << left << setw(14) << directories[sno][4];
		cout << left << setw(12) << directories[sno][5];
		sno++;
	}
}
void list()
{
	directories.clear();
	directories = list_store(path);
	upper = 0;
	low = rows-1;
	list_display(upper,low);
	cout << endl << endl << path << endl;
	gotoxy(0,0);
	cursor = 0;
}

#endif