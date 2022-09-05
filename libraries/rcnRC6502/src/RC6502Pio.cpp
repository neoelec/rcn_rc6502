// SPDX-License-Identifier: GPL-3.0-or-later

#include "rcnRC6502.h"

#define KEY_CODE_RS 0x12 // Ctrl+R

RC6502PioClass RC6502Pio;

void RC6502PioClass::begin(void)
{
  dev_.begin();
  __beginCommon();
  RC6502Menu.begin(dev_);
  state_ = &st_keyboard_;

  Serial.println(F("  - Ctrl+R - Racccoon's Menu"));
  Serial.println();
}

void RC6502PioClass::beginClassic(void)
{
  dev_.beginNoSd();
  __beginCommon();
  state_ = &st_classic_;
}

void RC6502PioClass::run(void)
{
  state_->handle(*this);
}

void RC6502PioClass::__beginCommon(void)
{
  clk_src_ = dev_.getClock();
  kbd_ = dev_.getKbd();
  video_ = dev_.getVideo();

  clk_src_->enable();
  clk_src_->reset();
}

// states

void __RC6002StateClassic::handle(RC6502PioClass &pio)
{
  RC6502Kbd *kbd = pio.kbd_;
  RC6502Video *video = pio.video_;

  while (Serial.available() && !kbd->isBufferFull())
    kbd->pushToBuffer(Serial.read());

  kbd->run();
  video->run();
}

void __RC6002StateKbd::handle(RC6502PioClass &pio)
{
  RC6502Kbd *kbd = pio.kbd_;
  RC6502Video *video = pio.video_;

  while (Serial.available() && !kbd->isBufferFull())
  {
    int c = Serial.read();

    if (c == KEY_CODE_RS)
    {
      pio.state_ = &pio.st_menu_enter_;
      break;
    }

    kbd->pushToBuffer(c);
  }

  kbd->run();
  video->run();
}

void __RC6002StateMenuEnter::handle(RC6502PioClass &pio)
{
  RC6502Menu.enter();
  __flushTtyRx();
  pio.state_ = &pio.st_menu_run_;
}

void __RC6002StateMenuRun::handle(RC6502PioClass &pio)
{
  if (!RC6502Menu.run())
  {
    __flushTtyRx();
    pio.state_ = &pio.st_keyboard_;
  }
}

void __RC6502State::__flushTtyRx(void)
{
  while (Serial.available() > 0)
    Serial.read();
}
