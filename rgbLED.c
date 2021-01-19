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

// TODO maybe have two different PWM configs port mapped to LEDs?

void RGBLED_init(void)
{
    GPIO_setAsOutputPin(RGB_PORT, RGB_ALL_PINS);
    GPIO_setOutputLowOnPin(RGB_PORT, RGB_ALL_PINS);
    const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,
                                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                                            RG_PERIOD,
                                            TIMER_A_TAIE_INTERRUPT_ENABLE,
                                            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
                                            TIMER_A_DO_CLEAR };

    MAP_Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);

    const Timer_A_CompareModeConfig rgbCompare = {
            TIMER_A_CAPTURECOMPARE_REGISTER_1,
            TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,
            TIMER_A_OUTPUTMODE_SET_RESET, 0

    };

    Timer_A_initCompare(TIMER_A2_BASE, &rgbCompare);
    MAP_Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
    MAP_Interrupt_enableInterrupt(INT_TA2_0);
    MAP_Interrupt_enableInterrupt(INT_TA2_N);
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
    Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1,
                            500 * abs(RPM));

}
