#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "util.h"
#include "Button.h"

using namespace std;

void default_click_handler(const Button & sender)
{
  cout << "* click *" << endl;
}

void * threadProc(void * arg)
{
  Button * button = (Button*) arg;

  if( button != NULL )
  {
    button->threadProc();
  }

  return NULL;
}

Button::Button() :
    GroveButton(2),
    m_click_handler(default_click_handler)
{
  /*
   pthread_t thread_id;
   pthread_attr_t attr;

   pthread_attr_init(&attr);

   //  int stack_size = 0;
   //  pthread_attr_setstacksize(&attr, stack_size);

   m_thread = pthread_create(&thread_id, &attr, ::threadProc, this);

   pthread_attr_destroy(&attr);
   */
}

Button::~Button()
{
}

void Button::threadProc()
{
  bool done = false;

  bool on = false;
  long time_on = 0;
  long time_off = 0;

  while( !done )
  {
    if( !on && (value() == 1) )
    {
      on = true;
      time_on = millis();
    }
    else if( on && (value() == 0) )
    {
      on = false;
      time_off = millis();
    }

    long time_diff = time_off - time_on;

    if( (time_diff >= 50) && (time_diff <= 150) )
    {
      time_on = 0;
      time_off = 0;

      if( m_click_handler != NULL )
      {
        m_click_handler(*this);
      }
    }
  }
}
