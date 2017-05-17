/* Uncomment ONE of the following depending on what PHY interface you are using. */
//#define USE_ENC28J60
//#define USE_ENCX24J600
#ifndef FASTIPv6_H
#define FASTIPv6_H

#ifdef USE_ENC28J60
#include <ENC28J60_registers.h>
#else
#include <ENCX24J600_registers.h>
#endif
#endif


extern void solicitRouter(uint8_t registerName, uint8_t data);

