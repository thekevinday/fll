#include "mock-network.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t __wrap_htonl(uint32_t hostlong) {

  return mock_type(uint32_t);
}

uint16_t __wrap_htons(uint16_t hostshort) {

  return mock_type(uint16_t);
}

uint32_t __wrap_ntohl(uint32_t netlong) {

  return mock_type(uint32_t);
}

uint16_t __wrap_ntohs(uint16_t netshort) {

  return mock_type(uint16_t);
}

#ifdef __cplusplus
} // extern "C"
#endif
