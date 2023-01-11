#pragma once

#include "networkingTS/NetworkInterface.h"

namespace ei06125::net {

  class NetworkManager : public NetworkInterface {
   public:
    NetworkManager();
    ~NetworkManager() override;

   private:
    void PrintAdaptersAddresses_() const override;
  };

} // namespace ei06125::net
