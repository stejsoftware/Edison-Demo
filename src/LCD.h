#ifndef __LCD_H
#define __LCD_H

#include "upm/jhd1313m1.h"

class LCD: public upm::Jhd1313m1
{
public:
  LCD();
  ~LCD();

  void test();

private:
  LCD(const LCD & rhs);
  LCD & operator=(const LCD & rhs);
};

#endif // __LCD_H
