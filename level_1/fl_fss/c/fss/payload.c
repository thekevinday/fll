#include "payload.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_payload_header_write_
  void fl_fss_payload_header_write(const f_abstruse_maps_t headers, const f_abstruse_maps_t * const signatures, f_string_dynamic_t * const destination, f_state_t * const state) {
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

    if (!data->cache) {
      state->status = F_status_set_error(F_parameter);

      if (state->handle) {
        state->handle((void * const) state, 0);
      }

      return;
    }

    // Pre-allocate as much as possible to reduce memory reallocation chances, using 'j'.
    {
      internal.j = 0;

      if (state->code & f_fss_payload_write_comment_header_e) {
        internal.j += f_fss_payload_comment_header_s.used + 1;
      }

      if (state->code & f_fss_payload_write_header_object_e) {
        internal.j += f_fss_payload_object_header_s.used + 1;
      }

      // This uses step large to at least do something for header content.
      if (state->code & f_fss_payload_write_header_content_e) {
        internal.j += state->step_large + headers.used + 1;
      }

      if (state->code & f_fss_payload_write_signature_object_e) {
        internal.j += f_fss_payload_object_signature_s.used + 1;
      }

      // This uses step large to at least do something for signature content.
      if ((state->code & f_fss_payload_write_signature_content_e) && signatures) {
        internal.j += state->step_large + signatures->used + 1;
      }

      if (state->code & f_fss_payload_write_payload_object_e) {
        internal.j += f_fss_payload_object_payload_s.used + 1;
      }

      state->status = f_memory_array_increase_by(internal.j + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

      internal.j = 0;

      if (F_status_is_error(state->status)) {
        if (state->handle) {
          state->handle((void * const) state, (void * const) &internal);

          if (F_status_is_error(state->status)) {
            destination->used = internal.original;

            return;
          }
        }
        else {
          destination->used = internal.original;

          return;
        }
      }
    }

    if (state->code & f_fss_payload_write_comment_header_e) {
      internal.step = f_fss_payload_write_comment_header_e;

      state->status = f_string_dynamic_append(f_fss_payload_comment_header_s, destination);

      if (F_status_is_error(state->status)) {
        if (state->handle) {
          state->handle((void * const) state, (void * const) &internal);

          if (F_status_is_error(state->status)) {
            destination->used = internal.original;

            return;
          }
        }
        else {
          destination->used = internal.original;

          return;
        }
      }
    }

    if (state->code & f_fss_payload_write_header_object_e) {
      internal.step = f_fss_payload_write_header_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_header_s, destination);

      if (F_status_is_error(state->status)) {
        if (state->handle) {
          state->handle((void * const) state, (void * const) &internal);

          if (F_status_is_error(state->status)) {
            destination->used = internal.original;

            return;
          }
        }
        else {
          destination->used = internal.original;

          return;
        }
      }
    }

    if (state->code & f_fss_payload_write_header_content_e) {
      internal.step = f_fss_payload_write_header_content_e;

      f_string_static_t string_static = f_string_static_t_initialize;

      for (; internal.i < headers.used ; ++internal.i) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) &internal);
          if (F_status_set_fine(state->status) == F_interrupt) return;
        }

        if (!headers.array[internal.i].key.used) continue;

        internal.range.start = 0;
        internal.range.stop = headers.array[internal.i].key.used - 1;
        data->cache->used = 0;

        // Pre-allocate space for the key, value (using step_large), separator space, EOL, and terminating NULL if necessary.
        state->status = f_memory_array_increase_by(headers.array[internal.i].key.used + state->step_large + 3, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);

        if (F_status_is_error_not(state->status)) {
          data->cache->string[data->cache->used++] = f_fss_extended_open_s.string[0];

          private_fl_fss_basic_write(F_true, headers.array[internal.i].key, 0, &internal.range, data->cache, state, (void * const) &internal);
        }

        if (F_status_is_error_not(state->status)) {
          switch (headers.array[internal.i].value.type) {
            case f_abstruse_none_e:
            case f_abstruse_void_e:
            case f_abstruse_voids_e:
              break;

            case f_abstruse_signed_e:
              data->cache->used = 0;

              state->status = f_conversion_number_signed_to_string(headers.array[internal.i].value.is.a_signed, data->conversion, data->cache);

              break;

            case f_abstruse_unsigned_e:
              data->cache->used = 0;

              state->status = f_conversion_number_unsigned_to_string(headers.array[internal.i].value.is.a_unsigned, data->conversion, data->cache);

              break;

            case f_abstruse_int8s_e:
            case f_abstruse_int16s_e:
            case f_abstruse_int32s_e:
            case f_abstruse_int64s_e:
            case f_abstruse_signeds_e:
              // @todo
              break;

            case f_abstruse_uint8s_e:
            case f_abstruse_uint16s_e:
            case f_abstruse_uint32s_e:
            case f_abstruse_uint64s_e:
            case f_abstruse_unsigneds_e:
              // @todo
              break;

            case f_abstruse_string_e:
              string_static.string = headers.array[internal.i].value.is.a_string;
              string_static.used = strnlen(headers.array[internal.i].value.is.a_string, F_string_t_size_d);

              internal.range.start = 0;
              internal.range.stop = string_static.used;

              private_fl_fss_basic_write(F_false, string_static, 0, &internal.range, data->cache, state, (void * const) &internal);

              if (F_status_is_error(state->status)) {
                destination->used = internal.original;
              }

            case f_abstruse_strings_e:
              // @todo
              break;

            case f_abstruse_dynamic_e:
            case f_abstruse_dynamics_e:
              // @todo
              break;

            case f_abstruse_map_e:
            case f_abstruse_maps_e:
              // @todo
              break;

            case f_abstruse_map_multi_e:
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
            case f_abstruse_triples_e:
              // @todo
              break;

            default:
              break;
          }
        }

        if (F_status_is_error_not(state->status)) {
          if (data->cache->used) {

            // Pre-allocate space for the built string and terminating NULL if necessary.
            state->status = f_memory_array_increase_by(data->cache->used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

            if (F_status_is_error_not(state->status)) {
              state->status = f_string_dynamic_append(*data->cache, destination);
            }
          }
        }

        if (F_status_is_error(state->status)) {
          if (state->handle) {
            state->handle((void * const) state, (void * const) &internal);

            if (F_status_is_error(state->status)) {
              destination->used = internal.original;

              return;
            }
          }
          else {
            destination->used = internal.original;

            return;
          }
        }
      } // for
    }

    if (state->code & f_fss_payload_write_signature_object_e) {
      internal.step = f_fss_payload_write_signature_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_signature_s, destination);

      if (F_status_is_error(state->status)) {
        if (state->handle) {
          state->handle((void * const) state, (void * const) &internal);

          if (F_status_is_error(state->status)) {
            destination->used = internal.original;

            return;
          }
        }
        else {
          destination->used = internal.original;

          return;
        }
      }
    }

    if ((state->code & f_fss_payload_write_signature_content_e) && !signatures) {
      internal.step = f_fss_payload_write_signature_content_e;

      for (internal.i = 0; internal.i < signatures->used ; ++internal.i) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) &internal);
          if (F_status_set_fine(state->status) == F_interrupt) return;
        }

        switch (signatures->array[internal.i].value.type) {
          case f_abstruse_none_e:
          case f_abstruse_void_e:
          case f_abstruse_voids_e:
            break;

          case f_abstruse_signed_e:
          case f_abstruse_unsigned_e:
            // @todo
            break;

          case f_abstruse_int8s_e:
          case f_abstruse_int16s_e:
          case f_abstruse_int32s_e:
          case f_abstruse_int64s_e:
          case f_abstruse_signeds_e:
            // @todo
            break;

          case f_abstruse_uint8s_e:
          case f_abstruse_uint16s_e:
          case f_abstruse_uint32s_e:
          case f_abstruse_uint64s_e:
          case f_abstruse_unsigneds_e:
            // @todo
            break;

          case f_abstruse_string_e:
          case f_abstruse_strings_e:
            // @todo
            break;

          case f_abstruse_dynamic_e:
          case f_abstruse_dynamics_e:
            // @todo
            break;

          case f_abstruse_map_e:
          case f_abstruse_maps_e:
            // @todo
            break;

          case f_abstruse_map_multi_e:
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
          case f_abstruse_triples_e:
            // @todo
            break;

          default:
            break;
        }
      } // for
    }

    if (state->code & f_fss_payload_write_payload_object_e) {
      internal.step = f_fss_payload_write_payload_object_e;

      state->status = f_string_dynamic_append(f_fss_payload_object_payload_s, destination);

      if (F_status_is_error(state->status)) {
        if (state->handle) {
          state->handle((void * const) state, (void * const) &internal);

          if (F_status_is_error(state->status)) {
            destination->used = internal.original;

            return;
          }
        }
        else {
          destination->used = internal.original;

          return;
        }
      }
    }

    state->status = F_okay;
  }
#endif // _di_fl_fss_payload_header_write_

#ifdef __cplusplus
} // extern "C"
#endif
