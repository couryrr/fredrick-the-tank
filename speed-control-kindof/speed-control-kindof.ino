#include <Servo.h>

// create servo object to control a servo
Servo head_servo;  

// Sensor setup
const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor

// Motor setup
const int E1 = 3;  
const int M1 = 12;
const int E2 =11;                        
const int M2 = 13;   

void setup() {

  head_servo.attach(9);
  
  // Motor pins
  pinMode(M1, OUTPUT);  
  pinMode(M2, OUTPUT);

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

void loop() {
//turn left 
  head_servo.write(180);
  delay(500);
   Serial.println("looking left");
  takeMeasurment();
delay(3500);
 //look strait
  head_servo.write(90);
    delay(500);

     Serial.println("looking straight");
    takeMeasurment();
  delay(3500);
  //turn right
  head_servo.write(0);
    delay(500);
   Serial.println("looking right");
    takeMeasurment();
delay(3500);
  //look strait
  head_servo.write(90);

  delay(4000);
  
  /*
  if(inches < 10){
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(E1, 0);   // PWM regulate speed
    analogWrite(E2, 0);   // PWM regulate speed
  } else {
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(E1, 200);   // PWM regulate speed
    analogWrite(E2, 200);
  }
  */
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
long takeMeasurment() {
 long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();
  return inches;
}
