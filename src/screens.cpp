/**
 * Funcions for screens
 */

#include <Arduino.h>
#include "pico/stdlib.h"
#include "screens.h"

uint8_t prev_screen_selection, current_screen_selection, home_screen_selection = 1;
const screen *current_screen;

struct repeating_timer timer;

void back2Home() {
  cancel_repeating_timer(&timer);
  digitalWrite(PIN_LED, false);
  prev_screen_selection = 0;
  current_screen_selection = home_screen_selection;
  current_screen = &home_screen;
}

bool forceRedraw(__unused struct repeating_timer *t) {
  prev_screen_selection = 0;
  return true;
}

void goToShowDateTime() {
  add_repeating_timer_ms(-1000, forceRedraw, NULL, &timer);
  home_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &show_datetime_screen;
}

void goToShowTemp() {
  add_repeating_timer_ms(-1000, forceRedraw, NULL, &timer);
  home_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &show_temp_screen;
}

// Blink when on About... screen
bool is_on = false;
bool blink(__unused struct repeating_timer *t) {
  digitalWrite(PIN_LED, is_on);
  is_on = !is_on;
  return true;
}

void goToAbout() {
  add_repeating_timer_ms(-500, blink, NULL, &timer);
  home_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &about_screen;
}
