// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>

#include "RC6502Sd.h"

void RC6502Sd::begin(uint8_t pin_ss)
{
  FRESULT error;

  pin_ss_ = pin_ss;

  do
  {
    uint8_t i = 25;
    do
    {
      error = PFF3a.begin(&fatfs_, pin_ss_);
      delay(1);
    } while (--i && (error != FR_OK));
    printError(error, MOUNT);

    if (error != FR_OK)
      waitKey();
  } while (error != FR_OK);
}

uint8_t RC6502Sd::mount(void)
{
  FRESULT error;

  error = PFF3a.begin(&fatfs_, pin_ss_);

  return static_cast<uint8_t>(error);
}

uint8_t RC6502Sd::open(const char *file_name)
{
  FRESULT error;

  error = PFF3a.open(file_name);

  return static_cast<uint8_t>(error);
}

void RC6502Sd::printError(uint8_t error, uint8_t operation, const char *file_name)
{
  __printErrorCode(static_cast<FRESULT>(error));
  __printOperation(operation);

  if (file_name)
  {
    Serial.print(F(" - File : "));
    Serial.print(file_name);
  }

  Serial.println();
}

void RC6502Sd::waitKey(void)
{
  __flushTtyRx();

  Serial.println(F("RCN: Check SD and press a key to repeat"));
  Serial.println();

  __waitTtyRx();
  __flushTtyRx();
}

void RC6502Sd::__flushTtyRx(void)
{
  while (Serial.available() > 0)
    Serial.read();
}

void RC6502Sd::__printErrorCode(FRESULT error)
{
  Serial.print(F("RCN: SD error "));
  Serial.print(static_cast<unsigned int>(error));
  Serial.print(F(" ("));
  switch (error)
  {
  case FR_OK:
    Serial.print(F("OK"));
    break;
  case FR_DISK_ERR:
    Serial.print(F("DISK_ERR"));
    break;
  case FR_NOT_READY:
    Serial.print(F("NOT_READY"));
    break;
  case FR_NO_FILE:
    Serial.print(F("NO_FILE"));
    break;
  case FR_NOT_OPENED:
    Serial.print(F("NOT_OPENED"));
    break;
  case FR_NOT_ENABLED:
    Serial.print(F("NOT_ENABLED"));
    break;
  case FR_NO_FILESYSTEM:
    Serial.print(F("NO_FILESYSTEM"));
    break;
  default:
    Serial.print(F("UNKNOWN"));
    break;
  }
  Serial.print(F(")"));
}

void RC6502Sd::__printOperation(uint8_t operation)
{
  Serial.print(F(" on "));

  switch (operation)
  {
  case MOUNT:
    Serial.print(F("MOUNT"));
    break;
  case OPEN:
    Serial.print(F("OPEN"));
    break;
  case READ:
    Serial.print(F("READ"));
    break;
  case WRITE:
    Serial.print(F("WRITE"));
    break;
  case SEEK:
    Serial.print(F("SEEK"));
    break;
  default:
    Serial.print(F("UNKNOWN"));
    break;
  }
}

void RC6502Sd::__waitTtyRx(void)
{
  while (Serial.available() < 1)
    ;
}
