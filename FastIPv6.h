/* Uncomment ONE of the following depending on what PHY interface you are using. */
//#define USE_ENC28J60
//#define USE_ENCX24J600
#ifndef FAST_IPv6_H // Include guard
#define FAST_IPv6_H

#ifdef USE_ENC28J60
#include <ENC28J60_registers.h>
#else
#include <ENCX24J600_registers.h>
#endif /* USE_ENC28J60 */
#endif /* FAST_IPv6_H */

/* Functions visible to other files. */
extern void solicitRouter(uint8_t registerName, uint8_t data);

