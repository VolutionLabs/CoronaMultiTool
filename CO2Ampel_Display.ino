
// Corona CO2 Ampel

//INFOS

// CO2
// im Freien: 400ppm. 
// gut ventilierter Innenraum: 800ppm
// kritisch ab 1000ppm
// Quelle: Umweltbundesamt
// Link: https://www.umweltbundesamt.de/sites/default/files/medien/2546/dokumente/irk_stellungnahme_lueften_sars-cov-2_0.pdf
// In Räumen mit hoher Personenbelegung, wie z. B. Schulen, können sogenannte CO2-Ampeln als grober Anhaltspunkt für gute oder schlechte Lüftung dienen. 
// Kohlendioxid (CO2) gilt seit langem als guter Indikator für den Luftwechsel, 
// eine CO2-Konzentration von höchstens 1000 ppm (0,1Vol-%) zeigt unter normalen Bedingungen einen hygienisch ausreichenden Luftwechsel an
// CO2-Ampeln können somit einen raschen und einfachen Hinweis liefern, ob und wann Lüftung notwendig ist. 
// Der Einsatz von CO2-Ampeln ist besonders für Schulen zu empfehlen, da die wenigsten Schulen bis heute über RLT-Anlagen verfügen. 


// Luftfeuchtigkeit
// ==> relative Luftfeuchtigkeit der Raumluft  mindestens 40 - 60 Prozent
// Quelle: Leipziger TROPOS-Institut 
// Link: https://www.tropos.de/aktuelles/pressemitteilungen/details/coronavirus-sars-cov-2-breitet-sich-bei-niedriger-luftfeuchtigkeit-in-innenraeumen-staerker-aus
// Die Ausbreitung des Coronavirus SARS-CoV-2 über Aerosole in Innenräumen wird offenbar stark von der Luftfeuchtigkeit beeinflusst. 
// Eine relative Feuchte von 40 bis 60 Prozent könne die Ausbreitung der Viren und die Aufnahme über die Nasenschleimhaut reduzieren. 
// Liegt die relative Luftfeuchtigkeit der Raumluft unter 40 Prozent, dann nehmen die von Infizierten ausgestoßenen Partikel weniger Wasser auf, 
// bleiben leichter, fliegen weiter durch den Raum und werden eher von Gesunden eingeatmet. 
// Außerdem werden bei trockener Luft auch die Nasenschleimhäute in unseren Nasen trockner und durchlässiger für Viren“

// Abstandsmessung Ultraschall
// Distance = (Time x Speed of Sound in Air (340 m/s))/2
// ECHO of sound. A pulse is sent for about 10us to trigger the module. 
// After which the module automatically sends 8 cycles of 40 KHz ultrasound signal and checks its echo. 
// The signal after striking with an obstacle returns back and is captured by the receiver. 
// Thus the distance of the obstacle from the sensor is simply calculated by the formula given as
// Distance = (time x speed)/2.



// Code wie folgt, überschreibt die Ausgabe des OLEDs -> nur 4-Digit für den CO2-Wert wird angezeigt.
// 4-Digit Display muss ausgeschaltet/'comment' als mit '//' deaktiviert  werden, um OLED Display nutzen zu können.
// bug: only 1 display works. further workaround along: https://forum.pjrc.com/threads/54494-Adafruit-SSD1306-multiple-instances-issue



// *********************************************************************

#include <Adafruit_BME280.h>
#include "Seeed_BME280.h"
#include <SoftwareSerial.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <TM1637Display.h>

const int analogPin = A3; // Pin4
const int pwmPin = 3; // Pin6

const long samplePeriod = 10000L;

// SoftwareSerial library allows any digital pin to do the UART communication, as long as device supports UART procotol as well. 
// rx: receive
// tx: transmit
//SoftwareSerial sensor(10, 11); // RX, TX
SoftwareSerial sensor(A0, A1); // A0 and A1 on Arduino to RX, TX on MH-Z14 respectively

