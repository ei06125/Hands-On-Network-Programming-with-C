#include "networkingTS/DefaultNetworkManager.h"

#include "networkingTS/SocketUtil.h"

namespace ei06125::net {

  DefaultNetworkManager::DefaultNetworkManager() {
    if (!SocketUtil::StaticInit()) {
      throw std::runtime_error("Failed to initialize WSA");
    }
  }

  DefaultNetworkManager::~DefaultNetworkManager() {
    SocketUtil::CleanUp();
  }

} // namespace ei06125::net