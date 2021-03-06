/* Macro functions for USART in SPI mode */
#define SerialTX(data, ...) UDR1 = (data); __VA_ARGS__ ; while(!(UCSR1A & (1 << UDRE1)));
#define SerialTXend() UCSR1A = 1 << TXC1; while(!(UCSR1A & (1 << TXC1)));
#define SerialRX(retVal, ...) UDR1 = 0; __VA_ARGS__ ; while(!(UCSR1A & (1 << RXC1))); (retVal) = UDR1;
#define SerialRXend(retVal, ...) __VA_ARGS__ ; while(!(UCSR1A & (1 << RXC1))); (retVal) = UDR1;
#define SerialRXflush() while(UCSR1A & (1 << RXC1)) { uint8_t trashByte = UDR1; }

 
#define RX_BUF_END 4573U
#define SS_low() SS_PORT &= ~(1 << SS_PIN_NUM)
#define SS_high() SS_PORT |= 1 << SS_PIN_NUM
#define RST_low() RST_PORT &= ~(1 << RST_PIN_NUM)
#define RST_high() RST_PORT |= 1 << RST_PIN_NUM
/* SPI opcodes */
#define RCR(address) (0b00011111U & (address))
#define RBM 0b00111010U
#define WCR(address) ((0b00011111U & (address)) | 0b01000000U)
#define WBM 0b01111010U
#define BFS(address) ((0b00011111U & (address)) | 0b10000000U)
#define BFC(address) ((0b00011111U & (address)) | 0b10100000U)
#define SRC 0b11111111U

/* PHY registers */
#define PHCON1  0x00U
#define PHSTAT1 0x01U
#define PHID1   0x02U
#define PHID2   0x03U
#define PHCON2  0x10U
#define PHSTAT2 0x11U
#define PHIE    0x12U
#define PHIR    0x13U
#define PHLCON  0x14U

/* All banks */
#define EIE   0x1BU
#define EIR   0x1CU
#define ESTAT 0x1DU
#define ECON2 0x1EU
#define ECON1 0x1FU

/* Bank 0 */
#define ERDPTL   0x00U
#define ERDPTH   0x01U
#define EWRPTL   0x02U
#define EWRPTH   0x03U
#define ETXSTL   0x04U
#define ETXSTH   0x05U
#define ETXNDL   0x06U
#define ETXNDH   0x07U
#define ERXSTL   0x08U
#define ERXSTH   0x09U
#define ERXNDL   0x0AU
#define ERXNDH   0x0BU
#define ERXRDPTL 0x0CU
#define ERXRDPTH 0x0DU
#define ERXWRPTL 0x0EU
#define ERXWRPTH 0x0FU
#define EDMASTL  0x10U
#define EDMASTH  0x11U
#define EDMANDL  0x12U
#define EDMANDH  0x13U
#define EDMADSTL 0x14U
#define EDMADSTH 0x15U
#define EDMACSL  0x16U
#define EDMACSH  0x17U

/* Bank 1 */
#define EHT0    0x00U
#define EHT1    0x01U
#define EHT2    0x02U
#define EHT3    0x03U
#define EHT4    0x04U
#define EHT5    0x05U
#define EHT6    0x06U
#define EHT7    0x07U
#define EPMM0   0x08U
#define EPMM1   0x09U
#define EPMM2   0x0AU
#define EPMM3   0x0BU
#define EPMM4   0x0CU
#define EPMM5   0x0DU
#define EPMM6   0x0EU
#define EPMM7   0x0FU
#define EPMCSL  0x10U
#define EPMCSH  0x11U
#define EPMOL   0x14U
#define EPMOH   0x15U
#define EWOLIE  0x16U // Deprecated, do not use
#define EWOLIR  0x17U // Deprecated, do not use
#define ERXFCON 0x18U
#define EPKTCNT 0x19U

/* Bank 2 */
#define MACON1   0x00U
#define MACON2   0x01U // Deprecated, do not use
#define MACON3   0x02U
#define MACON4   0x03U
#define MABBIPG  0x04U
#define MAIPGL   0x06U
#define MAIPGH   0x07U
#define MACLCON1 0x08U
#define MACLCON2 0x09U
#define MAMXFLL  0x0AU
#define MAMXFLH  0x0BU
#define MAPHSUP  0x0DU // Deprecated, do not use
#define MICON    0x11U // Deprecated, do not use
#define MICMD    0x12U
#define MIREGADR 0x14U
#define MIWRL    0x16U
#define MIWRH    0x17U
#define MIRDL    0x18U
#define MIRDH    0x19U

/* Bank 3 */
#define MAADR5  0x00U
#define MAADR6  0x01U
#define MAADR3  0x02U
#define MAADR4  0x03U
#define MAADR1  0x04U
#define MAADR2  0x05U
#define EBSTSD  0x06U
#define EBSTCON 0x07U
#define EBSTCSL 0x08U
#define EBSTCSH 0x09U
#define MISTAT  0x0AU
#define EREVID  0x12U
#define ECOCON  0x15U
#define EFLOCON 0x17U
#define EPAUSL  0x18U
#define EPAUSH  0x19U

