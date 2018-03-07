/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "pitches.h"



const int buttonPin = 8;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
Servo myservo;               // create servo object to control a servo
                             // twelve servo objects can be created on most boards
bool directie = 0;
int pos = 0;                 // variable to store the servo position
int trig=6;
int echo=7;
int duration=0;
int dist=0;
int limit = 50;
                            // notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };
                            // note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

unsigned long cMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;

void setup() {
  
  myservo.attach(12);  // attaches the servo on pin 12 to the servo object
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
}

void loop() {
  
      motor();
      use_sensor();
      //fantome();
      
}


void motor()
{
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
   
  if (buttonState == HIGH) 
  {
   if (pos < 180 && directie == 0)
     {
       myservo.write(pos);
       delay(15);
       pos++;
       
     }
     else
     {
       directie = 1;
     }

   if (pos > 0 && directie == 1)
     {
       myservo.write(pos);
       delay(15);
       pos--;
     }
     else
     {
       directie = 0;
     }
  }
  else
  {
    myservo.write(90);
  }

}

void play_sound()
{
  unsigned cMillis2 = millis();
  tone(13, NOTE_B2, 30);
  cMillis2 = millis();
   //after pauseBetweenNotes, stop the tone playing:
   if (cMillis2 - prevMillis2 >= 20)
    {
      noTone(13);
      prevMillis2 = cMillis2;
    }  
}

void use_sensor()
{
  digitalWrite(trig, LOW);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration=pulseIn(echo, HIGH);
  dist=duration/2/29;

  if (dist <= limit)
     play_sound();

  Serial.println(dist);
}



