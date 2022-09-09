#ifndef __RC6502PIO_H__
#define __RC6502PIO_H__

#include "RC6502Dev.h"

class RC6502PioClass;

extern RC6502PioClass RC6502Pio;

class __RC6502State
{
public:
  virtual void handle(RC6502PioClass *pio) = 0;

protected:
  void __flushTtyRx(void);
};

class __RC6002StateClassic : public __RC6502State
{
public:
  void handle(RC6502PioClass *pio);
};

class __RC6002StateKbd : public __RC6502State
{
public:
  void handle(RC6502PioClass *pio);
};

class __RC6002StateMenuEnter : public __RC6502State
{
public:
  void handle(RC6502PioClass *pio);
};

class __RC6002StateMenuRun : public __RC6502State
{
public:
  void handle(RC6502PioClass *pio);
};

class RC6502PioClass
{
public:
  void begin(void);
  void beginClassic(void);
  void run(void);

private:
  void __beginCommon(void);

private:
  RC6502Dev dev_;

  RC6502Clock *clk_src_;
  RC6502Kbd *kbd_;
  RC6502Video *video_;

  __RC6502State *state_;
  __RC6002StateClassic st_classic_;
  __RC6002StateKbd st_keyboard_;
  __RC6002StateMenuEnter st_menu_enter_;
  __RC6002StateMenuRun st_menu_run_;

  friend class __RC6502State;
  friend class __RC6002StateClassic;
  friend class __RC6002StateKbd;
  friend class __RC6002StateMenuEnter;
  friend class __RC6002StateMenuRun;
};

#endif // __RC6502PIO_H__
