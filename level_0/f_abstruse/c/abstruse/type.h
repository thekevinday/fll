/**
 * FLL - Level 0
 *
 * Project: Abstuse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines abstruse type data.
 *
 * This is auto-included by abstruse.h and should not need to be explicitly included.
 */
#ifndef _F_type_abstruse_type_h
#define _F_type_abstruse_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An abstruse type is a union representing any particular set of common types.
 *
 * The common type property names are prefixed with "a_" followed by the type name without the suffix "_t".
 *
 * This must be specially handled when swapping between types that contain allocated data.
 * Be sure to de-allocate all memory before swapping to a differrent type.
 */
#ifndef _di_f_abstruse_type_t_
  typedef union {
    f_uint8s_t            a_u8s;
    f_uint16s_t           a_u16s;
    f_uint32s_t           a_u32s;
    f_uint64s_t           a_u64s;
    f_int8s_t             a_i8s;
    f_int16s_t            a_i16s;
    f_int32s_t            a_i32s;
    f_int64s_t            a_i64s;
    f_number_signed_t     a_signed;
    f_number_signeds_t    a_signeds;
    f_number_unsigned_t   a_unsigned;
    f_number_unsigneds_t  a_unsigneds;
    f_range_t             a_range;
    f_ranges_t            a_ranges;
    f_string_t            a_string;
    f_string_t *          a_strings;
    f_string_dynamic_t    a_dynamic;
    f_string_dynamics_t   a_dynamics;
    f_string_map_t        a_map;
    f_string_maps_t       a_maps;
    f_string_map_multi_t  a_map_multi;
    f_string_map_multis_t a_map_multis;
    f_quantity_t   a_quantity;
    f_quantitys_t  a_quantitys;
    f_string_triple_t     a_triple;
    f_string_triples_t    a_triples;
    void *                a_void;
    void **               a_voids;
  } f_abstruse_type_t;

  #define f_abstruse_type_t_initialize { 0 }

  #define macro_f_abstruse_type_t_initialize_1(value) { value }

  #define macro_f_abstruse_type_t_clear(abstruse_type) \
    abstruse_type = 0;
#endif // _di_f_abstruse_type_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_abstruse_type_h
