#ifndef ENC28J60_FUNCTIONS_H // Include guard
#define ENC28J60_FUNCTIONS_H
extern void WriteReg(const uint8_t registerName, const uint8_t data);

extern uint8_t ReadReg(const uint8_t registerName);

extern uint8_t ReadRegDelayed(const uint8_t registerName);

extern void SetRegBit(const uint8_t registerName, const uint8_t data);

extern void ClearRegBit(const uint8_t registerName, const uint8_t data);

extern void WritePHY(const uint8_t registerName, const uint8_t dataH, const uint8_t dataL);

extern uint16_t ReadPHY(const uint8_t registerName);

extern void StartPHYscan(const uint8_t registerName);

extern uint8_t ReadPHYscan(const uint8_t whichByte);

extern void StopPHYscan(void);

extern void IPv6reset(const uint8_t resetType);

#endif /* ENC28J60_FUNCTIONS_H */
