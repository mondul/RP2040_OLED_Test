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

// Variables
extern uint8_t prev_screen_selection, current_screen_selection;
extern const screen *current_screen;

void back2Home(void);
void goToAbout(void);

const screenItem back_2_home_item = {
  text: "< Back to home",
  action: back2Home,
};

// -----------------------------------------------------------------------------
// About screen

extern void drawOverAbout(void);

const screenItem about_items[] = {
  back_2_home_item,
};

const screen about_screen = {
  length: 1,
  items: about_items,
  drawOver: drawOverAbout,
};

// -----------------------------------------------------------------------------
// Home screen

extern void invertColors(void);
extern void turnScreenOff(void);

const screenItem home_items[] = {
  {
    text: "Show date & time",
    action: NULL,
  },
  {
    text: "Show temperature",
    action: NULL,
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

#endif
