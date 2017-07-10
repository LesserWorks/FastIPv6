#include <FastIPv6.h>
#include <avr/io.h>
#ifdef USE_ENC28J60
  #include <ENC28J60_functions.h>
  #include <ENC28J60_macros.h>
#elif defined(ENCX24J600_SPI)
  #include <ENCX24J600_functions.h>
  #include <ENCX24J600_SPI_registers.h>
#elif defined(ENCX24J600_PARALLEL)
  #include <ENCX24J600_PSP_functions.h>
  #include <ENCX24J600_PSP_registers.h>
#endif /* USE_ENC28J60 */
/* Global variables here */
/*extern uint8_t myMACaddress[6] = {0, 0, 0, 0, 0, 0};
extern uint8_t globalIPaddress*/
#ifdef USE_ENC28J60
  // put functions definitions for ENC28J60 here
extern void IPv6hardwareInit(const uint8_t MAC2, const uint8_t MAC1, const uint8_t MAC0)
{ // Microchip OUI = 0x0004A3
  // Remember memory banks!
  EICRA &= ~(1 << ISC20); // Configure INT2
  EICRA |= 1 << ISC21;
  EIMSK &= ~(1 << INT2); // Disable INT2 for now
  IPv6reset(HARD_RESET); // Toggles reset line
  SetRegBit(ECON1, (1 << BSEL0) | (1 << BSEL1)); // Bank 3
  WriteReg(ECOCON, 0); // Disable clock out pin
  ClearRegBit(ECON1, (1 << BSEL0) | (1 << BSEL1)); // Bank 0
  WriteReg(ERXSTL, 0); // RX buffer starts at 0x00
  WriteReg(ERXSTH, 0);
  WriteReg(ERXNDL, 4573U & 255); // RX buffer can hold 3 maximum length packets
  WriteReg(ERXNDH, 4573U >> 8);
  WriteReg(ERXRDPTL, 4573U & 255);
  WriteReg(ERXRDPTH, 4573U >> 8);
  SetRegBit(ECON1, 1 << BSEL0); // Bank 1
  WriteReg(ERXFCON, (1 << UCEN) | (1 << CRCEN) | (1 << MCEN));
  WriteReg(ECON2, 1 << AUTOINC);
  while(!(ReadReg(ESTAT) & (1 << CLKRDY))); // Wait till CLKRDY sets
  SetRegBit(ECON1, 1 << BSEL1); // Bank 3
  WriteReg(MAADR6, 0); // Microchip OUI
  WriteReg(MAADR5, 0x04);
  WriteReg(MAADR4, 0xA3);
  WriteReg(MAADR3, MAC2); // User defined low 24 bits
  WriteReg(MAADR2, MAC1);
  WriteReg(MAADR1, MAC0);
  ClearRegBit(ECON1, 1 << BSEL0); // Bank 2
  WriteReg(MACON1, (1 << MARXEN) | (1 << TXPAUS) | (1 << RXPAUS));
  // Flow control is manual
  WriteReg(MACON3, (1 << PADCFG0) | (1 << TXCRCEN) | (1 << FRMLNEN) | (1 << FULDPX));
  WriteReg(MAMXFLL, 1530U & 255U);
  WriteReg(MAMXFLH, 1530U >> 8);
  WriteReg(MABBIPG, 0x15);
  WriteReg(MAIPGL, 0x12);
  WriteReg(MAIPGL, 0x0C);
  WritePHY(PHCON1, 1 << PDPXMD, 0);
  WritePHY(PHLCON, 1 << LACFG2, (1 << LBCFG2) | (1 << LBCGF1) | (1 << LBCFG0) | (1 << LRFQ0) | (1 << STRCH));
  WritePHY(PHIE, 0, (1 << PLNKIE) | (1 << PGEIE));
  // Write in premade packets here
}
extern void IPv6hardwareSleep(void)
{
  ClearRegBit(ECON1, 1 << RXEN);
  while(ReadReg(ESTAT) & (1 << RXBUSY)); // wait for RXBUSY to clear
  while(ReadReg(ECON1), (1 << TXRTS)); // wait for TXRTS to clear
  SetRegBit(ECON2, 1 << VRPS);
  SetRegBit(ECON2, 1 << PWRSV);
  return;
}
extern void IPv6hardwareWake(void)
{
  ClearRegBit(ECON2, 1 << PWRSV);
  while(!(ReadReg(ESTAT) & (1 << CLKRDY))); // Wait for CLKRDY to set
  SetRegBit(ECON1, 1 << RXEN);
  return;
}
  
