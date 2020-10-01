//  Created by psksvp on 12/1/20.
//  Copyright © 2020 psksvp. All rights reserved.
//

#ifndef __CLASS_PID__
#define __CLASS_PID__

#include "utils.h"

class PID 
{
  private: 
    float integral = 0;
    float derivative = 0;
    
    float kP, kI, kD;
    float setPoint;

    float outputMin, outputMax;

  public:
    PID(float setPt, 
        float p, float i, float d,
        float outMin = -10.0f,
        float outMax = 10.0f)
    {
      kP = p;
      kI = i;
      kD = d; 
      setPoint = setPt;

      if(outMax < outMin)
        swap(outMin, outMax);

      outputMin = outMin;
      outputMax = outMax;
    }

    float step(float input)
    {
      float error = setPoint - input;
      float nextIntegral = clamp(integral + error, outputMin, outputMax);
      float nextDerivative = error;
      float p = kP * error;
      float d = kD * (error - derivative);
      float i = nextIntegral * kI; 
      integral = nextIntegral;
      derivative = nextDerivative;
      return p + i + d;
    }
};

// class PID2
// {
//   private: 
//     float integral = 0;
//     float derivative = 0;
    
//     float kP, kI, kD;
//     float setPoint;

//     float outputMin, outputMax;

//   public:
//     PID2(float setPt, 
//         float p, float i, float d,
//         float outMin = -10.0f,
//         float outMax = 10.0f)
//     {
//       kP = p;
//       kI = i;
//       kD = d; 
//       setPoint = setPt;

//       if(outMax < outMin)
//         swap(outMin, outMax);

//       outputMin = outMin;
//       outputMax = outMax;
//     }

//     float step(float input)
//     {
//       return 0.0f;
//     }
// };

#endif