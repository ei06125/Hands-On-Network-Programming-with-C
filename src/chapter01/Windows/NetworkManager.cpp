#include "NetworkManager.h"

#include "networkingTS/SocketUtil.h"
using namespace ei06125::net;

NetworkManager::NetworkManager() {
  if (!SocketUtil::StaticInit()) {
    throw std::runtime_error("Failed to initialize WSA");
  }
}

NetworkManager::~NetworkManager() {
  SocketUtil::CleanUp();
}

void NetworkManager::PrintAdaptersAddresses() const {
  DWORD asize = 20000;
  PIP_ADAPTER_ADDRESSES adapters;
  do {
    adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);

    if (!adapters) {
      printf("Couldn't allocate %ld bytes for adapters.\n", asize);
      return;
    }

    int r = GetAdaptersAddresses(
      AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);
    if (r == ERROR_BUFFER_OVERFLOW) {
      printf("GetAdaptersAddresses wants %ld bytes.\n", asize);
      free(adapters);
    } else if (r == ERROR_SUCCESS) {
      break;
    } else {
      printf("Error from GetAdaptersAddresses: %d\n", r);
      free(adapters);
      return;
    }
  } while (!adapters);

  PIP_ADAPTER_ADDRESSES adapter = adapters;
  while (adapter) {

    printf("\nAdapter name: %S\n", adapter->FriendlyName);

    PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
    while (address) {
      printf("\t%s",
             address->Address.lpSockaddr->sa_family == AF_INET ? "IPv4"
                                                               : "IPv6");

      char ap[100];

      getnameinfo(address->Address.lpSockaddr,
                  address->Address.iSockaddrLength,
                  ap,
                  sizeof(ap),
                  0,
                  0,
                  NI_NUMERICHOST);
      printf("\t%s\n", ap);

      address = address->Next;
    }

    adapter = adapter->Next;
  }
}
