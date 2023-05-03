//we need to include various libraries to use the lcd and dht sensor and its fucntions
#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 4      // the DHT11 data pin
#define DHTTYPE DHT11 // the DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);
// Digital pin connected for the dht sensor and the ultrasonic 
#define trigPin 6    
#define echoPin 5    
#define maxDistance 100 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  //we need to start the serial monitor so we can write to it 
  Serial.begin(9600);
  //we need to define the pins and their functions so the ultrasonic sensor works 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //we need to start the dht sensor with this esnor
  dht.begin();
  //we need to define the bounds of the LCD screen
  lcd.begin(16, 2);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // measure distance using HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  //we register the distance value in a float value
  float distance = duration * 0.034 / 2;

 
    // calculate the compensated distance based on temperature and humidity
    float compensatedDistance = distance / (1 + 0.00016 * temperature + 0.00039 * humidity);
//with all the data calculated we can print it on teh serial monitor and the LCD screen
    Serial.print("Distance cm= ");
    Serial.print(compensatedDistance);
    Serial.print("Temperature C= ");
    Serial.print(temperature);
    Serial.print("Humidity %= ");
    Serial.println(humidity);
    //it is important to set the cursor at its 0,0 point so it writes correctly
  lcd.setCursor(0, 0);
  lcd.print("Dist= ");
  lcd.print(compensatedDistance);
  lcd.print("Cm ");
  //it is impportant to change the cursor setting to go to the lower level
  lcd.setCursor(0,1);
lcd.print("T=");
  lcd.print(temperature);
  lcd.setCursor(8,1);
  lcd.print("H=");
  lcd.print(humidity);


  delay(500);

  }

  
  
