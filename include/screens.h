#ifndef SCREENS_H
#define SCREENS_H

#include <stdint.h>

typedef struct
{
  const char *text;
  void (*action)(void);
} screenItem;

typedef struct
{
  const uint8_t length;
  const screenItem *items;
} screen;

// -----------------------------------------------------------------------------
// Home screen

extern void invertColors(void);
extern void turnScreenOff(void);

const screenItem home_items[] = {
  {
    text: "Show date & time",
    action: NULL
  },
  {
    text: "Show temperature",
    action: NULL
  },
  {
    text: "Invert colors",
    action: invertColors
  },
  {
    text: "About...",
    action: NULL
  },
  {
    text: "Turn screen off",
    action: turnScreenOff
  }
};

const screen home_screen = {
  length: 5,
  items: home_items
};

#endif
