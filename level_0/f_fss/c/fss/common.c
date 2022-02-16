#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_strings_
  const f_string_static_t f_fss_string_header_s = macro_f_string_static_t_initialize(F_fss_string_header_s, 0, F_fss_string_header_s_length);
  const f_string_static_t f_fss_string_payload_s = macro_f_string_static_t_initialize(F_fss_string_payload_s, 0, F_fss_string_payload_s_length);
#endif // _di_f_fss_strings_

#ifdef __cplusplus
} // extern "C"
#endif
