#include <stdlib.h>
#include "parameters.h"

bool resolutionChanged(void)
{
  static bool hasOld = false;
  static int oldLines, oldCols;
  bool returnValue;

  if (!hasOld) {
    hasOld = returnValue = true;
  } else {
    if (oldLines != LINES || oldCols != COLS)
      returnValue = true;
    else
     returnValue = false;
  }
  
  oldLines = LINES;
  oldCols = COLS;

  return returnValue;
}

bool paramsChanged(double baseAngle, double riseAngle, int amplitude)
{
  static bool hasOld = false;
  static double oldBaseAngle, oldRiseAngle;
  static int oldAmplitude;
  bool returnValue;

  if (!hasOld) {
    hasOld = returnValue = true;
  } else {
    if (oldBaseAngle != baseAngle || oldRiseAngle != riseAngle || oldAmplitude != amplitude)
      returnValue = true;
    else
      returnValue = false;
  }

  oldBaseAngle = baseAngle;
  oldRiseAngle = riseAngle;
  oldAmplitude = amplitude;

  return returnValue;
}

bool modeChanged(MODES mode)
{
  static bool hasOld = false;
  static MODES oldMode;
  bool returnValue;
  
  if (!hasOld) {
    hasOld = returnValue = true;
  } else {
    if (oldMode != mode)
      returnValue = true;
    else
      returnValue = false;
  }

  oldMode = mode;
  
  return returnValue;
}

void updParameters(double *baseAngle, double *riseAngle, int *amplitude, MODES mode)
{
  switch (mode) {
    case IDLE: 
      *baseAngle = 0.0;
      *riseAngle = 0.0;
      break;
    case STATIC: 
      /* static does nothing :) */ 
      break;
    case CONTINUOUS: 
      *baseAngle += CONT_INCR;
      break;
    case RANDOM: 
      *baseAngle += (double) ( (double) (rand() % 21) / (double) 1000) - 0.01;
      *riseAngle += (double) ( (double) (rand() % 21) / (double) 1000) - 0.01;
      break;
    default: break;
  }
}
