# CoronaMultiTool for Arduino -  Distance + CO2 + Humidity 
A device for the measurement of Corona virus related physical parameters of space
### #CO2-Ampel #DistanceFeedback #Air Quality

![CoronaMultitool-1](https://user-images.githubusercontent.com/2845142/94610655-e5e5d600-02a0-11eb-9cc0-14b8dc722e2c.jpg)
 
![CoronaMultitool-4](https://user-images.githubusercontent.com/2845142/94610693-f6964c00-02a0-11eb-8e22-46c80e15bd6a.jpg)


Arduino Nano

### Sensors:
- MH-Z14a (CO2 (NDIR)) 
- DHT-22 (temperature, humidity) alternativ:
- BME260 (temperature, humidity, pressure, altitude) 

### Actuators:
- OLED 128x64 Adafruit_SSD1306 
- Buzzer
- LED red
- 4-point LED

split into 2 tools in v.1.1:
DistanzKasten & Luft-Ampel




## Info Parameter

### CO2
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


### Luftfeuchtigkeit
// ==> relative Luftfeuchtigkeit der Raumluft  mindestens 40 - 60 Prozent
// Quelle: Leipziger TROPOS-Institut 
// Link: https://www.tropos.de/aktuelles/pressemitteilungen/details/coronavirus-sars-cov-2-breitet-sich-bei-niedriger-luftfeuchtigkeit-in-innenraeumen-staerker-aus
// Die Ausbreitung des Coronavirus SARS-CoV-2 über Aerosole in Innenräumen wird offenbar stark von der Luftfeuchtigkeit beeinflusst. 
// Eine relative Feuchte von 40 bis 60 Prozent könne die Ausbreitung der Viren und die Aufnahme über die Nasenschleimhaut reduzieren. 
// Liegt die relative Luftfeuchtigkeit der Raumluft unter 40 Prozent, dann nehmen die von Infizierten ausgestoßenen Partikel weniger Wasser auf, 
// bleiben leichter, fliegen weiter durch den Raum und werden eher von Gesunden eingeatmet. 
// Außerdem werden bei trockener Luft auch die Nasenschleimhäute in unseren Nasen trockner und durchlässiger für Viren“

### Abstandsmessung Ultraschall
// Distance = (Time x Speed of Sound in Air (340 m/s))/2
// ECHO of sound. A pulse is sent for about 10us to trigger the module. 
// After which the module automatically sends 8 cycles of 40 KHz ultrasound signal and checks its echo. 
// The signal after striking with an obstacle returns back and is captured by the receiver. 
// Thus the distance of the obstacle from the sensor is simply calculated by the formula given as
// Distance = (time x speed)/2.


### MultiTool
![CoronaMultitool-Fritzing_Schema_multitool-combined](https://user-images.githubusercontent.com/2845142/98366994-29b4c380-2035-11eb-81f4-64932d8c753e.jpeg)

### CO2-Ampel
![CoronaMultitool-Fritzing_Schema-CO2](https://user-images.githubusercontent.com/2845142/98366702-b57a2000-2034-11eb-9143-880c6ea64829.png)

### Distanz-Kasten
![CoronaMultitool-Fritzing_Schema-DistTool](https://user-images.githubusercontent.com/2845142/98366843-eb1f0900-2034-11eb-9c9b-c08f677ff377.jpeg)


## Einsatzzweck

- Überwachung der Raumluft
- Unterstützung bei Lüftungskonzept
- Coronavirus Aerosolvermeidung 


## Hintergrund

Umweltbundesamt: Stellungnahme der Kommission Innenraumlufthygiene: 
“Das Risiko einer Übertragung von SARS-CoV-2 in Innenräumen lässt sich durch geeignete Lüftungsmaßnahmen reduzieren” (Stand: 12. August 2020)  
(Microsoft Word - IRK Stellungnahme Lüften SARS-CoV-2) https://www.umweltbundesamt.de/sites/default/files/medien/2546/dokumente/irk_stellungnahme_lueften_sars-cov-2_0.pdf

Richtiges Lüften reduziert Risiko der SARS-CoV-2-Infektion | Umweltbundesamt
https://www.umweltbundesamt.de/presse/pressemitteilungen/richtiges-lueften-reduziert-risiko-der-sars-cov-2

## Pins
- Ultraschall HC-SR04	D5, D6
- LED	D7
- Buzzer	D8
- MH-Z14a	analog A3, pwd D3, serial A0, A1
- DHT-22	D2
- BME280	A4, A5
- OLED	A4, A5

## Costs
| Komponenten  | DistanzTool | CO2/LuftfeuchtigkeitsTool |
| ------------- | ------------- | ------------- |
| Arduino Nano  | 15,69 € |15,69 € |
| Ultraschall HC-SR04 | 1,56 €  | - |
| LED  | 0,3 € | - |
| Buzzer | 2,05 € | - |
| MH-Z14a  | - | 27 € |
| DHT-22 | - | 4 € |
| BME280  | - | 3,31 € |
| OLED | -  | 4 € |
| 4-Digit LED  | - | 6 € |
| Jumperkabel | 3 €  | 3 €|
| Widerstand  | 0,09 €  | 0,09 € |
| Level Converter  |  | 4 € |
| Kosten gesamt  | 22,69 € | 63,09 € |


## current state

working.



## further

.Value CO2
- better calibrate MH-Z14a
- test MH-Z19b

.upload plans v.1.1

