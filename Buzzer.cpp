#include "Buzzer.h"  
#define GAP 400

Buzzer::Buzzer(byte pin)
{
    this->pin = pin;
}

void Buzzer::buzz(){
    digitalWrite(this->pin, HIGH);
    delay(GAP);
    this->off();
}
void Buzzer::off(){
 digitalWrite(this->pin, LOW);
}
void Buzzer::multipleBuzz(int n){
  for (int i = 0; i < n; i++)
  {
    this->buzz();
  }
}

void Buzzer::delay(int count){
     delay(count*GAP);
}

void Buzzer::init()
{
  pinMode(this->pin, OUTPUT);  // Set Buzzer - pin 19 as an output
  this->off();
}

Buzzer::~Buzzer()
{

}