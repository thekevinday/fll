#include "payload.h"
#include "../private-fss.h"
#include "private-payload.h"
#include "private-payload-helper.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_payload_header_map_
  void fl_fss_payload_header_map(const f_abstruse_maps_t headers, f_string_maps_t * const destinations, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!destinations || !state->data) {
        state->status = F_status_set_error(F_parameter);

        if (state->handle) {
          state->handle((void * const) state, 0);
        }

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_payload_header_state_t * const data = (f_fss_payload_header_state_t *) state->data;
    f_fss_payload_header_internal_t internal = macro_f_fss_payload_header_internal_t_initialize_2(destinations, destinations->used);

    if (!data->cache) {
      state->status = F_status_set_error(F_parameter);

      if (state->handle) {
        state->handle((void * const) state, 0);
      }

      return;
    }

    if (!headers.used) {
      state->status = F_data_not;

      return;
    }

    internal.i = 0;
    internal.j = 0;
    internal.k = 0;
    internal.l = 0;

    if (data->flag & f_fss_payload_header_map_flag_quote_double_e) {
      internal.quote = f_string_ascii_quote_double_s.string[0];
      internal.quote_null = f_fss_quote_double_null_s;
    }
    else if (data->flag & f_fss_payload_header_map_flag_quote_single_e) {
      internal.quote = f_string_ascii_quote_single_s.string[0];
      internal.quote_null = f_fss_quote_single_null_s;
    }
    else if (data->flag & f_fss_payload_header_map_flag_quote_grave_e) {
      internal.quote = f_string_ascii_grave_s.string[0];
      internal.quote_null = f_fss_quote_grave_null_s;
    }
    else {
      internal.quote = 0;
      internal.quote_null = f_fss_quote_double_null_s;
    }

    state->status = f_memory_array_increase_by(headers.used, sizeof(f_string_map_t), (void **) &destinations->array, &destinations->used, &destinations->size);

    macro_f_fss_payload_header_write_handle_error_d(destinations, state, internal);

    {
      f_string_static_t string_static = f_string_static_t_initialize;

      for (internal.i = 0; internal.i < headers.used; ++internal.i) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) &internal);
          if (F_status_set_fine(state->status) == F_interrupt) return;
        }

        destinations->array[destinations->used].name.used = 0;
        destinations->array[destinations->used].value.used = 0;

        internal.range.start = 0;
        internal.range.stop = headers.array[internal.i].key.used ? headers.array[internal.i].key.used - 1 : 0;

        private_fl_fss_basic_write(F_true, headers.array[internal.i].key, internal.quote, &internal.range, &destinations->array[destinations->used].name, state, (void * const) &internal);

        if (F_status_is_error_not(state->status)) {
          state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].name);
        }

        if (F_status_is_error_not(state->status)) {
          switch (headers.array[internal.i].value.type) {
            case f_abstruse_none_e:
            case f_abstruse_void_e:
            case f_abstruse_voids_e:
              // Voids and none are unknown or non-existent and so they cannot be converted.
              break;

            case f_abstruse_signed_e:
              data->cache->used = 0;

              if (private_fl_payload_header_map_number_signed(data, state, &internal, headers.array[internal.i].value.is.a_signed) == F_false) {
                if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, &internal, data->cache, destinations) == F_false) {
                  ++destinations->used;
                }
              }

              break;

            case f_abstruse_unsigned_e:
              data->cache->used = 0;

              if (private_fl_payload_header_map_number_unsigned(data, state, &internal, headers.array[internal.i].value.is.a_unsigned) == F_false) {
                if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, &internal, data->cache, destinations) == F_false) {
                  ++destinations->used;
                }
              }

              break;

            case f_abstruse_int8s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i8s, destinations);

              break;

            case f_abstruse_int16s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i16s, destinations);

              break;

            case f_abstruse_int32s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i32s, destinations);

              break;

            case f_abstruse_int64s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i64s, destinations);

              break;

            case f_abstruse_signeds_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_signeds, destinations);

              break;

            case f_abstruse_uint8s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u8s, destinations);

              break;

            case f_abstruse_uint16s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u16s, destinations);

              break;

            case f_abstruse_uint32s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u32s, destinations);

              break;

            case f_abstruse_uint64s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u64s, destinations);

              break;

            case f_abstruse_unsigneds_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_unsigneds, destinations);

              break;

            case f_abstruse_string_e:
              string_static.string = headers.array[internal.i].value.is.a_string;
              string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

              if (string_static.used || (data->flag & f_fss_payload_header_map_flag_null_string_e)) {
                if (private_fl_payload_helper_header_map_destination_write_buffer_or_empty(data, state, &internal, &string_static, destinations, f_fss_payload_header_map_flag_null_string_e) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_strings_e:
              if (headers.array[internal.i].value.is.a_strings || (data->flag & f_fss_payload_header_map_flag_null_strings_e)) {
                if (private_fl_payload_header_map_strings(data, state, &internal, headers.array[internal.i].value.is.a_strings, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamic_e:
              if (headers.array[internal.i].value.is.a_dynamic.used || (data->flag & f_fss_payload_header_map_flag_null_dynamic_e)) {
                if (private_fl_payload_helper_header_map_destination_write_buffer_or_empty(data, state, &internal, &headers.array[internal.i].value.is.a_dynamic, destinations, f_fss_payload_header_map_flag_null_dynamic_e) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamics_e:
              if (headers.array[internal.i].value.is.a_dynamics.used || (data->flag & f_fss_payload_header_map_flag_null_dynamics_e)) {
                if (private_fl_payload_header_map_dynamics(data, state, &internal, &headers.array[internal.i].value.is.a_dynamics, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_map_e:
              if (headers.array[internal.i].value.is.a_map.name.used || headers.array[internal.i].value.is.a_map.value.used) {
                if (private_fl_payload_header_map_map(data, state, &internal, &headers.array[internal.i].value.is.a_map, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_maps_e:
              if (headers.array[internal.i].value.is.a_maps.used || (data->flag & f_fss_payload_header_map_flag_null_maps_e)) {
                if (private_fl_payload_header_map_maps(data, state, &internal, &headers.array[internal.i].value.is.a_maps, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_map_multi_e:
              if (headers.array[internal.i].value.is.a_map_multi.name.used || headers.array[internal.i].value.is.a_map_multi.value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_name_e)) {
                if (private_fl_payload_header_map_map_multi(data, state, &internal, &headers.array[internal.i].value.is.a_map_multi, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_map_multis_e:
              if (headers.array[internal.i].value.is.a_map_multis.used || (data->flag & f_fss_payload_header_map_flag_null_map_multis_e)) {
                if (private_fl_payload_header_map_map_multis(data, state, &internal, &headers.array[internal.i].value.is.a_map_multis, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_quantity_e:
              if (!headers.array[internal.i].value.is.a_quantity.total || (data->flag & f_fss_payload_header_map_flag_null_quantity_e)) {
                if (private_fl_payload_header_map_quantity(data, state, &internal, headers.array[internal.i].value.is.a_quantity, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_quantitys_e:
              if (headers.array[internal.i].value.is.a_quantitys.used || (data->flag & f_fss_payload_header_map_flag_null_quantitys_e)) {
                if (private_fl_payload_header_map_quantitys(data, state, &internal, headers.array[internal.i].value.is.a_quantitys, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_range_e:
              if (headers.array[internal.i].value.is.a_range.start <= headers.array[internal.i].value.is.a_range.stop || (data->flag & f_fss_payload_header_map_flag_null_range_e)) {
                if (private_fl_payload_header_map_range(data, state, &internal, headers.array[internal.i].value.is.a_range, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_ranges_e:
              if (headers.array[internal.i].value.is.a_ranges.used || (data->flag & f_fss_payload_header_map_flag_null_ranges_e)) {
                if (private_fl_payload_header_map_ranges(data, state, &internal, headers.array[internal.i].value.is.a_ranges, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_triple_e:
              if (headers.array[internal.i].value.is.a_triple.a.used || headers.array[internal.i].value.is.a_triple.b.used || headers.array[internal.i].value.is.a_triple.c.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
                if (private_fl_payload_header_map_triple(data, state, &internal, headers.array[internal.i].value.is.a_triple, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_triples_e:
              if (headers.array[internal.i].value.is.a_triples.used || (data->flag & f_fss_payload_header_map_flag_null_triples_e)) {
                if (private_fl_payload_header_map_triples(data, state, &internal, headers.array[internal.i].value.is.a_triples, destinations) == F_false) {
                  ++destinations->used;
                }
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            default:
              break;
          }
        }

        macro_f_fss_payload_header_write_handle_error_d(destinations, state, internal);
      } // for
    }

    if (F_status_is_error(state->status)) return;

    state->status = F_okay;
  }
#endif // _di_fl_fss_payload_header_map_

#ifdef __cplusplus
} // extern "C"
#endif
