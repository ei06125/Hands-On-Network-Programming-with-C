#pragma once

#include "networkingTS/NetworkInterface.h"

class NetworkManager : public ei06125::net::NetworkInterface {
 public:
  NetworkManager();
  ~NetworkManager() override;

  void PrintAdaptersAddresses() const;
};
