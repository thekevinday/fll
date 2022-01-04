#include "../controller.h"
#include "../private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_packet_delete_simple_
  void controller_packet_delete_simple(controller_packet_t * const packet) {

    f_string_dynamic_resize(0, &packet->payload);
  }
#endif // _di_controller_packet_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
