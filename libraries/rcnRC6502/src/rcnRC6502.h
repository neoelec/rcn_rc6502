#ifndef __RCNRC6502_H__
#define __RCNRC6502_H__

#ifndef ARDUINO_AVR_NANO
#error "This sketch is only for Arduion NANO"
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif

#include "RC6502Clock.h"
#include "RC6502Dev.h"
#include "RC6502Kbd.h"
#include "RC6502Menu.h"
#include "RC6502Pio.h"
#include "RC6502Pgm.h"
#include "RC6502Sd.h"
#include "RC6502Video.h"

#endif // __RCNRC6502_H__
