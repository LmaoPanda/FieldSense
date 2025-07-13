#include <Arduino.h>
#define DIR_PIN1 2
#define STEP_PIN1 3
#define DIR_PIN2 4
#define STEP_PIN2 5
#define BAUD_RATE 9600
#define MOTOR_STEPS_PER_REV 200
#define MICROSTEPS = 16
#define PULLEY_TEETH 12
#define BELT_PITCH 3
#define BOARD_X 185
#define BOARD_Y 125
#define STEPS_PER_MM 88.89

float currentX = 0;
float currentY = 0;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(STEP_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(STEP_PIN2, OUTPUT);
}

void spinSteppa(int motorDir, int motorStep, bool dir){
  digitalWrite(motorDir, dir);
  digitalWrite(motorStep, HIGH);
  delayMicroseconds(800);
  digitalWrite(motorStep, LOW);
  delayMicroseconds(800);
}

void moveCoreXY(int targetX, int targetY)
{
  float motorA_current = (currentX + currentY) * STEPS_PER_MM;
  float motorB_current = (currentX - currentY) * STEPS_PER_MM;

  float stepsA = (targetX + targetY)*STEPS_PER_MM;
  float stepsB = (targetX - targetY)*STEPS_PER_MM;

  int deltaA = round(stepsA - motorA_current);
  int deltaB = round(stepsB - motorB_current);

  bool dirA = deltaA >= 0;
  bool dirB = deltaB >= 0;

  deltaA = abs(stepsA);
  deltaB = abs(stepsB);

  int maxSteps = max(stepsA, stepsB);

  for (int i = 0; i < maxSteps; i++) {
    if (i < stepsA) {
      spinSteppa(DIR_PIN1, STEP_PIN1, dirA);
    }
    if (i < stepsB) {
      spinSteppa(DIR_PIN2, STEP_PIN2, dirB);
    }
  }

  currentX = stepsA;
  currentY = stepsB;

}

void loop() {
  moveCoreXY(100, 50);
}
