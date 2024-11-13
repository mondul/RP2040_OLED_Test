#ifndef SCREENS_H
#define SCREENS_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
  const char *text;
  void (*action)(void);
} screenItem;

typedef struct
{
  const uint8_t length;
  const screenItem *items;
  void (*drawOver)(void);
} screen;

// -----------------------------------------------------------------------------
// Variables and constants

extern volatile uint8_t prev_screen_selection;
extern uint8_t current_screen_selection;
extern const screen *current_screen;

void back2Home(void);
void goToShowDateTime(void);
void goToShowTemp(void);
void goToAbout(void);

const screenItem back_2_home_item = {
  text: "< Back to home",
  action: back2Home,
};

const screenItem back_2_home_items[] = {
  back_2_home_item,
};

// -----------------------------------------------------------------------------
// Home screen

extern void invertColors(void);
extern void turnScreenOff(void);

const screenItem home_items[] = {
  {
    text: "Show date & time",
    action: goToShowDateTime,
  },
  {
    text: "Show temperature",
    action: goToShowTemp,
  },
  {
    text: "Invert colors",
    action: invertColors,
  },
  {
    text: "About...",
    action: goToAbout,
  },
  {
    text: "Turn screen off",
    action: turnScreenOff,
  }
};

const screen home_screen = {
  length: 5,
  items: home_items,
  drawOver: NULL,
};

// -----------------------------------------------------------------------------
// Show date & time screen

extern void drawOverShowDateTime(void);

const screenItem show_datetime_items[] = {
  back_2_home_item,
  {
    text: "Adjust date & time",
    action: NULL,
  },
};

const screen show_datetime_screen = {
  length: 2,
  items: show_datetime_items,
  drawOver: drawOverShowDateTime,
};

// -----------------------------------------------------------------------------
// Show temperature screen

extern void drawOverShowTemp(void);

const screen show_temp_screen = {
  length: 1,
  items: back_2_home_items,
  drawOver: drawOverShowTemp,
};

// -----------------------------------------------------------------------------
// About screen

extern void drawOverAbout(void);

const screen about_screen = {
  length: 1,
  items: back_2_home_items,
  drawOver: drawOverAbout,
};

#endif
