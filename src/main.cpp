#include <Arduino.h>
#define DIR_PIN1 2
#define STEP_PIN1 3
#define DIR_PIN2 4
#define STEP_PIN2 5
#define BAUD_RATE 9600
#define BOARD_X 10
#define BOARD_Y 8

int x = 10, y = 50;

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

void moveCoreXY(int xSteps, int ySteps)
{
  int stepsA = xSteps + ySteps;
  int stepsB = xSteps - ySteps;

  bool dirA = stepsA >= 0;
  bool dirB = stepsB >= 0;

  stepsA = abs(stepsA);
  stepsB = abs(stepsB);

  int maxSteps = max(stepsA, stepsB);

  for (int i = 0; i < maxSteps; i++) {
    if (i < stepsA) {
      spinSteppa(DIR_PIN1, STEP_PIN1, dirA);
    }
    if (i < stepsB) {
      spinSteppa(DIR_PIN2, STEP_PIN2, dirB);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
