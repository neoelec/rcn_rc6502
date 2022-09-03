// SPDX-License-Identifier: GPL-3.0-or-later

#pragma GCC optimize("O2")

#include "rcnRC6502.h"

#define PIN_KBD_D0 8  // of MCP23S17
#define PIN_KBD_D1 9  // of MCP23S17
#define PIN_KBD_D2 10 // of MCP23S17
#define PIN_KBD_D3 11 // of MCP23S17
#define PIN_KBD_D4 12 // of MCP23S17
#define PIN_KBD_D5 13 // of MCP23S17
#define PIN_KBD_D6 14 // of MCP23S17
#define PIN_KBD_DA 15 // of MCP23S17
#define PIN_KBD_STR 4 // of Arduino

void RC6502Kbd::begin(Adafruit_MCP23X17 *mcp)
{
  mcp_ = mcp;

  interrupt_ = false;
  state_ = &st_idle_;
  serial_buf_.clear();

  __beginMcp();
  __beginPin();
}

void RC6502Kbd::run(void)
{
  state_->handle(*this);
}

void RC6502Kbd::setInterrupt(void)
{
  interrupt_ = true;
}

void RC6502Kbd::pushToBuffer(int c)
{
  c = toupper(c);

  if (c >= 0x80) // ignore ASCII Extended Characters
    return;

  serial_buf_.push(c);
}

bool RC6502Kbd::isBufferFull(void)
{
  return serial_buf_.isFull();
}

int RC6502Kbd::popFromBuffer(void)
{
  int c;

  serial_buf_.pop(c);

  return c;
}

bool RC6502Kbd::isBufferEmpty(void)
{
  return serial_buf_.isEmpty();
}

void RC6502Kbd::__beginMcp(void)
{
  for (int pin = PIN_KBD_D0; pin <= PIN_KBD_DA; pin++)
    mcp_->pinMode(pin, OUTPUT);

  mcp_->writeGPIOB(0x0);
}

void RC6502Kbd::__beginPin(void)
{
  pinMode(PIN_KBD_CLR, INPUT);

  pinMode(PIN_KBD_STR, OUTPUT);
  digitalWrite(PIN_KBD_STR, LOW);
}

// states

void __RC6502KbdStIdle::handle(RC6502Kbd &kbd)
{
  if (kbd.isBufferEmpty())
    return;

  kbd.state_ = &kbd.st_write_;
}

void __RC6502KbdStPollClear::handle(RC6502Kbd &kbd)
{
  if (digitalRead(PIN_KBD_CLR) != LOW)
    return;

  kbd.state_ = &kbd.st_idle_;
}

void __RC6502KbdStWrite::handle(RC6502Kbd &kbd)
{
  int c = kbd.popFromBuffer();
  Adafruit_MCP23X17 *mcp = kbd.mcp_;

  mcp->writeGPIOB(c | 0x80);
  digitalWrite(PIN_KBD_STR, HIGH);

  kbd.state_ = &kbd.st_wait_int_;
}

void __RC6502KbdStWaitInt::handle(RC6502Kbd &kbd)
{
  if (!kbd.interrupt_)
    return;

  digitalWrite(PIN_KBD_STR, LOW);

  kbd.interrupt_ = false;
  kbd.state_ = &kbd.st_poll_clear_;
}
