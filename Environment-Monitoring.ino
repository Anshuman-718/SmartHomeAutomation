// To control all room lights and fan by using IR sensor and Bluetooth module(mobile app)

#define LED_PIN_1 3   
#define LED_PIN_2 4   
#define MOTOR_PIN 5   
#define IR_PIN 8 

bool isBluetoothControl = false;  

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT); 
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(MOTOR_PIN, LOW);
  Serial.println("Bluetooth and IR Control Ready");
 }

 void loop() {
  int irState = digitalRead(IR_PIN); 

  // Check if Bluetooth command is received
  if (Serial.available() > 0) {
    char command = Serial.read();  // Read the incoming command from Bluetooth
    isBluetoothControl = true;     // Set Bluetooth control flag
    // Control LEDs based on Bluetooth command

    if (command == '0') {
      digitalWrite(LED_PIN_1, HIGH);  
      Serial.println("LED 1 ON");
    } 
    else if (command == '1') {
      digitalWrite(LED_PIN_1, LOW);   
      Serial.println("LED 1 OFF");
    } 
    else if (command == '2') {
      digitalWrite(LED_PIN_2, HIGH); 
      Serial.println("LED 2 ON");
    } 
    else if (command == '3') {
      digitalWrite(LED_PIN_2, LOW);  
      Serial.println("LED 2 OFF");
    } 
    else if (command == '4') {
      digitalWrite(MOTOR_PIN, HIGH);  
      Serial.println("MOTOR ON");
    } 
    else if (command == '5') {
      digitalWrite(MOTOR_PIN, LOW);   
      Serial.println("MOTOR OFF");
    } 
    else {
      Serial.println("Invalid command");
    }
  }

  // If IR sensor detects an object and Bluetooth control is not active

  if (irState == LOW && !isBluetoothControl) {
    // If no Bluetooth command is controlling the LEDs, turn them on
    digitalWrite(LED_PIN_1, HIGH);  
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(MOTOR_PIN, HIGH);
    Serial.println("IR Sensor detected an object! LEDs ON");
  }

  // If no object is detected by the IR sensor (irState == HIGH) and Bluetooth control is active
  if (irState == HIGH && isBluetoothControl) {
    // Allow Bluetooth to control the LEDs
    // Do nothing here, because Bluetooth control is already taking care of LED states
  }

  // If no Bluetooth control, and IR sensor does not detect an object, turn off all LEDs
  if (irState == HIGH && !isBluetoothControl) {
    digitalWrite(LED_PIN_1, LOW);  
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("No object detected, LEDs AND MOTOR OFF");
  }

  delay(200);
 }