/* Bit defines */
// EIE
#define INTIE  7U
#define PKTIE  6U
#define DMAIE  5U
#define LINKIE 4U
#define TXIE   3U
#define WOLIE  2U // Deprecated, do not use
#define TXERIE 1U
#define RXERIE 0U
// EIR
#define PKTIF  6U
#define DMAIF  5U
#define LINKIF 4U
#define TXIF   3U
#define WOLIF  2U // Deprecated, do not use
#define TXERIF 1U
#define RXERIF 0U
// ESTAT
#define INT     7U
#define BUFER   6U
#define LATECOL 4U
#define RXBUSY  2U
#define TXABRT  1U
#define CLKRDY  0U
// ECON2
#define AUTOINC 7U
#define PKTDEC  6U
#define PWRSV   5U
#define VRPS    3U
// ECON1
#define TXRST  7U
#define RXRST  6U
#define DMAST  5U
#define CSUMEN 4U
#define TXRTS  3U
#define RXEN   2U
#define BSEL1  1U
#define BSEL0  0U
// EWOLIE // Deprecated, do not use
#define UCWOLIE 7U
#define AWOLIE  6U
#define PMWOLIE 4U
#define MPWOLIE 3U
#define HTWOLIE 2U
#define MCWOLIE 1U
#define BCWOLIE 0U
// EWOLIR // Deprecated, do not use
#define UCWOLIF 7U
#define AWOLIF  6U
#define PMWOLIF 4U
#define MPWOLIF 3U
#define HTWOLIF 2U
#define MCWOLIF 1U
#define BCWOLIF 0U
// ERXFCON
#define UCEN  7U
#define ANDOR 6U
#define CRCEN 5U
#define PMEN  4U
#define MPEN  3U
#define HTEN  2U
#define MCEN  1U
#define BCEN  0U
// MACON1
#define TXPAUS  3U
#define RXPAUS  2U
#define PASSALL 1U
#define MARXEN  0U
// MACON2 // Deprecated, do not use
#define MARST   7U
#define RNDRST  6U
#define MARXRST 3U
#define RFUNRST 2U
#define MATXRST 1U
#define TFUNRST 0U
// MACON3
#define PADCFG2 7U
#define PADCFG1 6U
#define PADCFG0 5U
#define TXCRCEN 4U
#define PHDREN  3U
#define HRFMEN  2U
#define FRMLNEN 1U
#define FULDPX  0U
// MACON4
#define DEFER   6U
#define BPEN    5U
#define NOBKOFF 4U
#define LONGPRE 1U // Deprecated, do not use
#define PUREPRE 0U // Deprecated, do not use
// MAPHSUP // Deprecated, do not use
#define RSTINTFC 7U
#define RSTRMII  3U
// MICON // Deprecated, do not use
#define RSTMII 7U
// MICMD
#define MIISCAN 1U
#define MIIRD   0U
// EBSTCON
#define PSV2   7U
#define PSV1   6U
#define PSV0   5U
#define PSEL   4U
#define TMSEL1 3U
#define TMSEL0 2U
#define TME    1U
#define BISTST 0U
// MISTAT
#define NVALID 2U
#define SCAN   1U
#define BUSY   0U
// ECOCON
#define COCON2 2U
#define COCON1 1U
#define COCON0 0U
// EFLOCON
#define FULDPXS 2U
#define FCEN1   1U
#define FCEN0   0U
// PHCON1
#define PRST    7U
#define PLOOPBK 6U
#define PPWRSV  3U
#define PDPXMD  0U
// PHSTAT1
#define PFDPX  4U
#define PHDPX  3U
#define LLSTAT 2U
#define JBSTAT 1U
// PHCON2
#define FRCLNK 6U
#define TXDIS  5U
#define JABBER 2U
#define HDLDIS 0U
// PHSTAT2
#define TXSTAT  5U
#define RXSTAT  4U
#define COLSTAT 3U
#define LSTAT   2U
#define DPXSTAT 1U
#define PLRITY  5U
// PHIE
#define PLNKIE 4U
#define PGEIE  1U
// PHIR
#define PLNKIF 4U
#define PGIF   2U
// PHLCON
#define LACFG3 3U
#define LACFG2 2U
#define LACFG1 1U
#define LACFG0 0U
#define LBCFG3 7U
#define LBCFG2 6U
#define LBCFG1 5U
#define LBCFG0 4U
#define LFRQ1  3U
#define LFRQ0  2U
#define STRCH  1U
// Control byte bit defines 
#define PHUGEEN   3U
#define PPADEN    2U
#define PCRCEN    1U
#define POVERRIDE 0U
