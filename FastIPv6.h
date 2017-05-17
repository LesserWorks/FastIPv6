#ifndef FAST_IPv6_H // Include guard
#define FAST_IPv6_H
/* Uncomment ONE of the following depending on what ethernet controller you are using. */
//#define USE_ENC28J60
//#define USE_ENCX24J600




/* Functions visible to other files. */
extern void solicitRouter(uint8_t registerName, uint8_t data);


#endif /* FAST_IPv6_H */
