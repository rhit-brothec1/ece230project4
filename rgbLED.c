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

// PWM configs for LEDs
// TODO fix startup bug
Timer_A_PWMConfig pwmConfig1 = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                 TIMER_A_CLOCKSOURCE_DIVIDER_1,
                                 RG_PERIOD,
                                 TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                 TIMER_A_OUTPUTMODE_TOGGLE_SET,
                                 0 };

Timer_A_PWMConfig pwmConfig2 = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                 TIMER_A_CLOCKSOURCE_DIVIDER_1,
                                 RG_PERIOD,
                                 TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                 TIMER_A_OUTPUTMODE_TOGGLE_RESET,
                                 0 };

void RGBLED_init(void)
{
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(
            RGB_PORT, RGB_ALL_PINS, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setOutputLowOnPin(RGB_PORT, RGB_ALL_PINS);

    const uint8_t port_mapping[] = {
    //Port P2:
            PMAP_TA1CCR1A,
            PMAP_TA1CCR2A,
            PMAP_NONE, PMAP_NONE, PMAP_NONE, PMAP_TA0CCR2A,
            PMAP_NONE,
            PMAP_NONE };

    MAP_PMAP_configurePorts((const uint8_t*) port_mapping, PMAP_P2MAP, 1,
    PMAP_DISABLE_RECONFIGURATION);

    Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfig1);
    Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfig2);
}

void update_LEDs(int RPM)
{
    pwmConfig1.dutyCycle = abs(RPM) * 500;
    pwmConfig2.dutyCycle = abs(RPM) * 500;
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfig1);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfig2);
}
