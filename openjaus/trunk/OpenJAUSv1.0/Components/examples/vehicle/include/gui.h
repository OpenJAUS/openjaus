#ifndef GUI_H
#define GUI_H

#include <GL/glx.h>
#include <X11/Xlib.h>

typedef struct
{
	Display *display;
	Window window;
	GLXContext context;
	XSetWindowAttributes attr;
	int screen;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	unsigned int depth;	
}GlWindow;

void guiResizeWindow(unsigned int, unsigned int);
void guiUpdateWindow(GlWindow);
void guiDestroyWindow(GlWindow);
GlWindow guiCreateWindow(char* title, int width, int height);

#endif // GUI_H
