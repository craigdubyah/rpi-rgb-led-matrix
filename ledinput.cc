// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>


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

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


static void DrawTarget(Canvas *canvas) {

	int ch;
	int xpos=15;
	int ypos = 15;
	canvas ->Fill(0,0,0);
	
	while(1)
	{
		
	canvas ->Fill(0,0,0);
		if(kbhit())
		{
			ch=getch();
			if(ch == KEY_UP)//move upward
			{
				x=0;
				y=-1;
				//printw("UP pressed \n");
			}
			if(ch == KEY_LEFT) //move left
			{
				x=-1;
				y=0;
				//printw("LEFT pressed \n");
			}
			if(ch == KEY_RIGHT) //move right
			{
				x=1;
				y=0;
				//printw("RIGHT pressed \n");
			}
			if(ch == KEY_DOWN) //move downward
			{
				x=0;
				y=1;
				//printw("DOWN pressed \n");
			}
			if(ch == 'q') //exit when q pressed
			{
				echo();
				exit(0);
			}
		}
		xpos = xpos + x;
		ypos =ypos + y;
		x=0;
		y=0;
		canvas->SetPixel(xpos, ypos, 0, 0, 255);
		usleep(1 * 1000);
	}
}
		

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * Let's create a simple animation. We use the canvas to draw
   * pixels. We wait between each step to have a slower animation.
   */
  canvas->Fill(0, 0, 255);

  int center_x = canvas->width() / 2;
  int center_y = canvas->height() / 2;
  float radius_max = canvas->width() / 2;
  float angle_step = 1.0 / 360;
  for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
    float dot_x = cos(a * 2 * M_PI) * r;
    float dot_y = sin(a * 2 * M_PI) * r;
    canvas->SetPixel(center_x + dot_x, center_y + dot_y,
                     255, 0, 0);
    usleep(1 * 1000);  // wait a little to slow down things.
  }
}

int main(int argc, char *argv[]) {
	
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	
  /*
   * Set up GPIO pins. This fails when not running as root.
   */
  GPIO io;
  if (!io.Init())
    return 1;
    
  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
  int rows = 16;    // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 2;    // Number of boards chained together.
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
  Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);

  //DrawOnCanvas(canvas);    // Using the canvas.
  DrawTarget(canvas);

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
