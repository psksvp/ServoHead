//  Created by psksvp on 12/1/20.
//  Copyright © 2020 psksvp. All rights reserved.
//
#ifndef __CLASS_TASK__
#define __CLASS_TASK__

class Task
{
  private: 
    unsigned long lastRun;
    unsigned long runInterval;

  public:
    Task(unsigned long interval)
    {
      runInterval = interval;
    }

    void timeslice(unsigned long currentMillis)
    {
      if((currentMillis - lastRun) > runInterval)
      {
        run();
      }
    }

    virtual void run();
};


#endif