#include "NetworkManager.h"

NetworkManager::NetworkManager() = default;

NetworkManager::~NetworkManager() = default;

void NetworkManager::PrintAdaptersAddresses() const {

  struct ifaddrs* addresses;

  if (getifaddrs(&addresses) == -1) {
    printf("getifaddrs call failed\n");
    return;
  }

  struct ifaddrs* address = addresses;
  while (address) {
    if (address->ifa_addr == NULL) {
      address = address->ifa_next;
      continue;
    }
    int family = address->ifa_addr->sa_family;
    if (family == AF_INET || family == AF_INET6) {

      printf("%s\t", address->ifa_name);
      printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");

      char ap[100];
      const unsigned int family_size = family == AF_INET
                                         ? sizeof(struct sockaddr_in)
                                         : sizeof(struct sockaddr_in6);
      getnameinfo(
        address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
      printf("\t%s\n", ap);
    }
    address = address->ifa_next;
  }

  freeifaddrs(addresses);
}
