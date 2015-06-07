#ifndef __Knob_H
#define __Knob_H

#include "upm/grove.h"

class Knob: public upm::GroveRotary
{
public:
  Knob();
  ~Knob();

  int percent();
  void test();

private:
  Knob(const Knob & rhs);
  Knob & operator=(const Knob & rhs);
};

#endif // __Knob_H
