#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

#define RED_BKG 1
#define IDLE_COLOR 2
#define STATIC_COLOR 3
#define CONTINUOUS_COLOR 4
#define RANDOM_COLOR 5

//                    COLOR STYLES                       //
//-------------------------------------------------------//

#define ERR_STYLE (COLOR_PAIR(RED_BKG))
#define DEFAULT_STYLE (A_NORMAL)

#define IDLE_STYLE (COLOR_PAIR(IDLE_COLOR) | A_DIM)
#define STATIC_STYLE (COLOR_PAIR(STATIC_COLOR))
#define CONTINUOUS_STYLE (COLOR_PAIR(CONTINUOUS_COLOR))
#define RANDOM_STYLE (COLOR_PAIR(RANDOM_COLOR) | A_BLINK)

void color_setup(void);

#endif
