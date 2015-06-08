#ifndef __Button_H
#define __Button_H

#include "upm/grove.h"

class Button;

typedef void (*ClickHandler)(const Button & sender);

class Button: public upm::GroveButton
{
public:
  Button();
  ~Button();

  void setClickHandler(ClickHandler handler);
  void threadProc();

private:
  Button(const Button & rhs);
  Button & operator=(const Button & rhs);

  ClickHandler m_click_handler;
  long m_thread;
};

#endif // __Button_H
