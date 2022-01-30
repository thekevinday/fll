#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_control_delete_simple_
  void controller_control_delete_simple(controller_control_t * const control) {

    f_string_dynamic_resize(0, &control->cache_1);
    f_string_dynamic_resize(0, &control->cache_2);
    f_string_dynamic_resize(0, &control->cache_3);

    f_string_dynamic_resize(0, &control->input);
    f_string_dynamic_resize(0, &control->output);
  }
#endif // _di_controller_control_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
