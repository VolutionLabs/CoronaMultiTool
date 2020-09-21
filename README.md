# CoronaMultiTool -  Distance / CO2 / Humidity Corona Tool for Arduino 
A device for the measurement of Corona virus related physical parameters of space - corona tool arduino

Arduino Nano

Sensors:
- MH-Z14a (CO2 (NDIR))
- DHT-22 (temperature, humidity)
- BME260 (temperature, humidity, pressure, altitude)


Actuators:
- OLED 128x64 Adafruit_SSD1306
- Buzzer
- LED red
- 4-point LED



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



PINS:

// DHT
#define DHTPIN 2     // Digital pin connected to the DHT sensor

//MH-Z14a
//read method: PWM in use not UART
// set interrupt pin numbers to recive output signal:
const int sensorPin = 3; // Pin 3 as the sensor pin


current state:  - currently uses PWD MH-Z14a communication: wrong value ca. 1600ppm
                - UART communication (A0, A1): gives Arduino port error
