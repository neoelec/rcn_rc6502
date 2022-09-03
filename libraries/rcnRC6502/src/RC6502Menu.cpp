// SPDX-License-Identifier: GPL-3.0-or-later

#include <avr/wdt.h>

#include "rcnRC6502.h"

static RC6502MenuClass RC6502Menu;

RC6502MenuClass::RC6502MenuClass()
{
  nr_programs_ = 0;
}

void RC6502MenuClass::begin(RC6502Dev &dev)
{
  kbd_ = dev.getKbd();
  sd_ = dev.getSd();
  video_ = dev.getVideo();
}

void RC6502MenuClass::enterMenu(void)
{
  Serial.println();
  Serial.print(F("RCN: Entering to menu ..."));

  done_ = false;

  sd_->mount();
  if (nr_programs_ == 0)
  {
    Serial.println();
    Serial.print(F("RCN: 1st run. Building a table of contents..."));

    pgm_.begin(sd_);
    nr_programs_ = pgm_.getNrPrograms();
  }

  menu_cmd_.ShowMenu();
  menu_cmd_.giveCmdPrompt();
}

SerialMenuCmd *RC6502MenuClass::getMenuCmd(void)
{
  return &menu_cmd_;
}
void RC6502MenuClass::doCmdHelp(void)
{
  menu_cmd_.ShowMenu();
  menu_cmd_.giveCmdPrompt();
}

void RC6502MenuClass::doCmdExit(void)
{
  Serial.println();
  Serial.println(F("RCN: Exiting from menu ..."));
  Serial.println();

  done_ = true;
}

void RC6502MenuClass::doCmdListPrograms(void)
{
  RC6502Pgm pgm_tmp;
  size_t n;

  Serial.println();

  for (uint16_t i = 0; i < nr_programs_; i++)
  {
    pgm_tmp.begin(sd_, i);
    n = Serial.print(i, DEC);
    Serial.print(F("."));
    __printSpaces(4 - n);

    n = Serial.print(pgm_tmp.getDescription());
    Serial.print(F(" ("));
    n += Serial.print(pgm_tmp.getTypeT());
    Serial.print(F(")"));

    if (i % 2)
      Serial.println();
    else
      __printSpaces(30 - n);
  }

  Serial.println();
  menu_cmd_.giveCmdPrompt();
}

void RC6502MenuClass::doCmdLoadProgram(void)
{
  String str_bm;
  long pgm_number;

  Serial.println();
  Serial.print(F("RCN: PROGRAM NUMBER [0-"));
  Serial.print(nr_programs_ - 1, DEC);
  Serial.print(F("]"));
  if (!menu_cmd_.getStrValue(str_bm) || !str_bm.length())
    goto __exit;

  pgm_number = str_bm.toInt();
  if (pgm_number < 0 || pgm_number >= nr_programs_)
  {
    Serial.println();
    Serial.print(F("Wrong Value "));
    Serial.print(pgm_number, DEC);
    Serial.print(F(". It should be 0 <= boot_mode <= "));
    Serial.println(nr_programs_ - 1, DEC);
    goto __exit;
  }

  pgm_.begin(sd_, static_cast<uint16_t>(pgm_number));
  __loadPgmFile();

__exit:
  menu_cmd_.giveCmdPrompt();
}

void RC6502MenuClass::doCmdWarmReset(void)
{
  Serial.println();
  Serial.println(F("RCN: Warm reset ..."));
  wdt_enable(WDTO_15MS);
}

bool RC6502MenuClass::isDone(void)
{
  return done_;
}

void RC6502MenuClass::__feedOneCharacter(int c)
{
  c = c == '\n' ? '\r' : c;

  kbd_->pushToBuffer(c);
}

void RC6502MenuClass::__busyWaitConsole(void)
{
  while (!kbd_->isBufferEmpty())
  {
    kbd_->run();
    video_->run();
  }
}

void RC6502MenuClass::__loadPgmFile(void)
{
  __openPgmFile();
  Serial.println();
  Serial.print(F("RCN: Loading program ("));
  Serial.print(pgm_.getPgmFile());
  Serial.println(F(")..."));
  ____loadPgmFile();
  Serial.println();
  pgm_.printProgram();
  Serial.println();
}

