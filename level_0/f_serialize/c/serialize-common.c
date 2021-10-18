#include "serialize.h"
#include "private-serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_splitter_s_
  const f_string_t f_serialize_simple_splitter_s = F_serialize_simple_splitter_s;
  const f_string_t f_serialize_delimited_splitter_s = F_serialize_delimited_splitter_s;
  const f_string_t f_serialize_delimited_delimiter_s = F_serialize_delimited_delimiter_s;
#endif // _di_f_serialize_splitter_s_

#ifdef __cplusplus
} // extern "C"
#endif
