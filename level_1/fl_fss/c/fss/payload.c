#include "payload.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_payload_header_write_
  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Process the signed number, converting it to a string and appending that string onto data->cache_1.
   * The resulting data->cache_1 is then appended onto the destination value on success.
   * If the number is not appended to data->cache_1, then nothing is appended to the destination value.
   *
   * @param data
   *   The f_fss_payload_header_write_state_t pointer.
   *   This resets data->cache_1.used as needed.
   * @param state
   *   The state passed directly from the f_fss_payload_header_write() parameters.
   * @param internal
   *   The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
   * @param number
   *   The signed number.
   *
   * @return
   *   F_true if the caller should break or exit due to an error or something similar.
   *   F_false, otherwise.
   */
  static inline uint8_t private_inline_f_payload_header_write_number_signed(f_fss_payload_header_write_state_t * const data, f_state_t * const state, f_fss_payload_header_write_internal_t * const internal, const f_number_signed_t number) {

    data->cache_1->used = 0;

    state->status = f_conversion_number_signed_to_string(number, data->conversion, data->cache_1);
    if (F_status_is_error(state->status)) return F_true;

    if (data->cache_1->used) {
      internal->range.start = 0;
      internal->range.stop = data->cache_1->used - 1;

      private_fl_fss_basic_write(F_false, *data->cache_1, 0, &internal->range, &internal->destinations->array[internal->destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;
    }

    return F_false;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Process the unsigned number, converting it to a string and appending that string onto data->cache_1.
   * The resulting data->cache_1 is then appended onto the destination value on success.
   * If the number is not appended to data->cache_1, then nothing is appended to the destination value.
   *
   * @param data
   *   The f_fss_payload_header_write_state_t pointer.
   *   This resets data->cache_1.used as needed.
   * @param state
   *   The state passed directly from the f_fss_payload_header_write() parameters.
   * @param internal
   *   The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
   * @param number
   *   The unsigned number.
   *
   * @return
   *   F_true if the caller should break or exit due to an error or something similar.
   *   F_false, otherwise.
   */
  static inline uint8_t private_inline_f_payload_header_write_number_unsigned(f_fss_payload_header_write_state_t * const data, f_state_t * const state, f_fss_payload_header_write_internal_t * const internal, const f_number_unsigned_t number) {

    data->cache_1->used = 0;

    state->status = f_conversion_number_unsigned_to_string(number, data->conversion, data->cache_1);
    if (F_status_is_error(state->status)) return F_true;

    if (data->cache_1->used) {
      internal->range.start = 0;
      internal->range.stop = data->cache_1->used - 1;

      private_fl_fss_basic_write(F_false, *data->cache_1, 0, &internal->range, &internal->destinations->array[internal->destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;
    }

    return F_false;
  }
#endif // _di_fl_fss_payload_header_write_

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

    f_fss_payload_header_write_state_t * const data = (f_fss_payload_header_write_state_t *) state->data;
    f_fss_payload_header_write_internal_t internal = macro_f_fss_payload_header_write_internal_t_initialize_2(destinations, destinations->used);

    if (!data->cache_1) {
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

        private_fl_fss_basic_write(F_true, headers.array[internal.i].key, 0, &internal.range, &destinations->array[destinations->used].name, state, (void * const) &internal);

        if (F_status_is_error_not(state->status)) {
          // @todo need flag to specify whether or not to append NULL for single-valued and one for multi-valued number conversion results in invalid or does not exist.
          // @todo the same for single-valued strings and multi-valued strings (like maps).
          // @todo need a flag to designate whether to use single, double quotes, or auto.
          switch (headers.array[internal.i].value.type) {
            case f_abstruse_none_e:
            case f_abstruse_void_e:
            case f_abstruse_voids_e:
              break;

            case f_abstruse_signed_e:
              private_inline_f_payload_header_write_number_signed(data, state, &internal, headers.array[internal.i].value.is.a_signed);

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_unsigned_e:
              private_inline_f_payload_header_write_number_unsigned(data, state, &internal, headers.array[internal.i].value.is.a_unsigned);

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_int8s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i8s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int16s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i16s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int32s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i32s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_int64s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i64s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_signeds_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_signeds, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint8s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u8s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint16s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u16s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint32s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u32s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_uint64s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u64s, destinations->array[destinations->used].value);

              break;

            case f_abstruse_unsigneds_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_unsigneds, destinations->array[destinations->used].value);

              break;

            case f_abstruse_string_e:
              string_static.string = headers.array[internal.i].value.is.a_string;
              string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

              if (string_static.used) {
                internal.range.start = 0;
                internal.range.stop = string_static.used - 1;

                private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, &destinations->array[destinations->used].value, state, (void * const) &internal);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_strings_e:
              // @todo flag to break strings into multiple rows.
              data->cache_1->used = 0;

              if (headers.array[internal.i].value.is.a_strings) {
                internal.k = 0;

                for (internal.j = 0; headers.array[internal.i].value.is.a_strings[internal.j]; ++internal.j) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  string_static.string = headers.array[internal.i].value.is.a_strings[internal.j];
                  string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

                  internal.k += string_static.used ? string_static.used : f_string_ascii_quote_double_s.used * 2;
                  internal.k += f_fss_extended_next_s.used;
                } // for

                state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
                if (F_status_is_error(state->status)) break;

                for (internal.j = 0; headers.array[internal.i].value.is.a_strings[internal.j]; ++internal.j) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  string_static.string = headers.array[internal.i].value.is.a_strings[internal.j];
                  string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

                  if (string_static.used) {
                    internal.range.start = 0;
                    internal.range.stop = string_static.used - 1;

                    private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, data->cache_1, state, (void * const) &internal);
                    if (F_status_is_error(state->status)) break;

                    data->cache_1->string[data->cache_1->used++] = f_fss_extended_open_s.string[0];
                  }
                } // for

                if (F_status_is_error_not(state->status)) {

                  // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
                  data->cache_1->used -= f_fss_extended_next_s.used;

                  state->status = f_string_dynamic_append(*data->cache_1, &destinations->array[destinations->used].value);
                }
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamic_e:
              data->cache_1->used = 0;

              if (headers.array[internal.i].value.is.a_dynamic.used) {
                internal.j = headers.array[internal.i].value.is.a_dynamic.used;
              }
              else {
                internal.j = f_string_ascii_quote_double_s.used * 2;
              }

              state->status = f_memory_array_increase_by(internal.j, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_dynamic);

              if (F_status_is_error_not(state->status)) {

                // The f_fss_extended_next_s is always added at the end of the macro.
                data->cache_1->used -= f_fss_extended_next_s.used;

                state->status = f_string_dynamic_append(*data->cache_1, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_dynamics_e:
              // @todo flag to break dynamics into multiple rows.
              data->cache_1->used = 0;

              if (headers.array[internal.i].value.is.a_dynamics.used) {
                internal.k = 0;

                for (internal.j = 0; internal.j < headers.array[internal.i].value.is.a_dynamics.used; ++internal.j) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  internal.k += headers.array[internal.i].value.is.a_dynamics.array[internal.j].used ? headers.array[internal.i].value.is.a_dynamics.array[internal.j].used : f_string_ascii_quote_double_s.used * 2;
                  internal.k += f_fss_extended_next_s.used;
                } // for

                state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
                if (F_status_is_error(state->status)) break;

                for (internal.j = 0; internal.j < headers.array[internal.i].value.is.a_dynamics.used; ++internal.j) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_dynamics.array[internal.j]);
                  if (F_status_is_error(state->status)) break;
                } // for

                if (F_status_is_error_not(state->status)) {

                  // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
                  data->cache_1->used -= f_fss_extended_next_s.used;

                  state->status = f_string_dynamic_append(*data->cache_1, &destinations->array[destinations->used].value);
                }
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_map_e:
              data->cache_1->used = 0;
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

              state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.name);
              if (F_status_is_error(state->status)) break;

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.value);

              if (F_status_is_error_not(state->status)) {

                // The f_fss_extended_next_s is always added at the end of the macro.
                data->cache_1->used -= f_fss_extended_next_s.used;

                state->status = f_string_dynamic_append(*data->cache_1, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error_not(state->status)) {
                ++destinations->used;
              }

              break;

            case f_abstruse_maps_e:
              // @todo
              break;

            case f_abstruse_map_multi_e:
              data->cache_1->used = 0;
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

                state->status = f_memory_array_increase_by(internal.k, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
                if (F_status_is_error(state->status)) break;

                macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map_multi.name);

                data->cache_1->string[data->cache_1->used++] = f_fss_extended_next_s.string[0];

                for (internal.l = 0; internal.l < headers.array[internal.i].value.is.a_map_multi.value.used; ++internal.l) {

                  if (state->interrupt) {
                    state->interrupt((void * const) state, (void * const) &internal);
                    if (F_status_set_fine(state->status) == F_interrupt) return;
                  }

                  if (headers.array[internal.i].value.is.a_map_multi.value.array[internal.l].used) {
                    state->status = f_string_dynamic_append(headers.array[internal.i].value.is.a_map_multi.value.array[internal.l], data->cache_1);
                    if (F_status_is_error(state->status)) break;
                  }
                  else {
                    data->cache_1->string[data->cache_1->used++] = f_string_ascii_quote_double_s.string[0];
                    data->cache_1->string[data->cache_1->used++] = f_string_ascii_quote_double_s.string[0];
                  }

                  data->cache_1->string[data->cache_1->used++] = f_fss_extended_next_s.string[0];
                } // for

                if (F_status_is_error_not(state->status)) {

                  // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
                  data->cache_1->used -= f_fss_extended_next_s.used;

                  state->status = f_string_dynamic_append(*data->cache_1, &destinations->array[destinations->used].value);
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
/*
            case f_abstruse_triple_e:
              data->cache_1->used = 0;

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

              internal.k += f_fss_extended_open_s.used * 2;

              if (data->cache_1->used + internal.k > data->cache_1->size) {
                state->status = f_memory_array_increase_by(state->step_small + internal.k, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);
                if (F_status_is_error(state->status)) break;
              }

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.a);

              data->cache_1->string[data->cache_1->used++] = f_fss_extended_open_s.string[0];

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.b);

              data->cache_1->string[data->cache_1->used++] = f_fss_extended_open_s.string[0];

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.c);

              if (F_status_is_error_not(state->status) && data->cache_1->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_1, data->cache_1);
              }

              break;
*/
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

    if (F_status_is_error_not(state->status)) {
      state->status = F_okay;
    }
  }
#endif // _di_fl_fss_payload_header_map_

#ifdef __cplusplus
} // extern "C"
#endif
