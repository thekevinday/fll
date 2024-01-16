#include "payload.h"
#include "../private-fss.h"
#include "private-payload.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_cache(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal) {

    if (!data->cache->used) return F_false;

    internal->range.start = 0;
    internal->range.stop = data->cache->used - 1;

    private_fl_fss_basic_write(F_false, *data->cache, internal->quote, &internal->range, &internal->destinations->array[internal->destinations->used].value, state, (void * const) internal);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_strip_null(&internal->destinations->array[internal->destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_dynamic(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations) {

    if (buffer->used) {
      internal->range.start = 0;
      internal->range.stop = buffer->used - 1;

      private_fl_fss_basic_write(F_false, *buffer, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    }
    else {
      state->status = f_memory_array_increase_by(2, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      private_fl_payload_header_map_null_add(*internal, &destinations->array[destinations->used].value);
    }

    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_dynamics(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_statics_t * const buffers, f_string_maps_t * const destinations) {

    // @todo this needs to implement f_fss_payload_header_map_flag_join_dynamics_e.

    data->cache->used = 0;
    internal->k = 0;

    for (internal->j = 0; internal->j < buffers->used; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      internal->k += buffers->array[internal->j].used ? buffers->array[internal->j].used : f_string_ascii_quote_double_s.used * 2;
      internal->k += f_fss_extended_next_s.used;
    } // for

    state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
    if (F_status_is_error(state->status)) return F_true;

    for (internal->j = 0; internal->j < buffers->used; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      macro_f_fss_payload_header_write_process_dynamic_d(data, state, (*internal), buffers->array[internal->j]);
      if (F_status_is_error(state->status)) return F_true;
    } // for

    // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
    data->cache->used -= f_fss_extended_next_s.used;

    state->status = f_string_dynamic_append(*data->cache, &destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  void private_fl_payload_header_map_null_add(const f_fss_payload_header_internal_t internal, f_string_dynamic_t * const destination) {

    destination->string[destination->used++] = internal.quote ? internal.quote : f_string_ascii_quote_double_s.string[0];
    destination->string[destination->used++] = internal.quote ? internal.quote : f_string_ascii_quote_double_s.string[0];
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_number_signed(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_signed_t number) {

    if (data->cache->used) {
      state->status = f_string_dynamic_append(f_fss_extended_next_s, data->cache);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = f_conversion_number_signed_to_string(number, data->conversion, data->cache);
    if (F_status_is_error(state->status)) return F_true;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_number_unsigned(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_unsigned_t number) {

    if (data->cache->used) {
      state->status = f_string_dynamic_append(f_fss_extended_next_s, data->cache);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = f_conversion_number_unsigned_to_string(number, data->conversion, data->cache);
    if (F_status_is_error(state->status)) return F_true;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)
#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_strings(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_t * const buffers, f_string_maps_t * const destinations) {

    f_string_static_t string_static = f_string_static_t_initialize;

    data->cache->used = 0;
    internal->k = 0;

    for (internal->j = 0; buffers[internal->j]; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      string_static.string = buffers[internal->j];
      string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

      internal->k += string_static.used ? string_static.used : f_string_ascii_quote_double_s.used * 2;
      internal->k += f_fss_extended_next_s.used;
    } // for

    // Save the total strings as internal.l so that intenal.j can be used for the loop counter later on.
    internal->l = internal->j;

    if (data->flag & f_fss_payload_header_map_flag_join_strings_e) {
      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
      if (F_status_is_error(state->status)) return F_true;

      for (internal->j = 0; internal->j < internal->l; ++internal->j) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        string_static.string = buffers[internal->j];
        string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

        if (string_static.used) {
          internal->range.start = 0;
          internal->range.stop = string_static.used - 1;

          private_fl_fss_basic_write(F_false, string_static, internal->quote, &internal->range, data->cache, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;

          data->cache->string[data->cache->used++] = f_fss_extended_open_s.string[0];
        }
      } // for

      if (data->cache->used) {

        // The f_fss_extended_next_s is always added at the end of the loop to avoid an additional condition check in the loop.
        data->cache->used -= f_fss_extended_next_s.used;
      }
      else if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
        private_fl_payload_header_map_null_add(*internal, data->cache);
      }

      if (data->cache->used) {
        state->status = f_string_dynamic_append(*data->cache, &destinations->array[destinations->used].value);
      }
    }
    else {
      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);

      for (internal->j = 0; internal->j < internal->l; ++internal->j) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        string_static.string = buffers[internal->j];
        string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

        state->status = f_string_dynamic_append(string_static, data->cache);
        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append(f_fss_extended_next_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      } // for

      // Do not include the f_fss_extended_next_s that is always added at the end of the loop.
      data->cache->used -= f_fss_extended_next_s.used;

      internal->range.start = 0;
      internal->range.stop = data->cache->used - 1;

      private_fl_fss_basic_write(F_false, *data->cache, internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    }

    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif
