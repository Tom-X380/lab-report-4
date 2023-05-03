//we need to include various libraries to use the lcd and dht sensor and its fucntions
#include <afstandssensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

const int trigPin=6;
const int echoPin=5;
double d;


//we need to define the 2 pins that the ultrasonic sensor
AfstandsSensor afstandssensor (6,5);
uint32_t delayMS;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//before we go into the setup we define certain variables 
//this one is for the counter so that we can three displays 
int PBState = LOW;
//this is a variable to save the last state of the button
int lastButtonState;
//this is the variable to save the current button state
int currentButtonState;
//this variable is for duration and distance of the sensor. We will use it later
int distance;
long duration;
void setup() {

//you must define and enable serial monitor which helps with trouble shooting later
  Serial.begin(9600);
// set up the LCD's number of columns and rows:
lcd.begin(16,2);
//we need to define the pins being used and their functions
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

long duration;
int distance;
}

void loop() {

delay(500);
//we clear the LCD for the data to be displayed
lcd.clear();
lcd.print("Dist= ");
//because we included the correct library we can directly do the calculations and call the function in the print function
lcd.print(afstandssensor.afstandCM());
lcd.print("CM");



}

