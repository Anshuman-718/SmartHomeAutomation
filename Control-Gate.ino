// To control room gate (opening and closing) by using IR sensor
 
 #include <Servo.h>

 Servo myServo;  

int servoPin = 9; 
int irPin = 8;     
int lastIrState = HIGH;  // To store the previous IR sensor state
 int irState = HIGH;      // To store the current IR sensor state

 void setup() {
  myServo.attach(servoPin);
  pinMode(irPin, INPUT);
  myServo.write(80);
 }

 void loop() {
  irState = digitalRead(irPin);

  // Only take action if the IR state changes 

  if (irState != lastIrState) {
    if (irState == LOW) { 
      for (int angle = 80; angle >= 0; angle--) {
        myServo.write(angle);   
        delay(20);             
      }
    } 
    else { 
      for (int angle = 0; angle <=80 ; angle++) {
        myServo.write(angle);  
        delay(20);                
      }
    }

    // Saving the current state for next comparison
    lastIrState = irState;
  }
  delay(50);  
}