#elif defined(ENCX24J600_SPI)
  // put function definitions for X24J600 SPI here
#elif defined(ENCX24J600_PARALLEL)
  // put function definitions for X24J600 PSP here
extern uint8_t IPv6hardwareInit(void)
{
  XMCRA = (1 << SRE) | (1 << SRW10); // Enable external memory interface
  XMCRB = (1 << XMBK) | (1 << XMM0);
  do
  {
    indir(EUDASTL) = 0x34;
  }
  while(indir(EUDASTL) != 0x34);
  while(!(indir(ESTATH) & (1 << CLKRDY))); // Wait for clock ready
  indir(ECON2SETL) = 1 << ETHRST; // System reset
  // Wait 25uS here
  if(indir(EUDASTL)) // Is it nonzero?
  {
    // Some sort of error
  }
  // Wait 256uS here
  indir(ECON2H) = (1 << ETHEN) | (1 << STRCH) | (1 << TXMAC) | (1 << COCON3) | (1 << COCON2) | (1 << COCON1) | (1 << COCON0);
  indir(ECON2L) = 1 << AUTOFC;
  indir(EIDLEDH) = (1 << LACFG2) | (1 << LACFG1) | (1 << LBCFG1);
  indir(ERXSTL) = 4268 & 255; // About 7000 bytes for RX buffer
  indir(ERXSTH) = 4268 >> 8;
  indir(ERXFCONL) = (1 << MCEN) | (1 << RUNTEN) | (1 << CRCEN) | (1 << UCEN);
  indir(ERXFCONH) = (1 << HTEN);
  // Initialize flow control here
  indir(ERXWML) = 0; // How few 96 byte blocks must be filled to stop flow control
  indir(ERXWMH) = 0; // How many 96 byte blocks must be filled to start flow control
  indir(MACON2L) = (1 << FULDPX) | (1 << 1) | (1 << TXCRCEN) | (1 << PADCFG2) | (1 << PADCFG0);
  indir(MACON2H) = 0;
  indir(MABBIPGL) = (1 << BBIPG4) | (1 << BBIPG2) | (1 << BBIPG0); // 0x15
  indir(MABBIPGH) = 0;
  indir(MAIPGL) = (1 << IPG4) | (1 << IPG1); // 0x12
  indir(MAIPGH) = 0x0C;
  indir(MAMXFLL) = 1522 & 255; // Maximum frame size
  indir(MAMXFLH) = 1522 >> 8;
  // Program source MAC address if desired here
  WritePHY(PHCON1, (1 << ANEN) | (1 << PFULDPX), 0);
  WritePHY(PHANA, (1 << ADPAUS0) | (1 << AD100FD), (1 << AD100) | (1 << AD10FD) | (1 << AD10) | (1 << ADIEEE0)); // 0x05E1
  indir(ECON1L) = 1 << RXEN;
  /*myMACaddress[0] = indir(MAADR1L); // Read hardwired MAC address
  myMACaddress[1] = indir(MAADR1H);
  myMACaddress[2] = indir(MAADR2L);
  myMACaddress[3] = indir(MAADR2H);
  myMACaddress[4] = indir(MAADR3L);
  myMACaddress[5] = indir(MAADR3H);*/
}
#endif /* USE_ENC28J60 */
