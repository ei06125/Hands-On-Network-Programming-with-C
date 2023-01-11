#pragma once

#include "networkingTS/NetworkInterface.h"

namespace ei06125::net {

  class DefaultNetworkManager : public NetworkInterface {
   public:
    DefaultNetworkManager();
    ~DefaultNetworkManager() override;
  };

} // namespace ei06125::net