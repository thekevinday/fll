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
 * When both *_split_range_e and *_split_ranges_e are set, then both the individual ranges and the range sets are split into separate Content (separate columns).
 *
 * Values of f_fss_payload_header_map_flag_*_e:
 *   - none:           No flag set.
 *   - join_digits:    Types of digits are combined into a single Content (single column).
 *   - join_dynamics:  Types of dynamics are combined into a single Content (single column).
 *   - join_map:       Types of map are combined into a single Content (single column), example: "key1 value1" "key2 value2" as opposed to "key1" "value1" "key2" "value2".
 *   - join_maps:      Types of maps are combined into a single Content (single column), example: "key1 value1 key2 value2" as opposed to "key1 value1" "key2 value2" or "key1" "value1" "key2" "value2".
 *   - join_range:     Types of range are combined into a single Content (single column).
 *   - join_ranges:    Types of ranges are combined into a single Content (single column) (this effectively forces join_range to always be treated as set).
 *   - join_strings:   Types of strings are combined into a single Content (single column).
 *   - join_triple:    Types of triple are combined into a single Content (single column), example: "a b c" "d e f" as opposed to "a" "b" "c" "d" "e" "f".
 *   - join_triples:   Types of triples are combined into a single Content (single column), example: "a b c d e f" as opposed to "a b c" "d e f" or "a" "b" "c" "d" "e" "f".
 *   - null:           When the key has no header Content (header value.used is 0), still add the Object (header key) (When this is not set then the Object (header key) is not added).
 *   - null_dynamic:   Types of dynamic and dynamics have empty strings (such as "") added for NULL values (used is 0).
 *   - null_map_key:   Types of map and maps has empty strings (such as "") added for NULL values (used is 0) for the map key.
 *   - null_map_value: Types of map and maps has empty strings (such as "") added for NULL values (used is 0) for the map value.
 *   - null_maps:      Types of dynamic and dynamics have empty strings (such as "") added for when null_map_key and null_map_value are not set and both map key and map value have NULL values (used is 0).
 *   - null_string:    Types of string and strings have empty strings (such as "") for NULL values.
 *   - null_triple_a:  Types of triple and triples has empty strings (such as "") added for NULL values (used is 0) for the "a" property.
 *   - null_triple_b:  Types of triple and triples has empty strings (such as "") added for NULL values (used is 0) for the "b" property.
 *   - null_triple_c:  Types of triple and triples has empty strings (such as "") added for NULL values (used is 0) for the "c" property.
 *   - quote_double:   Use double quotes (U+0022) when quoting strings.
 *   - quote_grave:    Use grave (U+0060) when quoting strings.
 *   - quote_single:   Use single quotes (U+0027) when quoting strings.
 *   - last:           This does nothing and is provided to be used as a starting point for anything extending this (there should be a max total of 64 bits allowed).
 */
#ifndef _di_f_fss_payload_header_map_flag_e_
  enum {
    f_fss_payload_header_map_flag_none_e           = 0x0,
    f_fss_payload_header_map_flag_join_digits_e    = 0x1,
    f_fss_payload_header_map_flag_join_dynamics_e  = 0x2,
    f_fss_payload_header_map_flag_join_range_e     = 0x4,
    f_fss_payload_header_map_flag_join_ranges_e    = 0x8,
    f_fss_payload_header_map_flag_join_strings_e   = 0x10,
    f_fss_payload_header_map_flag_join_triple_e    = 0x20,
    f_fss_payload_header_map_flag_join_triples_e   = 0x40,
    f_fss_payload_header_map_flag_null_e           = 0x80,
    f_fss_payload_header_map_flag_null_dynamic_e   = 0x100,
    f_fss_payload_header_map_flag_null_map_key_e   = 0x200,
    f_fss_payload_header_map_flag_null_map_value_e = 0x400,
    f_fss_payload_header_map_flag_null_maps_e      = 0x800,
    f_fss_payload_header_map_flag_null_triple_a_e  = 0x1000,
    f_fss_payload_header_map_flag_null_triple_b_e  = 0x2000,
    f_fss_payload_header_map_flag_null_triple_c_e  = 0x4000,
    f_fss_payload_header_map_flag_null_string_e    = 0x8000,
    f_fss_payload_header_map_flag_quote_double_e   = 0x10000,
    f_fss_payload_header_map_flag_quote_grave_e    = 0x20000,
    f_fss_payload_header_map_flag_quote_single_e   = 0x40000,
    f_fss_payload_header_map_flag_last_e           = 0x80000,
  }; // enum
#endif // _di_f_fss_payload_header_flag_map_e_

