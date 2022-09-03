// SPDX-License-Identifier: GPL-3.0-or-later

#include <rcnRC6502.h>

void setup(void)
{
  RC6502Pio.begin();
  // RC6502Pio.beginClassic();
}

void loop(void)
{
  RC6502Pio.run();
}
