#include "colors.h"
#include <ncurses.h>

void color_setup(void)
{
  start_color();
  use_default_colors();

  init_pair(RED_BKG, COLOR_RED, COLOR_RED);
  init_pair(IDLE_COLOR, COLOR_WHITE, -1);
  init_pair(STATIC_COLOR, COLOR_WHITE, -1);
  init_pair(CONTINUOUS_COLOR, COLOR_GREEN, -1);
  init_pair(RANDOM_COLOR, COLOR_MAGENTA, -1);
}
