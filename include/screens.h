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
void back2ShowDateTime(void);
void goToSetDate(void);
void goToSetTime(void);
void goToShowTemp(void);
void goToAbout(void);

const screenItem back_2_home_item = {
  text: "< Back to home",
  action: back2Home,
};

const screenItem back_2_home_items[] = {
  back_2_home_item,
};

const screenItem back_2_show_datetime = {
  text: "< Back to show d&t",
  action: back2ShowDateTime,
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
    text: NULL, // Current date will be overwritten here
    action: goToSetDate,
  },
  {
    text: NULL, // Current time will be overwritten here
    action: goToSetTime,
  },
};

const screen show_datetime_screen = {
  length: 3,
  items: show_datetime_items,
  drawOver: drawOverShowDateTime,
};

// -----------------------------------------------------------------------------
// Set date screen

extern void drawOverSetDate(void);

const screenItem set_date_items[] = {
  back_2_show_datetime,
  {
    text: "Year:",
    action: NULL,
  },
  {
    text: "Month:",
    action: NULL,
  },
  {
    text: "Day:",
    action: NULL,
  },
  {
    text: "DoW:",
    action: NULL,
  },
};

const screen set_date_screen = {
  length: 5,
  items: set_date_items,
  drawOver: drawOverSetDate,
};

// -----------------------------------------------------------------------------
// Set time screen

extern void drawOverSetTime(void);

const screenItem set_time_items[] = {
  back_2_show_datetime,
  {
    text: "Hour:",
    action: NULL,
  },
  {
    text: "Min:",
    action: NULL,
  },
  {
    text: "Sec:",
    action: NULL,
  },
};

const screen set_time_screen = {
  length: 4,
  items: set_time_items,
  drawOver: drawOverSetTime,
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
