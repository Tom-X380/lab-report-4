//we need to include various libraries to use the lcd and dht sensor and its fucntions
#include <afstandssensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#define DHTPIN 4   // Digital pin connected to the DHT sensor 



double d;
//we define which type of dht sensor we are using
#define DHTTYPE    DHT11     


//these functions enable the dht sensor to work 
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


// initialize the library with the numbers of the interface pins for the LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//for the degree symbol ont he LCD we need to make one using the custom charcter funtion to custom define the display matrix bits to turn on and off since the LCD uses 5x8 squares 
byte customChar[8] = {
	0b01100,
	0b10010,
	0b10010,
	0b01100,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};
//before we go into the setup we define certain variables 
//this one is for the counter so that we can three displays 
int PBState = LOW;
//this is a variable to save the last state of the button
int lastButtonState;
//this is the variable to save the current button state
int currentButtonState;

void setup() {
//we must actually create the custom character to use at any time in the code
lcd.createChar(0,customChar);
//you must define and enable serial monitor which helps with trouble shooting later
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

pinMode(3, INPUT_PULLUP);

currentButtonState = digitalRead(3);




}

void loop() {
  //this is the process where we count 
 lastButtonState    = currentButtonState;      // save the last state
currentButtonState = digitalRead(3); //saves the current states

//if the conditons are met ofr a button press we will add 1 to pbstate 
if(lastButtonState == 1 && currentButtonState == 0) {
    PBState = PBState + 1;
  //if the pbstate goes above 2 it will rese tback to 0 since we dont want the counter to go up forever 
if (PBState>2){
  PBState = 0;
}

  }



  sensors_event_t event;
  //this is the functions which retrives the data from the sensor
  dht.temperature().getEvent(&event);
  //because of a unkown bug we have to save the temeprature value in a variable instead of calling ti directly into the LCD
  float temp = event.temperature;
  float tempf = (temp*1.8) +32;
  // this simple function checks for erros in the temperature reading 
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  //without any errors we print the temp ont he serial monitor
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));
    Serial.println(F("\t"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  //same as before if there is an error we display an error 
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  //print the humidity 
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.print(F("%"));
    Serial.println(F("\t"));
  }
  //for troubleshooting purpose we print the state of the counter to ensure its working correctly 
Serial.print(PBState);
Serial.print("\t");
//for each pb state is a screen that will display either temp in celcius fahrenheit or humidtiy 
  lcd.setCursor(0, 0);
if (PBState == 0){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity ");
lcd.print(event.relative_humidity);
lcd.print("%");
}
if (PBState==1){
lcd.clear();
lcd.print("Temp: ");
lcd.print(temp);
lcd.print("C");
//we will use now use our custom charcter we made for the degree symbol
lcd.write(byte(0));
}
if(PBState==2){
lcd.clear();
float tempf = ((9/5)*temp)+32;
lcd.print("Temp: ");
lcd.print(tempf);
lcd.print("F");
//we will use now use our custom charcter we made for the degree symbol
lcd.write(byte(0));
}



}


