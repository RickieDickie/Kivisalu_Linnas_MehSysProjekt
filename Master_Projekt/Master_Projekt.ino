#include<Wire.h>          // Slave Arduinoga kommunikatsioon

const int button = 5;    
const int GREEN =  12; 
const int GREEN_2 = 10;
const int GREEN_3 = 8;
const int GREEN_4 = 6;
const int RED = 13;             
const int RED_2 = 11;            
const int RED_3 = 9; 
const int RED_4 = 7; 
int buttonState = 0; 

const int BRIGHTNESS_MAX = 255;             //Dioodi eredusenimetajad
const int BRIGHTNESS_MIN = 0;               

int counter = 0;                            // Et counter algaks nullist


void setup() {
                                             
  pinMode(8,INPUT);                         //
  
  Wire.begin();                              //teine arduino
  
  buttonState = digitalRead(button);  
  pinMode(GREEN, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}


void SendByWire(int x){                       // Slave Arduinole andmete saatmine
  Wire.beginTransmission(4);       
  Wire.write(x);              
  Wire.endTransmission();
  }

void flashLEDs(){
    for(int i = 0; i < 10 ; i++){               //Lõpus LEDide vilgutamise funktsioon
        turnOffLEDs();
        analogWrite(RED, BRIGHTNESS_MAX);
        analogWrite(RED_2, BRIGHTNESS_MAX);
        analogWrite(RED_3, BRIGHTNESS_MAX);
        analogWrite(RED_4, BRIGHTNESS_MAX);
        SendByWire(9);
        delay(100);
        turnOffLEDs();
        analogWrite(GREEN, BRIGHTNESS_MAX);
        analogWrite(GREEN_2, BRIGHTNESS_MAX);
        analogWrite(GREEN_3, BRIGHTNESS_MAX);
        analogWrite(GREEN_4, BRIGHTNESS_MAX);
        SendByWire(8);
        delay(100);
        }

    }


void turnOffLEDs(){                                     //LEDide välja lülitamise funktsioon
        analogWrite(GREEN, BRIGHTNESS_MIN);
        analogWrite(GREEN_2, BRIGHTNESS_MIN);
        analogWrite(GREEN_3, BRIGHTNESS_MIN);
        analogWrite(GREEN_4, BRIGHTNESS_MIN);
        analogWrite(RED, BRIGHTNESS_MIN);
        analogWrite(RED_2, BRIGHTNESS_MIN);
        analogWrite(RED_3, BRIGHTNESS_MIN);
        analogWrite(RED_4, BRIGHTNESS_MIN);
        SendByWire(10);
    }

void resetLEDs(){                                     // LEDide reseti funktsioon
        analogWrite(GREEN, BRIGHTNESS_MIN);
        analogWrite(GREEN_2, BRIGHTNESS_MIN);
        analogWrite(GREEN_3, BRIGHTNESS_MIN);
        analogWrite(GREEN_4, BRIGHTNESS_MIN);
        analogWrite(RED, BRIGHTNESS_MAX);
        analogWrite(RED_2, BRIGHTNESS_MAX);
        analogWrite(RED_3, BRIGHTNESS_MAX);
        analogWrite(RED_4, BRIGHTNESS_MAX);
        SendByWire(11);
  }
       



void loop() {                                           
  // put your main code here, to run repeatedly''
  int buttonState3 = digitalRead(button);               // Nupu sisendi lugemine
    if(counter == 0){                                 // Algasendi saavutamine
      resetLEDs();
      counter++;
      }
      
if(buttonState3 == HIGH){
    
    
  Serial.println(counter);
    switch(counter){
    case 1:
      analogWrite(GREEN, BRIGHTNESS_MAX);
      analogWrite(RED, BRIGHTNESS_MIN);
      counter++;
      break;
    case 2:
      analogWrite(GREEN_2, BRIGHTNESS_MAX);
      analogWrite(RED_2, BRIGHTNESS_MIN);
      counter++;
      break;
    case 3:
      analogWrite(GREEN_3, BRIGHTNESS_MAX);
      analogWrite(RED_3, BRIGHTNESS_MIN);
      counter++;
    break;
    case 4:
      analogWrite(GREEN_4, BRIGHTNESS_MAX);
      analogWrite(RED_4, BRIGHTNESS_MIN);
      counter++;
      break;    
    case 5:
      SendByWire(counter);                //Saadab Slave Arduinole counteri seisu
      counter++;
      break;    
    case 6:
      SendByWire(counter);                //Saadab Slave Arduinole counteri seisu
      flashLEDs();
      counter++;
      break; 
    case 7:
      counter = 0;
      break;  
  }
    delay(500);                    
  }
}



  
