#include <FastIPv6_config.h>
#include <ENC28J60_functions.h>
#include <ENC28J60_registers.h>
extern void WriteReg(uint8_t registerName, uint8_t data)
{
  SS_low();
  SerialTX(
}
extern uint8_t ReadReg(uint8_t registerName)
{
  SS_low();
  SerialTX(RCR(registerName));
  SerialRX(uint8_t trashByte);
  SerialRXend(uint8_t readData);
  SS_high;
  return readData;
}
extern uint8_t ReadRegDelayed(uint8_t registerName)
    {
      gfjg
