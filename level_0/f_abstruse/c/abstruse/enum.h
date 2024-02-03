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
 * f_abstruse_*_e:
 *   - none:       No value set.
 *   - int8s:      Maps to f_int8s_t.
 *   - int16s:     Maps to f_int16s_t.
 *   - int32s:     Maps to f_int32s_t.
 *   - int64s:     Maps to f_int64s_t.
 *   - uint8s:     Maps to f_uint8s_t.
 *   - uint16s:    Maps to f_uint16s_t.
 *   - uint32s:    Maps to f_uint32s_t.
 *   - uint64s:    Maps to f_uint64s_t.
 *   - signed:     Maps to f_number_singed_t.
 *   - signeds:    Maps to f_number_singeds_t.
 *   - unsigned:   Maps to f_number_unsinged_t.
 *   - unsigneds:  Maps to f_number_unsingeds_t.
 *   - string:     Maps to f_string_t, also: (f_char_t *).
 *   - strings:    Maps to (f_string_t *).
 *   - dynamic:    Maps to f_string_dynamic_t, also: f_string_static_t.
 *   - dynamics:   Maps to f_string_dynamics_t, also: f_string_statics_t.
 *   - map:        Maps to f_string_map_t.
 *   - maps:       Maps to f_string_maps_t.
 *   - map_multi:  Maps to f_string_map_multi_t.
 *   - map_multis: Maps to f_string_map_multis_t.
 *   - quantity:   Maps to f_quantity_t.
 *   - quantitys:  Maps to f_quantitys_t.
 *   - range:      Maps to f_range_t.
 *   - ranges:     Maps to f_ranges_t.
 *   - triple:     Maps to f_string_triple_t.
 *   - triples:    Maps to f_string_triples_t.
 *   - void:       Maps to (void *).
 *   - voids:      Maps to (void **).
 */
#ifndef _di_f_abstruse_e_
  enum {
    f_abstruse_none_e = 0,
    f_abstruse_int8s_e,
    f_abstruse_int16s_e,
    f_abstruse_int32s_e,
    f_abstruse_int64s_e,
    f_abstruse_uint8s_e,
    f_abstruse_uint16s_e,
    f_abstruse_uint32s_e,
    f_abstruse_uint64s_e,
    f_abstruse_signed_e,
    f_abstruse_signeds_e,
    f_abstruse_unsigned_e,
    f_abstruse_unsigneds_e,
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
  }; // enum
#endif // _di_f_abstruse_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_abstruse_enum_h
