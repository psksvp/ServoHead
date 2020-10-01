//  Created by psksvp on 12/1/20.
//  Copyright © 2020 psksvp. All rights reserved.
//

#include <Arduino.h>
#include <Servo.h>
#include "PID.h"
#include "utils.h"


//func decl

void commandReceived(const String&);
void reportReady();
void moveServo(int, int);
void moveServoDelta(int, int);
void horizontalScan();
void verticalScan();

// config
const int screenWidth = 640;
const int screenHeight = 480;
const int screenCenterX = screenWidth / 2;
const int screenCenterY = screenHeight / 2;
const float panServoScale = 180.0f / screenWidth;
const float tiltServoScale = 180.0f / screenHeight;

// states
bool running = false;
Servo panServo, tiltServo;


// function
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  panServo.attach(2);
  tiltServo.attach(3);

  moveServo(90, 90); // reset
  reportReady();
}

void loop() 
{
  runSerialRead(commandReceived);
}


void reportReady()
{
  Serial.print("ready,");
  Serial.print(panServo.read());
  Serial.print(",");
  Serial.println(tiltServo.read());
}

void moveCenter(float panInput, float tiltInput)
{
  static PID panPID(screenCenterX, 0.08, 0.08, 0.06);
  static PID tiltPID(screenCenterY, 0.08, 0.08, 0.07);

  int dx = (int)panPID.step(panInput) * panServoScale;
  int dy = (int)tiltPID.step(tiltInput) * tiltServoScale;
  moveServoDelta(dx, -dy);
}

void moveServoDelta(int panDelta, int tiltDelta)
{
  int panNewPos = panServo.read() + panDelta;
  int tiltNewPos = tiltServo.read() + tiltDelta;
  moveServo(panNewPos, tiltNewPos);
}

void moveServo(int pan, int tilt)
{
  running = true;
  if(pan > 0)
    panServo.write(clamp(pan, 0, 180));
  
  if(tilt > 0)
    tiltServo.write(clamp(tilt, 0, 180));

  delay(15);
  running = false;
}

void horizontalScan()
{
  static int current = 90;
  static int dir = 1;
  moveServo(current, -1);
  current = current + dir;
  if(current > 180 || current < 0)
    dir = -dir;
}

void verticalScan()
{
  static int current = 90;
  static int dir = 1;
  moveServo(-1, current);
  current = current + dir;
  if(current > 160 || current < 30)
    dir = -dir;
}

void commandReceived(const String& s)
{
  static int b[] = {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};

  if(parseIntCSV(s, b, 10) >= 2)
  {
    moveCenter(b[0], b[1]);
    reportReady();
  }
}


