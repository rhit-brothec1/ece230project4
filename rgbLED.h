/*
 * rgbLED.h
 *
 *  Created on: Dec 18, 2020
 *  Edited on:  Jan 16, 2021
 *      Author: Cooper Brotherton
 */

#ifndef RGBLED_H_
#define RGBLED_H_

#ifdef __cplusplus
extern "C" {
#endif

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define RGB_PORT                                                    GPIO_PORT_P2
#define RGB_ALL_PINS                                                0x0007
#define RGB_RED_PIN                                                 GPIO_PIN0
#define RGB_GREEN_PIN                                               GPIO_PIN1

#define RG_PERIOD                                                   3000
// 500 ticks/RPM

/*!
 * \brief This function configures LED2 pins as output pins
 *
 * This function configures P2.0, P2.1, and P2.2 as output pins for the RGB
 * LED2, and initializes them to 'off'
 *
 * TA1 in PWM mode with CCR1 and CCR2 mapped to P2.0 and P2.1 repsectively
 *      CCR1 in toggle/set, CCR2 in toggle/reset
 *      Interrupts are disabled
 *
 * \return None
 */
extern void RGBLED_init(void);

/*!
 * \brief This function updates the red and green LEDs on P2
 *
 * This function updates the duty cycle that control P2.0 and P2.1
 *
 * \param RPM is the revolutions per minute the motor should be spinning at.
 *          As the magnitude of the RPM increases, the percentage of the duty
 *          cycle for decreases for green and increases for red.
 *
 */
extern void update_LEDs(int RPM);

#ifdef __cplusplus
}
#endif

#endif /* RGBLED_H_ */
