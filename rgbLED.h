/*
 * rgbLED.h
 *
 *  Created on: Dec 18, 2020
 *  Edited on:  Jan 20, 2021
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

#define RG_PERIOD                                                   3000

/*!
 * \brief This function configures LED2 pins as output pins
 *
 * This function configures P2.0, P2.1, and P2.2 as peripheral output pins for
 * the RGB LED, and initializes them to 'off'
 *
 * TA1 in PWM mode with CCR1 and CCR2 mapped to P2.0 and P2.1 respectively.
 * Frequency of 1kHz with green on, red off initially.
 *      CCR1 in toggle/set output mode, CCR2 in toggle/reset output mode.
 *
 * \return None
 */
extern void RGBLED_init(void);

/*!
 * \brief This function updates the duty cycles of the red and green LEDs
 *
 * This function updates the duty cycle of the PWM that control P2.0 and P2.1
 *
 * \param RPM is the revolutions per minute the motor should be spinning at.
 *          As the magnitude of the RPM increases, the percentage of the duty
 *          cycle for decreases linearly for green and increases linearly for red.
 *          0 RPM   - Green 100% duty cycle, Red 0% duty cycle
 *          3 RPM   - Green 50% duty cycle, Red 50% duty cycle
 *          6 RPM   - Green 0% duty cycle, Red 100% duty cycle
 *
 */
extern void update_LEDs(int RPM);

#ifdef __cplusplus
}
#endif

#endif /* RGBLED_H_ */
