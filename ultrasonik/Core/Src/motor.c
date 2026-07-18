#include "motor.h"

void Motor_Init(Motor_t* m)
{
    // STBY управляется отдельно в main, здесь только старт PWM
    HAL_TIM_PWM_Start(m->htim, m->pwm_channel);
    Motor_Stop(m);
}

void Motor_Set(Motor_t* m, MotorDir_t dir, uint16_t speed_pct)
{
    if (speed_pct > 100) speed_pct = 100;
    uint32_t duty = (m->max_duty * speed_pct) / 100;

    switch (dir)
    {
        case MOTOR_FORWARD:
            HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
            break;

        case MOTOR_BACKWARD:
            HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_SET);
            break;

        case MOTOR_STOP:
            HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
            duty = 0;
            break;

        case MOTOR_BRAKE:
            HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_SET);
            duty = 0;
            break;
    }

    __HAL_TIM_SET_COMPARE(m->htim, m->pwm_channel, duty);
}

void Motor_Stop(Motor_t* m)
{
    Motor_Set(m, MOTOR_STOP, 0);
}
