#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_payload_type_identify_
  const uint8_t control_payload_type_identify(const f_string_static_t payload) {

    if (f_compare_dynamic(payload, control_controller_s) == F_equal_to) return control_payload_type_controller_e;
    if (f_compare_dynamic(payload, control_error_s) == F_equal_to) return control_payload_type_error_e;
    if (f_compare_dynamic(payload, control_init_s) == F_equal_to) return control_payload_type_init_e;

    return 0;
  }
#endif // _di_control_payload_type_identify_

#ifndef _di_control_payload_type_name_
  const f_string_static_t control_payload_type_name(const uint8_t type) {

    switch (type) {
      case control_payload_type_controller_e:
        return control_controller_s;

      case control_payload_type_error_e:
        return control_error_s;

      case control_payload_type_init_e:
        return control_init_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_payload_type_name_

#ifdef __cplusplus
} // extern "C"
#endif
