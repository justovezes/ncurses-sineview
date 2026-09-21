#ifndef DEFS_H
#define DEFS_H

/* some default values */
#define BUFFER_SIZE 128
#define BASE_ANGLE 0.0
#define RISE_ANGLE 0.0
#define RISE_ANGLE_INC 0.1
#define CONT_INCR 0.01
#define AMPLITUDE 0 /* aka max available */

#define UDELAY 5000

typedef enum {
  IDLE,
  STATIC,
  CONTINUOUS,
  RANDOM,
  NUM_MODES
} MODES;

#endif
