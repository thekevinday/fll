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

    state->status = F_okay;

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
      state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
    }

    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_dynamics(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_statics_t * const buffers, f_string_maps_t * const destinations) {

    data->cache->used = 0;
    internal->k = 0;

    state->status = f_memory_array_increase_by(buffers->used + ((f_fss_extended_next_s.used + internal->quote_null.used) * buffers->used), sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
    if (F_status_is_error(state->status)) return F_true;

    if (data->flag & f_fss_payload_header_map_flag_join_dynamics_e) {
      state->status = f_memory_array_increase_by(buffers->used + ((f_fss_extended_next_s.used + internal->quote_null.used) * buffers->used), sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
      if (F_status_is_error(state->status)) return F_true;
    }

    for (internal->j = 0; internal->j < buffers->used; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      if (data->flag & f_fss_payload_header_map_flag_join_dynamics_e) {
        state->status = f_string_dynamic_append(buffers->array[internal->j], data->cache);
        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_string_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }
      else {
        if (buffers->array[internal->j].used) {
          internal->range.start = 0;
          internal->range.stop = buffers->array[internal->j].used - 1;

          private_fl_fss_basic_write(F_false, buffers->array[internal->j], internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;

          state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    } // for

    if (data->flag & f_fss_payload_header_map_flag_join_dynamics_e) {
      if (data->cache->used) {

        // Do not include the f_string_space_s that is always added at the end of the loop.
        data->cache->used -= f_string_space_s.used;

        internal->range.start = 0;
        internal->range.stop = data->cache->used - 1;

        private_fl_fss_basic_write(F_false, *data->cache, internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
      else {
        if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_map(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_map_t * const map, f_string_maps_t * const destinations) {

    if (data->flag & f_fss_payload_header_map_flag_join_map_e) {
      state->status = f_memory_array_increase_by(map->name.used + map->value.used + f_string_space_s.used, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      data->cache->used = 0;

      if (map->name.used) {
        f_string_dynamic_append(map->name, data->cache);
        if (F_status_is_error(state->status)) return F_true;

        if (map->value.used) {
          f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }
      }

      if (map->value.used) {
        f_string_dynamic_append(map->value, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }

      private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;
    }
    else {
      if (map->name.used) {
        internal->range.start = 0;
        internal->range.stop = map->name.used - 1;

        private_fl_fss_basic_write(F_false, map->name, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;

        if (map->value.used) {
          f_string_dynamic_append_assure(f_string_space_s, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }

      if (map->value.used) {
        internal->range.start = 0;
        internal->range.stop = map->value.used - 1;

        private_fl_fss_basic_write(F_false, map->value, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_map_name_value_null(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_maps_t * const destinations) {

    state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + f_fss_extended_next_s.used, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_none;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_maps_)
  uint8_t private_fl_payload_header_map_maps(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_maps_t * const maps, f_string_maps_t * const destinations) {

    if (data->flag & f_fss_payload_header_map_flag_join_maps_e) {
      // @todo
    }
    else if (data->flag & f_fss_payload_header_map_flag_null_map_name_value_e) {
      // @todo
    }
    else {
      for (internal->k = 0; internal->k < maps->used; ++internal->k) {

        if (maps->array[internal->k].name.used) {
          internal->k += maps->array[internal->k].name.used + f_fss_extended_next_s.used + internal->quote_null.used;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }

        if (maps->array[internal->k].value.used) {
          internal->k += maps->array[internal->k].value.used + f_fss_extended_next_s.used + internal->quote_null.used;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }
      } // for

      // @todo all of this below.

      if (data->flag & f_fss_payload_header_map_flag_join_map_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (maps->array[internal->l].name.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
            if (maps->array[internal->l].name.used) {
              f_string_dynamic_append(maps->array[internal->l].name, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            if (maps->array[internal->l].value.used) {
              f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (maps->array[internal->l].value.used) {
            f_string_dynamic_append(maps->array[internal->l].value, data->cache);
          }
          else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
            state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          }

          if (F_status_is_error(state->status)) return F_true;

          state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        } // for

        // Remove any trailing "extended_next".
        if (data->cache->used) {
          data->cache->used -= f_fss_extended_next_s.used;
        }

        private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
      else {
        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
        if (F_status_is_error(state->status)) return F_true;

        // @todo
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_maps_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_number_signed(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_signed_t number) {

    if (data->cache->used) {
      state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = f_conversion_number_signed_to_string(number, data->conversion, data->cache);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_number_unsigned(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_unsigned_t number) {

    if (data->cache->used) {
      state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = f_conversion_number_unsigned_to_string(number, data->conversion, data->cache);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_strings(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_t * const buffers, f_string_maps_t * const destinations) {

    f_string_static_t string_static = f_string_static_t_initialize;

    data->cache->used = 0;
    internal->k = 0;

    // Pre-process the string lengths to allow for a single allocation.
    for (internal->j = 0; buffers[internal->j]; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      string_static.string = buffers[internal->j];
      string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;
      internal->k += string_static.used + f_fss_extended_next_s.used + internal->quote_null.used;
    } // for

    state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
    if (F_status_is_error(state->status)) return F_true;

    if (data->flag & f_fss_payload_header_map_flag_join_strings_e) {
      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
      if (F_status_is_error(state->status)) return F_true;
    }

    for (internal->l = internal->j, internal->j = 0; internal->j < internal->l; ++internal->j) {

      if (state->interrupt) {
        state->interrupt((void * const) state, (void * const) internal);
        if (F_status_set_fine(state->status) == F_interrupt) return F_true;
      }

      string_static.string = buffers[internal->j];
      string_static.used = string_static.string ? strnlen(string_static.string, F_string_t_size_d) : 0;

      if (data->flag & f_fss_payload_header_map_flag_join_strings_e) {
        state->status = f_string_dynamic_append(string_static, data->cache);
        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_string_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }
      else {
        if (string_static.used) {
          internal->range.start = 0;
          internal->range.stop = string_static.used - 1;

          private_fl_fss_basic_write(F_false, string_static, internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;

          state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    } // for

    if (data->flag & f_fss_payload_header_map_flag_join_strings_e) {
      if (data->cache->used) {

        // Do not include the f_string_space_s that is always added at the end of the loop.
        data->cache->used -= f_string_space_s.used;

        internal->range.start = 0;
        internal->range.stop = data->cache->used - 1;

        private_fl_fss_basic_write(F_false, *data->cache, internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
      else {
        if (data->flag & f_fss_payload_header_map_flag_null_string_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    ++destinations->used;
    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif
