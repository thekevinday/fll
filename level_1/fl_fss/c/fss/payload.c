#include "payload.h"
#include "../private-fss.h"
#include "private-payload.h"

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
    internal.quote = f_fss_payload_header_map_flag_quote_double_e
      ? f_string_ascii_quote_double_s.string[0]
      : f_fss_payload_header_map_flag_quote_single_e
        ? f_string_ascii_quote_single_s.string[0]
        : f_fss_payload_header_map_flag_quote_grave_e
          ? f_string_ascii_grave_s.string[0]
          : 0;

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

        if (!headers.array[internal.i].key.used) continue;

        internal.range.start = 0;
        internal.range.stop = headers.array[internal.i].key.used - 1;

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
                private_fl_payload_header_map_cache(data, state, &internal);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_unsigned_e:
              data->cache->used = 0;

              if (private_fl_payload_header_map_number_unsigned(data, state, &internal, headers.array[internal.i].value.is.a_unsigned) == F_false) {
                private_fl_payload_header_map_cache(data, state, &internal);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_int8s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i8s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int16s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i16s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int32s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i32s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int64s_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_i64s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_signeds_e:
              macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, headers.array[internal.i].value.is.a_signeds, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint8s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u8s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint16s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u16s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint32s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u32s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint64s_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_u64s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_unsigneds_e:
              macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, headers.array[internal.i].value.is.a_unsigneds, destinations->array[destinations->used].value);

              break;

            case f_abstruse_string_e:
              string_static.string = headers.array[internal.i].value.is.a_string;
              string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

              if (string_static.used || (data->flag & f_fss_payload_header_map_flag_null_string_e)) {
                private_fl_payload_header_map_dynamic(data, state, &internal, &string_static, destinations);
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_strings_e:
              if (headers.array[internal.i].value.is.a_strings) {
                private_fl_payload_header_map_strings(data, state, &internal, headers.array[internal.i].value.is.a_strings, destinations);
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
                state->status = f_memory_array_increase_by(2, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
                if (F_status_is_error(state->status)) break;

                private_fl_payload_header_map_null_add(internal, &destinations->array[destinations->used].value);
                if (F_status_is_error(state->status)) break;

                ++destinations->used;
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamic_e:
              if (headers.array[internal.i].value.is.a_dynamic.used || (data->flag & f_fss_payload_header_map_flag_null_dynamic_e)) {
                private_fl_payload_header_map_dynamic(data, state, &internal, &headers.array[internal.i].value.is.a_dynamic, destinations);
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamics_e:
              if (headers.array[internal.i].value.is.a_dynamics.used) {
                private_fl_payload_header_map_dynamics(data, state, &internal, &headers.array[internal.i].value.is.a_dynamics, destinations);
              }
              else if (data->flag & f_fss_payload_header_map_flag_null_e) {
                ++destinations->used;
              }

              break;

// @todo resume here.
            case f_abstruse_map_e:
              data->cache->used = 0;
              internal.k = f_fss_extended_next_s.used;

              if (headers.array[internal.i].value.is.a_map.name.used) {
                internal.k += headers.array[internal.i].value.is.a_map.name.used;
                internal.k += headers.array[internal.i].value.is.a_map.value.used ? headers.array[internal.i].value.is.a_map.value.used : (f_string_ascii_quote_double_s.used * 2);
              }
              else if (headers.array[internal.i].value.is.a_map.value.used) {
                internal.k += (f_string_ascii_quote_double_s.used * 2) + headers.array[internal.i].value.is.a_map.value.used;
              }
              else {
                internal.k += f_string_ascii_quote_double_s.used * 4;
              }

              state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
              if (F_status_is_error(state->status)) break;

              // @todo this should be different, in regards to the f_fss_payload_header_map_flag_null_dynamic_e bit.
              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.name);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.value);

              if (F_status_is_error_not(state->status)) {

                // The f_fss_extended_next_s is always added at the end of the macro.
                data->cache->used -= f_fss_extended_next_s.used;

                state->status = f_string_dynamic_append(*data->cache, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_maps_e:
              // @todo
              break;

            case f_abstruse_map_multi_e:
              data->cache->used = 0;
              internal.k = headers.array[internal.i].value.is.a_map_multi.name.used ? headers.array[internal.i].value.is.a_map_multi.name.used : f_string_ascii_quote_double_s.used * 2;
              internal.k += f_fss_extended_next_s.used;

              if (headers.array[internal.i].value.is.a_map_multi.value.used) {
                for (internal.l = 0; internal.l < headers.array[internal.i].value.is.a_map_multi.value.used; ++internal.l) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  internal.k += headers.array[internal.i].value.is.a_map_multi.value.array[internal.l].used ? headers.array[internal.i].value.is.a_map_multi.value.array[internal.l].used : f_string_ascii_quote_double_s.used * 2;
                  internal.k += f_fss_extended_next_s.used;
                } // for

                state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
                if (F_status_is_error(state->status)) break;

                macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map_multi.name);

                data->cache->string[data->cache->used++] = f_fss_extended_next_s.string[0];

                for (internal.l = 0; internal.l < headers.array[internal.i].value.is.a_map_multi.value.used; ++internal.l) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  if (headers.array[internal.i].value.is.a_map_multi.value.array[internal.l].used) {
                    state->status = f_string_dynamic_append(headers.array[internal.i].value.is.a_map_multi.value.array[internal.l], data->cache);
                    if (F_status_is_error(state->status)) break;
                  }
                  else {
                    data->cache->string[data->cache->used++] = f_string_ascii_quote_double_s.string[0];
                    data->cache->string[data->cache->used++] = f_string_ascii_quote_double_s.string[0];
                  }

                  data->cache->string[data->cache->used++] = f_fss_extended_next_s.string[0];
                } // for

                if (F_status_is_error_not(state->status)) {

                  // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
                  data->cache->used -= f_fss_extended_next_s.used;

                  state->status = f_string_dynamic_append(*data->cache, &destinations->array[destinations->used].value);
                }
              }
              else if (headers.array[internal.i].value.is.a_map_multi.name.used) {
                state->status = f_string_dynamic_append(headers.array[internal.i].value.is.a_map_multi.name, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_map_multis_e:
              // @todo
              break;

            case f_abstruse_quantity_e:
            case f_abstruse_quantitys_e:
              // @todo
              break;

            case f_abstruse_range_e:
            case f_abstruse_ranges_e:
              // @todo
              break;

            case f_abstruse_triple_e:
              data->cache->used = 0;

              if (headers.array[internal.i].value.is.a_triple.a.used) {
                internal.k = headers.array[internal.i].value.is.a_triple.a.used;

                if (headers.array[internal.i].value.is.a_triple.b.used) {
                  internal.k += headers.array[internal.i].value.is.a_triple.b.used;
                  internal.k += headers.array[internal.i].value.is.a_triple.c.used ? headers.array[internal.i].value.is.a_triple.c.used : (f_string_ascii_quote_double_s.used * 2);
                }
                else if (headers.array[internal.i].value.is.a_triple.c.used) {
                  internal.k += headers.array[internal.i].value.is.a_triple.c.used + (f_string_ascii_quote_double_s.used * 2);
                }
                else {
                  internal.k = f_string_ascii_quote_double_s.used * 4;
                }
              }
              else if (headers.array[internal.i].value.is.a_triple.b.used) {
                if (headers.array[internal.i].value.is.a_triple.c.used) {
                  internal.k = (f_string_ascii_quote_double_s.used * 2) + headers.array[internal.i].value.is.a_triple.b.used + headers.array[internal.i].value.is.a_triple.c.used;
                }
                else {
                  internal.k = (f_string_ascii_quote_double_s.used * 4) + headers.array[internal.i].value.is.a_triple.b.used;
                }
              }
              else if (headers.array[internal.i].value.is.a_triple.c.used) {
                internal.k = (f_string_ascii_quote_double_s.used * 4) + headers.array[internal.i].value.is.a_triple.c.used;
              }
              else {
                internal.k = f_string_ascii_quote_double_s.used * 6;
              }

              internal.k += f_fss_extended_next_s.used * 2;

              state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.a);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.b);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.c);

              if (F_status_is_error_not(state->status)) {

                // The f_fss_extended_next_s is always added at the end of the macro.
                data->cache->used -= f_fss_extended_next_s.used;

                state->status = f_string_dynamic_append(*data->cache, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_triples_e:
              // @todo
              break;

            default:
              break;
          }
        }

        macro_f_fss_payload_header_write_handle_error_d(destinations, state, internal);
      } // for
    }

    state->status = F_okay;
  }
#endif // _di_fl_fss_payload_header_map_

#ifdef __cplusplus
} // extern "C"
#endif
