/*
 * Motors.h
 *
 *  Created on: Jan 17, 2021
 *      Author: Cooper Brotherton
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MOTOR_PINS                                                  0x00F0
#define MOTOR_PORT                                                  GPIO_PORT_P4
#define RPM_PERIOD                                                  21973
#define SERVO_PORT                                                  GPIO_PORT_P2
#define SERVO_PIN                                                   GPIO_PIN5

#define SERVO_PERIOD                                                60000
#define MIN_ANGLE                                                   1400
#define MAX_ANGLE                                                   7304
#define MIDDLE_ANGLE                                                4352
#define FIFTEEN_DEGREE                                              492

// Step sequences for different directions
#define CCW_HALFSTEP { 0b0001, 0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000, 0b1001 }
#define CW_HALFSTEP  { 0b1000, 0b1100, 0b0100, 0b0110, 0b0010, 0b0011, 0b0001, 0b1001 }
#define CCW_FULLSTEP { 0b0001, 0b0010, 0b0100, 0b1000 }
#define CW_FULLSTEP  { 0b1000, 0b0100, 0b0010, 0b0001 }

typedef enum _dir
{
    CCW, CW
} Direction;

/*!
 * \brief This function configures the pins and timers for the motor and servo
 *
 * This function configures P4.4, P4.5, P4.6, and P4.7 as output pins for
 * the motor and P2.5 as an output pin for the servo.
 *
 * TA0 in PWM mode using CCR2 with reset/set output mode.
 * Frequency of 50Hz with servo arm in middle position initially.
 *
 * TA2 in up mode using CCR0. CCR0 interrupts are enabled.
 * Period of 1 RPM, motor at stop initially.
 *
 * \return None
 */
extern void Motors_init(void);

/*!
 * \brief This function updates the motor based on the input
 *
 * This function updates the speed of the motor based on the input.
 *
 * \param RPM is the revolutions per minute the motor should be spinning at.
 *          The period of TA2 is adjusted according to the RPM, which changes
 *          its speed accordingly.
 *
 * \return None
 */
extern void update_motor(int RPM);

/*!
 * \brief This function updates the servo based on the input
 *
 *  This function updates the angle of the servo arm's position based on
 *  the RPM.
 *
 *  \param RPM is the revolutions per minute the motor should be spinning at.
 *          Based on the RPM, the servo will adjust its angle accordingly.
 *          15� for every RPM where 0� for 0 RPM.
 *
 * \return None
 */
extern void update_servo(int RPM);

#ifdef __cplusplus
}
#endif

#endif /* MOTORS_H_ */
