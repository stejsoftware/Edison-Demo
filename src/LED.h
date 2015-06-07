#ifndef __LED_H
#define __LED_H

#include "upm/grove.h"

class LED: public upm::GroveLed
{
public:
  LED();
  ~LED();

  void test();

private:
  LED(const LED & rhs);
  LED & operator=(const LED & rhs);
};

#endif // __LED_H
