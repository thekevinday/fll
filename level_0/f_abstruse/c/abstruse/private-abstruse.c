#include "../abstruse.h"
#include "private-abstruse.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_abstruses_delete_callback_) || !defined(_di_f_abstrusess_delete_callback_) || !defined(_di_f_abstruse_maps_delete_callback_) || !defined(_di_f_abstruse_mapss_delete_callback_)
  f_status_t private_f_abstruses_delete_switch(f_abstruse_t * const abstruse) {

    switch (abstruse->type) {
      case f_abstruse_int8s_e:
        if (abstruse->is.a_i8s.size) {
          return f_memory_array_resize(0, sizeof(int8_t), (void **) &abstruse->is.a_i8s.array, &abstruse->is.a_i8s.used, &abstruse->is.a_i8s.size);
        }

        break;

      case f_abstruse_int16s_e:
        if (abstruse->is.a_i16s.size) {
          return f_memory_array_resize(0, sizeof(int16_t), (void **) &abstruse->is.a_i16s.array, &abstruse->is.a_i16s.used, &abstruse->is.a_i16s.size);
        }

        break;

      case f_abstruse_int32s_e:
        if (abstruse->is.a_i32s.size) {
          return f_memory_array_resize(0, sizeof(int32_t), (void **) &abstruse->is.a_i32s.array, &abstruse->is.a_i32s.used, &abstruse->is.a_i32s.size);
        }

        break;

      case f_abstruse_int64s_e:
        if (abstruse->is.a_i64s.size) {
          return f_memory_array_resize(0, sizeof(int64_t), (void **) &abstruse->is.a_i64s.array, &abstruse->is.a_i64s.used, &abstruse->is.a_i64s.size);
        }

        break;

      case f_abstruse_uint8s_e:
        if (abstruse->is.a_u8s.size) {
          return f_memory_array_resize(0, sizeof(uint8_t), (void **) &abstruse->is.a_u8s.array, &abstruse->is.a_u8s.used, &abstruse->is.a_u8s.size);
        }

        break;

      case f_abstruse_uint16s_e:
        if (abstruse->is.a_u16s.size) {
          return f_memory_array_resize(0, sizeof(uint16_t), (void **) &abstruse->is.a_u16s.array, &abstruse->is.a_u16s.used, &abstruse->is.a_u16s.size);
        }

        break;

      case f_abstruse_uint32s_e:
        if (abstruse->is.a_u32s.size) {
          return f_memory_array_resize(0, sizeof(uint32_t), (void **) &abstruse->is.a_u32s.array, &abstruse->is.a_u32s.used, &abstruse->is.a_u32s.size);
        }

        break;

      case f_abstruse_uint64s_e:
        if (abstruse->is.a_u64s.size) {
          return f_memory_array_resize(0, sizeof(uint64_t), (void **) &abstruse->is.a_u64s.array, &abstruse->is.a_u64s.used, &abstruse->is.a_u64s.size);
        }

        break;

      case f_abstruse_signeds_e:
        if (abstruse->is.a_signeds.size) {
          return f_memory_array_resize(0, sizeof(f_number_signed_t), (void **) &abstruse->is.a_signeds.array, &abstruse->is.a_signeds.used, &abstruse->is.a_signeds.size);
        }

        break;

      case f_abstruse_unsigneds_e:
        if (abstruse->is.a_unsigneds.size) {
          return f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &abstruse->is.a_unsigneds.array, &abstruse->is.a_unsigneds.used, &abstruse->is.a_unsigneds.size);
        }

        break;

      case f_abstruse_dynamic_e:
        if (abstruse->is.a_dynamic.size) {
          return f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_dynamic.string, &abstruse->is.a_dynamic.used, &abstruse->is.a_dynamic.size);
        }

        break;

      case f_abstruse_dynamics_e:
        if (abstruse->is.a_dynamics.size) {
          return f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &abstruse->is.a_dynamics.array, &abstruse->is.a_dynamics.used, &abstruse->is.a_dynamics.size, &f_string_dynamics_delete_callback);
        }

        break;

      case f_abstruse_map_e:
        if (abstruse->is.a_map.key.size || abstruse->is.a_map.value.size) {
          {
            const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_map.key.string, &abstruse->is.a_map.key.used, &abstruse->is.a_map.key.size);
            if (F_status_is_error(status)) return status;
          }

          return f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_map.value.string, &abstruse->is.a_map.value.used, &abstruse->is.a_map.value.size);
        }

        break;

      case f_abstruse_maps_e:
        if (abstruse->is.a_maps.size) {
          return f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &abstruse->is.a_maps.array, &abstruse->is.a_maps.used, &abstruse->is.a_maps.size, &f_string_maps_delete_callback);
        }

        break;

      case f_abstruse_map_multi_e:
        if (abstruse->is.a_map_multi.key.size || abstruse->is.a_map_multi.value.size) {
          {
            const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_map_multi.key.string, &abstruse->is.a_map_multi.key.used, &abstruse->is.a_map_multi.key.size);
            if (F_status_is_error(status)) return status;
          }

          return f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &abstruse->is.a_map_multi.value.array, &abstruse->is.a_map_multi.value.used, &abstruse->is.a_map_multi.value.size, &f_string_dynamics_delete_callback);
        }

        break;

      case f_abstruse_map_multis_e:
        if (abstruse->is.a_map_multis.size) {
          return f_memory_arrays_resize(0, sizeof(f_string_map_multi_t), (void **) &abstruse->is.a_map_multis.array, &abstruse->is.a_map_multis.used, &abstruse->is.a_map_multis.size, &f_string_map_multis_delete_callback);
        }

        break;

      case f_abstruse_quantitys_e:
        if (abstruse->is.a_quantitys.size) {
          return f_memory_array_resize(0, sizeof(f_quantity_t), (void **) &abstruse->is.a_quantitys.array, &abstruse->is.a_quantitys.used, &abstruse->is.a_quantitys.size);
        }

        break;

      case f_abstruse_ranges_e:
        if (abstruse->is.a_ranges.size) {
          return f_memory_array_resize(0, sizeof(f_range_t), (void **) &abstruse->is.a_ranges.array, &abstruse->is.a_ranges.used, &abstruse->is.a_ranges.size);
        }

        break;

      case f_abstruse_triple_e:
        if (abstruse->is.a_triple.a.size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.a.string, &abstruse->is.a_triple.a.used, &abstruse->is.a_triple.a.size);
          if (F_status_is_error(status)) return status;
        }

        if (abstruse->is.a_triple.b.size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.b.string, &abstruse->is.a_triple.b.used, &abstruse->is.a_triple.b.size);
          if (F_status_is_error(status)) return status;
        }

        if (abstruse->is.a_triple.c.size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.c.string, &abstruse->is.a_triple.c.used, &abstruse->is.a_triple.c.size);
          if (F_status_is_error(status)) return status;
        }

        break;

      case f_abstruse_triples_e:
        if (abstruse->is.a_triples.size) {
          return f_memory_arrays_resize(0, sizeof(f_string_triple_t), (void **) &abstruse->is.a_triples.array, &abstruse->is.a_triples.used, &abstruse->is.a_triples.size, &f_string_triples_delete_callback);
        }

        break;

      default:
        break;
    };

    return F_okay;
  }
