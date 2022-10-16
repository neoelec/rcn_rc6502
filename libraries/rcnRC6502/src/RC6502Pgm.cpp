// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>

#include "RC6502Pgm.h"

#define SZ_BUF 32
#define SZ_CSV_BUF (SZ_BUF * 3)

#define CSV_NAME_FMT "yy/PGMxxx.CSV"

bool RC6502Pgm::begin(RC6502Sd *sd)
{
  sd_ = sd;

  return __beginPgmNumber(0, 0);
}

bool RC6502Pgm::begin(RC6502Sd *sd, uint8_t dir_number, uint16_t pgm_number)
{
  bool is_ok;

  sd_ = sd;
  is_ok = __beginPgmNumber(dir_number, pgm_number);

  return is_ok;
}

bool RC6502Pgm::begin(RC6502Sd *sd, const char *csv_name)
{
  bool is_ok;

  sd_ = sd;
  is_ok = __beginCsvName(csv_name);

  return is_ok;
}

const char *RC6502Pgm::getDescription(void)
{
  return description_;
}

uint8_t RC6502Pgm::getType(void)
{
  return type_;
}

const char *RC6502Pgm::getTypeT(void)
{
  return type_t_;
}

const char *RC6502Pgm::getPgmFile(void)
{
  return pgm_file_;
}

uint16_t RC6502Pgm::getLoadAddress(void)
{
  return load_address_;
}

uint16_t RC6502Pgm::getRunAddress(void)
{
  return run_address_;
}

void RC6502Pgm::printProgram(void)
{
  size_t n;

  Serial.print(F("RCN: "));
  Serial.print(description_);
  Serial.print(F(" ("));
  Serial.print(type_t_);
  Serial.println(F(")"));

  Serial.print(F("     F> "));
  n = Serial.print(pgm_file_);
  __printSpaces(12 - n);

  Serial.print(F(" L> "));
  n = Serial.print(load_address_, HEX);
  __printSpaces(4 - n);

  Serial.print(F(" R> "));
  Serial.print(run_address_, HEX);
}

bool RC6502Pgm::__openCsv(const char *csv_name)
{
  uint8_t error;

  error = sd_->open(csv_name);
  if (error == FR_NO_FILE)
    return false;

  if (error == FR_OK)
    return true;

  sd_->printError(error, RC6502Sd::OPEN, csv_name);
  while (1)
    ;

  return false;
}

bool RC6502Pgm::__readCsv(char *csv, uint8_t sz_csv, const char *csv_name)
{
  uint8_t error;
  uint8_t sz_read;

  error = sd_->read(csv, sz_csv, sz_read);
  if (error != FR_OK)
    goto __hang_on_error;

  return true;

__hang_on_error:
  sd_->printError(error, RC6502Sd::READ, csv_name);
  while (1)
    ;

  return false;
}

void RC6502Pgm::__parseCsv(char *csv)
{
  static const char *delim = ",";
  char *ptr = csv;
  char *token;
  unsigned int i = 0;

  token = strsep(&ptr, delim);
  while (token)
  {
    __parseToken(token, i++);
    token = strsep(&ptr, delim);
  }
}

#define __terminateCStr(__str) __str[sizeof(__str) - 1] = '\0'

void RC6502Pgm::__parseToken(char *token, uint8_t i)
{
  long tmp;

  switch (i)
  {
  case 0: // description_
    strncpy(description_, token, sizeof(description_));
    __terminateCStr(description_);
    break;
  case 1: // type_
    strncpy(type_t_, token, sizeof(type_t_));
    __terminateCStr(type_t_);
    if (!strcmp(token, "HEX"))
      type_ = TYPE_HEX;
    else if (!strcmp(token, "BIN"))
      type_ = TYPE_BIN;
    else
      type_ = TYPE_UNKNOWN;
    break;
  case 2: // pgm_file
    strncpy(pgm_file_, token, sizeof(pgm_file_));
    __terminateCStr(pgm_file_);
    /* NOTE: PF library can only recognize uppercase characters. */
    for (size_t i = 0; i < sizeof(pgm_file_) && !pgm_file_[i]; i++)
      pgm_file_[i] = toupper(pgm_file_[i]);
    break;
  case 3: // load_address_
    tmp = strtol(token, NULL, 16);
    load_address_ = static_cast<uint16_t>(tmp);
    break;
  case 4: // run_address_
    tmp = strtol(token, NULL, 16);
    run_address_ = static_cast<uint16_t>(tmp);
    break;
  }
}

bool RC6502Pgm::__beginPgmNumber(uint8_t dir_number, uint16_t pgm_number)
{
  static char csv_name[] = CSV_NAME_FMT;

  __updateCsvName(csv_name, dir_number, pgm_number);

  return __beginCsvName(csv_name);
}

bool RC6502Pgm::__beginCsvName(const char *csv_name)
{
  char csv[SZ_CSV_BUF];
  bool is_ok = __openCsv(csv_name);

  if (!is_ok)
    return is_ok;

  is_ok = __readCsv(csv, sizeof(csv), csv_name);
  if (is_ok)
    __parseCsv(csv);

  return is_ok;
}

void RC6502Pgm::__updateCsvName(char *csv_name, uint8_t dir_number, uint16_t pgm_number)
{
  csv_name[0] = static_cast<char>(dir_number / 10) + '0';
  csv_name[1] = static_cast<char>(dir_number % 10) + '0';

  csv_name[6] = static_cast<char>(pgm_number / 100) + '0';
  csv_name[7] = static_cast<char>((pgm_number % 100) / 10) + '0';
  csv_name[8] = static_cast<char>(pgm_number % 10) + '0';
}

inline void RC6502Pgm::__printSpaces(size_t n)
{
  for (size_t i = 0; i < n; i++)
    Serial.write(' ');
}
