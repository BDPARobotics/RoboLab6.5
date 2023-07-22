#ifndef _ESPMAX_H
#define _ESPMAX_H

#define L0      84.4
#define L1      8.14
#define L2      128.4
#define L3      138.0
#define L4      16.8

float* forward(float joints[3], float* pos);
float* inverse(float pos[3], float* ang);
float* pulse_to_deg(float pul[3], float* ang);
float* deg_to_pulse(float ang[3], float* pul);

#endif
