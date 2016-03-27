/*
 * getchtest.c
 * 
 * Copyright 2016 Unknown <craig@localhost>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

int kbhit(void)
{
	int ch = getch();
	if (ch != ERR)
	{
		ungetch(ch);
		return 1;
	}
	else
	{
		return 0;
	}
}
/*

int main()
{
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	while (true) {
		if (getch() == 'g') {
			printw("You pressed G\n");
			}
			napms(500);
			printw("Running\n");
			}
}

*/

int main()
{
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	int i=0;
	int j=0;
	int x=0;
	int y=0;
	int ch;
	while(1)
	{
		if(kbhit())
		{
			//printw("Running\n");
			//addch(getch());
			//printw("\n");
			ch=getch();
			if(ch == KEY_UP)//move upward
			{
				x=0;
				y=-1;
				printw("UP pressed \n");
			}
			if(ch == KEY_LEFT) //move left
			{
				x=-1;
				y=0;
				printw("LEFT pressed \n");
			}
			if(ch == KEY_RIGHT) //move right
			{
				x=1;
				y=0;
				printw("RIGHT pressed \n");
			}
			if(ch == KEY_DOWN) //move downward
			{
				x=0;
				y=1;
				printw("DOWN pressed \n");
			}
			if(ch == 'q') //exit when q pressed
			{
				echo();
				exit(0);
			}
		}
			i=i+x;
			j=j+y;
			x=0;
			y=0;
			
	}

}
