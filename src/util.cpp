#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

#include "util.h"

using namespace std;

long millis()
{
  long millis = 0;
  struct timespec tp = { 0 };

  if( clock_gettime(CLOCK_REALTIME, &tp) == 0 )
  {
    millis = (tp.tv_nsec / 1000000); // + (tp.tv_sec * 1000)
  }

  return millis;
}

std::string get_ip(const std::string & interface)
{
  struct ifaddrs * ifaddr;
  struct ifaddrs * ifa;
  int family;
  int n;
  char host[NI_MAXHOST];
  std::string ip;

  if( getifaddrs(&ifaddr) != -1 )
  {
    for( ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++ )
    {
      if( ifa->ifa_addr == NULL )
        continue;

      family = ifa->ifa_addr->sa_family;

      if( (family == AF_INET) && (std::string(ifa->ifa_name) == interface) )
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
