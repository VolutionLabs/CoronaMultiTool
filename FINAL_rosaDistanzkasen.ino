
// Corona DistanzTool

//INFOS

// Abstandsmessung Ultraschall
// Distance = (Time x Speed of Sound in Air (340 m/s))/2
// ECHO of sound. A pulse is sent for about 10us to trigger the module. 
// After which the module automatically sends 8 cycles of 40 KHz ultrasound signal and checks its echo. 
// The signal after striking with an obstacle returns back and is captured by the receiver. 
// Thus the distance of the obstacle from the sensor is simply calculated by the formula given as
// Distance = (time x speed)/2.




// *********************************************************************+
#include "Seeed_BME280.h"
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"


// DISTANCE TOOLar

int const trigPin = 5; // lila
int const echoPin = 6; // weiß
int const ledPin = 7; // gelb
int const buzzPin = 8; // orange

// var Ultraschalll
long duration;
int distance;
int safetyDistance;
int ppm;
int safetyPpm;




// **********************************************************

// FUNCTIONS

void setup() {

  // Distance Tool
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  pinMode(buzzPin, OUTPUT); // buzz pin is output to control buzzer
  pinMode(ledPin, OUTPUT); 

  Serial.begin(115200); // serial communication
 
  

}

void loop() {



// Ultrasound
// clear trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// sets the trigPin on HIGH  for 10 microseconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads echoPin, returns sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);


// calculating the distance
distance = duration*0.034/2;
// Distance is half the duration devided by 29.1 (from datasheet)


safetyDistance = distance;

//**************************************************************************
// if distance less than 0.2 meter and more than 0
if (safetyDistance <= 20) {   // <------------- hier Aenderung vornehmen. 20 ändern in 150 => 150cm Abstand

//**************************************************************************
//**************************************************************************
//**************************************************************************
  
  // Buzz
  tone (8,300); //  tone(pin, frequency, duration)
 // frequency: 100, 1000, 10000, 650000 the higher the number, the higher the pitch

  digitalWrite(ledPin, HIGH);
    
} else {
// Don't buzz
// set noTone: buzzPin: 8
  noTone(8);
  digitalWrite(ledPin, LOW);
}



// **************************************************************
// SERIAL MONITOR

Serial.print("Distanz:  ");
Serial.print(distance);
Serial.print(" cm");

// Waiting 60 ms won't hurt any one
delay(60);

  
 // delay(5000);

// **************************************************************
// TESTING 

  
// **************************************************************
// DISPLAY MONITOR
//
//     // display Distance
//  display.setTextSize(1);
//  display.setCursor(0, 30);
//  display.print("Dist: ");
//  display.setTextSize(1);
//  display.setCursor(65, 30);
//  display.print(distance);
//  display.print(" cm"); 
//
//  
//  display.display(); 


  
}
