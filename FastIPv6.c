#include <FastIPv6.h>
#include <avr/io.h>
#ifdef USE_ENC28J60
  #include <ENC28J60_functions.h>
  #include <ENC28J60_registers.h>
#elif defined(ENCX24J600_SPI)
  #include <ENCX24J600_functions.h>
  #include <ENCX24J600_SPI_registers.h>
#elif defined(ENCX24J600_PARALLEL)
  #include <ENCX24J600_PSP_functions.h>
  #include <ENCX24J600_PSP_registers.h>
#endif /* USE_ENC28J60 */
#ifdef USE_ENC28J60
  // put functions definitions for ENC28J60 here
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
  // Initialize receive filters here
  // Initialize flow control here
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
}
#endif /* USE_ENC28J60 */
