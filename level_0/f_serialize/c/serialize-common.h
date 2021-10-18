/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project serialize.
 *
 * This is auto-included by serialize.h and should not need to be explicitly included.
 */
#ifndef _F_serialize_common_h
#define _F_serialize_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_splitter_s_
  #define F_serialize_simple_splitter_s     ":"
  #define F_serialize_delimited_splitter_s  "'"
  #define F_serialize_delimited_delimiter_s "\\"

  extern const f_string_t f_serialize_simple_splitter_s;
  extern const f_string_t f_serialize_delimited_splitter_s;
  extern const f_string_t f_serialize_delimited_delimiter_s;
#endif // _di_f_serialize_splitter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_common_h
