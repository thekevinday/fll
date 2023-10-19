#include "payload.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_payload_header_write_
  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Process the signed number, converting it to a string and appending that string onto data->cache_2.
   * If the number is not appended to data->cache_2, then empty quotes are appended onto data->cache_2 to represent no data.
   *
   * @param data
   *   The f_fss_payload_header_write_state_t pointer.
   *   The caller is expected to reset data->cache_2.used as needed.
   *   The resulting data->cache_2 is then appended onto data->cache_1 on success.
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

    internal->k = data->cache_2->used;

    state->status = f_conversion_number_signed_to_string(number, data->conversion, data->cache_2);
    if (F_status_is_error(state->status)) return F_true;

    if (data->cache_2->used > internal->k) {
      internal->range.start = internal->k;
      internal->range.stop = data->cache_2->used - 1;

      private_fl_fss_basic_write(F_false, *data->cache_2, 0, &internal->range, data->cache_2, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;
    }
    else {
      if (data->cache_2->used + (f_string_ascii_quote_double_s.used * 2) > data->cache_2->size) {
        state->status = f_memory_array_increase_by(state->step_small + (f_string_ascii_quote_double_s.used * 2), sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
        if (F_status_is_error(state->status)) return F_true;
      }

      state->status = f_string_dynamic_append(f_string_ascii_quote_double_s, data->cache_2);

      if (F_status_is_error_not(state->status)) {
        state->status = f_string_dynamic_append(f_string_ascii_quote_double_s, data->cache_2);
      }

      if (F_status_is_error(state->status)) return F_true;
    }

    return F_false;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Process the unsigned number, converting it to a string and appending that string onto data->cache_2.
   * If the number is not appended to data->cache_2, then empty quotes are appended onto data->cache_2 to represent no data.
   *
   * @param data
   *   The f_fss_payload_header_write_state_t pointer.
   *   The caller is expected to reset data->cache_2.used as needed.
   *   The resulting data->cache_2 is then appended onto data->cache_1 on success.
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

    internal->k = data->cache_2->used;

    state->status = f_conversion_number_unsigned_to_string(number, data->conversion, data->cache_2);
    if (F_status_is_error(state->status)) return F_true;

    if (data->cache_2->used > internal->k) {
      internal->range.start = internal->k;
      internal->range.stop = data->cache_2->used - 1;

      private_fl_fss_basic_write(F_false, *data->cache_2, 0, &internal->range, data->cache_2, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;
    }
    else {
      if (data->cache_2->used + (f_string_ascii_quote_double_s.used * 2) > data->cache_2->size) {
        state->status = f_memory_array_increase_by(state->step_small + (f_string_ascii_quote_double_s.used * 2), sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
        if (F_status_is_error(state->status)) return F_true;
      }

      state->status = f_string_dynamic_append(f_string_ascii_quote_double_s, data->cache_2);

      if (F_status_is_error_not(state->status)) {
        state->status = f_string_dynamic_append(f_string_ascii_quote_double_s, data->cache_2);
      }

      if (F_status_is_error(state->status)) return F_true;
    }

    return F_false;
  }
#endif // _di_fl_fss_payload_header_write_

#ifndef _di_fl_fss_payload_header_write_
  void fl_fss_payload_header_write(const f_abstruse_maps_t headers, const f_uint8s_t * const signatures, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!destination || !state->data) {
        state->status = F_status_set_error(F_parameter);

        if (state->handle) {
          state->handle((void * const) state, 0);
        }

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_payload_header_write_state_t * const data = (f_fss_payload_header_write_state_t *) state->data;
    f_fss_payload_header_write_internal_t internal = macro_f_fss_payload_header_write_internal_t_initialize_2(destination, destination->used);

    if (!data->cache_1 || !data->cache_2 || !data->cache_3) {
      state->status = F_status_set_error(F_parameter);

      if (state->handle) {
        state->handle((void * const) state, 0);
      }

      return;
    }

    // Pre-allocate as much as possible to reduce memory reallocation chances.
    {
      internal.k = state->step_large;

      if (state->code & f_fss_payload_write_comment_header_e) {
        internal.k += f_fss_payload_comment_header_s.used + 1;
      }

      if (state->code & f_fss_payload_write_header_object_e) {
        internal.k += f_fss_payload_object_header_s.used + 1;
      }

      if (state->code & f_fss_payload_write_payload_object_e) {
        internal.k += f_fss_payload_object_payload_s.used + 1;
      }

      state->status = f_memory_array_increase_by(internal.j + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

      internal.j = 0;

      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    if (state->code & f_fss_payload_write_comment_header_e) {
      internal.step = f_fss_payload_write_comment_header_e;

      state->status = f_string_dynamic_append(f_fss_payload_comment_header_s, destination);
      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    if (state->code & f_fss_payload_write_header_object_e) {
      internal.step = f_fss_payload_write_header_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_header_s, destination);
      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    if ((state->code & f_fss_payload_write_header_content_e) || (state->code & f_fss_payload_write_signature_content_e)) {
      internal.step = f_fss_payload_write_header_content_e;

      data->cache_3->used = 0;

      f_string_static_t string_static = f_string_static_t_initialize;

      for (; internal.i < headers.used ; ++internal.i) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) &internal);
          if (F_status_set_fine(state->status) == F_interrupt) return;
        }

        if (!headers.array[internal.i].key.used) continue;

        internal.range.start = 0;
        internal.range.stop = headers.array[internal.i].key.used - 1;
        data->cache_1->used = 0;

        // Pre-allocate space for the key, value (using step_large), separator space, EOL, and terminating NULL if necessary.
        state->status = f_memory_array_increase_by(headers.array[internal.i].key.used + state->step_large + f_fss_extended_open_s.used + 2, sizeof(f_char_t), (void **) &data->cache_1->string, &data->cache_1->used, &data->cache_1->size);

        if (F_status_is_error_not(state->status)) {
          private_fl_fss_basic_write(F_true, headers.array[internal.i].key, 0, &internal.range, data->cache_1, state, (void * const) &internal);
        }

        if (F_status_is_error_not(state->status)) {
          data->cache_1->string[data->cache_1->used++] = f_fss_extended_open_s.string[0];
        }

        if (F_status_is_error_not(state->status)) {
          switch (headers.array[internal.i].value.type) {
            case f_abstruse_none_e:
            case f_abstruse_void_e:
            case f_abstruse_voids_e:
              break;

            case f_abstruse_signed_e:
              data->cache_2->used = 0;

              private_inline_f_payload_header_write_number_signed(data, state, &internal, headers.array[internal.i].value.is.a_signed);

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_unsigned_e:
              data->cache_2->used = 0;

              private_inline_f_payload_header_write_number_unsigned(data, state, &internal, headers.array[internal.i].value.is.a_unsigned);

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_int8s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i8s, signatures);

              break;

            case f_abstruse_int16s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i16s, signatures);

              break;

            case f_abstruse_int32s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i32s, signatures);

              break;

            case f_abstruse_int64s_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_i64s, signatures);

              break;

            case f_abstruse_signeds_e:
              macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_signeds, signatures);

              break;

            case f_abstruse_uint8s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u8s, signatures);

              break;

            case f_abstruse_uint16s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u16s, signatures);

              break;

            case f_abstruse_uint32s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u32s, signatures);

              break;

            case f_abstruse_uint64s_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_u64s, signatures);

              break;

            case f_abstruse_unsigneds_e:
              macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, headers.array[internal.i].value.is.a_unsigneds, signatures);

              break;

            case f_abstruse_string_e:
              string_static.string = headers.array[internal.i].value.is.a_string;
              string_static.used = strnlen(headers.array[internal.i].value.is.a_string, F_string_t_size_d);

              if (string_static.used) {
                internal.range.start = 0;
                internal.range.stop = string_static.used - 1;

                if (signatures && signatures->array[internal.i]) {
                  data->cache_2->used = 0;

                  private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, data->cache_2, state, (void * const) &internal);

                  if (F_status_is_error_not(state->status) && data->cache_2->used) {
                    // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                    state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
                  }
                } else {
                  private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, data->cache_1, state, (void * const) &internal);
                }
              }

              break;

            case f_abstruse_strings_e:
              data->cache_2->used = 0;

              // @todo this needs to be updated to handle empty strings accordingly (appending "").
              for (internal.j = 0; headers.array[internal.i].value.is.a_strings[internal.i]; ++internal.j) {

                if (state->interrupt) {
                  state->interrupt((void * const) state, (void * const) &internal);
                  if (F_status_set_fine(state->status) == F_interrupt) return;
                }

                string_static.string = headers.array[internal.i].value.is.a_strings[internal.j];
                string_static.used = strnlen(headers.array[internal.i].value.is.a_strings[internal.j], F_string_t_size_d);

                if (string_static.used) {
                  if (data->cache_2->used + f_fss_extended_open_s.used + string_static.used > data->cache_2->size) {
                    state->status = f_memory_array_increase_by(state->step_small + f_fss_extended_open_s.used + string_static.used, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                    if (F_status_is_error(state->status)) break;
                  }

                  internal.range.start = 0;
                  internal.range.stop = string_static.used - 1;

                  private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, data->cache_2, state, (void * const) &internal);
                  if (F_status_is_error(state->status)) break;

                  if (headers.array[internal.i].value.is.a_strings[internal.i + 1]) {
                    data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];
                  }
                }
              } // for

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_dynamic_e:
              data->cache_2->used = 0;

              if (headers.array[internal.i].value.is.a_dynamic.used) {
                internal.k = headers.array[internal.i].value.is.a_dynamic.used;
              }
              else {
                internal.k = f_string_ascii_quote_double_s.used * 2;
              }

              if (data->cache_2->used + internal.k > data->cache_2->size) {
                state->status = f_memory_array_increase_by(state->step_small + internal.k, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                if (F_status_is_error(state->status)) break;
              }

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_dynamic);

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_dynamics_e:
              data->cache_2->used = 0;

              for (internal.j = 0; internal.j < headers.array[internal.i].value.is.a_dynamics.used; ++internal.j) {

                if (state->interrupt) {
                  state->interrupt((void * const) state, (void * const) &internal);
                  if (F_status_set_fine(state->status) == F_interrupt) return;
                }

                // @todo rewrite this block to use structure as shown in f_abstruse_dynamic_e above.

                if (headers.array[internal.i].value.is.a_dynamics.array[internal.j].used) {
                  if (data->cache_2->used + f_fss_extended_open_s.used + headers.array[internal.i].value.is.a_dynamics.array[internal.j].used > data->cache_2->size) {
                    state->status = f_memory_array_increase_by(state->step_small + f_fss_extended_open_s.used + headers.array[internal.i].value.is.a_dynamics.array[internal.j].used, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                    if (F_status_is_error(state->status)) break;
                  }

                  internal.range.start = 0;
                  internal.range.stop = headers.array[internal.i].value.is.a_dynamics.array[internal.j].used - 1;

                  private_fl_fss_basic_write(F_false, headers.array[internal.i].value.is.a_dynamics.array[internal.j], 0, &internal.range, data->cache_2, state, (void * const) &internal);
                  if (F_status_is_error(state->status)) break;

                  if (headers.array[internal.i].value.is.a_strings[internal.i + 1]) {
                    data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];
                  }
                }
                else {
                  if (data->cache_2->used + (f_string_ascii_quote_double_s.used * 2) > data->cache_2->size) {
                    state->status = f_memory_array_increase_by(state->step_small + (f_string_ascii_quote_double_s.used * 2), sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                    if (F_status_is_error(state->status)) break;
                  }

                  data->cache_2->string[data->cache_2->used++] = f_string_ascii_quote_double_s.string[0];
                  data->cache_2->string[data->cache_2->used++] = f_string_ascii_quote_double_s.string[0];
                }
              } // for

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_map_e:
              data->cache_2->used = 0;

              if (headers.array[internal.i].value.is.a_map.name.used) {
                internal.k = headers.array[internal.i].value.is.a_map.name.used;
                internal.k += headers.array[internal.i].value.is.a_map.value.used ? headers.array[internal.i].value.is.a_map.value.used : (f_string_ascii_quote_double_s.used * 2);
              }
              else if (headers.array[internal.i].value.is.a_map.value.used) {
                internal.k = (f_string_ascii_quote_double_s.used * 2) + headers.array[internal.i].value.is.a_map.value.used;
              }
              else {
                internal.k = f_string_ascii_quote_double_s.used * 4;
              }

              internal.k += f_fss_extended_open_s.used;

              if (data->cache_2->used + internal.k > data->cache_2->size) {
                state->status = f_memory_array_increase_by(state->step_small + internal.k, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                if (F_status_is_error(state->status)) break;
              }

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.name);

              data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map.value);

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_maps_e:
              // @todo
              break;

            case f_abstruse_map_multi_e:
              data->cache_2->used = 0;

              if (headers.array[internal.i].value.is.a_map_multi.name.used) {
                internal.k = headers.array[internal.i].value.is.a_map_multi.name.used;
              }
              else {
                internal.k = f_string_ascii_quote_double_s.used * 2;
              }

              internal.k += f_fss_extended_open_s.used;

              if (data->cache_2->used + internal.k > data->cache_2->size) {
                state->status = f_memory_array_increase_by(state->step_small + internal.k, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                if (F_status_is_error(state->status)) break;
              }

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_map_multi.name);

              data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];

              // @todo loop over all values (which is a dynamics string).

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
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
              data->cache_2->used = 0;

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

              if (data->cache_2->used + internal.k > data->cache_2->size) {
                state->status = f_memory_array_increase_by(state->step_small + internal.k, sizeof(f_char_t), (void **) &data->cache_2->string, &data->cache_2->used, &data->cache_2->size);
                if (F_status_is_error(state->status)) break;
              }

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.a);

              data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.b);

              data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];

              macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, headers.array[internal.i].value.is.a_triple.c);

              if (F_status_is_error_not(state->status) && data->cache_2->used) {
                // @todo build signature, use a callback for this so that the caller can provide an appropriate algorithm.

                state->status = f_string_dynamic_append(*data->cache_2, data->cache_1);
              }

              break;

            case f_abstruse_triples_e:
              // @todo
              break;

            default:
              break;
          }
        }

        // Pre-allocate space for the built string, close string, and terminating NULL if necessary.
        if (F_status_is_error_not(state->status)) {
          state->status = f_memory_array_increase_by(data->cache_1->used + f_fss_extended_close_s.used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        }

        if (F_status_is_error_not(state->status) && data->cache_1->used) {
          state->status = f_string_dynamic_append(*data->cache_1, destination);
        }

        if (F_status_is_error_not(state->status)) {
          state->status = f_string_dynamic_append(f_fss_extended_close_s, destination);
        }

        macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
      } // for
    }

    if (state->code & f_fss_payload_write_signature_object_e) {
      internal.step = f_fss_payload_write_signature_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_signature_s, destination);
      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    if (data->cache_3->used) {
      state->status = f_string_dynamic_append(*data->cache_3, data->cache_1);
      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    if (state->code & f_fss_payload_write_payload_object_e) {
      internal.step = f_fss_payload_write_payload_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_payload_s, destination);
      macro_f_fss_payload_header_write_handle_error_d(destination, state, internal);
    }

    state->status = F_okay;
  }
#endif // _di_fl_fss_payload_header_write_

#ifdef __cplusplus
} // extern "C"
#endif
