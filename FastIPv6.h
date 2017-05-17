/* Uncomment ONE of the following depending on what PHY interface you are using. */
//#define USE_ENC28J60
//#define USE_ENCX24J600
#ifdef USE_ENC28J60
#include <ENC28J60_registers.h>
#else
#include <ENCX24J600_registers.h>
#endif


extern void WriteReg(uint8_t register, uint8_t data);
