// To control display lcd and temperature and humidity sensors and led by using IR sensor.

#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 7      
#define DHTTYPE DHT11  
#define LED_PIN 9      
#define IR_PIN 8   

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal mylcd(12, 11, 5, 4, 3, 2);

void setup() {
  mylcd.begin(16, 2);              
  Serial.begin(9600);              
  dht.begin();                     
  pinMode(LED_PIN, OUTPUT);      
  pinMode(IR_PIN, INPUT);          
  
  // Initially, we will have everything off
  digitalWrite(LED_PIN, LOW);     
  mylcd.clear();                  
  Serial.println("System Ready.");
 }

void loop() {
  int irState = digitalRead(IR_PIN);
  if (irState == LOW) {  
    float temperature = dht.readTemperature(); // Temperature in Celsius
    float humidity = dht.readHumidity();       // Humidity in percentage

    // Check if reading from DHT sensor failed
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      mylcd.clear();
      mylcd.print("DHT Sensor Error");
      return; 
    }

    // Print the temperature and humidity to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Display the readings on the LCD
    mylcd.setCursor(0, 0);  
    mylcd.print("Temp: ");
    mylcd.print(temperature);
    mylcd.print(" C");
    mylcd.setCursor(0, 1);  
    mylcd.print("Hum: ");
    mylcd.print(humidity);
    mylcd.print(" %");

    // Map humidity value to PWM range (0 to 255)
    int ledBrightness = map(humidity, 40, 100, 0, 255);  // Map humidity to LED brightness
    Serial.print("LED Brightness (PWM): ");
    Serial.println(ledBrightness);
    analogWrite(LED_PIN, ledBrightness);  // Control the LED brightness based on humidity
  }
   else {
    // If no object is detected by IR sensor, turn everything off
    digitalWrite(LED_PIN, LOW); 
    mylcd.clear();                  
  }

  delay(200); 
}
