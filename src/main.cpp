#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

#include "util.h"
#include "Knob.h"
#include "LCD.h"
#include "LED.h"
#include "Button.h"

#include <curl/curl.h>

int running = 0;

using namespace std;

void sig_handler(int signo)
{
  if( signo == SIGINT )
  {
    cout << endl << "[Done]" << endl << endl;
    running = -1;
  }
}

void post(bool button, int knob)
{
  ostringstream url;
  CURL *curl;
  CURLcode res;

  url << "https://data.sparkfun.com/input/Jx9wvp9dWqSEOdnxDXvZ?"
      << "private_key=gzekGMelPvUr0GjDglAE" << "&"
      << "button=" << (button ? 1 : 0) << "&"
      << "knob=" << knob;

  cout << url.str() << endl;

  curl = curl_easy_init();

  if( curl )
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());

    /* example.com is redirected, so we tell libcurl to follow redirection */
   // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if( res != CURLE_OK )
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
          curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
}

int main()
{
  signal(SIGINT, sig_handler);

  LCD lcd;
  LED led;
  Knob knob;
  Button button;

  int knob_value = 0;
  bool button_value = false;

  char msg[18];
  std::string ip;

  led.on();

  while( (ip = get_ip("wlan0")).length() == 0 )
  {
    lcd.clear();
    lcd.write("looking for IP   ");
    sleep(1);
  }

  led.off();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("My IP Address:");
  lcd.setCursor(1, 0);
  lcd.write(ip.c_str());

  sleep(3);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(ip.c_str());

  while( running == 0 )
  {
    lcd.setCursor(1, 0);
    snprintf(msg, sizeof(msg), "knob: %d%%       ", knob.percent());
    lcd.write(msg);

    if( button.value() )
    {
      led.on();
    }
    else
    {
      led.off();
    }

    if( (button_value != button.value()) || (knob.percent() != knob_value) )
    {
      button_value = button.value();
      knob_value = knob.percent();
   //   post( button_value, knob_value );
    }

    usleep(100000);
  }

  return MRAA_SUCCESS;
}
