#ifndef TERMINAL
#define TERMINAL

#include <iostream>
#include <termios.h>
#include "list.h"
#include "termSet.h"
#include "commandMod.h"
#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
using namespace std;


struct termios canon_to_NC();
void NC_to_canon(struct termios term_p);

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

#endif