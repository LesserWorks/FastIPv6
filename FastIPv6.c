#include <FastIPv6.h>
#include <avr/io.h>

#include <ENC28J60_functions.h>
#include <ENC28J60_macros.h>


/* Global variables here */
/*extern uint8_t myMACaddress[6] = {0, 0, 0, 0, 0, 0};
extern uint8_t globalIPaddress*/

  // put functions definitions for ENC28J60 here
void IPv6hardwareInit(const uint8_t MAC2, const uint8_t MAC1, const uint8_t MAC0)
{ // Microchip OUI = 0x0004A3
  // Remember memory banks!
  EICRA &= ~(1 << ISC20); // Configure INT2
  EICRA |= 1 << ISC21;
  EIMSK &= ~(1 << INT2); // Disable INT2 for now
  UBRRL = 0; // fosc/2 SPI clock
  UBRRH = 0;
  // Set XCK output here
  UCSR1C = (1 << UMSEL11) | (1 << UMSEL10); // USART in SPI mode 0,0
  UCSR1B = (1 << RXEN1) | (1 << TXEN1); // Enable TX and RX
  SS_low();
  SS_high();
  IPv6reset(HARD_RESET); // Toggles reset line
  SetRegBit(ECON1, (1 << BSEL0) | (1 << BSEL1)); // Bank 3
  WriteReg(ECOCON, 0); // Disable clock out pin
  ClearRegBit(ECON1, (1 << BSEL0) | (1 << BSEL1)); // Bank 0
  WriteReg(ERXSTL, 0); // RX buffer starts at 0x00
  WriteReg(ERXSTH, 0); // Entire buffer goes from 0-8191, so 8192 bytes (0-0x1FFF)
  WriteReg(ERXNDL, RX_BUF_END & 255); // RX buffer can hold 3 maximum length packets
  WriteReg(ERXNDH, RX_BUF_END >> 8);
  WriteReg(ERXRDPTL, RX_BUF_END & 255);
  WriteReg(ERXRDPTH, RX_BUF_END >> 8);
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
  WriteReg(MAIPGH, 0x0C);
  WritePHY(PHCON1, 1 << PDPXMD, 0);
  WritePHY(PHLCON, 1 << LACFG2, (1 << LBCFG2) | (1 << LBCGF1) | (1 << LBCFG0) | (1 << LRFQ0) | (1 << STRCH));
  WritePHY(PHIE, 0, (1 << PLNKIE) | (1 << PGEIE));
  // Write in premade packets here
  ClearRegBits(ECON1, (1 << BSEL1) | (1 << BSEL0)); // Bank 0
  WriteReg(ERDPTL, TX_BUF_ST & 255); // Write pointer at control byte
  WriteReg(ERDPTH, TX_BUF_ST >> 8);
  SS_low(); // Writing in generic headers to speed up transmission
  SerialTX(WBM);
  SerialTX(0); // control byte
  // Ethernet header
  SerialTX(0); // Destination MAC 5
  SerialTX(0); // DM4
  SerialTX(0); // DM3
  SerialTX(0); // DM2
  SerialTX(0); // DM1
  SerialTX(0); // DM0
  SerialTX(0); // Source MAC 5
  SerialTX(0x04); // Source MAC 4
  SerialTX(0xA3); // Source MAC 3
  SerialTX(MAC2); // Source MAC 2
  SerialTX(MAC1); // Source MAC 1
  SerialTX(MAC0); // Source MAC 0
  SerialTX(0x86); // Ethertype
  SerialTX(0xDD);
  SerialTXend();
  SS_high();
  WriteReg(ERDPTL, 7972U & 255); // Other headers start here
  WriteReg(ERDPTH, 7972U >> 8);
  SS_low();
  SerialTX(WBM);
  // Neighbor advertisement
  SerialTX(136); // Type
  SerialTX(0); // Code
  SerialTX(0); // Checksum
  SerialTX(0);
  SerialTX(0); // Flags
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Target address
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(2); // Type of options header
  SerialTX(1); // Length of options
  SerialTX(0); // Source MAC 5
  SerialTX(0x04); // Source MAC 4
  SerialTX(0xA3); // Source MAC 3
  SerialTX(MAC2); // Source MAC 2
  SerialTX(MAC1); // Source MAC 1
  SerialTX(MAC0); // Source MAC 0
  // Neighbor solicitation
  SerialTX(135); // Type
  SerialTX(code); // Code
  SerialTX(0); // Checksum
  SerialTX(0);
  SerialTX(0); // Zeros
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Target address
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(1); // Type of options header
  SerialTX(1); // Length of options
  SerialTX(0); // Source MAC 5
  SerialTX(0x04); // Source MAC 4
  SerialTX(0xA3); // Source MAC 3
  SerialTX(MAC2); // Source MAC 2
  SerialTX(MAC1); // Source MAC 1
  SerialTX(MAC0); // Source MAC 0
  // Router solicitation
  SerialTX(133); // Type
  SerialTX(code); // Code
  SerialTX(0); // Checksum
  SerialTX(0);
  SerialTX(0); // Zeros
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(1); // Type of options header
  SerialTX(1); // Length of options
  SerialTX(0); // Source MAC 5
  SerialTX(0x04); // Source MAC 4
  SerialTX(0xA3); // Source MAC 3
  SerialTX(MAC2); // Source MAC 2
  SerialTX(MAC1); // Source MAC 1
  SerialTX(MAC0); // Source MAC 0
  // ICMP pseudo header
  SerialTX(0xFE); // Start with our link local address
  SerialTX(128);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0x02); // EUI-64
  SerialTX(0x04);
  SerialTX(0xA3);
  SerialTX(0xFF);
  SerialTX(0xFE);
  SerialTX(MAC2);
  SerialTX(MAC1);
  SerialTX(MAC0);
  SerialTX(0xFF); // Destination address (start with all-routers address)
  SerialTX(0x02);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0x02);
  SerialTX(0); // Length for router solicitation
  SerialTX(0);
  SerialTX(0);
  SerialTX(16);
  SerialTX(0); // Zeros
  SerialTX(0);
  SerialTX(0);
  SerialTX(58); // Next header for ICMP
  // TCP pseudo header
  SerialTX(0); // Source IP
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Destination address
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Length
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Zeros
  SerialTX(0);
  SerialTX(0);
  SerialTX(6); // Next header for TCP
  // TCP header
  SerialTX(0); // Source port
  SerialTX(80);
  SerialTX(0); // Destination port
  SerialTX(0);
  SerialTX(0); // Sequence number
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Acknowledge number
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(5 << 4); // Data offset
  SerialTX(0); // flags
  SerialTX(0); // Window size
  SerialTX(0);
  SerialTX(0); // Checksum
  SerialTX(0);
  SerialTX(0); // Urgent pointer
  SerialTX(0);
  // IP header
  SerialTX(6U << 4); // Version
  SerialTX(0); // Traffic class and flow label
  SerialTX(0); // Flow label
  SerialTX(0);
  SerialTX(0); // Payload length
  SerialTX(0);
  SerialTX(0); // Next header
  SerialTX(255U); // Hop limit
  SerialTX(0); // Source IP
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // Destination address
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0);
  SerialTX(0); // By here we should be at byte 8191, the last of the buffer
  SerialTXend();
  SS_high();
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
  
