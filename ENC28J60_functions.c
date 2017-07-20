#include <FastIPv6_config.h>
#include <ENC28J60_functions.h>
#include <ENC28J60_macros.h>

extern void WriteReg(const uint8_t registerName, const uint8_t data)
{
  SS_low();
  SerialTX(WCR(registerName));
  SerialTX(data);
  SerialTXend();
  SS_high();
  return;
}
extern void WriteRegDelayed(const uint8_t registerName, const uint8_t data) // Use when writing to MAC or MII regs
{
  SS_low();
  SerialTX(WCR(registerName));
  SerialTX(data);
  SerialTXend();
  asm volatile("rjmp .+0\n\t" // Waste 4 clock cycles before raising SS.
               "rjmp .+0\n\t" // We need 210 ns from last SCK cycle to SS high.
                ::);
  SS_high(); // This take 2 cycles (sbi)
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
  setBank3();
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  setBank2();
  WriteRegDelayed(MIREGADR, registerName);
  WriteRegDelayed(MIWRL, dataL);
  WriteRegDelayed(MIWRH, dataH);
  return;
}
extern uint16_t ReadPHY(const uint8_t registerName)
{
  setBank3();
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  setBank2();
  WriteRegDelayed(MIREGADR, registerName);
  WriteRegDelayed(MICMD, 1 << MIIRD);
  setBank3();
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  setBank2();
  return (((uint16_t)ReadRegDelayed(MIRDH)) << 8) | ReadRegDelayed(MIRDL);
}
extern void StartPHYscan(const uint8_t registerName)
{
  setBank3();
  while(ReadRegDelayed(MISTAT) & (1 << BUSY)); // Wait till BUSY bit clears
  setBank2();
  WriteRegDelayed(MIREGADR, registerName);
  WriteRegDelayed(MICMD, 1 << MIISCAN);
  setBank3();
  while(ReadRegDelayed(MISTAT) & (1 << NVALID)); // Wait till NVALID bit clears
  return;
}
extern uint8_t ReadPHYscan(const uint8_t whichByte)
{
  setBank2();
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
  setBank2();
  WriteRegDelayed(MICMD, 0);
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
