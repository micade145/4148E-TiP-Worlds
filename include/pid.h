#include "vex.h"
// #pragma once

class PID {
private: 
  double m_kP = 0;
  double m_kD = 0;
  
  double m_error = 0;
  double m_lastError = 0;
  double m_derivative = 0;
  double m_output = 0;
  
public:
  PID(double kP, double kD);
  double calculateErr(double);
  double calculate(double, double);
  double getError();
  void reset();
};
