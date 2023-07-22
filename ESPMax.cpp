#include "ESPMax.h"
#include "_espmax.h"
#include "LobotSerialServoControl.h"

#define SERVO_SERIAL_RX   35
#define SERVO_SERIAL_TX   12
#define receiveEnablePin  13
#define transmitEnablePin 14
HardwareSerial HardwareSerial(2);
LobotSerialServoControl BusServo(HardwareSerial);

float ORIGIN[3] ={ 0, -(L1 + L3 + L4), (L0 + L2)};
float positions[3];

void ESPMax_init(){
    BusServo.OnInit();
    HardwareSerial.begin(115200,SERIAL_8N1,SERVO_SERIAL_RX,SERVO_SERIAL_TX);
}

int set_servo_in_range(int servo_id, int p, int duration){
    if(servo_id == 3 & p < 470) p = 470;
    if(servo_id == 2 & p > 700) p = 700;
    BusServo.LobotSerialServoMove(servo_id, p, duration);
    return int(1);
}

float* position_to_pulses(float pos[3], float* pul){
    float angles[3];
    inverse(pos,angles);
    deg_to_pulse(angles,pul);
    return pul;
}

float* pulses_to_position(float pul[3], float* pos){
    float joints[3];
    pulse_to_deg(pul,joints);
    forward(joints,pos);
    return pos;
}

int set_position(float pos[3], int duration){
    float x = pos[0];
    float y = pos[1];
    float z = pos[2];
    if(z > 255) z = 255;
    if(sqrt(x*x + y*y) < 50) return int(0);
    float angles[3];
    inverse(pos,angles);
    float pul[3];
    deg_to_pulse(angles,pul);
    for(int i=0; i<3; i++){
        positions[i] = pul[i];
        BusServo.LobotSerialServoMove(i+1,pul[i],duration);
        delay(2);
    }
    return int(1);
}

void set_position_with_speed(float pos[3], int speeds){
    float sum = 0.0;
    for(int i=0; i<3; i++){
        sum += (pos[i]-positions[i])*(pos[i]-positions[i]);
    }
    float distance = sqrt(sum);
    int duration = int(distance / speeds);
    set_position(pos, duration);
}

int set_position_relatively(float values[3], int duration){
    float x = positions[0];
    float y = positions[1];
    float z = positions[2];
    float dx = values[0];
    float dy = values[1];
    float dz = values[2];
    x += dx;
    y += dy;
    z += dz;
    float pos[3]={x,y,z};
    return set_position(pos, duration);  
}

void go_home(int duration){
    set_position(ORIGIN, duration);
}

void teaching_mode(){
    for(int i=1; i<4; i++){
        BusServo.LobotSerialServoUnload(i);
    }
}

float* read_position(float* pos){
    float pul[3];
    for(int i=0; i<3; i++){
        pul[i] = BusServo.LobotSerialServoReadPosition(i+1);
    }
    pulses_to_position(pul,pos);
}
