# FastIPv6
This is an optimized webserver library for AVR. Initially, it will only support ATmega devices and the ENC28J60 ethernet controller. Perhaps in the future, support will be added for ATXmega devices and the ENC624J600 ethernet controller. It is called FastIPv6 because it will only support IPv6 and is highly optimized for speed by minimizing function call overhead, using the USART in SPI mode instead of the SPI hardware, and by writing everything from scratch.
