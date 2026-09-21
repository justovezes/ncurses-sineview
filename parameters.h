#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <ncurses.h>
#include "defs.h"

/* checks if certain conditions suffered change. */
bool resolutionChanged(void);
bool paramsChanged(double baseAngle, double riseAngle, int amplitude);
bool modeChanged(MODES mode);

/* update parameters based on current mode */
void updParameters(double *baseAngle, double *riseAngle, int *amplitude, MODES mode);

#endif // !PARAMETERS_H
