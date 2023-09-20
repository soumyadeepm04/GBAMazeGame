#include "gba.h"
#include "startScreen.h"
#include "gameScreen.h"
#include "main.h"
#include "gameScreen2.h"
#include "endScreen.h"
#include <stdio.h>

void displayScreen(int row, int col, int width, int height, const u16 *image) {
    // char *s;
    // int x = 0;
    // if (image == frameS2) {
    //     s = "LEVEL 1";
    //     x = 1;
    // }
    // else if (image == frameS1) {
    //     s = "LEVEL 2";
    //     x = 1;
    // }
    waitForVBlank();
    drawImageDMA(row, col, width, height, image);
    // if (x == 1) {
    //     drawString(2, 2, s, BLUE);
    // }
}

void displayEndScreen(void) {
    waitForVBlank();
    fillScreenDMA(BLACK);
    drawPartImageDMA(55, 70, 100, 50, endScreen);
}

// void displayGame(void) {
//     waitForVBlank();
//     drawImageDMA(0, 0, FRAMES1_WIDTH, FRAMES1_HEIGHT, frameS1);
// }

enum gba_state playGame(struct sprite cs, struct sprite os, u32 previousButtons, u32 currentButtons, int row_low, int row_high, int col_low, int col_high, const unsigned short frame[], enum gba_state state) {
    int counter = 0;
    int seconds = 0;
    char *s;
    if (frame == frameS1) {
        s = "LEVEL 2";
    }
    else {
        s = "LEVEL 1";
    }
    int initialCol = 2;
    int increment = 1;
    while (1) {
        // if (SCANLINECOUNTER > 160) {
        //     counter++;
        // }
        currentButtons = BUTTONS;
        os = cs;
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            return START;
        }
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
            if (state == PLAYMAP1) {
                return PLAYMAP2;
            }
            else {
                return END;
            }
        }
        if ((cs.orig_row >= row_low && cs.orig_row <= row_high) && (cs.orig_col <= col_high && cs.orig_col >= col_low)) {
            if (state == PLAYMAP1) {
                return PLAYMAP2;
            }
            else {
                return END;
            }
        }
        if (KEY_DOWN(BUTTON_UP, previousButtons) != 0 && KEY_DOWN(BUTTON_UP, currentButtons) == 0) {
            // if (frameS1[OFFSET(cs.orig_row - cs.rd, cs.orig_col, WIDTH)] == 0x7fff) {
            //     cs.orig_row -= cs.rd;
            // }
            int x = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 1; j <= cs.rd; j++) {
                    if (frame[OFFSET(cs.orig_row - j, cs.orig_col + i, WIDTH)] != 0x7fff) {
                        x = 0;
                    }
                }
                
            }
            if (x == 1) {
                cs.orig_row -= cs.rd;
            }
        }
        else if (KEY_DOWN(BUTTON_DOWN, previousButtons) != 0 && KEY_DOWN(BUTTON_DOWN, currentButtons) == 0) {
            // if (frameS1[OFFSET(cs.orig_row + 3 + cs.rd, cs.orig_col + 3, WIDTH)] == 0x7fff) {
            //     cs.orig_row += cs.rd;
            // }
            int x = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 1; j <= cs.rd; j++) {
                    if (frame[OFFSET(cs.orig_row + 2 + j, cs.orig_col + i, WIDTH)] != 0x7fff) {
                        x = 0;
                    }
                }
            }
            if (x == 1) {
                cs.orig_row += cs.rd;
            }
        }
        else if (KEY_DOWN(BUTTON_LEFT, previousButtons) != 0 && KEY_DOWN(BUTTON_LEFT, currentButtons) == 0) {
            // if (frameS1[OFFSET(cs.orig_row, cs.orig_col - cs.cd, WIDTH)] == 0x7fff) {
            //     cs.orig_col -= cs.cd;
            // }
            int x = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 1; j <= cs.cd; j++) {
                    if (frame[OFFSET(cs.orig_row + i, cs.orig_col - j, WIDTH)] != 0x7fff) {
                        x = 0;
                    }
                }
            }
            if (x == 1) {
                cs.orig_col -= cs.cd;
            }
        }
        else if (KEY_DOWN(BUTTON_RIGHT, previousButtons) != 0 && KEY_DOWN(BUTTON_RIGHT, currentButtons) == 0) {
            // if (frameS1[OFFSET(cs.orig_row, cs.orig_col + 3 + cs.cd, WIDTH)] == 0x7fff) {
            //     cs.orig_col += cs.cd;
            // }
            int x = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 1; j <= cs.cd; j++) {
                    if (frame[OFFSET(cs.orig_row + i, cs.orig_col + 2 + j, WIDTH)] != 0x7fff) {
                        x = 0;
                    }
                }
            }
            if (x == 1) {
                cs.orig_col += cs.cd;
            }
        }
        previousButtons = currentButtons;
        int y = 0;
        
        waitForVBlank();
        // if (SCANLINECOUNTER > 160) {
            counter++;
        // }
        char g[20];
        if (counter % 60 == 0) {
            counter = 0;
            seconds++;
            y = 1;
            
            sprintf(g, "%d", seconds);    
        }
        if (y == 1) {
            drawRectDMA(148, 200, 20, 10, WHITE);
            drawString(148, 200, g, BLUE);
        }
        
        if (counter % 50  == 0) {
            if (increment == -1) {
                drawRectDMA(148, initialCol, 80, 10, WHITE);
            }
            else {
                drawRectDMA(148, initialCol, 50, 10, WHITE);
            }
            drawString(148, initialCol, s, BLUE);
            if (initialCol == 80) {
                increment = -1;
            
            }
            if (initialCol == 2) {
                increment = 1;
            
            }
            initialCol += increment;
        }
        

        drawRectDMA(os.orig_row, os.orig_col, 3, 3, WHITE);
        drawRectDMA(cs.orig_row, cs.orig_col, 3, 3, BLACK);
        
    }
}