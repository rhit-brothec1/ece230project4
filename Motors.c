/*
 * Motors.c
 *
 *  Created on: Jan 17, 2021
 *  Edited on: Jan 20, 2021
 *      Author: Cooper Brotherton
 */

/* DriverLib Includes */
#include <Motors.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

Timer_A_PWMConfig servo_PWMConfig = { TIMER_A_CLOCKSOURCE_SMCLK,
                                      TIMER_A_CLOCKSOURCE_DIVIDER_1,
                                      SERVO_PERIOD,
                                      TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                      TIMER_A_OUTPUTMODE_RESET_SET,
                                      MIDDLE_ANGLE };

extern void Motors_init(void)
{
    GPIO_setAsOutputPin(MOTOR_PORT, MOTOR_PINS);
    GPIO_setOutputLowOnPin(MOTOR_PORT, MOTOR_PINS);
    GPIO_setAsPeripheralModuleFunctionOutputPin(SERVO_PORT,
                                                SERVO_PIN,
                                                GPIO_PRIMARY_MODULE_FUNCTION);

    const Timer_A_UpModeConfig upConfig = { TIMER_A_CLOCKSOURCE_SMCLK,
                                            TIMER_A_CLOCKSOURCE_DIVIDER_2,
                                            RPM_PERIOD,
                                            TIMER_A_TAIE_INTERRUPT_DISABLE,
                                            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
                                            TIMER_A_DO_CLEAR };

    // Timer for stepper motor
    Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);
    Interrupt_enableInterrupt(INT_TA2_0);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    // PWM for servo
    Timer_A_generatePWM(TIMER_A0_BASE, &servo_PWMConfig);
    Timer_A_setCompareValue(TIMER_A2_BASE,
                            TIMER_A_CAPTURECOMPARE_REGISTER_0,
                            0);
}

void update_motor(int RPM)
{
    Timer_A_setCompareValue(TIMER_A2_BASE,
                            TIMER_A_CAPTURECOMPARE_REGISTER_0,
                            RPM_PERIOD / abs(RPM));
}

extern void update_servo(int RPM)
{
    servo_PWMConfig.dutyCycle = MIDDLE_ANGLE - (RPM * FIFTEEN_DEGREE);
    Timer_A_generatePWM(TIMER_A0_BASE, &servo_PWMConfig);
}
