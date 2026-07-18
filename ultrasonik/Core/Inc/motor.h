#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f1xx_hal.h"

// Дескриптор мотора
typedef struct {
    GPIO_TypeDef* in1_port;
    uint16_t      in1_pin;
    GPIO_TypeDef* in2_port;
    uint16_t      in2_pin;
    TIM_HandleTypeDef* htim;
    uint32_t      pwm_channel;
    uint32_t      max_duty;  // = ARR + 1 (1000)
} Motor_t;

typedef enum {
    MOTOR_FORWARD,
    MOTOR_BACKWARD,
    MOTOR_STOP,
    MOTOR_BRAKE
} MotorDir_t;

void Motor_Init  (Motor_t* m);
void Motor_Set   (Motor_t* m, MotorDir_t dir, uint16_t speed_pct); // speed 0–100
void Motor_Stop  (Motor_t* m);

#endif
