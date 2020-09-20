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

#ifndef _di_f_serialize_splitters_
  #define f_serialize_simple_splitter     ':'
  #define f_serialize_delimited_splitter  '\''
  #define f_serialize_delimited_delimiter '\\'

  #define f_serialize_simple_splitter_string     ":"
  #define f_serialize_delimited_splitter_string  "'"
  #define f_serialize_delimited_delimiter_string "\\"
#endif // _di_f_serialize_splitters_

#ifndef _di_f_serialize_default_allocation_step_
  // provide a UTF-8 friendly allocation step.
  #define f_serialize_default_allocation_step 4
#endif // _di_f_serialize_default_allocation_step_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_common_h
