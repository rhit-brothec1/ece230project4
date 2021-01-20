/*
 * Author:      Cooper Brotherton
 * Date:        January 16, 2021
 * Libraries:   GPIO and Timer A from DriverLib
 */
/******************************************************************************
 * MSP432 Project 4 ECE230 Winter 2020-2021
 *
 * Description: S1 and S2 control RPM and direction of stepper motor.
 *              Servo and RGB LED adjusted according to RPM.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|            P4.4  |---> Motor
 *          | |            P4.5  |---> Motor
 *          --|RST         P4.6  |---> Motor
 *            |            P4.7  |---> Motor
 *       S1-->|P1.1        P2.0  |---> LED2 red
 *            |            P2.1  |---> LED2 green
 *       S2-->|P1.4              |
 *            |                  |
 *******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "Switches.h"
#include "rgbLED.h"
#include "Motors.h"

uint8_t stepperSequence[2][8] = { CCW_HALFSTEP, CW_HALFSTEP };

uint8_t currentStep = 0;
Direction direction = CCW;
int8_t RPM = 0;

/*!
 * \brief This function sets up the device
 *
 * This function sets P1.1 and P1.4 as inputs with interrupts,
 * P4.4, P4.5, P4.6, P4.7 as outputs.
 * TODO update eventually
 *
 * \return None
 */
void setup(void)
{
    MAP_WDT_A_holdTimer();

    Switch_init();
//    RGBLED_init();
    Motors_init();

//    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();
}

int main(void)
{

    setup();

    while (1)
    {
//        MAP_PCM_gotoLPM0();
    }
}

// GPIO ISR
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // S1
    if (status & GPIO_PIN1)
    {
        if (RPM > -6)
        {
            RPM--;
        }
    }
    // S2
    if (status & GPIO_PIN4)
    {
        if (RPM < 6)
        {
            RPM++;
        }
    }
    update_servo(RPM);
    update_motor(RPM);
//    update_LEDs(RPM);
    // Change direction based on RPM
    direction = RPM < 0 ? CCW : CW;
}

// TA1 ISR
void TA2_0_IRQHandler(void)
{
    P4->OUT = (P4->OUT & 0x0F) + (stepperSequence[direction][currentStep] << 4);
    currentStep = (currentStep + 1) % 8;
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

//void TA2_0_IRQHandler(void)
//{
//    // turn on only red
//    RGBLED_turnOnOnlyPin(0);
//    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
//    TIMER_A_CAPTURECOMPARE_REGISTER_0);
////    Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1,
////                            500 * abs(RPM));
//}
//
//void TA2_N_IRQHandler(void)
//{
//
//    // turn on only green
//    RGBLED_turnOnOnlyPin(1);
//    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
//    TIMER_A_CAPTURECOMPARE_REGISTER_1);
//}
