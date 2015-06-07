#include <iostream>
#include <math.h>
#include <unistd.h>
#include "Knob.h"

using namespace std;

Knob::Knob() :
    GroveRotary(0)
{
}

Knob::~Knob()
{
}

int Knob::percent()
{
  return ceil((abs_value() / 1024.0) * 100);
}

void Knob::test()
{
  for( int x = 0; x < 100; x++ )
  {
    cout << "knob: %" << percent() << endl;
    usleep(100000);
  }
}
