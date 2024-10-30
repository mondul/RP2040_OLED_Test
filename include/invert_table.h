#ifndef INVERT_TABLE_H
#define INVERT_TABLE_H

#include <stdint.h>

uint8_t invert_table[][4] = {
    { 0, 0xF8, 1, 0x0F },
    { 2, 0xFF, 3, 0x01 },
    { 3, 0xE0, 4, 0x3F },
    { 5, 0xFC, 6, 0x07 },
    { 6, 0x80, 7, 0xFF },
};

#endif
