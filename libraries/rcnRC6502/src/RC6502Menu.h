#ifndef __RC6502MENU_H__
#define __RC6502MENU_H__

#include <SerialMenuCmd.h>

#include "RC6502Dev.h"
#include "RC6502Kbd.h"
#include "RC6502Pgm.h"
#include "RC6502Sd.h"
#include "RC6502Video.h"

class RC6502MenuClass
{
public:
  RC6502MenuClass();
  void begin(RC6502Dev &dev);
  void enter(void);
  bool run(void);
  SerialMenuCmd *getMenuCmd(void);
  void doCmdHelp(void);
  void doCmdExit(void);
  void doCmdListPrograms(void);
  void doCmdLoadProgram(void);
  void doCmdWarmReset(void);
  bool isDone(void);

private:
  void __busyWaitConsole(void);
  void __feedOneCharacter(int c);
  void __loadPgmFile(void);
  void ____loadPgmFile(void);
  void __openPgmFile(void);
  inline void __printSpaces(size_t n);
  void __initializeMenuCmd(void);
  void __listPrograms(uint16_t page_number, uint16_t pgm_per_page);

private:
  SerialMenuCmd menu_cmd_;
  RC6502Clock *clock_;
  RC6502Kbd *kbd_;
  RC6502Sd *sd_;
  RC6502Video *video_;

  bool done_;
  size_t nr_programs_;
  RC6502Pgm pgm_;
};

extern RC6502MenuClass RC6502Menu;

#endif // __RC6502MENU_H__
