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
// 1400 (0.467ms)
#define MIN_ANGLE                                                   1400
// 7304 (2.435ms)
#define MAX_ANGLE                                                   7304
// 4352 (1.451ms)
#define MIDDLE_ANGLE                                                4352

// MAX-MIN/(180/15)
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
 * TA0 in PWM mode using CCR2 with reset/set. Sources SMCLK with a divider of 1
 *
 * TA1 in up mode using CCR0. Sources SMCLK with a divider of 2
 *      CCR0 interrupts are enabled.
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
 *          15° for every RPM, which means RPM should range from -6 to 6.
 *
 * \return None
 */
extern void update_servo(int RPM);

#ifdef __cplusplus
}
#endif

#endif /* MOTORS_H_ */
