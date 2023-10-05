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
 * Flags used by the FSS-000E (Simple Packet) write functions.
 *
 * Values of f_fss_payload_write_*_e:
 *   - none:              No write flag set.
 *   - comment_header:    Print the header comment for the Simple Packet, "# fss-000f\n".
 *   - header_content:    Print the header content.
 *   - header_object:     Print the header object, "header:\n".
 *   - payload_object:    Print the payload object, "payload:\n".
 *   - signature_content: Print the signature content.
 *   - signature_object:  Print the signature object, "signature:\n".
 */
#ifndef _di_f_fss_payload_write_e_
  enum {
    f_fss_payload_write_none_e              = 0x0,
    f_fss_payload_write_comment_header_e    = 0x1,
    f_fss_payload_write_header_content_e    = 0x2,
    f_fss_payload_write_header_object_e     = 0x4,
    f_fss_payload_write_payload_object_e    = 0x8,
    f_fss_payload_write_signature_content_e = 0x10,
    f_fss_payload_write_signature_object_e  = 0x20,
  }; // enum
#endif // _di_f_fss_payload_write_e_

/**
 * FSS Simple Packet strings.
 *
 * f_fss_payload_*_s:
 *   - header_comment:   The header comment string for Simple Packet (FSS-000E).
 *   - header_object:    The header object.
 *   - payload_object:   The payload object.
 *   - signature_object: The signature object.
 */
#ifndef _di_f_fss_payload_s_
  #define F_fss_payload_comment_header_s   "# fss-000e"
  #define F_fss_payload_object_header_s    "header:\n"
  #define F_fss_payload_object_payload_s   "payload:\n"
  #define F_fss_payload_object_signature_s "signature:\n"

  #define F_fss_payload_comment_header_s_length   10
  #define F_fss_payload_object_header_s_length    8
  #define F_fss_payload_object_payload_s_length   9
  #define F_fss_payload_object_signature_s_length 11

  #ifndef _di_f_fss_payload_comment_header_s_
    extern const f_string_static_t f_fss_payload_comment_header_s;
  #endif // _di_f_fss_payload_comment_header_s_

  #ifndef _di_f_fss_payload_object_header_s_
    extern const f_string_static_t f_fss_payload_object_header_s;
  #endif // _di_f_fss_payload_object_header_s_

  #ifndef _di_f_fss_payload_object_payload_s_
    extern const f_string_static_t f_fss_payload_object_payload_s;
  #endif // _di_f_fss_payload_object_payload_s_

  #ifndef _di_f_fss_payload_object_signature_s_
    extern const f_string_static_t f_fss_payload_object_signature_s;
  #endif // _di_f_fss_payload_object_signature_s_
#endif // _di_f_fss_payload_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_payload_h
