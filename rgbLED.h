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
 * \return None
 */
extern void RGBLED_init(void);

/*!
 * \brief This function toggles the LED at the given pin
 *
 * This function changes the state of the LED at the pin.
 *
 * \param pin is the pin to have its LED toggled
 *
 * \return None
 */
extern void RGBLED_togglePin(int pin);

/*!
 * \brief This function turns off LED2
 *
 * \return None
 */
extern void RGBLED_turnOff();

/*!
 * \brief This function turns on only one LED
 *
 * This function turns on the LEd at the given pin and turns off the rest.
 *
 * \param pin is the pin which will have its LED on. All others will be off.
 *          Valid values are:
 *          - \b 0 (P2.0 = Red)
 *          - \b 1 (P2.1 = Green)
 *          - \b 2 (P2.2 = Blue)
 *
 * \return None
 */
extern void RGBLED_turnOnOnlyPin(int pin);

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
