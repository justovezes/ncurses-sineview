#ifndef WINDOWS_H
#define WINDOWS_H

#include <ncurses.h>
#include "defs.h"

#define MIN_LINES 9
#define MIN_COLS 65

/* magic number moment?????? */
#define TOP_WIN_SIZE 62
#define MODE_WIN_SIZE 20

static char *creditString = "Ver: 0.2 | Made by JustoVezes";
static char *modes[] = {"IDLE", "STATIC", "CONTINUOUS", "RANDOM"};

/* adjust window's border and contents position and size,
 * if first arg is NULL, creates windows.                */
void adjustTop(WINDOW **topWinBorder, WINDOW **contentsTop);
void adjustMid(WINDOW **midWinBorder, WINDOW **contentsMid);
void adjustLow(WINDOW **lowWinBorder, WINDOW **contentsLow);
void adjustMode(WINDOW **modeWin);

/* displays content of window */
void displayTop(WINDOW *contentsTop, double baseAngle, double riseAngle, int amplitude, bool triggerRefresh);
void displayMid(WINDOW *contentsMid, double baseAngle, double riseAngle, int amplitude, MODES mode, bool triggerRefresh);
void displayLow(WINDOW *contentsLow, bool triggerRefresh);
void displayMode(WINDOW *modeWin, MODES mode, bool triggerRefresh); 

/* covers screen in red until a valid resolution is met */
void blockUntilValid(void);

#endif // !WINDOWS_H
