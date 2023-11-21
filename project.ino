#include <Servo.h>
#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x3E, 16, 2);

const int trigPin1 = 11;  // Trig pin of the first ultrasonic sensor
const int echoPin1 = 10;  // Echo pin of the first ultrasonic sensor
const int trigPin2 = 5;   // Trig pin of the second ultrasonic sensor
const int echoPin2 = 6;   // Echo pin of the second ultrasonic sensor
const int servoPin = 3;   // Servo control pin
const int buzzer = 9;
const int binHeight = 20;

Servo myservo;
long duration1, distance1, duration2, distance2;
int angle = 140;


byte black[] = {
  B11111, 
  B11111,
  B11111,
  B11111,
  B11111, 
  B11111,
  B11111,
  B11111,
};

byte white[] = {
  B00000, 
  B00000,
  B00000,
  B00000,
  B00000, 
  B00000,
  B00000,
  B00000,
};

void setup() {
  myservo.attach(servoPin);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.setBacklight(true);

  lcd.customSymbol(1, black);
  lcd.customSymbol(0, white);

  lcd.setCursor(0,0);
  lcd.print(" Percentage:");
}

void loop() {
  // First ultrasonic sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH, 30000);
  if (duration1 > 0 && duration1 < 30000) {
    distance1 = (duration1 / 2) / 29.1;
  } else {
    distance1 = 0;
  }

  // Second ultrasonic sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH, 30000);
  if (duration2 > 0 && duration2 < 30000) {
    distance2 = (duration2 / 2) / 29.1;
  } else {
    distance2 = 0;
  }

  /*if (distance2 <= 5) {
    tone(buzzer,2000);
  } else {
    noTone(buzzer);
  }*/

  Serial.print("Distance Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  
    // You can use the distance2 value for tracking the distance between the second sensor and an obstacle.
  // The servo behavior is based on the distance from the first sensor (distance1).
  
  // Check if the distance from the first sensor is less than 10 cm
  // Check if the distance from the first sensor is less than 10 cm
// Check if the distance from the first sensor is less than 10 cm
  if (distance1 < 10) {
    while (angle > 0) {
      angle -= 10;
      myservo.write(angle);
      Serial.println(angle); // Print the servo angle for debugging
    }
  } else {
    while (angle < 140) {
      angle += 10;
      myservo.write(angle);
      Serial.println(angle); // Print the servo angle for debugging
    myservo.write(angle);
    Serial.println(angle); // Print the servo angle for debugging
  }
  myservo.write(angle);
  }

  lcdUpdate(distance2, binHeight);

  delay(500);
}

void lcdUpdate(float currentDistance, float totalDistance){
  float percentTrash=1-currentDistance/totalDistance;
  int slotCounter=int(percentTrash*15);
  for(int i=0;i<slotCounter;i++){
    lcd.setCursor(i,1);
    lcd.write((uint8_t)1);
  }
  for(int x=slotCounter;x<15;x++){
    lcd.setCursor(x,1);
    lcd.write((uint8_t)0);
  }
}

