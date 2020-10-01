//  Created by psksvp on 12/1/20.
//  Copyright © 2020 psksvp. All rights reserved.
//

#include "utils.h"

bool runSerialRead(void(*read)(const String&))
{
  static String command = "";
  if (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    command += inChar;
    if (inChar == '\n') 
    {
      read(command);
      command = "";
      return true;
    } 
  }

  return false;
}

int parseIntCSV(const String& s, int data[], unsigned int datalength)
{
  unsigned int i = 0;
  unsigned int f = 0;
  int idx = s.indexOf(',', f);
  while(i < datalength && idx >= 0)
  {
    data[i] = s.substring(f, idx).toInt();
    f = idx + 1;
    i = i + 1;
    idx = s.indexOf(',', f);
    if(i < 10 && idx < 0 && f < s.length()) // capture the last one 
    {
      data[i] = s.substring(f).toFloat();
      i = i + 1;
    }
  }
  return i; // number of data filled 
}

void blink(int pin = LED_BUILTIN, int delayMilliSec = 50)
{
  static int state = HIGH;
  digitalWrite(pin, state);   
  state = HIGH == state ? LOW : HIGH;
  delay(delayMilliSec);
}