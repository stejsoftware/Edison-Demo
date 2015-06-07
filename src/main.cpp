#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

#include <iostream>

#include "mraa.hpp"
#include "upm/jhd1313m1.h"
#include "upm/grove.h"

#include "Knob.h"
#include "LCD.h"
#include "LED.h"

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

void test_button()
{
  upm::GroveButton * button = new upm::GroveButton(2);

  for( int x = 0; x < 100; x++ )
  {
    cout << "button: " << (button->value() ? "On" : "Off") << endl;
    usleep(100000);
  }

  delete button;
}

std::string myIP()
{
  struct ifaddrs * ifaddr;
  struct ifaddrs * ifa;
  int family;
  int n;
  char host[NI_MAXHOST];
  std::string ip("[unknown]");

  if( getifaddrs(&ifaddr) != -1 )
  {
    for( ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++ )
    {
      if( ifa->ifa_addr == NULL )
        continue;

      family = ifa->ifa_addr->sa_family;

      if( (family == AF_INET) && (std::string(ifa->ifa_name) == "wlan0") )
      {
        getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST,
            NULL, 0, NI_NUMERICHOST);
        ip = host;
      }
    }

    freeifaddrs(ifaddr);
  }

  return ip;
}

int main()
{
  signal(SIGINT, sig_handler);

  LCD lcd;
  LED led;
  Knob knob;

  char msg[18];
  std::string ip;

  led.on();

  while( (ip = myIP()) == "[unknown]" )
  {
    lcd.write("looking for IP   ");

    led.off();
    usleep(500000);

    led.on();
    usleep(500000);
  }

  led.on();

  lcd.setCursor(0, 0);
  lcd.write(ip.c_str());
  lcd.write("   ");

  while( running == 0 )
  {
    lcd.setCursor(1, 0);
    snprintf(msg, sizeof(msg), "knob: %d%%    ", knob.percent());
    lcd.write(msg);

    usleep(10000);
  }

  return MRAA_SUCCESS;
}
