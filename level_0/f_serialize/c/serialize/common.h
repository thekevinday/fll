/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
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
  #define F_serialize_delimited_delimiter_s "\\"
  #define F_serialize_delimited_splitter_s  "'"
  #define F_serialize_simple_splitter_s     ":"

  #define F_serialize_delimited_delimiter_s_length 1
  #define F_serialize_delimited_splitter_s_length  1
  #define F_serialize_simple_splitter_s_length     1

  extern const f_string_static_t f_serialize_delimited_delimiter_s;
  extern const f_string_static_t f_serialize_delimited_splitter_s;
  extern const f_string_static_t f_serialize_to_simple_splitter_s;
#endif // _di_f_serialize_splitter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_common_h
