/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_payload_h
#define _F_fss_payload_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags used by the FSS-000E (Payload) header map functions.
 *
 * Values of f_fss_payload_header_map_*_e:
 *   - none:    No map flag set.
 *   - base_2:  Convert number to string using base 2.
 *   - base_8:  Convert number to string using base 8.
 *   - base_10: Convert number to string using base 10.
 *   - base_12: Convert number to string using base 12.
 *   - base_16: Convert number to string using base 16.
 */
#ifndef _di_f_fss_payload_header_map_e_
  enum {
    f_fss_payload_header_map_none_e    = 0x0,
    f_fss_payload_header_map_base_2_e  = 0x1,
    f_fss_payload_header_map_base_8_e  = 0x2,
    f_fss_payload_header_map_base_10_e = 0x4,
    f_fss_payload_header_map_base_12_e = 0x8,
    f_fss_payload_header_map_base_16_e = 0x10,
  }; // enum
#endif // _di_f_fss_payload_header_map_e_

/**
 * FSS-000E (Payload) strings.
 *
 * f_fss_payload_comment_*_s:
 *   - header:       The complete header comment line for Payload (FSS-000E).
 *   - header_end:   The complete header comment line for Payload (FSS-000E).
 *   - header_begin: The complete header comment line for Payload (FSS-000E).
 *
 * f_fss_payload_object_*_s:
 *   - end:       The Object end characters.
 *   - header:    The header Object or signature Content header Object.
 *   - length:    The header Content length Object.
 *   - part:      The header Content part Object.
 *   - payload:   The payload Object or signature Content payload Object.
 *   - signature: The signature Object.
 *   - status:    The header Content status Object.
 *   - total:     The header Content total Object.
 */
#ifndef _di_f_fss_payload_s_
  #define F_fss_payload_comment_header_s       "fss-000e"
  #define F_fss_payload_comment_header_end_s   "\n"
  #define F_fss_payload_comment_header_begin_s "# "

  #define F_fss_payload_object_end_s       ":\n"
  #define F_fss_payload_object_header_s    "header"
  #define F_fss_payload_object_length_s    "length"
  #define F_fss_payload_object_part_s      "part"
  #define F_fss_payload_object_payload_s   "payload"
  #define F_fss_payload_object_signature_s "signature"
  #define F_fss_payload_object_status_s    "status"
  #define F_fss_payload_object_total_s     "total"

  #define F_fss_payload_comment_header_s_length       8
  #define F_fss_payload_comment_header_end_s_length   1
  #define F_fss_payload_comment_header_begin_s_length 2

  #define F_fss_payload_object_end_s_length       2
  #define F_fss_payload_object_length_s_length    6
  #define F_fss_payload_object_header_s_length    6
  #define F_fss_payload_object_part_s_length      4
  #define F_fss_payload_object_payload_s_length   7
  #define F_fss_payload_object_signature_s_length 9
  #define F_fss_payload_object_status_s_length    6
  #define F_fss_payload_object_total_s_length     5

  #ifndef _di_f_fss_payload_comment_header_s_
    extern const f_string_static_t f_fss_payload_comment_header_s;
  #endif // _di_f_fss_payload_comment_header_s_

  #ifndef _di_f_fss_payload_comment_header_end_s_
    extern const f_string_static_t f_fss_payload_comment_header_end_s;
  #endif // _di_f_fss_payload_comment_header_end_s_

  #ifndef _di_f_fss_payload_comment_header_begin_s_
    extern const f_string_static_t f_fss_payload_comment_header_begin_s;
  #endif // _di_f_fss_payload_comment_header_begin_s_

  #ifndef _di_f_fss_payload_object_end_s_
    extern const f_string_static_t f_fss_payload_object_end_s;
  #endif // _di_f_fss_payload_object_end_s_

  #ifndef _di_f_fss_payload_object_header_s_
    extern const f_string_static_t f_fss_payload_object_header_s;
  #endif // _di_f_fss_payload_object_header_s_

  #ifndef _di_f_fss_payload_object_length_s_
    extern const f_string_static_t f_fss_payload_object_length_s;
  #endif // _di_f_fss_payload_object_length_s_

  #ifndef _di_f_fss_payload_object_payload_s_
    extern const f_string_static_t f_fss_payload_object_payload_s;
  #endif // _di_f_fss_payload_object_payload_s_

  #ifndef _di_f_fss_payload_object_signature_s_
    extern const f_string_static_t f_fss_payload_object_signature_s;
  #endif // _di_f_fss_payload_object_signature_s_

  #ifndef _di_f_fss_payload_object_status_s_
    extern const f_string_static_t f_fss_payload_object_status_s;
  #endif // _di_f_fss_payload_object_status_s_
#endif // _di_f_fss_payload_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_payload_h
