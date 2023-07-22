#include "Arduino.h"
#include "SuctionNozzle.h"

const int pumpPin1 = 21;
const int pumpPin2 = 19;
const int valvePin1 = 18;
const int valvePin2 = 5;

void Nozzle_init(){
    pinMode(pumpPin1, OUTPUT);
    pinMode(pumpPin2, OUTPUT);
    pinMode(valvePin1, OUTPUT);
    pinMode(valvePin2, OUTPUT);
    digitalWrite(pumpPin1,LOW);
    digitalWrite(pumpPin2,LOW);
    digitalWrite(valvePin1,LOW);
    digitalWrite(valvePin2,LOW);  
}

void Pump_on(){
    digitalWrite(pumpPin1,LOW);
    digitalWrite(pumpPin2,HIGH);
}

void Valve_on(){
    digitalWrite(pumpPin1,LOW);
    digitalWrite(pumpPin2,LOW);
    digitalWrite(valvePin1,LOW);
    digitalWrite(valvePin2,HIGH);
}

void Valve_off(){
    digitalWrite(valvePin1,LOW);
    digitalWrite(valvePin2,LOW);
}
