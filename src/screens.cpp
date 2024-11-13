/**
 * Funcions for screens
 */

#include <Arduino.h>
#include <hardware/rtc.h>
#include "screens.h"

volatile uint8_t prev_screen_selection;
uint8_t current_screen_selection, home_screen_selection = 1, datetime_screen_selection;
const screen *current_screen;

struct repeating_timer timer;

// Current datetime structure declared in main
extern datetime_t t;

void back2Home() {
  cancel_repeating_timer(&timer);
  digitalWrite(PIN_LED, false);
  prev_screen_selection = 0;
  current_screen_selection = home_screen_selection;
  current_screen = &home_screen;
}

static bool forceRedraw(__unused struct repeating_timer *t) {
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

void back2ShowDateTime() {
  add_repeating_timer_ms(-1000, forceRedraw, NULL, &timer);
  prev_screen_selection = 0;
  current_screen_selection = datetime_screen_selection;
  current_screen = &show_datetime_screen;
}

void goToSetDate() {
  cancel_repeating_timer(&timer);
  datetime_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &set_date_screen;
  rtc_get_datetime(&t);
}

void goToSetTime() {
  cancel_repeating_timer(&timer);
  datetime_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &set_time_screen;
  rtc_get_datetime(&t);
}

void goToShowTemp() {
  add_repeating_timer_ms(-1000, forceRedraw, NULL, &timer);
  home_screen_selection = current_screen_selection;
  prev_screen_selection = 0;
  current_screen_selection = 1;
  current_screen = &show_temp_screen;
}

// Blink when on About... screen
volatile bool is_on = false;
static bool blink(__unused struct repeating_timer *t) {
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
