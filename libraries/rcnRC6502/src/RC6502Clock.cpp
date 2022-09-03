// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>

#include "rcnRC6502.h"

#define PIN_OC1A 9
#define PIN_OC0A_UNUSED 6
#define PIN_nRESET 8

void RC6502Clock::begin(void)
{
  pinMode(PIN_OC0A_UNUSED, INPUT);

  TCCR1B |= _BV(CS10) | _BV(WGM12);
  TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(WGM13));
  TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));

  OCR1AH = 0;
  OCR1AL = 7; // 1 MHz

  disable();
}

void RC6502Clock::enable(void)
{
  TCCR1A |= _BV(COM1A0);
  TCCR1A &= ~_BV(COM1A1);
}

void RC6502Clock::disable(void)
{
  TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));

  pinMode(PIN_nRESET, INPUT); // Hi-Z

  pinMode(PIN_OC1A, OUTPUT);
  digitalWrite(PIN_OC1A, LOW);
}

void RC6502Clock::reset(void)
{
  pinMode(PIN_nRESET, OUTPUT);
  digitalWrite(PIN_nRESET, LOW); // GND
  delay(15);                     // some delay ... (at least 6 clock cycles)
  pinMode(PIN_nRESET, INPUT);    // Hi-Z (the exteranl pull-up R2 already exits)
}
