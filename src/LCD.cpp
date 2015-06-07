#include <unistd.h>
#include "LCD.h"

LCD::LCD() :
    Jhd1313m1(0, 0x3E, 0x62)
{
  clear();
  setColor(100, 100, 100);
}

LCD::~LCD()
{
  clear();
  setColor(0, 0, 0);
}

void LCD::test()
{
  setCursor(0, 0);
  write("Hello Edison World");

  setColor(255, 0, 0);
  sleep(1);

  setColor(0, 255, 0);
  sleep(1);

  setColor(0, 0, 255);
  sleep(1);

  clear();
  setColor(0, 0, 0);
}