void RC6502MenuClass::____loadPgmFile(void)
{
  const char *pgm_file = pgm_.getPgmFile();
  bool empty_file = true;
  uint8_t buffer[32];
  uint8_t error;
  uint8_t sz_read;

  do
  {
    do
    {
      error = sd_->read(buffer, sizeof(buffer), sz_read);
      if (sz_read > 0)
        empty_file = false;

      if (error != FR_OK)
        break;

      for (uint8_t i = 0; i < sz_read; i++)
      {
        __busyWaitConsole();
        __feedOneCharacter(buffer[i]);
      }
    } while (sz_read == sizeof(buffer));

    if (error)
    {
      sd_->printError(error, RC6502Sd::READ, pgm_file);
      sd_->waitKey();
      sd_->lseek(0);
    }
  } while (error);

  if (empty_file)
    goto __empty_file;

  __busyWaitConsole();
  __feedOneCharacter('\r');
  __busyWaitConsole();

  return;

__empty_file:
  Serial.println();
  Serial.print(F("RCN: Empty file - Load aborted!"));
  while (1)
    ;

  return;
}

void RC6502MenuClass::__openPgmFile(void)
{
  const char *pgm_file = pgm_.getPgmFile();
  uint8_t error;

__remount:
  while (true)
  {
    error = sd_->mount();
    if (error == FR_OK)
      break;

    sd_->printError(error, RC6502Sd::MOUNT);
    sd_->waitKey();
  }

  while (true)
  {
    error = sd_->open(pgm_file);
    if (error == FR_OK)
      break;

    if (error != FR_NO_FILE)
      goto __remount;

    sd_->printError(error, RC6502Sd::OPEN, pgm_file);
    sd_->waitKey();
  }
}

inline void RC6502MenuClass::__printSpaces(size_t n)
{
  for (size_t i = 0; i < n; i++)
    Serial.write(' ');
}

// --

static void __initializeMenuCmd(void);

void rc6502MenuBegin(RC6502Dev &dev)
{
  RC6502Menu.begin(dev);
  __initializeMenuCmd();
}

void rcn6502MenuEnter(void)
{
  RC6502Menu.enterMenu();
}

bool rcn6502MenuRun(void)
{
  SerialMenuCmd *menu_cmd;
  uint8_t cmd;

  if (RC6502Menu.isDone())
    return false;

  menu_cmd = RC6502Menu.getMenuCmd();

  cmd = menu_cmd->UserRequest();
  if (cmd)
    menu_cmd->ExeCommand(cmd);

  return true;
}

static void __initializeMenuCmd(void)
{
  SerialMenuCmd *menu_cmd = RC6502Menu.getMenuCmd();
  static tMenuCmdTxt prompt[] PROGMEM = "-";
  static tMenuCmdTxt txt_l[] PROGMEM = "l - List Programs";
  static tMenuCmdTxt txt_o[] PROGMEM = "o - Load Program";
  static tMenuCmdTxt txt_x[] PROGMEM = "x - Exit";
  static tMenuCmdTxt txt_w[] PROGMEM = "w - Warm Reset";
  static tMenuCmdTxt txt__[] PROGMEM = "? - Help";
  static stMenuCmd menu_list[] = {
      {txt_l, 'l', []()
       { RC6502Menu.doCmdListPrograms(); }},
      {txt_o, 'o', []()
       { RC6502Menu.doCmdLoadProgram(); }},
      {txt_x, 'x', []()
       { RC6502Menu.doCmdExit(); }},
      {txt_w, 'w', []()
       { RC6502Menu.doCmdWarmReset(); }},
      {txt__, '?', []()
       { RC6502Menu.doCmdHelp(); }}};

  if (menu_cmd->getNbCmds() > 0)
    return;

  if (!menu_cmd->begin(menu_list, ARRAY_SIZE(menu_list), prompt))
  {
    Serial.println(F("RCN: MENU Failed"));
    while (1)
      ;
  }
}
