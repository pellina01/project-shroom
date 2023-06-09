//Libraries
#include <DHT.h>

//Constants
const int CONTROL_HUM = 14;    // GPIO14 for humidifier
const int LED_ERROR_HUM = 3;   // GPIO12 for error LED of humidity
const int MIN_RH = 90;

//Variables
float RH;     // Relative Humidity (%)
float TEMP;   // Temperature (C)


#define DHTPIN 2            // GPIO2 for DHT21
#define DHTTYPE DHT21       //DHT 21  (AM2301)
DHT dht(DHTPIN, DHTTYPE);   //Initialize DHT sensor for normal 16mhz Arduino


void ControlHumidity(float RH){
  
  if(isnan(RH)){ // there's an error in humidity reading
      digitalWrite(LED_ERROR_HUM, HIGH);
      digitalWrite(CONTROL_HUM, LOW);
    }
   else if(RH < MIN_RH){ // humidity reading too low
      digitalWrite(LED_ERROR_HUM, LOW);
      digitalWrite(CONTROL_HUM, LOW);
   }
   else{ // humidity reading is ok
      digitalWrite(LED_ERROR_HUM, LOW);
      digitalWrite(CONTROL_HUM, HIGH);
    }
  
  }


void setup() {
  pinMode(LED_ERROR_HUM, OUTPUT);
  pinMode(CONTROL_HUM, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  TEMP = dht.readTemperature();
  Serial.print("Temperature (Celsius): ");
  Serial.println(TEMP);
  
  RH = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(RH);
  
  ControlHumidity(RH);
  
  delay(3000);
}
