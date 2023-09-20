#include "gba.h"

void displayScreen(int row, int col, int width, int height, const u16 *image);
// void displayGame(void);
void displayEndScreen(void);
enum gba_state playGame(struct sprite cs, struct sprite os, u32 previousButtons, u32 currentButtons, int row_low, int row_high, int col_low, int col_high, const unsigned short frame[], enum gba_state state);