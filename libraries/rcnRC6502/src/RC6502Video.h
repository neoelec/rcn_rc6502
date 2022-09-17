#ifndef __RC6502VIDEO_H__
#define __RC6502VIDEO_H__

#include <Adafruit_MCP23X17.h>

class RC6502Video
{
public:
  void begin(Adafruit_MCP23X17 *mcp);
  void reset(void);
  void run(void);

private:
  void __beginMcp(void);
  void __beginPin(void);
  inline void __putchar(int c);
  inline void ____println(void);
  inline void ____putchar(int c);

private:
  Adafruit_MCP23X17 *mcp_;
};

#endif // __RC6502VIDEO_H__