/**
 * FSS-000E (Payload) strings.
 *
 * A small amount of recommended or assumed common "header" Content Object strings are provided and are noted as "an optional string".
 *
 * f_fss_payload_comment_*_s:
 *   - header:       The complete header comment line for Payload (FSS-000E).
 *   - header_end:   The complete header comment line for Payload (FSS-000E).
 *   - header_begin: The complete header comment line for Payload (FSS-000E).
 *
 * f_fss_payload_object_*_s:
 *   - end:       The Object end characters.
 *   - header:    The header Object or signature Content header Object.
 *   - id:        The header Content id Object (an optional string).
 *   - length:    The header Content length Object (an optional string).
 *   - name:      The header Content name Object (an optional string).
 *   - part:      The header Content part Object (an optional string).
 *   - payload:   The payload Object or signature Content payload Object.
 *   - signature: The signature Object.
 *   - size:      The header Content size Object (an optional string).
 *   - status:    The header Content status Object (an optional string).
 *   - total:     The header Content total Object (an optional string).
 *   - type:      The header Content type Object (an optional string).
 */
#ifndef _di_f_fss_payload_s_
  #define F_fss_payload_comment_header_s       "fss-000e"
  #define F_fss_payload_comment_header_end_s   "\n"
  #define F_fss_payload_comment_header_begin_s "# "

  #define F_fss_payload_object_end_s       ":\n"
  #define F_fss_payload_object_header_s    "header"
  #define F_fss_payload_object_id_s        "id"
  #define F_fss_payload_object_length_s    "length"
  #define F_fss_payload_object_name_s      "name"
  #define F_fss_payload_object_part_s      "part"
  #define F_fss_payload_object_payload_s   "payload"
  #define F_fss_payload_object_signature_s "signature"
  #define F_fss_payload_object_size_s      "size"
  #define F_fss_payload_object_status_s    "status"
  #define F_fss_payload_object_total_s     "total"
  #define F_fss_payload_object_type_s      "type"

  #define F_fss_payload_comment_header_s_length       8
  #define F_fss_payload_comment_header_end_s_length   1
  #define F_fss_payload_comment_header_begin_s_length 2

  #define F_fss_payload_object_end_s_length       2
  #define F_fss_payload_object_header_s_length    6
  #define F_fss_payload_object_id_s_length        2
  #define F_fss_payload_object_length_s_length    6
  #define F_fss_payload_object_name_s_length      4
  #define F_fss_payload_object_part_s_length      4
  #define F_fss_payload_object_payload_s_length   7
  #define F_fss_payload_object_signature_s_length 9
  #define F_fss_payload_object_size_s_length      4
  #define F_fss_payload_object_status_s_length    6
  #define F_fss_payload_object_total_s_length     5
  #define F_fss_payload_object_type_s_length      4

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

  #ifndef _di_f_fss_payload_object_id_s_
    extern const f_string_static_t f_fss_payload_object_id_s;
  #endif // _di_f_fss_payload_object_id_s_

  #ifndef _di_f_fss_payload_object_length_s_
    extern const f_string_static_t f_fss_payload_object_length_s;
  #endif // _di_f_fss_payload_object_length_s_

  #ifndef _di_f_fss_payload_object_name_s_
    extern const f_string_static_t f_fss_payload_object_name_s;
  #endif // _di_f_fss_payload_object_name_s_

  #ifndef _di_f_fss_payload_object_part_s_
    extern const f_string_static_t f_fss_payload_object_part_s;
  #endif // _di_f_fss_payload_object_part_s_

  #ifndef _di_f_fss_payload_object_payload_s_
    extern const f_string_static_t f_fss_payload_object_payload_s;
  #endif // _di_f_fss_payload_object_payload_s_

  #ifndef _di_f_fss_payload_object_signature_s_
    extern const f_string_static_t f_fss_payload_object_signature_s;
  #endif // _di_f_fss_payload_object_signature_s_

  #ifndef _di_f_fss_payload_object_size_s_
    extern const f_string_static_t f_fss_payload_object_size_s;
  #endif // _di_f_fss_payload_object_size_s_

  #ifndef _di_f_fss_payload_object_status_s_
    extern const f_string_static_t f_fss_payload_object_status_s;
  #endif // _di_f_fss_payload_object_status_s_

  #ifndef _di_f_fss_payload_object_total_s_
    extern const f_string_static_t f_fss_payload_object_total_s;
  #endif // _di_f_fss_payload_object_total_s_

  #ifndef _di_f_fss_payload_object_type_s_
    extern const f_string_static_t f_fss_payload_object_type_s;
  #endif // _di_f_fss_payload_object_type_s_
#endif // _di_f_fss_payload_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_payload_h
