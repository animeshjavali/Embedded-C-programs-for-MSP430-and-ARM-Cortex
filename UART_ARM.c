#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/eeprom.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
void main()
{
	 SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}


