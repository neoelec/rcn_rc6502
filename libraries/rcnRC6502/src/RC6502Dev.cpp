// SPDX-License-Identifier: GPL-3.0-or-later

#include "rcnRC6502.h"

#define PIN_MCP23S17_nSS 10
#define PIN_SD_nSS 7

static RC6502Kbd *kbd; // only for interrupt handler;

void RC6502Dev::begin(void)
{
  beginNoSd();
  __beginSd();
}

void RC6502Dev::beginNoSd(void)
{
  __beginPin();
  __beginTty();
  __beginMcp();
  __beginKbd();

  clock_.begin();
  video_.begin(&mcp_);
}

RC6502Clock *RC6502Dev::getClock(void)
{
  return &clock_;
}

RC6502Kbd *RC6502Dev::getKbd(void)
{
  return &kbd_;
}

Adafruit_MCP23X17 *RC6502Dev::getMcp(void)
{
  return &mcp_;
}

RC6502Sd *RC6502Dev::getSd(void)
{
  return &sd_;
}

RC6502Video *RC6502Dev::getVideo(void)
{
  return &video_;
}

static void ISR_RC6502KbdSetInterrupt(void)
{
  kbd->setInterrupt();
}

void RC6502Dev::__beginKbd(void)
{
  kbd_.begin(&mcp_);

  kbd = &kbd_;

  attachInterrupt(digitalPinToInterrupt(PIN_KBD_CLR), ISR_RC6502KbdSetInterrupt, HIGH);
}

void RC6502Dev::__beginMcp(void)
{
  mcp_.begin_SPI(PIN_MCP23S17_nSS);

  for (int pin = 0; pin < 16; pin++)
    mcp_.pinMode(pin, INPUT_PULLUP);
}

void RC6502Dev::__beginPin(void)
{
  pinMode(PIN_MCP23S17_nSS, OUTPUT);
  digitalWrite(PIN_MCP23S17_nSS, HIGH);
  pinMode(PIN_SD_nSS, OUTPUT);
  digitalWrite(PIN_SD_nSS, HIGH);
}

void RC6502Dev::__beginSd(void)
{
  sd_.begin(PIN_SD_nSS);
  Serial.println();
}

void RC6502Dev::__beginTty(void)
{
  Serial.begin(115200);

  Serial.print(F("\033[2J")); // clear screen
  Serial.println(F("RC6502 Apple 1 Replica - Raccoon's Mod"));
  Serial.println();
}
