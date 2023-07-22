#ifndef ESP32PWMSERVO_H
#define ESP32PWMSERVO_H

#include "Servo.h"
#include <Arduino.h>
void PWMServo_init();
void SetPWMServo(int id, int pul, int duration);

#endif
