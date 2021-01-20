/*
 * Author:      Cooper Brotherton
 * Date:        January 20, 2021
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
 *       S2-->|P1.4        P2.5  |---> Servo
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
 * This function sets P1.1 and P1.4 as inputs with interrupts, P4.4, P4.5, P4.6,
 * and P4.7 as outputs, maps P2.5 to TA0CCR2 and P2.0 and P2.1 to TA1CCR1 and
 * TA1CCR2 respectively.
 *
 * It also starts TA0 and TA1 in PWM mode and TA2 in up mode with interrupts.
 *
 * Interrupts and sleeping on ISR exit are enabled.
 *
 * \return None
 */
void setup(void)
{
    MAP_WDT_A_holdTimer();

    Switch_init();
    RGBLED_init();
    Motors_init();

    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();
}

/*!
 * \brief The function sets up the device and goes into LPM
 *
 * This function calls the function to set up the device then puts the controller
 * in low power mode
 *
 * \return None
 */
int main(void)
{

    setup();

    while (1)
    {
        PCM_gotoLPM0();
    }
}

/*!
 * \brief This function handles interrupts from port 1
 *
 * This function increments the RPM (up to 6) when S2 is pressed and decrements the
 * RPM (down to -6) when S1 is pressed. It also calls functions for the servo, motor
 * and RGB LED to update based on the RPM.
 *
 * A positive RPM correlates to clockwise rotation, a negative RPM correlates to
 * counterclockwise rotation.
 *
 * \return None
 */
void PORT1_IRQHandler(void)
{
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    if (status & S1_PIN)
    {
        if (RPM > -6)
            RPM--;
    }
    if (status & S2_PIN)
    {
        if (RPM < 6)
            RPM++;
    }
    // Update outputs based on RPM
    update_servo(RPM);
    update_motor(RPM);
    update_LEDs(RPM);
    // Change direction based on RPM
    direction = RPM < 0 ? CCW : CW;

    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
}

/*!
 * \brief This function rotates the stepper motor
 *
 * This function rotates the stepper motor in the appropriate direction by loading
 * the next half-step sequence step into the output pins associated with the motor.
 *
 * \return None
 */
void TA2_0_IRQHandler(void)
{
    P4->OUT = (P4->OUT & 0x0F) + (stepperSequence[direction][currentStep] << 4);
    currentStep = (currentStep + 1) % 8;
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
                                         TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
