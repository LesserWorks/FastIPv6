#include <FastIPv6.h>
#ifdef USE_ENC28J60
  #include <ENC28J60_functions.h>
  #include <ENC28J60_registers.h>
#else
  #include <ENCX24J600_registers.h>
#endif /* USE_ENC28J60 */
extern void solicitRouter(void) // Visible to other files
{
  return;
}
// Put local functions with static prototype and function here.
