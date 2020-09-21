
// Corona MultiTool

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




// *********************************************************************+
#include "Seeed_BME280.h"
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

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

//MH-Z14a
//read method: PWM in use not UART
// set interrupt pin numbers to recive output signal:
const int sensorPin = 3; // Pin 3 as the sensor pin

// var MH-Z14a
long laag = 0;
long hoog = 0;
long laagTijd = 0;
long hoogTijd = 0;


// DISTANCE TOOL

int const trigPin = 5;
int const echoPin = 6;
int const ledPin = 7;
int const buzzPin = 8;

// var Ultraschalll
long duration;
int distance;
int safetyDistance;
int ppm;
int safetyPpm;


// BME

BME280 bme280;

// **********************************************************

// FUNCTIONS

void setup() {

  // Distance Tool
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  pinMode(buzzPin, OUTPUT); // buzz pin is output to control buzzer
  pinMode(ledPin, OUTPUT); 

  Serial.begin(115200); // serial communication
 
  //DHT
  dht.begin();

  // BME Test
   if(!bme280.init()){
    Serial.println("BME error!");
  }
 
  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  //MH-Z14a
  // set sensor pin as an input
  pinMode(sensorPin, INPUT);
  // Read starting value for millis…
  while(digitalRead(sensorPin) == LOW) {;}
  hoog = millis();

}

void loop() {


  float pressure;
  
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

// if distance less than 0.5 meter and more than 0 (0 or less means over range)
if (safetyDistance <= 20) {
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


Serial.print("Distanz:  ");
Serial.print(distance);
Serial.print(" cm");

// Waiting 60 ms won't hurt any one
delay(60);

  
 // delay(5000);

// **************************************************************
// TESTING 

//DHT
  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
//MH-Z14a
  // read co2
  float c = dht.readTemperature();
  // testing
  if (isnan(c)) {
    Serial.println("Failed to read from CO2 sensor!");
  }

// **************************************************************
// SERIAL MONITOR

  //DHT
  Serial.println("Temperature: ");
  Serial.print(t);
  Serial.println("Hum: ");
  Serial.print(h);
  
  // BME
  //get and print temperatures
  Serial.print("BMP-Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols
  
  //get and print atmospheric pressure data
  Serial.print("BMP-Pressure: ");
  Serial.print(pressure = bme280.getPressure());
  Serial.println("Pa");

  //get and print altitude data
  Serial.print("BMP-Altitude: ");
  Serial.print(bme280.calcAltitude(pressure));
  Serial.println("m");

  //get and print humidity data
  Serial.print("BMP-Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");
 
// MH-Z14a
   // Check for high and low timing – low time * 2 = PPM
while(digitalRead(sensorPin) == HIGH) {;}
laag = millis();
//hoogTijd = laag – hoog;
hoogTijd=laag-hoog;
while(digitalRead(sensorPin) == LOW) {;}
hoog = millis();
//laagTijd = hoog – laag;
laagTijd=hoog-laag;
// Validity check high+low = 1004 (small margin or error allowed -> 990)
if(laagTijd + hoogTijd > 990)
{
Serial.print("H: ");
Serial.println(hoogTijd,DEC);
Serial.print("L: ");
Serial.println(laagTijd,DEC);
Serial.print("CO2 – ");
Serial.print(laagTijd * 2,DEC);
Serial.println(" ppm");

Serial.println(" ppmsafetay - ");
Serial.print(safetyPpm);

// **************************************************************
// DISPLAY

//OLED
  //clear display
  display.clearDisplay();

 // display CO2
  display.setTextSize(1);
  display.setCursor(0, 00);
  display.print("CO2: ");
  display.setTextSize(1);
  display.setCursor(65, 00);
  display.print(laagTijd * 2,DEC);
  display.print(" ppm"); 

// BME h
  // display humidity
  display.setTextSize(1);
  //display.setCursor(0, 10);
 // display.print("BME-Humidity: ");
  display.setTextSize(1);
  display.setCursor(65, 10);
  display.print(bme280.getHumidity());
   display.setTextSize(1);
 display.print("-");
 
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Hum: ");
  display.setTextSize(1);
  display.setCursor(85, 10);
  display.print(h);
  display.print("%"); 
  
  // display temperature
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Temp:");
  display.setTextSize(1);
 // display.setCursor(20,0);
 // display.print(t);
 // display.print(" ");
  display.setTextSize(1);
 // display.cp437(true);
 // display.write(167);
 display.setTextSize(1);
 //display.print("-");

  // BME temp
      display.setTextSize(1);
  display.setTextColor(WHITE);
 // display.setCursor(0,00);
  //display.print("Temp");
  display.setTextSize(1);
  display.setCursor(65,20);
  display.print(bme280.getTemperature());
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(1);
  display.print("C");
  
 




     // display Distance
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Dist: ");
  display.setTextSize(1);
  display.setCursor(65, 30);
  display.print(distance);
  display.print(" cm"); 

  // display pressure
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Press: ");
  display.setTextSize(1);
  display.setCursor(65, 40);
  display.print(pressure = (bme280.getPressure()));
  display.print("Pa");



  
 // display altitude
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Alt: ");
  display.setTextSize(1);
  display.setCursor(65, 50);
  display.print(bme280.calcAltitude(pressure));
  display.print("m"); 
  display.display(); 


} else {
// Output in case of invalid check: value instead of 1004 ms
Serial.print("– CK:");
Serial.println(laagTijd+hoogTijd, DEC);
}

 
  
  display.display(); 

// **************************************************************
// PPM ALARM 

safetyPpm = (laagTijd * 2,DEC);

// if distance less than 0.5 meter and more than 0 (0 or less means over range)
if (safetyPpm >= 100) {
  // Buzz
  tone (8,2000); //  tone(pin, frequency, duration)
 // frequency: 100, 1000, 10000, 650000 the higher the number, the higher the pitch

  digitalWrite(ledPin, HIGH);
    
} else {
// Don't buzz
// set noTone: buzzPin: 8
  noTone(8);
  digitalWrite(ledPin, LOW);
}

  
}
