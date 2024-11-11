/**
 * Funcions for screens
 */

#include "screens.h"

uint8_t prev_screen_selection, current_screen_selection, home_screen_selection = 1;
const screen *current_screen;

void back2Home() {
  prev_screen_selection = 0;
  current_screen_selection = home_screen_selection;
  current_screen = &home_screen;
}

void goToAbout() {
  home_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &about_screen;
}
