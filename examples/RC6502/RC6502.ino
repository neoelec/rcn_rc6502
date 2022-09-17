// SPDX-License-Identifier: GPL-3.0-or-later

#include <rcnRC6502.h>

#define PIN_PIO_MODE A7

static bool isClassicMode(void)
{
  return analogRead(PIN_PIO_MODE) <= 512;
}

void setup(void)
{
  if (isClassicMode())
    RC6502Pio.beginClassic();
  else
    RC6502Pio.begin();
}

void loop(void)
{
  RC6502Pio.run();
}
