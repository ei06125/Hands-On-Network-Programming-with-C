#pragma once

namespace ei06125::net {

  enum SocketAddressFamily { INET = AF_INET, INET6 = AF_INET6 };

  class SocketUtil {
   public:
    static bool StaticInit();
    static void CleanUp();

    static void ReportError(const char* inOperationDesc);
    static int GetLastError();
  };

} // namespace ei06125::net
