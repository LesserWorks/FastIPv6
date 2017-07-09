#include <FastIPv6_config.h>
#include <ENC28J60_functions.h>
#include <ENC28J60_registers.h>

extern void WriteReg(const uint8_t registerName, const uint8_t data)
{
  SS_low();
  SerialTX(WCR(registerName));
  SerialTX(data);
  SerialTXend();
  SS_high();
  return;
}
extern uint8_t ReadReg(const uint8_t registerName)
{
  SS_low();
  SerialTX(RCR(registerName));
  SerialRX(uint8_t trashByte);
  SerialRXend(uint8_t readData);
  SS_high();
  return readData;
}
extern uint8_t ReadRegDelayed(const uint8_t registerName)
{
  SS_low();
  SerialTX(RCR(registerName));
  SerialRX(register uint8_t trashByte);
  SerialRX(trashByte);
  SerialRXend(uint8_t readData);
  SS_high();
  return readData;
}
extern void SetRegBit(const uint8_t registerName, const uint8_t data)
{
  SS_low();
  SerialTX(BFS(registerName));
  SerialTX(data);
  SerialTXend();
  SS_high();
  return;
}
extern void ClearRegBit(const uint8_t registerName, const uint8_t data)
{
  SS_low();
  SerialTX(BFC(registerName));
  SerialTX(data);
  SerialTXend();
  SS_high();
  return;
}
extern void WritePHY(const uint8_t registerName, const uint8_t dataH, const uint8_t dataL)
{
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  WriteReg(MIREGADR, registerName);
  WriteReg(MIWRL, dataL);
  WriteReg(MIWRH, dataH);
  return;
}
extern uint16_t ReadPHY(const uint8_t registerName)
{
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  WriteReg(MIREGADR, registerName);
  WriteReg(MICMD, 1 << MIIRD);
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  return (((uint16_t)ReadRegDelayed(MIRDH)) << 8) | ReadRegDelayed(MIRDL);
}
extern void StartPHYscan(const uint8_t registerName)
{
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  WriteReg(MIREGADR, registerName);
  WriteReg(MICMD, 1 << MIISCAN);
  while(ReadRegDelayed(MISTAT) & (1 << NVALID)); // Wait till NVALID bit clears
  return;
}
extern uint8_t ReadPHYscan(const uint8_t whichByte)
{
  if(whichByte)
  {
    return ReadRegDelayed(MIRDH);
  }
  else
  {
    return ReadRegDelayed(MIRDL);
  }
}
extern void StopPHYscan(void)
{
  WriteReg(MICMD, 0);
  return;
}
extern void IPv6reset(const uint8_t resetType)
{
  switch(resetType)
  {
    case SYSTEM_RESET:
      SS_low();
      SerialTX(SRC);
      SerialTXend();
      SS_high();
      // wait 50uS here
      return;
    case TX_RESET:
      SetRegBit(ECON1, 1 << TXRST);
      ClearRegBit(ECON1, 1 << TXRST);
      return;
    case RX_RESET:
      SetRegBit(ECON1, 1 << RXRST);
      ClearRegBit(ECON1, 1 << RXRST);
      return;
    case HARD_RESET:
      // Toggle reset pin
      return;
    case PHY_RESET:
      return;
    default:
      return;
  }
      
}
