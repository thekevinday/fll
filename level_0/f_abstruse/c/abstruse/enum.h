/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines abstruse type data.
 *
 * This is auto-included by abstruse.h and should not need to be explicitly included.
 */
#ifndef _F_type_abstruse_enum_h
#define _F_type_abstruse_enum_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An enumeration representing all standard abstruse union types.
 *
 * Generally, the types ending in "s" represent an array.
 *
 * f_abstruse_uint8:      Maps to uint8_t.
 * f_abstruse_uint8s:     Maps to f_uint8s_t.
 * f_abstruse_uint16:     Maps to uint16_t.
 * f_abstruse_uint16s:    Maps to f_uint16s_t.
 * f_abstruse_uint32:     Maps to uint32_t.
 * f_abstruse_uint32s:    Maps to f_uint32s_t.
 * f_abstruse_uint64:     Maps to uint64_t.
 * f_abstruse_uint64s:    Maps to f_uint64s_t.
 * f_abstruse_int8:       Maps to int8_t.
 * f_abstruse_int8s:      Maps to f_int8_t.
 * f_abstruse_int16:      Maps to int16_t.
 * f_abstruse_int16s:     Maps to f_int16_t.
 * f_abstruse_int32:      Maps to int32_t.
 * f_abstruse_int32s:     Maps to f_int32s_t.
 * f_abstruse_int64:      Maps to int64_t.
 * f_abstruse_int64s:     Maps to f_int64_t.
 * f_abstruse_signed:     Maps to f_number_singed_t.
 * f_abstruse_signeds:    Maps to f_number_singeds_t.
 * f_abstruse_unsigned:   Maps to f_number_unsinged_t.
 * f_abstruse_unsigneds:  Maps to f_number_unsingeds_t.
 * f_abstruse_char:       Maps to f_char_t.
 * f_abstruse_string:     Maps to f_string_t (also: (f_char_t *)).
 * f_abstruse_strings:    Maps to (f_string_t *).
 * f_abstruse_dynamic:    Maps to f_string_dynamic_t (or f_string_static_t).
 * f_abstruse_dynamics:   Maps to f_string_dynamics_t (or f_string_statics_t).
 * f_abstruse_map:        Maps to f_string_map_t.
 * f_abstruse_maps:       Maps to f_string_maps_t.
 * f_abstruse_map_multi:  Maps to f_string_map_multi_t.
 * f_abstruse_map_multis: Maps to f_string_map_multis_t.
 * f_abstruse_quantity:   Maps to f_string_quantity_t.
 * f_abstruse_quantitys:  Maps to f_string_quantitys_t.
 * f_abstruse_range:      Maps to f_string_range_t.
 * f_abstruse_ranges:     Maps to f_string_ranges_t.
 * f_abstruse_triple:     Maps to f_string_triple_t.
 * f_abstruse_triples:    Maps to f_string_triples_t.
 * f_abstruse_void:       Maps to (void *).
 * f_abstruse_voids:      Maps to (void **).
 * f_abstruse_size:       Maps to size_t.
 * f_abstruse_sizes:      Maps to (size_t *).
 * f_abstruse_ssize:      Maps to ssize_t.
 * f_abstruse_ssizes:     Maps to (ssize_t *).
 */
#ifndef _di_f_abstruse_e_
  enum {
    f_abstruse_none_e = 0,
    f_abstruse_uint8_e,
    f_abstruse_uint8s_e,
    f_abstruse_uint16_e,
    f_abstruse_uint16s_e,
    f_abstruse_uint32_e,
    f_abstruse_uint32s_e,
    f_abstruse_uint64_e,
    f_abstruse_uint64s_e,
    f_abstruse_int8_e,
    f_abstruse_int8s_e,
    f_abstruse_int16_e,
    f_abstruse_int16s_e,
    f_abstruse_int32_e,
    f_abstruse_int32s_e,
    f_abstruse_int64_e,
    f_abstruse_int64s_e,
    f_abstruse_signed_e,
    f_abstruse_signeds_e,
    f_abstruse_unsigned_e,
    f_abstruse_unsigneds_e,
    f_abstruse_char_e,
    f_abstruse_string_e,
    f_abstruse_strings_e,
    f_abstruse_dynamic_e,
    f_abstruse_dynamics_e,
    f_abstruse_map_e,
    f_abstruse_maps_e,
    f_abstruse_map_multi_e,
    f_abstruse_map_multis_e,
    f_abstruse_quantity_e,
    f_abstruse_quantitys_e,
    f_abstruse_range_e,
    f_abstruse_ranges_e,
    f_abstruse_triple_e,
    f_abstruse_triples_e,
    f_abstruse_void_e,
    f_abstruse_voids_e,
    f_abstruse_size_e,
    f_abstruse_sizes_e,
    f_abstruse_ssize_e,
    f_abstruse_ssizes_e,
  };
#endif // _di_f_abstruse_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_abstruse_enum_h
