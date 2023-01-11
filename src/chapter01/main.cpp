#include "NetworkManager.h"

using namespace ei06125;

int main() {
  auto newNetworkManager = std::make_unique<NetworkManager>();
  net::SetNetworkInterface(newNetworkManager.get());
  newNetworkManager->PrintAdaptersAddresses();
  return 0;
}
