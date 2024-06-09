#include <Servo.h>

#define SERVO_OPENED_ANGLE 90
#define SERVO_CLOSED_ANGLE 0
#define SERVO_PIN 7

#define SERVO_TRIGGER_PIN 2
#define SERVO_ECHO_PIN 3
#define RESIDUE_TRIGGER_PIN 8
#define RESIDUE_ECHO_PIN 9
#define BUZZER_PIN A0
#define LED_PIN 11

Servo s;

int servoSensorDuration = 0;
int servoSensorDistance = 0;
int residueSensorDuration = 0;
int residueSensorDistance = 0;

void setup() {
  Serial.begin(9600);
  s.attach(SERVO_PIN);
  s.write(SERVO_CLOSED_ANGLE);

  pinMode(SERVO_TRIGGER_PIN, OUTPUT);
  pinMode(RESIDUE_TRIGGER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  pinMode(RESIDUE_ECHO_PIN, INPUT);
  pinMode(SERVO_ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(RESIDUE_TRIGGER_PIN, HIGH);
  digitalWrite(SERVO_TRIGGER_PIN, HIGH);
  delay(1);
  digitalWrite(RESIDUE_TRIGGER_PIN, LOW);
  digitalWrite(SERVO_TRIGGER_PIN, LOW);

  servoSensorDuration = pulseIn(SERVO_ECHO_PIN, HIGH);
  servoSensorDistance = (servoSensorDuration * 0.034) / 2;

  residueSensorDuration = pulseIn(RESIDUE_ECHO_PIN, HIGH);
  residueSensorDistance = (residueSensorDuration * 0.034) / 2;
	
  if (servoSensorDistance <= 5) {
    s.write(SERVO_OPENED_ANGLE);
    delay(3000);
  } else {
    s.write(SERVO_CLOSED_ANGLE);
    delay(10);
  }

  if (residueSensorDistance <= 5) {
    Serial.println("Detectando objeto.");
    analogWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    analogWrite(BUZZER_PIN, LOW);
  } else {
    Serial.println("Nada detectável.");
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}
