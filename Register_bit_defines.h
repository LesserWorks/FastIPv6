/* Bit defines for 8 bit registers */
// ESTAT
#define PKTCNT0 0U
#define PKTCNT1 1U
#define PKTCNT2 2U
#define PKTCNT3 3U
#define PKTCNT4 4U
#define PKTCNT5 5U
#define PKTCNT6 6U
#define PKTCNT7 7U
#define PHYLNK  0U
#define PHYDPX  2U
#define CLKRDY  4U
#define RXBUSY  5U
#define FCIDLE  6U
#define INT     7U
// EIR
#define PCFULIF 0U
#define RXABTIF 1U
#define TXABTIF 2U
#define TXIF    3U
#define DMAIF   5U
#define PKTIF   6U
#define LINKIF  3U
#define AESIF   4U
#define HASHIF  5U
#define MODEXIF 6U
#define CRYPTEN 7U
// ECON1
#define RXEN    0U
#define TXRTS   1U
#define DMANOCS 2U
#define DMACSSD 3U
#define DMACPY  4U
#define DMAST   5U
#define FCOP0   6U
#define FCOP1   7U
#define PKTDEC  0U
#define AESOP0  1U
#define AESOP1  2U
#define AESST   3U
#define HASTLST 4U
#define HASHOP  5U
#define HASHEN  6U
#define MODEXST 7U
// ETXSTAT
#define COLCNT0 0U
#define COLCNT1 1U
#define COLCNT2 2U
#define COLCNT2 2U
#define CRCBAD  4U
#define DEFER   7U
#define EXDEFER 0U
#define MAXCOL  1U
#define LATECOL 2U
// ERXFCON
#define BCEN    0U
#define MCEN    1U
#define NOTMEEN 2U
#define UCEN    3U
#define RUNTEN  4U
#define RENTEEN 5U
#define CRCEN   6U
#define CRCEEN  7U
#define PMEN0   0U
#define PMEN1   1U
#define PMEN2   2U
#define PMEN3   3U
#define NOTPM   4U
#define MPEN    6U
#define HTEN    7U
// MACON1
#define PASSALL 1U
#define RXPAUS  2U
#define LOOPBK  4U
// MACON2
#define FULFPX  0U
#define HFRMEN  2U
#define PHDREN  3U
#define TXCRCEN 4U
#define PADCFG0 5U
#define PADCFG1 6U
#define PADCFG2 7U
#define NOBKOFF 4U
#define BPEN    5U
#define DEFER   6U
// MABBIPG
#define BBIPG0 0U
#define BBIPG1 1U
#define BBIPG2 2U
#define BBIPG3 3U
#define BBIPG4 4U
#define BBIPG5 5U
#define BBIPG6 6U
// MAIPG
#define IPG0 0U
#define IPG1 1U
#define IPG2 2U
#define IPG3 3U
#define IPG4 4U
#define IPG5 5U
#define IPG6 6U
// MACLCON
#define MAXRET0 0U
#define MAXRET1 1U
#define MAXRET2 2U
#define MAXRET3 3U
// MICMD
#define MIIRD   0U
#define MIISCAN 1U
// MIREGADR
#define PHREG0 0U
#define PHREG1 1U
#define PHREG2 2U
#define PHREG3 3U
#define PHREG4 4U
// MISTAT
#define BUSY   0U
#define SCAN   1U
#define NVALID 2U
// ECON2
#define AESLEN0 0U
#define AESLEN1 1U
#define MODLEN0 2U
#define MODLEN1 3U
#define ETHRST  4U
#define RXRST   5U
#define TXRST   6U
#define AUTOFC  7U
#define COCON0  0U
#define COCON1  1U
#define COCON2  2U
#define COCON3  3U
#define SHA1MD5 4U
#define TXMAC   5U
#define STRCH   6U
#define ETHEN   7U
// ERXWM
#define RXEWM0 0U
#define RXEWM1 1U
#define RXEWM2 2U
#define RXEWM3 3U
#define RXEWM4 4U
#define RXEWM5 5U
#define RXEWM6 6U
#define RXEWM7 7U
#define RXFWM0 0U
#define RXFWM1 1U
#define RXFWM2 2U
#define RXFWM3 3U
#define RXFWM4 4U
#define RXFWM5 5U
#define RXFWM6 6U
#define RXFWM7 7U
// EIE
#define PCFULIE 0U
#define RXABTIE 1U
#define TXABTIE 2U
#define TXIE    3U
#define DMAIE   5U
#define PKTIE   6U
#define LINKIE  3U
#define AESIE   4U
#define HASHIE  5U
#define MODEXIE 6U
#define INTIE   7U
// EIDLED
#define REVID0 0U
#define REVID1 1U
#define REVID2 2U
#define REVID3 3U
#define REVID4 4U
#define DEVID0 5U
#define DEVID1 6U
#define DEVID2 7U
#define LBCFG0 0U
#define LBCFG1 1U
#define LBCFG2 2U
#define LBCFG3 3U
#define LACFG0 4U
#define LACFG1 5U
#define LACFG2 6U
#define LACFG3 7U
// PHCON1
#define PFULDPX 0U
#define RENEG   1U
#define PSLEEP  3U
#define ANEN    4U
#define SPD100  5U
#define PLOOKBK 6U
#define PRST    7U
// PHSTAT1
#define EXTREGS 0U
#define LLSTAT  2U
#define ANABLE  3U
#define LRFAULT 4U
#define ANDONE  5U
#define HALF10  3U
#define FULL10  4U
#define HALF100 5U
#define FULL100 6U
// PHANA
#define ADIEEE0 0U
#define ADIEEE1 1U
#define ADIEEE2 2U
#define ADIEEE3 3U
#define ADIEEE4 4U
#define AD10    5U
#define AD10FD  6U
#define AD100   7U
#define AD100FD 0U
#define ADPAUS0 2U
#define ADPAUS1 3U
#define ADFAULT 5U
#define ADNP    7U
// PHANLPA
#define LPIEEE0 0U
#define LPIEEE1 1U
#define LPIEEE2 2U
#define LPIEEE3 3U
#define LPIEEE4 4U
#define LP10    5U
#define LP10FD  6U
#define LP100   7U
#define LP100FD 0U
#define LP100T4 1U
#define LPPAUS0 2U
#define LPPAUS1 3U
#define LPFAULT 5U
#define LPACK   6U
#define LPNP    7U
// PHANE
#define LPANABL 0U
#define LPARCD  1U
#define PDFLT   4U
// PHCON2
#define EDSTAT  1U
#define FRCLNK  2U
#define EDTHRES 3U
#define EDPWRDN 5U
// PHSTAT2
#define PLRITY 4U
// PHSTAT3
#define SPDDPX0 2U
#define SPDDPX1 3U
#define SPDDPX2 4U
