#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gba.h"
#include "helper.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"
#include "startScreen.h"
#include "gameScreen.h"
#include "gameScreen2.h"
/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.


int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  struct sprite cs, os;
  
  cs.orig_row = 115;
  cs.orig_col = 108;
  cs.rd = 2;
  cs.cd = 2;
  
  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    os = cs;
    
    // for (int i = 0; i < 10; i++) {
    //   justReleasedButton[i] = KEY_DOWN(1 << i, BUTTONS) == 0 && justReleasedButton[i];
    //   buttonWasDown[i] = KEY_DOWN(1 << i, BUTTONS) != 0;
    // }

    switch (state) {
      case START:
        displayScreen(0, 0, PIXILFRAME0_WIDTH, PIXILFRAME0_HEIGHT, pixilframe0);
        // state = ?
        // if (KEY_JUST_PRESSED(BUTTON_SELECT, BUTTONS, buttonWasDown[2])) {
        //   state = PLAY;
        // }
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          displayScreen(0, 0, FRAMES2_WIDTH, FRAMES2_HEIGHT, frameS2);
          state = PLAYMAP1;
        }
        break;
      case PLAYMAP1:
        cs.orig_row = 93;
        cs.orig_col = 46;
        state = playGame(cs, os, previousButtons, currentButtons, 47, 54, 146, 146, frameS2, state);
        break;
      case PLAYMAP2:
        // drawRectDMA(0, 0, 10, 10, GREEN);
        // state = ?
        cs.orig_row = 115;
        cs.orig_col = 108;
        displayScreen(0, 0, FRAMES1_WIDTH, FRAMES1_HEIGHT, frameS1);
        state = playGame(cs, os, previousButtons, currentButtons, 11, 11, 93, 100, frameS1, state);
        if (state == END) {
          displayEndScreen();
        }
        break;
      case END:
        // state = ?
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          displayScreen(0, 0, PIXILFRAME0_WIDTH, PIXILFRAME0_HEIGHT, pixilframe0);
          state = START;
        }
        break;
    }
    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
