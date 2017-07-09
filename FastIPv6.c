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
extern void IPv6hardwareInit(void)
{
  IPv6reset(HARD_RESET); // Toggles reset line
  WriteReg(ECOCON, 0); // Disbale clock out pin
  WriteReg(ERXSTL, 0); // RX buffer starts at 0x00
  WriteReg(ERXSTH, 0);
  WriteReg(ERXNDL, endval & 255); // Some odd address
  WriteReg(ERXNDH, endval >> 8);
  WriteReg(ERXRDPTL, endval & 255);
  WriteReg(ERXRDPTH, endval >> 8);
  WriteReg(ERXFCON, (1 << UCEN) | (1 << CRCEN) | (1 << MCEN));
  while(!(ReadReg(ESTAT) & (1 << CLKRDY))); // Wait till CLKRDY sets
  WriteReg(MACON1, (1 << MARXEN) | (1 << TXPAUS) | (1 << RXPAUS));
  // program flow control here
  WriteReg(MACON3, (1 << PADCFG0) | (1 << TXCRCEN) | (1 << FRMLNEN) | (1 << FULDPX));
  WriteReg(MAMXFLL, 1530U & 255U);
  WriteReg(MAMXFLH, 1530U >> 8);
  WriteReg(MABBIPG, 0x15);
  WriteReg(MAIPGL, 0x12);
  WriteReg(MAIPGL, 0x0C);
  WritePHY(PHCON1, 1 << PDPXMD, 0);
  // progrm MAADR registers here
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
