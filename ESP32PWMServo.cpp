#include "ESP32PWMServo.h"

Servo servo1;
Servo servo2;
static const int servo1Pin = 15;
static const int servo2Pin = 4;

int stat = 0;
int init_pulse[2] = {500,500};

void PWMServo_init(){
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
}

void SetPWMServo(int id, int pul, int duration){
    if(0 < id & id < 3){
        if(pul < 500) pul = 500;
        if(pul > 2500) pul = 2500;
        if(stat){
            int pulse = init_pulse[id-1];
            int value = pul - pulse;
            int degree = duration / 20;
            int d = value / degree;
            for(int count=0; count<int(degree); count++){            
                pulse = int(pulse + d);
                if(id == 1)servo1.writeMicroseconds(pulse);    // 输出PWM
                else if(id == 2)servo2.writeMicroseconds(pulse); // 输出PWM
                delay(20);
            }
            init_pulse[id-1] = pul;
        }  
        else{
            if(id == 1)servo1.writeMicroseconds(pul); // 输出PWM
            else if(id == 2)servo2.writeMicroseconds(pul); // 输出PWM
            init_pulse[id-1] = pul;
            stat = 1;
        }
    }
}