#endif // !defined(_di_f_abstruses_delete_callback_) || !defined(_di_f_abstrusess_delete_callback_) || !defined(_di_f_abstruse_maps_delete_callback_) || !defined(_di_f_abstruse_mapss_delete_callback_)

#if !defined(_di_f_abstruses_destroy_callback_) || !defined(_di_f_abstrusess_destroy_callback_) || !defined(_di_f_abstruse_maps_destroy_callback_) || !defined(_di_f_abstruse_mapss_destroy_callback_)
  f_status_t private_f_abstruses_destroy_switch(f_abstruse_t * const abstruse) {

    switch (abstruse->type) {
      case f_abstruse_uint8s_e:
        if (abstruse->is.a_u8s.size) {
          return f_memory_array_adjust(0, sizeof(uint8_t), (void **) &abstruse->is.a_u8s.array, &abstruse->is.a_u8s.used, &abstruse->is.a_u8s.size);
        }

        break;

      case f_abstruse_uint16s_e:
        if (abstruse->is.a_u16s.size) {
          return f_memory_array_adjust(0, sizeof(uint16_t), (void **) &abstruse->is.a_u16s.array, &abstruse->is.a_u16s.used, &abstruse->is.a_u16s.size);
        }

        break;

      case f_abstruse_uint32s_e:
        if (abstruse->is.a_u32s.size) {
          return f_memory_array_adjust(0, sizeof(uint32_t), (void **) &abstruse->is.a_u32s.array, &abstruse->is.a_u32s.used, &abstruse->is.a_u32s.size);
        }

        break;

      case f_abstruse_uint64s_e:
        if (abstruse->is.a_u64s.size) {
          return f_memory_array_adjust(0, sizeof(uint64_t), (void **) &abstruse->is.a_u64s.array, &abstruse->is.a_u64s.used, &abstruse->is.a_u64s.size);
        }

        break;

      case f_abstruse_int8s_e:
        if (abstruse->is.a_i8s.size) {
          return f_memory_array_adjust(0, sizeof(int8_t), (void **) &abstruse->is.a_i8s.array, &abstruse->is.a_i8s.used, &abstruse->is.a_i8s.size);
        }

        break;

      case f_abstruse_int16s_e:
        if (abstruse->is.a_i16s.size) {
          return f_memory_array_adjust(0, sizeof(int16_t), (void **) &abstruse->is.a_i16s.array, &abstruse->is.a_i16s.used, &abstruse->is.a_i16s.size);
        }

        break;

      case f_abstruse_int32s_e:
        if (abstruse->is.a_i32s.size) {
          return f_memory_array_adjust(0, sizeof(int32_t), (void **) &abstruse->is.a_i32s.array, &abstruse->is.a_i32s.used, &abstruse->is.a_i32s.size);
        }

        break;

      case f_abstruse_int64s_e:
        if (abstruse->is.a_i64s.size) {
          return f_memory_array_adjust(0, sizeof(int64_t), (void **) &abstruse->is.a_i64s.array, &abstruse->is.a_i64s.used, &abstruse->is.a_i64s.size);
        }

        break;

      case f_abstruse_signeds_e:
        if (abstruse->is.a_signeds.size) {
          return f_memory_array_adjust(0, sizeof(f_number_signed_t), (void **) &abstruse->is.a_signeds.array, &abstruse->is.a_signeds.used, &abstruse->is.a_signeds.size);
        }

        break;

      case f_abstruse_unsigneds_e:
        if (abstruse->is.a_unsigneds.size) {
          return f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &abstruse->is.a_unsigneds.array, &abstruse->is.a_unsigneds.used, &abstruse->is.a_unsigneds.size);
        }

        break;

      case f_abstruse_dynamic_e:
        if (abstruse->is.a_dynamic.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_dynamic.string, &abstruse->is.a_dynamic.used, &abstruse->is.a_dynamic.size);
        }

        break;

      case f_abstruse_dynamics_e:
        if (abstruse->is.a_dynamics.size) {
          return f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &abstruse->is.a_dynamics.array, &abstruse->is.a_dynamics.used, &abstruse->is.a_dynamics.size, &f_string_dynamics_destroy_callback);
        }

        break;

      case f_abstruse_map_e:
        if (abstruse->is.a_map.key.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_map.key.string, &abstruse->is.a_map.key.used, &abstruse->is.a_map.key.size);
        }

        if (abstruse->is.a_map.value.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_map.value.string, &abstruse->is.a_map.value.used, &abstruse->is.a_map.value.size);
        }

        break;

      case f_abstruse_maps_e:
        if (abstruse->is.a_maps.size) {
          return f_memory_arrays_adjust(0, sizeof(f_string_map_t), (void **) &abstruse->is.a_maps.array, &abstruse->is.a_maps.used, &abstruse->is.a_maps.size, &f_string_maps_destroy_callback);
        }

        break;

      case f_abstruse_map_multi_e:
        if (abstruse->is.a_map_multi.key.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_map_multi.key.string, &abstruse->is.a_map_multi.key.used, &abstruse->is.a_map_multi.key.size);
        }

        if (abstruse->is.a_map_multi.value.size) {
          return f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &abstruse->is.a_map_multi.value.array, &abstruse->is.a_map_multi.value.used, &abstruse->is.a_map_multi.value.size, &f_string_dynamics_destroy_callback);
        }

        break;

      case f_abstruse_map_multis_e:
        if (abstruse->is.a_map_multis.size) {
          return f_memory_arrays_adjust(0, sizeof(f_string_map_multi_t), (void **) &abstruse->is.a_map_multis.array, &abstruse->is.a_map_multis.used, &abstruse->is.a_map_multis.size, &f_string_map_multis_destroy_callback);
        }

        break;

      case f_abstruse_quantitys_e:
        if (abstruse->is.a_quantitys.size) {
          return f_memory_array_adjust(0, sizeof(f_quantity_t), (void **) &abstruse->is.a_quantitys.array, &abstruse->is.a_quantitys.used, &abstruse->is.a_quantitys.size);
        }

        break;

      case f_abstruse_ranges_e:
        if (abstruse->is.a_quantitys.size) {
          return f_memory_array_adjust(0, sizeof(f_range_t), (void **) &abstruse->is.a_ranges.array, &abstruse->is.a_ranges.used, &abstruse->is.a_ranges.size);
        }

        break;

      case f_abstruse_triple_e:
        if (abstruse->is.a_triple.a.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.a.string, &abstruse->is.a_triple.a.used, &abstruse->is.a_triple.a.size);
        }

        if (abstruse->is.a_triple.b.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.b.string, &abstruse->is.a_triple.b.used, &abstruse->is.a_triple.b.size);
        }

        if (abstruse->is.a_triple.c.size) {
          return f_memory_array_adjust(0, sizeof(f_char_t), (void **) &abstruse->is.a_triple.c.string, &abstruse->is.a_triple.c.used, &abstruse->is.a_triple.c.size);
        }

        break;

      case f_abstruse_triples_e:
        if (abstruse->is.a_triples.size) {
          return f_memory_arrays_adjust(0, sizeof(f_string_triple_t), (void **) &abstruse->is.a_triples.array, &abstruse->is.a_triples.used, &abstruse->is.a_triples.size, &f_string_triples_destroy_callback);
        }

        break;

      default:
        break;
    };

    return F_okay;
  }
#endif // !defined(_di_f_abstruses_destroy_callback_) || !defined(_di_f_abstrusess_destroy_callback_) || !defined(_di_f_abstruse_maps_destroy_callback_) || !defined(_di_f_abstruse_mapss_destroy_callback_)

#ifdef __cplusplus
} // extern "C"
#endif
