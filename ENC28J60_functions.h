#ifndef ENC28J60_FUNCTIONS_H // Include guard
#define ENC28J60_FUNCTIONS_H
extern void WriteReg(uint8_t registerName, uint8_t data);
extern uint8_t ReadReg(uint8_t registerName);
#endif /* ENC28J60_FUNCTIONS_H */
