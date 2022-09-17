// SPDX-License-Identifier: GPL-3.0-or-later

#pragma GCC optimize("O2")

#include "RC6502Video.h"

#define PIN_VIDEO_D0 0   // of MCP23S17
#define PIN_VIDEO_D1 1   // of MCP23S17
#define PIN_VIDEO_D2 2   // of MCP23S17
#define PIN_VIDEO_D3 3   // of MCP23S17
#define PIN_VIDEO_D4 4   // of MCP23S17
#define PIN_VIDEO_D5 5   // of MCP23S17
#define PIN_VIDEO_D6 6   // of MCP23S17
#define PIN_VIDEO_nRDA 5 // of Arduino
#define PIN_VIDEO_DA 3   // of Arduino

void RC6502Video::begin(Adafruit_MCP23X17 *mcp)
{
  mcp_ = mcp;

  __beginMcp();
  __beginPin();
}

void RC6502Video::reset(void)
{
  __beginMcp();
  __beginPin();
}

void RC6502Video::run(void)
{
  digitalWrite(PIN_VIDEO_nRDA, HIGH);

  if (digitalRead(PIN_VIDEO_DA) == HIGH)
  {
    int c = mcp_->readGPIOA() & 0x7F;

    __putchar(c);

    digitalWrite(PIN_VIDEO_nRDA, LOW);
  }
}

void RC6502Video::__beginMcp(void)
{
  for (int pin = PIN_VIDEO_D0; pin <= PIN_VIDEO_D6; pin++)
    mcp_->pinMode(pin, INPUT);
}

void RC6502Video::__beginPin(void)
{
  pinMode(PIN_VIDEO_DA, INPUT);

  pinMode(PIN_VIDEO_nRDA, OUTPUT);
  digitalWrite(PIN_VIDEO_nRDA, HIGH);
}

inline void RC6502Video::__putchar(int c)
{
  if (c == '\r')
    ____println();
  else
    ____putchar(c);
}

inline void RC6502Video::____println(void)
{
  while (!Serial.println())
    ;
}

inline void RC6502Video::____putchar(int c)
{
  switch (c)
  {
  case 0x08:          /* 'BS' */
  case 0x09:          /* 'TAB' */
  case 0x12:          /* 'LF' */
  case 0x13:          /* 'VT' */
  case 0x20 ... 0x7E: /* 'space' to '~' */
    break;
  default:
    return;
  }

  while (!Serial.print((char)c))
    ;
}
