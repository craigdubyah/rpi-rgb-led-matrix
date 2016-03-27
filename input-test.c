/*
 * input-test.c
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
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{
WINDOW *menu_win;
int highlight = 3;
int choice = 0;
int c;

initscr();
clear();
noecho();

cbreak();
startx = (80 - WIDTH) / 2;
starty = (24 - HEIGHT) / 2;
cbreak();

menu_win = newwin(HEIGHT, WIDTH, starty, startx);
keypad(menu_win, TRUE);
mvprintw(0, 0, "Use arrow keys to go up and down. Press enter to select a choice");
refresh();

print_menu(menu_win, highlight);

while(1) 
{
	c = wgetch(menu_win);
	switch(c){
		case KEY_UP:{
		printf("UP pressed");
		//if(highlight == 1)
		//highlight = n_choices;
		//else
		//--highlight;
		break;
	}
		case KEY_DOWN:{
		printf("DOWN pressed");
		//if(highlight == n_choices)
		//highlight = 1;
		//else
		//++highlight;
		break;
	}
		case 10:{
		choice = highlight;
		break;
	}
		default:{
		mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);
		refresh();
		break;
	}
	}
	print_menu(menu_win, highlight);
	
	if(choice != 0)
	break;
}

mvprintw(23, 0, "you chose choice %d with choice string %s\n", choice, choices[choice -1]);
clrtoeol();
refresh();
endwin();
return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	
	for(i = 0; i < n_choices; ++i)
	{
		if(highlight == i + 1)
		{
			wattron(menu_win, A_REVERSE);
			mvprintw(&menu_win, y, x, "%s", &choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
		mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