const byte requestReading[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
byte result[9];
long lastSampleTime = 0;


// OLED Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET -1
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT-22 Temperature & Humidity
#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT22     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// BME
BME280 bme280;


// TM1637 4-digit Display
//
//#define CLK 9
//#define DIO 10
//
//// Create display object of type TM1637Display:
//TM1637Display digit_display = TM1637Display(CLK, DIO);
//// You can create more than one display object. Give them different names and connection pins:
//TM1637Display digit_display_1  = TM1637Display(2, 3);
//TM1637Display digit_display_2  = TM1637Display(4, 5);
//TM1637Display digit_display_3  = TM1637Display(6, 7);
//
//// Create degree Celsius symbol:
//const uint8_t celsius[] = {
//  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
//  SEG_A | SEG_D | SEG_E | SEG_F   // C
//};


// **********************************************************

// FUNCTIONS


void setup() {
  Serial.begin(9600);
  sensor.begin(9600);
  pinMode(pwmPin, INPUT_PULLUP);

  Serial.begin(115200); // serial communication
  
//  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
// }
  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  //DHT
  dht.begin();

  // BME Test
   if(!bme280.init()){
    Serial.println("BME error!");
  }

  // 4-digit display
  // Set the 4-digit display brightness (0-7):
  // turn off for OLED display use
//  digit_display.setBrightness(7);
//  // Clear the display:
//  digit_display.clear();
//  
}


// **************************************************************
// MH-Z14 ANALOG 
int readPPMV() {
  float v = analogRead(analogPin) * 5.0 / 1023.0;
  int ppm = int((v - 0.4) * 3125.0);
  return ppm;
}

// **************************************************************
// MH-Z14 Serial
int readPPMSerial() {
  for (int i = 0; i < 9; i++) {
    sensor.write(requestReading[i]); 
  }
  //Serial.println("sent request");
  while (sensor.available() < 9) {}; // wait for response
  for (int i = 0; i < 9; i++) {
    result[i] = sensor.read(); 
  }
  int high = result[2];
  int low = result[3];
    //Serial.print(high); Serial.print(" ");Serial.println(low);
  return high * 256 + low;
}

// **************************************************************
// MH-Z14 PWM
int readPPMPWM() {
  while (digitalRead(pwmPin) == LOW) {}; // wait for pulse to go high
  long t0 = millis();
  while (digitalRead(pwmPin) == HIGH) {}; // wait for pulse to go low
  long t1 = millis();
  while (digitalRead(pwmPin) == LOW) {}; // wait for pulse to go high again
  long t2 = millis();
  long th = t1-t0;
  long tl = t2-t1;
  long ppm = 5000L * (th - 2) / (th + tl - 4);
  while (digitalRead(pwmPin) == HIGH) {}; // wait for pulse to go low
  delay(10); // allow output to settle.
  return int(ppm);
}

// *************************

void loop() {

  float pressure;

  
  // **************************************************************
// TESTING 

//DHT
  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  // read co2
  float c = dht.readTemperature();
  // testing
  if (isnan(c)) {
    Serial.println("Failed to read from CO2 sensor!");
  }


  // **************************************************************
// MH-Z14a

  long now = millis();
  if (now > lastSampleTime + samplePeriod) {
    lastSampleTime = now;
    int ppmV = readPPMV();
    int ppmS = readPPMSerial();
    int ppmPWM = readPPMPWM();

    Serial.print(ppmV); 
    Serial.print("\t"); 
    Serial.print(ppmPWM); 
    Serial.print("\t");
    Serial.println(ppmS);
  }

  // **************************************************************
// SERIAL MONITOR

//  //DHT
//  Serial.print("DHT-Temperature: ");
//  Serial.print(t);
//  Serial.println("C");

//  Serial.print("DHT-Hum: ");
//  Serial.print(h);
//  Serial.println("%");
//  
//  // BME
//  //get and print temperatures
//  Serial.print("BME-Temp: ");
//  Serial.print(bme280.getTemperature());
//  Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols
//  
//  //get and print atmospheric pressure data
//  Serial.print("BME-Pressure: ");
//  Serial.print(pressure = bme280.getPressure());
//  Serial.println("Pa");
//
//  //get and print altitude data
//  Serial.print("BME-Altitude: ");
//  Serial.print(bme280.calcAltitude(pressure));
//  Serial.println("m");
//
//  //get and print humidity data
//  Serial.print("BME-Humidity: ");
//  Serial.print(bme280.getHumidity());
//  Serial.println("%");
//
//  Serial.print("CO2-Analog: ");   
//  Serial.println(readPPMV()); 
//  //Serial.print("\t"); 
//  Serial.print("CO2-PWM: ");  
//  Serial.println(readPPMPWM()); 
// // Serial.print("\t");
//  Serial.print("CO2-Serial: ");  
//  Serial.println(readPPMSerial());
//
//  Serial.println("****************");



  
//// **************************************************************
//// OLED DISPLAY

  //clear display
  display.clearDisplay();


// display CO2: ANALOG-PWM-SERIAL
  display.setTextSize(1);
  display.setCursor(0, 00);
  display.print("CO2: ");
  
  // display CO2 Analog
  display.setTextSize(1);
  display.setCursor(25, 00);
 // display.print(" a "); 
  display.print(readPPMV());
  
  // display CO2 PWM
  display.setTextSize(1);
  display.setCursor(55, 00);
 // display.print(" p "); 
  display.print(readPPMPWM());
    display.print(" ");
    
  // display CO2 Serial
  display.setTextSize(1);
  display.setCursor(80, 00);
 // display.print(" s "); 
  display.print(readPPMSerial());
  display.print("ppm"); 
  

// display humidity

  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Hum: ");

  // display humidity BME 
  display.setTextSize(1);
  display.setCursor(40, 10);
  display.print(bme280.getHumidity());
  display.setTextSize(1);
  display.print(" - ");
  
  // display humidity DHT
  display.setTextSize(1);
  display.setCursor(70, 10);
  display.print(h);
  display.print("%"); 

    // display temperature
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Temp:");

  // DHT temp
//  display.setTextSize(1);
 // display.setCursor(35,20);
//  display.print(t);
 // display.print(" ");
 // display.setTextSize(1);
 // display.cp437(true);
 // display.write(167);
 //display.setTextSize(1);
// display.print(" - ");

  // BME temp
  display.setTextSize(1);
  display.setCursor(40,20);
  display.print(bme280.getTemperature());
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(1);
  display.print("C");


  // display pressure
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Press: ");
  display.setTextSize(1);
  display.setCursor(40, 40);
  display.print(pressure = (bme280.getPressure()));
  display.print("Pa");

  
 // display altitude
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Alt: ");
  display.setTextSize(1);
  display.setCursor(40, 50);
  display.print(bme280.calcAltitude(pressure));
  display.print("m"); 
  display.display(); 

  display.display(); 


// **************************************************************
// 4-digit DISPLAY


  // Show  CO2 (PWD) on the TM1637 display:
  // turn off for OLED display use
  
// display.write(readPPMPWM());
// digit_display.showNumberDec(readPPMPWM(), false, 4, 0);
// //digit_display.setSegments(celsius, 2, 2);
// delay(2000);
  

}
