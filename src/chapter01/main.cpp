#include "NetworkingTS/NetworkManager.h"

#include <format>
#include <iostream>

int main() {
  using namespace ei06125::net;
  auto* network = GetNetworkInterface();
  network->PrintAdaptersAddresses();
}
