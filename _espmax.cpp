#include "math.h"
#include "_espmax.h"
#include "Arduino.h"

float L2_SQUARE = L2*L2;
float L3_SQUARE = L3*L3;
float DOUBLE_PI = M_PI*2.0;

//求正解
float* forward(float joints[3], float* pos){
    float alpha1 = joints[0]*(M_PI/180);
    float alpha2 = joints[1]*(M_PI/180);
    float alpha3 = joints[2]*(M_PI/180);
    alpha1 += 150*(M_PI/180);
    if(alpha1 > DOUBLE_PI) alpha1 = alpha1 - DOUBLE_PI;
    float beta = alpha2 - alpha3;
    float side_beta = sqrt(L2_SQUARE + L3_SQUARE - (2.0 * L2 * L3 *cos(beta))); 
    float cos_gamma = ((side_beta*side_beta+ L2_SQUARE) - L3_SQUARE) / (2.0 * side_beta * L2);
    if(cos_gamma > 1.0) cos_gamma = 1.0;
    float gamma = acos(cos_gamma);
    float alpha_gamma = M_PI - alpha2;
    float alpha = alpha_gamma - gamma;
    float z = side_beta*sin(alpha);
    float r = sqrt(side_beta*side_beta - z * z);
    z = z + L0;
    r = r + L1 + L4;
    float x = r * cos(alpha1);
    float y = r * sin(alpha1);
    pos[0] = -x;
    pos[1] = y;
    pos[2] = z;
    return pos;
}

//求逆解
float* inverse(float pos[3], float* ang){
    float x = -pos[0];
    float y = pos[1];
    float z = pos[2];
    float theta1  = 0.0;
    if(x == 0.0){
        if(y >= 0.0)theta1 = M_PI / 2.0;
        else theta1 = M_PI / 2.0 * 3.0;
    }
    else{
        if(y == 0.0){
            if(x > 0.0)theta1 = 0.0;
            else theta1 = M_PI;}
        else{
            if(x < 0.0)theta1 = atan(y / x) + M_PI;
            else theta1 = atan(y / x) + DOUBLE_PI;}
    }
    float r = sqrt(x*x + y*y) - L1 - L4; //旋转半径
    z = z - L0;
    if(sqrt(r*r + z*z) > (L2 + L3)){
        Serial.print("r: ");
        Serial.println(r);
        Serial.print(L2);
        Serial.println(L3);
    }
    float alpha = atan(z / r);
    //余弦定理求各关节夹角
    float beta = acos((L2_SQUARE + L3_SQUARE - (r*r + z*z)) / (2.0 * L2 * L3));
    float gamma = acos((L2_SQUARE + (r*r + z*z - L3_SQUARE)) / (2.0 * L2 * sqrt(r*r + z*z)));
    float theta2 = M_PI - (alpha + gamma);
    float theta3 = M_PI - (alpha + beta + gamma);
    //根据需要将角度进行一下偏转，这里将底盘旋转的起始处定为-120度，将坐标系旋转
    float angles = degrees(theta1);
    if(angles <= 30.0) angles += 360.0;
    float angle1 = angles - 150.0;
    float angle2 = degrees(theta2);
    float angle3 = degrees(theta3);
    ang[0] = angle1;
    ang[1] = angle2;
    ang[2] = angle3; 
    return ang;  
}

//脉冲转角度
float* pulse_to_deg(float pul[3], float* ang){
    for(int i=0; i<3; i++){
        if(pul[i]<0|pul[i]>1000){
            Serial.print("Invalid pulse:");
            Serial.println(pul[i]);}
    }
    float angle1 = pul[0] * 240.0 / 1000.0; //0~1000 to 0~240
    float angle2 = pul[1] * -240.0 / 1000.0 + 210.0; //0~1000 to 210~-30
    float angle3 = pul[2] * 240.0 / 1000.0 - 120.0; //0~1000 to -120~120
    ang[0] = angle1;
    ang[1] = angle2;
    ang[2] = angle3; 
    return ang;
}

//角度转脉冲
float* deg_to_pulse(float ang[3], float* pul){
    for(int i=0; i<3; i++){
        if(ang[i]<0.0|ang[i]>240.0){
            Serial.print("Invalid angle:");
            Serial.println(ang[i]);}
    }
    float pulse1 = ang[0]*1000.0 / 240.0;
    float pulse2 = (ang[1] - 210.0) * 1000.0 / -240.0;
    float pulse3 = (ang[2] + 120.0) * 1000.0 / 240.0;
    pul[0] = pulse1;
    pul[1] = pulse2;
    pul[2] = pulse3;
    return pul;
}
