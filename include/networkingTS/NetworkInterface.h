#pragma once

namespace ei06125::net {

  class NetworkInterface {
   public:
    virtual ~NetworkInterface() noexcept = default;

    // void PrintAdaptersAddresses() const { PrintAdaptersAddresses_(); }

   private:
    // virtual void PrintAdaptersAddresses_() const = 0;
  };

  [[nodiscard]] NetworkInterface* GetNetworkInterface();
  void SetNetworkInterface(NetworkInterface* aNetworkInterfaceInstance);

  extern NetworkInterface* instance;

} // namespace ei06125::net
