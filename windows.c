#include <unistd.h>
#include <string.h>
#include <math.h>
#include "windows.h"
#include "colors.h"

static int sinToY(int lines, double sin);

void adjustTop(WINDOW **topWinBorder, WINDOW **contentsTop)
{
  if (!*topWinBorder) { // window creation.
    *topWinBorder = newwin(2, 2, 0, 0);
    *contentsTop = derwin(*topWinBorder, 1, 1, 1, 1);
  }
  
  wresize(*topWinBorder, 3, TOP_WIN_SIZE + 2);
  wresize(*contentsTop, 3 - 2, TOP_WIN_SIZE);

  mvwin(*topWinBorder, 0, 0);
  mvwin(*contentsTop, 1, 1);

  wborder(*topWinBorder, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(*topWinBorder);
}

void adjustMid(WINDOW **midWinBorder, WINDOW **contentsMid)
{
  if (!*midWinBorder) { // window creation.
    *midWinBorder = newwin(2, 2, 0, 0);
    *contentsMid = derwin(*midWinBorder, 1, 1, 1, 1);
  }

  wresize(*midWinBorder, LINES - (3 + 3), COLS);
  wresize(*contentsMid, LINES - (3 + 3) - (2), COLS-2);

  mvwin(*midWinBorder, 3, 0);
  mvwin(*contentsMid, 4, 1);

  wborder(*midWinBorder, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(*midWinBorder);
}

void adjustLow(WINDOW **lowWinBorder, WINDOW **contentsLow)
{
  if (!*lowWinBorder) { // window creation.
    *lowWinBorder = newwin(2, 2, 0, 0);
    *contentsLow = derwin(*lowWinBorder, 1, 1, 1, 1);
  }

  wresize(*lowWinBorder, 3, strlen(creditString) + 2);
  wresize(*contentsLow, 1, strlen(creditString));

  mvwin(*lowWinBorder, LINES - (3), COLS - (strlen(creditString) + 2)); // COLS tem index 0???????
  mvwin(*contentsLow, LINES - (2), COLS - (strlen(creditString) + 2) + 1);

  wborder(*lowWinBorder, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(*lowWinBorder);
}

void adjustMode(WINDOW **modeWin)
{
  // tossing out for now
  if (!*modeWin) { // window creation.
    *modeWin = newwin(1, 1, 0, 0);
  }

  wresize(*modeWin, 1, MODE_WIN_SIZE);
  mvwin(*modeWin, LINES - 3, 1);
  wrefresh(*modeWin);
}

void displayTop(WINDOW *contentsTop, double baseAngle, double riseAngle, int amplitude, bool triggerRefresh)
{
  char buffer[BUFFER_SIZE];
  int lines, cols;

  if (!(triggerRefresh))
    return;

  getmaxyx(contentsTop, lines, cols);

  snprintf(buffer, BUFFER_SIZE - 1, "baseAngle: %010.3f | riseAngle: %010.4f | amplitude: %.3d",
           baseAngle, riseAngle, amplitude);

  wclear(contentsTop);
  mvwaddstr(contentsTop, 0, 0, buffer);
  if (strlen(buffer) > cols)
    mvwaddstr(contentsTop, 0, cols - 3, "...");
  wrefresh(contentsTop);
}

void displayMid(WINDOW *contentsMid, double baseAngle, double riseAngle, int amplitude, MODES mode, bool triggerRefresh)
{
  double sinVal, vAngle;
  int y, oldY, lines, cols, remainingLines;
  
  if (!(triggerRefresh))
    return;

  if (mode + 2 == IDLE_COLOR)
    wattrset(contentsMid, IDLE_STYLE);
  else
    wattrset(contentsMid, DEFAULT_STYLE);

  wclear(contentsMid);
  getmaxyx(contentsMid, lines, cols);

  vAngle = baseAngle;
  remainingLines = lines - amplitude;
  oldY = sinToY(amplitude, sinVal);

  for (int x = 0; x < COLS; x++) {
    sinVal = sin(vAngle);
    y = sinToY(amplitude, sinVal) + (remainingLines / 2);

    if (y > oldY + 1) {
      for (int i = 0; i < (y - oldY); i++)
        if (x) mvwaddch(contentsMid, (oldY + i), x - 1, '|');
    } else if (y < oldY - 1) {
      for (int i = 0; i < (oldY - y); i++)
        if (x) mvwaddch(contentsMid, (oldY - i), x - 1, '|');
    }
    mvwaddch(contentsMid, y, x, '-');

    oldY = y;
    vAngle += riseAngle;
  }

  wrefresh(contentsMid);
}

void displayLow(WINDOW *contentsLow, bool triggerRefresh)
{
  if (!triggerRefresh)
    return;

  wclear(contentsLow);

  mvwaddstr(contentsLow, 0, 0, creditString);
  wrefresh(contentsLow);
}

void displayMode(WINDOW *modeWin, MODES mode, bool triggerRefresh)
{
  if (!(triggerRefresh))
    return;


  switch (mode) {
    case IDLE: wattrset(modeWin, IDLE_STYLE); break;
    case STATIC: wattrset(modeWin, STATIC_STYLE); break;
    case CONTINUOUS: wattrset(modeWin, CONTINUOUS_STYLE); break;
    case RANDOM: wattrset(modeWin, RANDOM_STYLE); break;
    default: break;
  }

  wclear(modeWin);
  mvwprintw(modeWin, 0, 0, "-- %s --", modes[mode]);
  wrefresh(modeWin);
}

static int sinToY(int lines, double sin)
{
  sin += 1.0;
  return (int) (sin / (2.0 / lines));
}

void blockUntilValid(void)
{
  if (LINES < MIN_LINES || COLS < MIN_COLS) {
      
    bkgd(ERR_STYLE);
    touchwin(stdscr);
    refresh();

    do {
      getch();
      usleep(UDELAY);
    } while (LINES < MIN_LINES || COLS < MIN_COLS);

    bkgd(DEFAULT_STYLE);
    clear();
    refresh();
  }
}
