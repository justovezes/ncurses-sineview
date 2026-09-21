#include <unistd.h>
#include "windows.h"
#include "parameters.h"
#include "colors.h"

int main(void)
{
  WINDOW *topWinBorder = NULL, *contentsTop,
         *midWinBorder = NULL, *contentsMid,
         *lowWinBorder = NULL, *contentsLow,
         *modeWin = NULL;
  double baseAngle,
         riseAngle;
  int amplitude,
      ch;
  MODES mode;
  bool triggerRefresh, stickyAmplitude,
       localRefresh, localModeRefresh;

  initscr();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);
  color_setup();

  // DEFAULT VALUES
  baseAngle = BASE_ANGLE;
  riseAngle = RISE_ANGLE;
  mode = IDLE;
  amplitude = 0;

  while (true) {
      ch = getch();
      
      if (resolutionChanged()) { // runs on first execution.
        clear();
        refresh();

        blockUntilValid();

        if (!amplitude || amplitude >= LINES - 8)
          stickyAmplitude = true;

        if (stickyAmplitude)
          amplitude = LINES - 8;

        adjustTop(&topWinBorder, &contentsTop);
        adjustMid(&midWinBorder, &contentsMid);
        adjustLow(&lowWinBorder, &contentsLow);
        adjustMode(&modeWin);

        triggerRefresh = true;
      }

      updParameters(&baseAngle, &riseAngle, &amplitude, mode);

      localRefresh = paramsChanged(baseAngle, riseAngle, amplitude);
      localModeRefresh = modeChanged(mode);

      displayTop(contentsTop, baseAngle, riseAngle, amplitude, (triggerRefresh | localRefresh));
      displayMid(contentsMid, baseAngle, riseAngle, amplitude, mode, (triggerRefresh | localRefresh | localModeRefresh));
      displayLow(contentsLow, triggerRefresh);
      displayMode(modeWin, mode, (triggerRefresh | localModeRefresh));

      switch (ch) {
          case '\t':      mode = (mode + 1) % NUM_MODES;
                          break;
          case KEY_BTAB:  mode = (NUM_MODES + mode - 1) % NUM_MODES;
                          break;
          case KEY_LEFT:  riseAngle -= RISE_ANGLE_INC;
                          break;
          case KEY_RIGHT: riseAngle += RISE_ANGLE_INC;
                          break;
          case KEY_DOWN:  if (!(amplitude <= 1)) (amplitude--, stickyAmplitude = false);
                          stickyAmplitude = false;
                          break;
          case KEY_UP:    if (!(amplitude >= (LINES - 8))) amplitude++;
                          if (amplitude >= (LINES - 8))
                            stickyAmplitude = true;
                          break;

          case 'p':      endwin(); 
                         return 0;
          default:       break;   
      }

      triggerRefresh = false;
      usleep(UDELAY);
  }

  endwin();
}
