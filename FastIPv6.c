#include <FastIPv6.h>
#include <avr/io.h>
#ifdef USE_ENC28J60
  #include <ENC28J60_functions.h>
  #include <ENC28J60_registers.h>
#elif defined(ENCX24J600_SPI)
  #include <ENCX24J600_functions.h>
  #include <ENCX24J600_SPI_registers.h>
#elif defined(ENCX24J600_PARALLEL)
  #include <ENCX24J600_PSP_registers.h>
#endif /* USE_ENC28J60 */
#ifdef USE_ENC28J60
  // put functions definitions for ENC28J60 here
#elif defined(ENCX24J600_SPI)
  // put function definitions for X24J600 SPI here
#elif defined(ENCX24J600_PARALLEL)
  // put function definitions for X24J600 PSP here
#endif /* USE_ENC28J60 */
