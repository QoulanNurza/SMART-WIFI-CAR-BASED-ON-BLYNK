#define BLYNK_TEMPLATE_ID "TMPL6Lqde6oXR"
#define BLYNK_TEMPLATE_NAME "WiFi Car"
#define BLYNK_AUTH_TOKEN "Q0-TEUnPFUcgH3K5gYVi8yTB9hruiWPE"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
 
//Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

// HC-SR04 pins
#define TRIG_PIN D6
#define ECHO_PIN D7

// LDR pin
#define LDR_PIN A0

// LED pin
#define LED_PIN D8

void carforward();
void carbackward();
void carturnleft();
void carturnright();
void carStop();

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "Q0-TEUnPFUcgH3K5gYVi8yTB9hruiWPE"; //Enter your Blynk application auth token
char ssid[] = "Rakha"; //Enter your WIFI name
char pass[] = "rakha4002"; //Enter your WIFI passowrd
 
 
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 
 pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}

 // Ultrasonic sensor logic


void ultrasonic(){
    // LDR sensor logic
  int duration, distance;
  
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
   distance = duration * 0.034 / 2;

  if (distance <= 20) {
    carbackward();
    delay(1000);
    carStop();

  }
 int sensorValue = analogRead(LDR_PIN);
   if (sensorValue<=1000)
   {
    digitalWrite(LED_PIN,LOW);
   }
   else
  {
   digitalWrite(LED_PIN,HIGH);
  }
  Serial.println(sensorValue);
  delay(10); 
}


// Motor control functions
void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void smartcar() {
  if (forward == 1) {
    carforward(); 
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward(); 
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft(); 
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright(); 
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop(); 
    Serial.println("carstop");
  }
}

void loop() {
  Blynk.run();
  smartcar();
  ultrasonic();

  // LDR sensor logic
  int duration, distance;
  
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
   distance = duration * 0.034 / 2;

  if (distance <= 20) {
    carbackward();
    delay(1000);
    carStop();

  }
 int sensorValue = analogRead(LDR_PIN);
   if (sensorValue<=1000)
   {
    digitalWrite(LED_PIN,LOW);
   }
   else
  {
   digitalWrite(LED_PIN,HIGH);
  }
  Serial.println(sensorValue);
  delay(10); 
}