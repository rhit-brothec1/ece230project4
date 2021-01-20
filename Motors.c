/*
 * Motors.c
 *
 *  Created on: Jan 17, 2021
 *      Author: Cooper Brotherton
 */

/* DriverLib Includes */
#include <Motors.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Timer A0 PWM config for servo
// 50 Hz period, start w/ arm in middle
Timer_A_PWMConfig pwmConfig = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                TIMER_A_CLOCKSOURCE_DIVIDER_1,
                                SERVO_PERIOD,
                                TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                TIMER_A_OUTPUTMODE_RESET_SET,
                                MIDDLE_ANGLE };

extern void Motors_init(void)
{
    MAP_GPIO_setAsOutputPin(MOTOR_PORT, MOTOR_PINS);
    MAP_GPIO_setOutputLowOnPin(MOTOR_PORT, MOTOR_PINS);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(
            SERVO_PORT, SERVO_PIN, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,                      // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_2,          // SMCLK/2 = 1.5MHz
            RPM_PERIOD,                             // 1 RPM tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,     // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
            };

    /* Configuring Timer_A1 for Up Mode */
    MAP_Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);

    MAP_Interrupt_enableInterrupt(INT_TA2_0);
    MAP_Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    MAP_Timer_A_setCompareValue(TIMER_A2_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                0);
}

void update_motor(int RPM)
{
    // CCR0 <- RPM_PERIOD / RPM
    MAP_Timer_A_setCompareValue(TIMER_A2_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                RPM_PERIOD / abs(RPM));
}

extern void update_servo(int RPM)
{
    pwmConfig.dutyCycle = MIDDLE_ANGLE + (RPM * FIFTEEN_DEGREE);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
}
