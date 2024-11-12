/**
 * RP2040 OLED Test
 * Author: mondul
 */

// Default I2C pins for Raspberry Pi Pico
// SDA --> GPIO 4
// SCL --> GPIO 5

#include <Arduino.h>
#include <pio_encoder.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <hardware/rtc.h>
// Custom font
#include "Charcoal6pt8b.h"
// XOR table
#include "invert_table.h"
// Screens
#include "screens.h"

// HW-040 encoder button
#define PIN_BTN 6u

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define MAX_BASE 11 // Tallest character height
#define setLine(LN) display.setCursor(0, (MAX_BASE * (LN)) + (2 * ((LN) - 1))) // One pixel bottom padding

PioEncoder encoder(2); // encoder is connected to GPIO2 and GPIO3

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Display buffer
uint8_t *buf;

void invertLine(uint8_t line) {
  line--;
  uint16_t pos;
  for (uint8_t i = 0; i < 4; i += 2) {
    pos = invert_table[line][i] * SCREEN_WIDTH;
    for (uint8_t j = 0; j < SCREEN_WIDTH; j++) buf[pos++] ^= invert_table[line][i + 1];
  }
}

bool is_inverted = false;

void showScreen() {
  display.clearDisplay();
  display.invertDisplay(is_inverted);
  for (uint8_t i = 0; i < current_screen->length; i++) {
    setLine(1 + i);
    display.print(current_screen->items[i].text);
  }
  invertLine(current_screen_selection);
  if (current_screen->drawOver)
    current_screen->drawOver();
  display.display();
}

// Functions in _screens_ that use _display_

void invertColors() {
  is_inverted = !is_inverted;
  prev_screen_selection = 0; // Force screen redraw
}

// Start on Friday 5th of June 2020 15:45:00
datetime_t t = {
  .year  = 2020,
  .month = 06,
  .day   = 05,
  .dotw  = 5, // 0 is Sunday, so 5 is Friday
  .hour  = 15,
  .min   = 45,
  .sec   = 00
};

void drawOverShowDateTime() {
  rtc_get_datetime(&t);
  setLine(4);
  display.printf("%d-%02d-%02d %02d:%02d:%02d", t.year, t.month, t.day, t.hour, t.min, t.sec);
}

void drawOverShowTemp() {
  setLine(3);
  display.printf("IC temp: %2.1f\xB0""C", analogReadTemp());
}

void drawOverAbout() {
  setLine(3);
  display.print("RP2040 OLED Test\ngithub.com/mondul");
}

void turnScreenOff() {
  display.clearDisplay();
  display.invertDisplay(0);
  display.display();
}

// Program entry point
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  // Start PIO encoder
  encoder.begin();
  // Start RTC
  rtc_init();
  rtc_set_datetime(&t);
  // Start display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3D for 128x64
  buf = display.getBuffer();
  display.setTextColor(WHITE);
  display.setFont(&Charcoal6pt8b);
  // Load home screen
  back2Home();
}

int prev_count = 0, current_count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  // First check button press
  if (!digitalRead(PIN_BTN)) {
    if (current_screen->items[current_screen_selection - 1].action)
      current_screen->items[current_screen_selection - 1].action();
    delay(250); // Discard bounces
    return;
  }
  // Now check selection
  current_count = encoder.getCount();
  // Give some encoder counts before changing selection count
  if (current_count > prev_count + 6) {
    prev_count = current_count;
    current_screen_selection++;
    if (current_screen_selection > current_screen->length)
      current_screen_selection = 1;
  }
  else if (current_count < prev_count - 6) {
    prev_count = current_count;
    current_screen_selection--;
    if (current_screen_selection < 1)
      current_screen_selection = current_screen->length;
  }

  if (prev_screen_selection != current_screen_selection) {
    prev_screen_selection = current_screen_selection;
    showScreen();
  }
}
