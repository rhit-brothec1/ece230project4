/*
 * Switches.h
 *
 *  Created on: Dec 18, 2020
 *  Edited on:  Jan 20, 2021
 *      Author: Cooper Brotherton
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define SWITCH_PORT                                                 GPIO_PORT_P1
#define SWITCH_PINS                                                 0x0012
#define S1_PIN                                                      GPIO_PIN1
#define S2_PIN                                                      GPIO_PIN4

/*!
 * \brief This function configures the switches as inputs
 *
 * This function configures P1.1 and P1.4 as input pins with pull-up resistors.
 * Port 1 interrupts are enabled.
 *
 * \return None
 */
extern void Switch_init(void);

#ifdef __cplusplus
}
#endif

#endif /* SWITCHES_H_ */
