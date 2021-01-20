/*
 * Switches.c
 *
 *  Created on: Dec 18, 2020
 *  Edited on:  Jan 16, 2021
 *      Author: Cooper Brotherton
 */
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Switches.h"

void Switch_init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(SWITCH_PORT, SWITCH_PINS);
    GPIO_clearInterruptFlag(SWITCH_PORT, SWITCH_PINS);
    GPIO_enableInterrupt(SWITCH_PORT, SWITCH_PINS);
    Interrupt_enableInterrupt(INT_PORT1);
}
