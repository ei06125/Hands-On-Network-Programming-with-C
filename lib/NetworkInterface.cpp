#include "networkingTS/NetworkInterface.h"

#include "networkingTS/DefaultNetworkManager.h"

namespace ei06125::net {

  NetworkInterface* instance = nullptr;

  NetworkInterface* GetNetworkInterface() {

    // Local object, initialized by an 'Immediately Invoked Lambda Expression
    // (IILE)'
    static bool init = []() {
      if (!instance) {
        static DefaultNetworkManager theNetworkManager;
        instance = &theNetworkManager;
      }
      return true; // or false, as the actual value does not matter.
    }(); // Note the '()' after the lambda expression. This invokes the lambda.

    return instance;
  }

  void SetNetworkInterface(NetworkInterface* aNetworkInterfaceInstance) {
    instance = aNetworkInterfaceInstance;
  }

} // namespace ei06125::net
