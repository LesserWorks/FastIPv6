/* SPI opcodes */
#define B0SEL      0b11000000U
#define B1SEL      0b11000010U
#define B2SEL      0b11000100U
#define B3SEL      0b11000110U
#define SETETHRST  0b11001010U
#define FCDISABLE  0b11100000U
#define FCSINGLE   0b11100010U
#define FCMULTIPLE 0b11100100U
#define FCCLEAR    0b11100110U
#define SETPKTDEC  0b11001100U
#define DMASTOP    0b11010010U
#define DMACKSUM   0b11011000U
#define DMACKSUMS  0b11011010U
#define DMACOPY    0b11011100U
#define DMACOPYS   0b11011110U
#define SETTXRTS   0b11010100U
#define ENABLERX   0b11101000U
#define DISABLERX  0b11101010U
#define SETEIE     0b11101100U
#define CLREIE     0b11101110U
#define RBSEL      0b11001000U
#define WGPRDPT    0b01100000U
#define RGPRDPT    0b01100010U
#define WRXRDPT    0b01100100U
#define RRXRDPT    0b01100110U
#define WUDARDPT   0b01101000U
#define RUDARDPT   0b01101010U
#define WGPWRPT    0b01101100U
#define RGPWRPT    0b01101110U
#define WRXWRPT    0b01110000U
#define RRXWRPT    0b01110010U
#define WUDAWRPT   0b01110100U
#define RUDAWRPT   0b01110110U
#define RCR(address) (0b00011111U & (address))
#define WCR(address) ((0b00011111U & (address)) | 0b01000000U)
#define RCRU       0b00100000U
#define WCRU       0b00100010U
#define BFS(address) ((0b00011111U & (address)) | 0b10000000U)
#define BFC(address) ((0b00011111U & (address)) | 0b10100000U)
#define BFSU       0b00100100U
#define BFCU       0b00100110U
#define RGPDATA    0b00101000U
#define WGPDATA    0b00101010U
#define RRXDATA    0b00101100U
#define WRXDATA    0b00101110U
#define RUDADATA   0b00110000U
#define WUDADATA   0b00100010U
/* Registers */
#define ETXSTL
#define ETXSTH
#define ETXLENL
#define ETXLENH
#define ERXSTL
#define ERXSTH
#define ERXTAILL
#define ERXTAILH
#define ERXHEADL
#define ERXHEADH
#define EDMASTL
#define EDMASTH
#define EDMALENL
#define EDAMLENH
#define EDMADSTL
#define EDMADSTH
#define EDMACSL
#define EDMACSH
#define ETXSTATL
#define ETXSTATH
#define ETXWIREL
#define ETXWRIEH
#define EUDASTL
#define EUDASTH
#define EUDANDL
#define EUDANDH
#define ESTATL
#define ESTATH
#define EIRL
#define EIRH
#define ECON1L
#define ECON1H
