#ifndef __RC6502SD_H__
#define __RC6502SD_H__

#include <PFF3a.h>

class RC6502Sd
{
public:
  enum
  {
    MOUNT = 0,
    OPEN,
    READ,
    WRITE,
    SEEK,
  };

  void begin(uint8_t pin_ss);
  uint8_t mount(void);
  uint8_t open(const char *file_name);
  inline uint8_t read(void *buf, uint8_t sz_to_read, uint8_t &sz_read);
  inline uint8_t write(const void *buf, uint8_t sz_to_write, uint8_t &sz_wrote);
  inline uint8_t lseek(uint32_t sz_offset);
  void printError(uint8_t error, uint8_t operation, const char *file_name = nullptr);
  void waitKey(void);

private:
  void __flushTtyRx(void);
  void __printErrorCode(FRESULT error);
  void __printOperation(uint8_t operation);
  void __waitTtyRx(void);

  FATFS fatfs_;
  uint8_t pin_ss_;
};

inline uint8_t RC6502Sd::read(void *buf, uint8_t sz_to_read, uint8_t &__sz_read)
{
  UINT sz_read;
  FRESULT error;

  error = PFF3a.read(buf, sz_to_read, &sz_read);

  __sz_read = static_cast<uint8_t>(sz_read);

  return static_cast<uint8_t>(error);
}

inline uint8_t RC6502Sd::write(const void *buf, uint8_t sz_to_write, uint8_t &__sz_wrote)
{
  UINT sz_wrote;
  FRESULT error;

  error = PFF3a.write(buf, sz_to_write, &sz_wrote);

  __sz_wrote = static_cast<uint8_t>(sz_wrote);

  return static_cast<uint8_t>(error);
}

inline uint8_t RC6502Sd::lseek(uint32_t sz_offset)
{
  FRESULT error;

  error = PFF3a.lseek(sz_offset);

  return static_cast<uint8_t>(error);
}

#endif // __RC6502SD_H__
