#ifndef __RC6502DEV_H__
#define __RC6502DEV_H__

#include <Adafruit_MCP23X17.h>

#include "RC6502Clock.h"
#include "RC6502Kbd.h"
#include "RC6502Sd.h"
#include "RC6502Video.h"

class RC6502Dev
{
public:
  void begin(void);
  void beginNoSd(void);
  RC6502Clock *getClock(void);
  RC6502Kbd *getKbd(void);
  Adafruit_MCP23X17 *getMcp(void);
  RC6502Sd *getSd(void);
  RC6502Video *getVideo(void);

private:
  void __beginKbd(void);
  void __beginMcp(void);
  void __beginPin(void);
  void __beginSd(void);
  void __beginTty(void);

private:
  Adafruit_MCP23X17 mcp_;
  RC6502Clock clock_;
  RC6502Kbd kbd_;
  RC6502Sd sd_;
  RC6502Video video_;
};

#endif // __RC6502DEV_H__
