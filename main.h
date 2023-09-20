#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs
struct sprite {
    int orig_row;
    int orig_col;
    int rd;
    int cd;
    unsigned short color;
};

enum gba_state {
  START,
  PLAYMAP1,
  PLAYMAP2,
  END
};


/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

#endif