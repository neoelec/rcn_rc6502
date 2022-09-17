#ifndef __RC6502KBD_H__
#define __RC6502KBD_H__

#include <Adafruit_MCP23X17.h>
#include <RingBuf.h>

#define PIN_KBD_CLR 2 // of Arduino

class RC6502Kbd;

class __RC6502KbdState
{
public:
  virtual void handle(RC6502Kbd *kbd) = 0;
};

class __RC6502KbdStIdle : public __RC6502KbdState
{
public:
  void handle(RC6502Kbd *kbd);
};

class __RC6502KbdStPollClear : public __RC6502KbdState
{
public:
  void handle(RC6502Kbd *kbd);
};

class __RC6502KbdStWaitInt : public __RC6502KbdState
{
public:
  void handle(RC6502Kbd *kbd);
};

class __RC6502KbdStWrite : public __RC6502KbdState
{
public:
  void handle(RC6502Kbd *kbd);
};

class RC6502Kbd
{
public:
  void begin(Adafruit_MCP23X17 *mcp);
  void reset(void);
  bool isBufferEmpty(void);
  bool isBufferFull(void);
  int popFromBuffer(void);
  void pushToBuffer(int ch);
  void run(void);
  void setInterrupt(void);

private:
  void __beginMcp(void);
  void __beginPin(void);

private:
  Adafruit_MCP23X17 *mcp_;
  RingBuf<int, 128> serial_buf_;

  bool interrupt_;
  __RC6502KbdState *state_;
  __RC6502KbdStIdle st_idle_;
  __RC6502KbdStPollClear st_poll_clear_;
  __RC6502KbdStWaitInt st_wait_int_;
  __RC6502KbdStWrite st_write_;

  friend class __RC6502KbdState;
  friend class __RC6502KbdStIdle;
  friend class __RC6502KbdStPollClear;
  friend class __RC6502KbdStWaitInt;
  friend class __RC6502KbdStWrite;
};

#endif // __RC6502KBD_H__
