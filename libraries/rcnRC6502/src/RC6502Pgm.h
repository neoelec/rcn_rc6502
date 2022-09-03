#ifndef __RC6502PGM_H__
#define __RC6502PGM_H__

#include <stdint.h>

#include "RC6502Sd.h"

#define PGM_NUMBER_MAX 1000

class RC6502Pgm
{
public:
  enum {
    TYPE_UNKNOWN,
    TYPE_HEX,
    TYPE_BIN
  };

  bool begin(RC6502Sd *sd, const char *csv_name);
  bool begin(RC6502Sd *sd, uint16_t pgm_number);
  bool begin(RC6502Sd *sd);
  const char *getDescription(void);
  uint8_t getType(void);
  const char *getTypeT(void);
  const char *getPgmFile(void);
  uint16_t getLoadAddress(void);
  uint16_t getRunAddress(void);
  uint8_t getNrPrograms(void);
  void printProgram(void);

private:
  bool __openCsv(const char *csv_name);
  bool __readCsv(char *csv, const char *csv_name);
  void __parseCsv(char *csv);
  void __parseToken(char *toeke, uint8_t i);
  void __initNrProgram(void);
  bool __beginPgmNumber(uint16_t pgm_number);
  bool __beginCsvName(const char *csv_name);
  void __updateCsvName(char *csv_name, uint16_t pgm_number);
  inline void __printSpaces(size_t n);

private:
  RC6502Sd *sd_;
  uint8_t nr_programs_;

  char description_[24];
  uint8_t type_;
  char type_t_[8];
  char pgm_file_[13];
  uint16_t load_address_;
  uint16_t run_address_;
};

#endif // __RC6502PGM_H__
