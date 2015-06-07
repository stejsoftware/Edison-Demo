#include <unistd.h>
#include "LED.h"

LED::LED() :
    GroveLed(3)
{
}

LED::~LED()
{
  off();
}

void LED::test()
{
  for( int x = 0; x < 5; x++ )
  {
    on();
    usleep(500000);

    off();
    usleep(500000);
  }
}
