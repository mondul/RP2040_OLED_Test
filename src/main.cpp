/**
 * RP2040 OLED Test
 * Author: mondul
 */

// Default I2C pins for Raspberry Pi Pico
// SDA --> GPIO 4
// SCL --> GPIO 5

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Custom font
#include "Charcoal6pt8b.h"
// XOR table
#include "invert_table.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define MAX_BASE 11 // Tallest character height
#define setLine(LN) display.setCursor(0, (MAX_BASE * LN) + (2 * (LN - 1))) // One pixel bottom padding

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

uint8_t current_screen_selection = 1;

void showScreen() {
  display.clearDisplay();
  setLine(1);
  display.print("Show date & time");
  setLine(2);
  display.print("Show temperature");
  setLine(3);
  display.print("Invert colors");
  setLine(4);
  display.print("About...");
  setLine(5);
  display.print("Turn screen off");
  invertLine(current_screen_selection);
  display.display();
}

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3D for 128x64
  buf = display.getBuffer();
  display.setTextColor(WHITE);
  display.setFont(&Charcoal6pt8b);
  showScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BOOTSEL) {
    current_screen_selection++;
    if (current_screen_selection > 5) current_screen_selection = 1;
    showScreen();
    delay(250);
  }
}
