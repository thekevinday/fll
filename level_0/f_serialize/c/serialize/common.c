#include "../serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_splitter_s_
  #ifndef _di_f_serialize_delimited_delimiter_s_
    const f_string_static_t f_serialize_delimited_delimiter_s = macro_f_string_static_t_initialize(F_serialize_delimited_delimiter_s, 0, F_serialize_delimited_delimiter_s_length);
  #endif // _di_f_serialize_delimited_delimiter_s_

  #ifndef _di_f_serialize_delimited_splitter_s_
    const f_string_static_t f_serialize_delimited_splitter_s = macro_f_string_static_t_initialize(F_serialize_delimited_splitter_s, 0, F_serialize_delimited_splitter_s_length);
  #endif // _di_f_serialize_delimited_splitter_s_

  #ifndef _di_f_serialize_to_simple_splitter_s_
    const f_string_static_t f_serialize_to_simple_splitter_s = macro_f_string_static_t_initialize(F_serialize_simple_splitter_s, 0, F_serialize_simple_splitter_s_length);
  #endif // _di_f_serialize_to_simple_splitter_s_
#endif // _di_f_serialize_splitter_s_

#ifdef __cplusplus
} // extern "C"
#endif
