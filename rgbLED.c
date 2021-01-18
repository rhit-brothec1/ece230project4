/*
 * rgbLED.c
 *
 *  Created on: Dec 18, 2020
 *  Edited on:  Jan 16, 2021
 *      Author: Cooper Brotherton
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "rgbLED.h"

void RGBLED_init(void)
{
    GPIO_setAsOutputPin(RGB_PORT, RGB_ALL_PINS);
    GPIO_setOutputLowOnPin(RGB_PORT, RGB_ALL_PINS);

    // TODO initialize timer for PWM
}

void RGBLED_togglePin(int pin)
{
    MAP_GPIO_toggleOutputOnPin(RGB_PORT, 1 << pin);
}

void RGBLED_turnOff()
{
    MAP_GPIO_setOutputLowOnPin(RGB_PORT, RGB_ALL_PINS);
}

void RGBLED_turnOnOnlyPin(int pin)
{
    int mask = 1 << pin;
    MAP_GPIO_setOutputLowOnPin(RGB_PORT, ~mask);
    MAP_GPIO_setOutputHighOnPin(RGB_PORT, mask);
}

void update_LEDs(int RPM)
{
    // TODO
    int a = abs(RPM);
}
