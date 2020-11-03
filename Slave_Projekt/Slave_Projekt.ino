#include <Wire.h>             //Kommunikeerimine Master Arduinoga
#include<Servo.h>             //Servomootor 

const int GREEN_5 = 12;
const int GREEN_6 = 10;
const int GREEN_7 = 9;  
const int RED_5 = 13;            
const int RED_6 = 11; 
const int RED_7 = 8;   
const int SERVO = 7;   
const int BRIGHTNESS_MAX = 255;
const int BRIGHTNESS_MIN = 0;   
Servo Myservo;
void setup()
{
  Wire.begin(4);                //Kahe Arduino vaheline ühendus
  Wire.onReceive(receiveEvent); //Saadetise registreerimine
  Serial.begin(9600);           //Avab porti
  pinMode(SERVO,INPUT);
  Myservo.attach(SERVO);
}

void loop()
{
  delay(100);
}

void receiveEvent(){
  int x = Wire.read();          //Arduino loeb saadetud baiti ja võtab selle endale muutujuaks
  Serial.println(x);            
  switch(x){
    case 5:
      analogWrite(GREEN_5, BRIGHTNESS_MAX);     //Viienda LEDi õmber lülitamine
      analogWrite(RED_5, BRIGHTNESS_MIN);       
    break; 
    case 6:
      analogWrite(GREEN_6, BRIGHTNESS_MAX);      //Kuues ja seitsmes LED
      analogWrite(RED_6, BRIGHTNESS_MIN);
      analogWrite(GREEN_7, BRIGHTNESS_MAX);
      analogWrite(RED_7, BRIGHTNESS_MIN);        
      Myservo.write(70);                          //Servo liigutamine
    break; 
    case 8:
      analogWrite(GREEN_5, BRIGHTNESS_MAX);       //LEDide vilgutamise funktsiooni osa
      analogWrite(GREEN_6, BRIGHTNESS_MAX);
    break;
    case 9:
      analogWrite(RED_5, BRIGHTNESS_MAX);         //LEDide vilgutamise funktsiooni osa
      analogWrite(RED_6, BRIGHTNESS_MAX);
    break;
    case 10:                                      //LEDide väljalülitamise funktsiooni osa
      analogWrite(GREEN_5, BRIGHTNESS_MIN);
      analogWrite(GREEN_6, BRIGHTNESS_MIN);
      analogWrite(RED_5, BRIGHTNESS_MIN);
      analogWrite(RED_6, BRIGHTNESS_MIN);
    break;
    case 11:                                       //LED reset funktsiooni osa
      Myservo.write(10);
      analogWrite(GREEN_5, BRIGHTNESS_MIN);
      analogWrite(GREEN_6, BRIGHTNESS_MIN);
      analogWrite(GREEN_7, BRIGHTNESS_MIN);
      analogWrite(RED_5, BRIGHTNESS_MAX);
      analogWrite(RED_6, BRIGHTNESS_MAX);
      analogWrite(RED_7, BRIGHTNESS_MAX);
    break;
  }

}
