// SPDX-License-Identifier: GPL-3.0-or-later

#include "rcnRC6502.h"

RC6502MenuClass RC6502Menu;

void RC6502MenuClass::begin(RC6502Dev &dev)
{
  clock_ = dev.getClock();
  kbd_ = dev.getKbd();
  sd_ = dev.getSd();
  video_ = dev.getVideo();

  __initializeMenuCmd();
}

void RC6502MenuClass::enter(void)
{
  Serial.println();
  Serial.print(F("RCN: Entering to menu ..."));

  done_ = false;

  sd_->mount();
  pgm_.begin(sd_);

  menu_cmd_.ShowMenu();
  menu_cmd_.giveCmdPrompt();
}

bool RC6502MenuClass::run(void)
{
  uint8_t cmd;

  if (isDone())
    return false;

  cmd = menu_cmd_.UserRequest();
  if (cmd)
    menu_cmd_.ExeCommand(cmd);

  return true;
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
  String str_bm;
  const uint16_t pgm_per_page = 20;
  long page_number;

  Serial.println();
  Serial.print(F("RCN: PAGE NUMBER [>=0]"));
  if (!menu_cmd_.getStrValue(str_bm) || !str_bm.length())
    goto __exit;

  page_number = str_bm.toInt();
  if (page_number < 0)
  {
    Serial.println();
    Serial.print(F("Wrong Value "));
    Serial.print(page_number, DEC);
    Serial.println(F(". It should be page_number >= 0"));
    goto __exit;
  }

  __listPrograms(page_number, pgm_per_page);

__exit:
  menu_cmd_.giveCmdPrompt();
}

void RC6502MenuClass::doCmdLoadProgram(void)
{
  String str_bm;
  long pgm_number;

  Serial.println();
  Serial.print(F("RCN: PROGRAM NUMBER [>=0]"));
  if (!menu_cmd_.getStrValue(str_bm) || !str_bm.length())
    goto __exit;

  pgm_number = str_bm.toInt();
  if (pgm_number < 0)
  {
    Serial.println();
    Serial.print(F("Wrong Value "));
    Serial.print(pgm_number, DEC);
    Serial.println(F(". It should be boot_mode  >= 0"));
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
  clock_->reset();
  done_ = true;
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

void RC6502MenuClass::__initializeMenuCmd(void)
{
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

  if (menu_cmd_.getNbCmds() > 0)
    return;

  if (!menu_cmd_.begin(menu_list, ARRAY_SIZE(menu_list), prompt))
  {
    Serial.println(F("RCN: MENU Failed"));
    while (1)
      ;
  }
}

void RC6502MenuClass::__listPrograms(uint16_t page_number, uint16_t pgm_per_page)
{
  RC6502Pgm pgm_tmp;
  uint16_t pgm_begin = page_number * pgm_per_page;
  Serial.println();
  size_t n;

  for (uint16_t i = 0; i < pgm_per_page; i++)
  {
    uint16_t pgm_number = i + pgm_begin;

    if (!pgm_tmp.begin(sd_, pgm_number))
      break;

    n = Serial.print(pgm_number, DEC);
    Serial.print(F("."));
    __printSpaces(4 - n);

    n = Serial.print(pgm_tmp.getDescription());
    __printSpaces(26 - n);
    Serial.print(F(" ("));
    Serial.print(pgm_tmp.getTypeT());
    Serial.println(F(")"));
  }

  Serial.println();
}
