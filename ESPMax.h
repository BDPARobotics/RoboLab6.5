#ifndef ESPMAX_H
#define ESPMAX_H

void ESPMax_init(void);
int set_servo_in_range(int servo_id, int p, int duration);
float* position_to_pulses(float pos[3], float* pul);
float* pulses_to_position(float pul[3], float* pos);
int set_position(float pos[3], int duration);
void set_position_with_speed(float pos[3], int speeds);
int set_position_relatively(float values[3], int duration);
void go_home(int duration);
void teaching_mode(void);
float* read_position(float* pos);

#endif
