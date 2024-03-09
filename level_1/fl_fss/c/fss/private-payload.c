#include "payload.h"
#include "../private-fss.h"
#include "private-payload.h"
#include "private-payload-helper.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_dynamics(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_statics_t * const buffers, f_string_maps_t * const destinations) {

    if (buffers->used) {
      data->cache->used = 0;
      internal->k = 0;

      state->status = f_memory_array_increase_by(buffers->used + ((f_fss_extended_next_s.used + internal->quote_null.used) * buffers->used), sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_dynamics_e) {
        state->status = f_memory_array_increase_by(buffers->used + ((f_fss_space_s.used + internal->quote_null.used) * buffers->used), sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
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

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
          else if (data->flag & f_fss_payload_header_map_flag_null_dynamic_e) {
            state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        }
      } // for

      if (data->flag & f_fss_payload_header_map_flag_join_dynamics_e) {
        if (data->cache->used) {

          // Remove the always added trailing space.
          data->cache->used -= f_string_space_s.used;

          internal->range.start = 0;
          internal->range.stop = data->cache->used - 1;

          private_fl_fss_basic_write(F_false, *data->cache, internal->quote, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;
        }
        else {
          if (data->flag & f_fss_payload_header_map_flag_null_dynamic_e) {
            state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        }
      }
      else if (destinations->array[destinations->used].value.used) {

        // Remove the always added trailing extended next.
        destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
      }
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_null_dynamic_e) {
        state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_map(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_map_t * const map, f_string_maps_t * const destinations) {

    state->status = f_memory_array_increase_by(map->key.used + map->value.used + f_string_space_s.used + internal->quote_null.used * 2, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
    if (F_status_is_error(state->status)) return F_true;

    if (data->flag & f_fss_payload_header_map_flag_join_map_e) {
      data->cache->used = 0;

      state->status = f_memory_array_increase_by(map->key.used + map->value.used + f_string_space_s.used, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
      if (F_status_is_error(state->status)) return F_true;

      if (map->key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
        if (map->key.used) {
          state->status = f_string_dynamic_append(map->key, data->cache);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }

      if (map->value.used || (data->flag & f_fss_payload_header_map_flag_null_map_value_e)) {
        if (map->value.used) {
          state->status = f_string_dynamic_append(map->value, data->cache);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }

      // Remove the always added trailing space.
      if (data->cache->used) {
        data->cache->used -= f_fss_space_s.used;
      }

      if (data->cache->used) {
        internal->range.start = 0;
        internal->range.stop = data->cache->used - 1;

        private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
    }
    else {
      if (map->key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
        if (map->key.used) {
          internal->range.start = 0;
          internal->range.stop = map->key.used - 1;

          private_fl_fss_basic_write(F_false, map->key, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;
      }

      if (map->value.used || (data->flag & f_fss_payload_header_map_flag_null_map_value_e)) {
        if (map->value.used) {
          internal->range.start = 0;
          internal->range.stop = map->value.used - 1;

          private_fl_fss_basic_write(F_false, map->value, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;
      }

      // Remove the always added trailing space.
      if (destinations->array[destinations->used].value.used) {
        destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_map_multi(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_map_multi_t * const map, f_string_maps_t * const destinations) {

    if (map->key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
      internal->k = map->key.used + internal->quote_null.used;
    }
    else {
      internal->k = 0;
    }

    if (map->value.used) {
      for (internal->l = 0; internal->l < map->value.used; ++internal->l) {

        if (map->value.array[internal->l].used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
          internal->k += f_string_space_s.used + map->value.array[internal->l].used + internal->quote_null.used;
        }
      } // for
    }
    else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
      internal->k += f_string_space_s.used + internal->quote_null.used;
    }

    // Add additional characters for the standard placeholders.
    if (internal->k) {
      internal->k += f_fss_placeholder_s.used * 4;
    }

    state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
    if (F_status_is_error(state->status)) return F_true;

    if (data->flag & f_fss_payload_header_map_flag_join_map_multi_e) {
      data->cache->used = 0;

      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
      if (F_status_is_error(state->status)) return F_true;

      if (map->key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
        if (map->key.used) {
          state->status = f_string_dynamic_append(map->key, data->cache);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }

      if (map->value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
        if (map->value.used) {
          for (internal->m = 0; internal->m < map->value.used; ++internal->m) {

            if (map->value.array[internal->m].used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
              if (map->value.array[internal->m].used) {
                state->status = f_string_dynamic_append(map->value.array[internal->m], data->cache);
              }
              else {
                state->status = f_string_dynamic_append(internal->quote_null, data->cache);
              }

              if (F_status_is_error(state->status)) return F_true;

              state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }

        state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
        if (F_status_is_error(state->status)) return F_true;
      }

      // Remove the always added trailing space.
      if (data->cache->used) {
        data->cache->used -= f_fss_space_s.used;
      }

      if (data->cache->used) {
        internal->range.start = 0;
        internal->range.stop = data->cache->used - 1;

        private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        if (F_status_is_error(state->status)) return F_true;
      }
    }
    else {
      if (map->key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
        if (map->key.used) {
          internal->range.start = 0;
          internal->range.stop = map->key.used - 1;

          private_fl_fss_basic_write(F_false, map->key, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;
      }

      if (map->value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
        if (map->value.used) {
          for (internal->m = 0; internal->m < map->value.used; ++internal->m) {

            if (map->value.array[internal->m].used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
              if (map->value.array[internal->m].used) {
                internal->range.start = 0;
                internal->range.stop = map->value.array[internal->m].used - 1;

                private_fl_fss_basic_write(F_false, map->value.array[internal->m], 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              }
              else {
                state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              }

              if (F_status_is_error(state->status)) return F_true;

              state->status = f_string_dynamic_append_assure(f_fss_space_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }
          } // for
        }
        else {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
        }

        if (F_status_is_error(state->status)) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;
      }

      // Remove the always added trailing space.
      if (destinations->array[destinations->used].value.used) {
        destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_maps_)
  uint8_t private_fl_payload_header_map_map_multis(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_map_multis_t * const maps, f_string_maps_t * const destinations) {

    if (maps->used) {
      internal->k = 0;
      internal->l = 0;

      for (; internal->l < maps->used; ++internal->l) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        if (maps->array[internal->l].key.used) {
          internal->k += maps->array[internal->l].key.used + f_fss_extended_next_s.used + internal->quote_null.used;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }

        if (maps->array[internal->l].value.used) {
          for (internal->m = 0; internal->m < maps->array[internal->l].value.used; ++internal->m) {

            if (maps->array[internal->l].value.array[internal->m].used) {
              internal->k += maps->array[internal->l].value.array[internal->m].used + f_fss_extended_next_s.used + internal->quote_null.used;
            }
            else {
              internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
            }
          } // for
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }
      } // for

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 4;
      }

      if (data->flag & f_fss_payload_header_map_flag_join_map_multis_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
            if (maps->array[internal->l].key.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].key, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (maps->array[internal->l].value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
            if (maps->array[internal->l].value.used) {
              for (internal->m = 0; internal->m < maps->array[internal->l].value.used; ++internal->m) {

                if (maps->array[internal->l].value.array[internal->m].used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
                  if (maps->array[internal->l].value.array[internal->m].used) {
                    state->status = f_string_dynamic_append(maps->array[internal->l].value.array[internal->m], data->cache);
                  }
                  else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
                    state->status = f_string_dynamic_append(internal->quote_null, data->cache);
                  }

                  if (F_status_is_error(state->status)) return F_true;

                  state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
                  if (F_status_is_error(state->status)) return F_true;
                }
              } // for
            }
            else {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for

        // Remove the always added trailing space.
        if (data->cache->used) {
          data->cache->used -= f_fss_space_s.used;
        }

        if (data->cache->used) {
          internal->range.start = 0;
          internal->range.stop = data->cache->used - 1;

          private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
      else if (data->flag & f_fss_payload_header_map_flag_join_map_multi_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          data->cache->used = 0;

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
            if (maps->array[internal->l].key.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].key, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (maps->array[internal->l].value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
            if (maps->array[internal->l].value.used) {
              for (internal->m = 0; internal->m < maps->array[internal->l].value.used; ++internal->m) {

                if (maps->array[internal->l].value.array[internal->m].used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
                  if (maps->array[internal->l].value.array[internal->m].used) {
                    state->status = f_string_dynamic_append(maps->array[internal->l].value.array[internal->m], data->cache);
                  }
                  else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
                    state->status = f_string_dynamic_append(internal->quote_null, data->cache);
                  }

                  if (F_status_is_error(state->status)) return F_true;

                  state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
                  if (F_status_is_error(state->status)) return F_true;
                }
              } // for
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          // Remove the always added trailing space.
          if (data->cache->used) {
            data->cache->used -= f_fss_space_s.used;
          }

          if (data->cache->used) {
            internal->range.start = 0;
            internal->range.stop = data->cache->used - 1;

            private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for

        // Remove the always added trailing space.
        if (destinations->array[destinations->used].value.used) {
          destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
        }
      }
      else {
        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e)) {
            if (maps->array[internal->l].key.used) {
              internal->range.start = 0;
              internal->range.stop = maps->array[internal->l].key.used - 1;

              private_fl_fss_basic_write(F_false, maps->array[internal->l].key, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (maps->array[internal->l].value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
            for (internal->m = 0; internal->m < maps->array[internal->l].value.used; ++internal->m) {

              if (maps->array[internal->l].value.used || (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e)) {
                if (maps->array[internal->l].value.used) {
                  internal->range.start = 0;
                  internal->range.stop = maps->array[internal->l].value.array[internal->m].used - 1;

                  private_fl_fss_basic_write(F_true, maps->array[internal->l].value.array[internal->m], 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
                  if (F_status_is_error(state->status)) return F_true;
                }
                else if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
                  state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
                  if (F_status_is_error(state->status)) return F_true;
                }

                state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
                if (F_status_is_error(state->status)) return F_true;
              }
            } // for
          }
        } // for

        // Remove the always added trailing space.
        if (destinations->array[destinations->used].value.used) {
          destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
        }
      }

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_join_map_multi_e) {
        if ((data->flag & f_fss_payload_header_map_flag_null_map_multi_values_name_e) == f_fss_payload_header_map_flag_null_map_multi_values_name_e) {
          state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + f_fss_space_s.used, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          if (F_status_is_error(state->status)) return F_true;

          if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        if ((data->flag & f_fss_payload_header_map_flag_null_map_multi_values_name_e) == f_fss_payload_header_map_flag_null_map_multi_values_name_e) {
          state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + f_fss_space_s.used, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_multi_name_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;

          if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_multi_values_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_maps_)

#if !defined(_di_fl_fss_payload_header_maps_)
  uint8_t private_fl_payload_header_map_maps(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_maps_t * const maps, f_string_maps_t * const destinations) {

    if (maps->used) {
      internal->k = 0;

      for (internal->l = 0; internal->l < maps->used; ++internal->l) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        if (maps->array[internal->l].key.used) {
          internal->k += maps->array[internal->l].key.used + f_fss_extended_next_s.used + internal->quote_null.used;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }

        if (maps->array[internal->l].value.used) {
          internal->k += maps->array[internal->l].value.used + f_fss_extended_next_s.used + internal->quote_null.used;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used;
        }
      } // for

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 4;
      }

      if (data->flag & f_fss_payload_header_map_flag_join_maps_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
            if (maps->array[internal->l].key.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].key, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (maps->array[internal->l].value.used || (data->flag & f_fss_payload_header_map_flag_null_map_value_e)) {
            if (maps->array[internal->l].value.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].value, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for

        // Remove the always added trailing space.
        if (data->cache->used) {
          data->cache->used -= f_fss_space_s.used;
        }

        if (data->cache->used) {
          internal->range.start = 0;
          internal->range.stop = data->cache->used - 1;

          private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
      else if (data->flag & f_fss_payload_header_map_flag_join_map_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          data->cache->used = 0;

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
            if (maps->array[internal->l].key.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].key, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
            if (maps->array[internal->l].value.used) {
              state->status = f_string_dynamic_append(maps->array[internal->l].value, data->cache);
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
            }

            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }

          // Remove the always added trailing space.
          if (data->cache->used) {
            data->cache->used -= f_fss_space_s.used;
          }

          if (data->cache->used) {
            internal->range.start = 0;
            internal->range.stop = data->cache->used - 1;

            private_fl_fss_basic_write(F_false, *data->cache, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
            if (F_status_is_error(state->status)) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for

        // Remove the always added trailing space.
        data->cache->used -= f_fss_extended_next_s.used;
      }
      else {
        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < maps->used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (maps->array[internal->l].key.used || (data->flag & f_fss_payload_header_map_flag_null_map_name_e)) {
            if (maps->array[internal->l].key.used) {
              internal->range.start = 0;
              internal->range.stop = maps->array[internal->l].key.used - 1;

              private_fl_fss_basic_write(F_false, maps->array[internal->l].key, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            if (maps->array[internal->l].value.used) {
              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (maps->array[internal->l].value.used) {
            internal->range.start = 0;
            internal->range.stop = maps->array[internal->l].value.used - 1;

            private_fl_fss_basic_write(F_true, maps->array[internal->l].value, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
            if (F_status_is_error(state->status)) return F_true;
          }
          else if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
            state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for
      }

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_join_map_e) {
        if ((data->flag & f_fss_payload_header_map_flag_null_map_value_name_e) == f_fss_payload_header_map_flag_null_map_value_name_e) {
          state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + f_fss_space_s.used, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          if (F_status_is_error(state->status)) return F_true;

          if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
            state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
            if (F_status_is_error(state->status)) return F_true;
          }
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
          state->status = f_string_dynamic_append(internal->quote_null, data->cache);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        if ((data->flag & f_fss_payload_header_map_flag_null_map_value_name_e) == f_fss_payload_header_map_flag_null_map_value_name_e) {
          state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + f_fss_space_s.used, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
          if (F_status_is_error(state->status)) return F_true;
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_name_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;

          if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        }

        if (data->flag & f_fss_payload_header_map_flag_null_map_value_e) {
          state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
          if (F_status_is_error(state->status)) return F_true;
        }
      }
    }

    state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_maps_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_number_signed(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_number_signed_t number) {

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
  uint8_t private_fl_payload_header_map_number_unsigned(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_number_unsigned_t number) {

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
  uint8_t private_fl_payload_header_map_quantity(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_quantity_t quantity, f_string_maps_t * const destinations) {

    if (quantity.total) {
      data->cache->used = 0;

      if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantity.start) == F_true) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_quantity_e) {
        if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantity.total) == F_true) return F_true;
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;

        data->cache->used = 0;

        if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantity.total) == F_true) return F_true;
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_null_quantity_e) {
        if (data->flag & f_fss_payload_header_map_flag_join_quantity_e) {
          data->cache->used = 0;

          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
        else {
          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, &destinations->array[destinations->used].value, f_fss_extended_next_s) == F_true) return F_true;
        }
      }
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_quantitys(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_quantitys_t quantitys, f_string_maps_t * const destinations) {

    if (quantitys.used) {
      internal->k = 0;

      for (internal->l = 0; internal->l < quantitys.used; ++internal->l) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        if (quantitys.array[internal->l].total) {
          internal->k += FL_payload_digit_size_2_d + f_fss_extended_next_s.used + internal->quote_null.used * 2;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_quantity_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used * 2;
        }
      } // for

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 2;
      }

      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_quantitys_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < quantitys.used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (quantitys.array[internal->l].total) {
            if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].start) == F_true) return F_true;
            if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].total) == F_true) return F_true;

            continue;
          }

          if (data->flag & f_fss_payload_header_map_flag_null_quantity_e) {
            if (data->cache->used) {
              state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }

            if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          }
        } // for

        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        data->cache->used = 0;

        if (data->flag & f_fss_payload_header_map_flag_join_quantity_e) {
          state->status = f_memory_array_increase_by(FL_payload_digit_size_2_d, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;

          for (internal->l = 0; internal->l < quantitys.used; ++internal->l) {

            if (state->interrupt) {
              state->interrupt((void * const) state, (void * const) internal);
              if (F_status_set_fine(state->status) == F_interrupt) return F_true;
            }

            if (quantitys.array[internal->l].total) {
              data->cache->used = 0;

              if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].start) == F_true) return F_true;
              if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].total) == F_true) return F_true;
              if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

              continue;
            }

            if (data->flag & f_fss_payload_header_map_flag_null_quantity_e) {
              data->cache->used = 0;

              if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
              if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
            }
          } // for
        }
        else {
          state->status = f_memory_array_increase_by(FL_payload_digit_size_1_d, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;

          for (internal->l = 0; internal->l < quantitys.used; ++internal->l) {

            if (state->interrupt) {
              state->interrupt((void * const) state, (void * const) internal);
              if (F_status_set_fine(state->status) == F_interrupt) return F_true;
            }

            if (quantitys.array[internal->l].total) {
              data->cache->used = 0;

              if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].start) == F_true) return F_true;
              if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

              data->cache->used = 0;

              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;

              if (private_fl_payload_header_map_number_unsigned(data, state, internal, quantitys.array[internal->l].total) == F_true) return F_true;
              if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;

              continue;
            }

            if (data->flag & f_fss_payload_header_map_flag_null_quantity_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          } // for

          // Remove the always added trailing space (except when all quantitys are NULL and f_fss_payload_header_map_flag_null_quantity_e is not set).
          if (destinations->array[destinations->used].value.used) {
            destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
          }
        }
      }
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_null_quantitys_e) {
        if (data->flag & f_fss_payload_header_map_flag_join_quantitys_quantity_e) {
          data->cache->used = 0;

          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
        else {
          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, &destinations->array[destinations->used].value, f_fss_extended_next_s) == F_true) return F_true;
        }
      }
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_range(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_range_t range, f_string_maps_t * const destinations) {

    if (range.start > range.stop) {
      if (data->flag & f_fss_payload_header_map_flag_null_range_e) {
        if (data->flag & f_fss_payload_header_map_flag_join_range_e) {
          data->cache->used = 0;

          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
        else {
          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, &destinations->array[destinations->used].value, f_fss_extended_next_s) == F_true) return F_true;
        }
      }
    }
    else {
      data->cache->used = 0;

      if (private_fl_payload_header_map_number_unsigned(data, state, internal, range.start) == F_true) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_range_e) {
        if (private_fl_payload_header_map_number_unsigned(data, state, internal, range.stop) == F_true) return F_true;
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

        state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
        if (F_status_is_error(state->status)) return F_true;

        data->cache->used = 0;

        if (private_fl_payload_header_map_number_unsigned(data, state, internal, range.stop) == F_true) return F_true;
        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_ranges(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_ranges_t ranges, f_string_maps_t * const destinations) {

    if (ranges.used) {
      internal->k = 0;

      for (internal->l = 0; internal->l < ranges.used; ++internal->l) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        if (ranges.array[internal->l].start > ranges.array[internal->l].stop) {
          internal->k += FL_payload_digit_size_2_d + f_fss_extended_next_s.used + internal->quote_null.used * 2;
        }
        else if (data->flag & f_fss_payload_header_map_flag_null_range_e) {
          internal->k += f_fss_extended_next_s.used + internal->quote_null.used * 2;
        }
      } // for

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 4;
      }

      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_ranges_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < ranges.used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (ranges.array[internal->l].start > ranges.array[internal->l].stop) {
            if (data->flag & f_fss_payload_header_map_flag_null_range_e) {
              if (data->cache->used) {
                state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
                if (F_status_is_error(state->status)) return F_true;
              }

              if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
            }

            continue;
          }

          if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].start) == F_true) return F_true;
          if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].stop) == F_true) return F_true;
        } // for

        if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
      }
      else {
        data->cache->used = 0;

        if (data->flag & f_fss_payload_header_map_flag_join_range_e) {
          state->status = f_memory_array_increase_by(FL_payload_digit_size_2_d, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;

          for (internal->l = 0; internal->l < ranges.used; ++internal->l) {

            if (state->interrupt) {
              state->interrupt((void * const) state, (void * const) internal);
              if (F_status_set_fine(state->status) == F_interrupt) return F_true;
            }

            if (ranges.array[internal->l].start > ranges.array[internal->l].stop) {
              if (data->flag & f_fss_payload_header_map_flag_null_range_e) {
                data->cache->used = 0;

                if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
                if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
              }

              continue;
            }

            data->cache->used = 0;

            if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].start) == F_true) return F_true;
            if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].stop) == F_true) return F_true;
            if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
          } // for
        }
        else {
          state->status = f_memory_array_increase_by(FL_payload_digit_size_1_d, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
          if (F_status_is_error(state->status)) return F_true;

          for (internal->l = 0; internal->l < ranges.used; ++internal->l) {

            if (state->interrupt) {
              state->interrupt((void * const) state, (void * const) internal);
              if (F_status_set_fine(state->status) == F_interrupt) return F_true;
            }

            if (ranges.array[internal->l].start > ranges.array[internal->l].stop) {
              if (data->flag & f_fss_payload_header_map_flag_null_range_e) {
                state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
                if (F_status_is_error(state->status)) return F_true;
              }

              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;

              continue;
            }

            data->cache->used = 0;

            if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].start) == F_true) return F_true;
            if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

            data->cache->used = 0;

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;

            if (private_fl_payload_header_map_number_unsigned(data, state, internal, ranges.array[internal->l].stop) == F_true) return F_true;
            if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          } // for

          // Remove the always added trailing space (except when all ranges are NULL and f_fss_payload_header_map_flag_null_range_e is not set).
          if (destinations->array[destinations->used].value.used) {
            destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
          }
        }
      }
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_null_ranges_e) {
        if (data->flag & f_fss_payload_header_map_flag_join_ranges_range_e) {
          data->cache->used = 0;

          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
        else {
          if (private_fl_payload_helper_header_map_destination_write_empty_two(data, state, internal, &destinations->array[destinations->used].value, f_fss_extended_next_s) == F_true) return F_true;
        }
      }
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_strings(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_t * const buffers, f_string_maps_t * const destinations) {

    if (buffers && buffers[0]) {
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

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 4;
      }

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

            if (internal->j + 1 < internal->l) {
              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }
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
    }
    else {
      state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_triple(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_string_triple_t triple, f_string_maps_t * const destinations) {

    f_string_dynamic_t * const destination = (data->flag & f_fss_payload_header_map_flag_join_triple_e) ? data->cache : &destinations->array[destinations->used].value;
    const f_string_static_t separator = (data->flag & f_fss_payload_header_map_flag_join_triple_e) ? f_string_space_s : f_fss_extended_next_s;
    const f_string_static_t a = triple.a.used ? triple.a : internal->quote_null;
    const f_string_static_t b = triple.b.used ? triple.b : internal->quote_null;
    const f_string_static_t c = triple.c.used ? triple.c : internal->quote_null;

    data->cache->used = 0;

    state->status = f_memory_array_increase_by(a.used + b.used + c.used + separator.used * 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
    if (F_status_is_error(state->status)) return F_true;

    if (triple.a.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
      if (data->flag & f_fss_payload_header_map_flag_join_triple_e) {
        state->status = f_string_dynamic_append(a, destination);
      }
      else {
        internal->range.start = 0;
        internal->range.stop = a.used - 1;

        private_fl_fss_basic_write(F_false, a, internal->quote, &internal->range, destination, state, (void * const) internal);
      }

      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
        state->status = f_string_dynamic_append(separator, destination);
        if (F_status_is_error(state->status)) return F_true;
      }
    }

    if (triple.b.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
      if (data->flag & f_fss_payload_header_map_flag_join_triple_e) {
        state->status = f_string_dynamic_append(b, destination);
      }
      else {
        internal->range.start = 0;
        internal->range.stop = b.used - 1;

        private_fl_fss_basic_write(F_false, b, internal->quote, &internal->range, destination, state, (void * const) internal);
      }

      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
        state->status = f_string_dynamic_append(separator, destination);
        if (F_status_is_error(state->status)) return F_true;
      }
    }

    if (triple.c.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
      if (data->flag & f_fss_payload_header_map_flag_join_triple_e) {
        state->status = f_string_dynamic_append(c, destination);
      }
      else {
        internal->range.start = 0;
        internal->range.stop = c.used - 1;

        private_fl_fss_basic_write(F_false, c, internal->quote, &internal->range, destination, state, (void * const) internal);
      }

      if (F_status_is_error(state->status)) return F_true;
    }

    if (data->flag & f_fss_payload_header_map_flag_join_triple_e) {
      if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
    }
    else {
      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_header_map_triples(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, const f_string_triples_t triples, f_string_maps_t * const destinations) {

    if (triples.used) {
      internal->k = 0;

      for (internal->l = 0; internal->l < triples.used; ++internal->l) {

        if (state->interrupt) {
          state->interrupt((void * const) state, (void * const) internal);
          if (F_status_set_fine(state->status) == F_interrupt) return F_true;
        }

        internal->k += (triples.array[internal->l].a.used) ? triples.array[internal->l].a.used : internal->quote_null.used;
        internal->k += (triples.array[internal->l].b.used) ? triples.array[internal->l].b.used : internal->quote_null.used;
        internal->k += (triples.array[internal->l].c.used) ? triples.array[internal->l].c.used : internal->quote_null.used;
        internal->k += (data->flag & f_fss_payload_header_map_flag_join_triple_e) ? f_fss_space_s.used * 2 : f_fss_extended_next_s.used * 2;
      } // for

      // Add additional characters for the standard placeholders.
      if (internal->k) {
        internal->k += f_fss_placeholder_s.used * 4;
      }

      state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &destinations->array[destinations->used].value.string, &destinations->array[destinations->used].value.used, &destinations->array[destinations->used].value.size);
      if (F_status_is_error(state->status)) return F_true;

      if (data->flag & f_fss_payload_header_map_flag_join_triples_triple_e) {
        data->cache->used = 0;

        state->status = f_memory_array_increase_by(internal->k, sizeof(f_char_t), (void **) &data->cache->string, &data->cache->used, &data->cache->size);
        if (F_status_is_error(state->status)) return F_true;

        for (internal->l = 0; internal->l < triples.used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (!(data->flag & f_fss_payload_header_map_flag_join_triples_e)) {
            if (data->cache->used) {
              state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            data->cache->used = 0;
          }
          else {
            if (data->cache->used) {
              state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (triples.array[internal->l].a.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].a.used) {
              state->status = f_string_dynamic_append(triples.array[internal->l].a, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }

            if (triples.array[internal->l].b.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
              state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (triples.array[internal->l].b.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].b.used) {
              state->status = f_string_dynamic_append(triples.array[internal->l].b, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }

            if (triples.array[internal->l].c.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
              state->status = f_string_dynamic_append_assure(f_fss_space_s, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (triples.array[internal->l].c.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].c.used) {
              state->status = f_string_dynamic_append(triples.array[internal->l].c, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, data->cache);
              if (F_status_is_error(state->status)) return F_true;
            }
          }

          if (!(data->flag & f_fss_payload_header_map_flag_join_triples_e)) {
            if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
          }
        } // for

        if (data->flag & f_fss_payload_header_map_flag_join_triples_e) {
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
      }
      else {
        data->cache->used = 0;

        for (internal->l = 0; internal->l < triples.used; ++internal->l) {

          if (state->interrupt) {
            state->interrupt((void * const) state, (void * const) internal);
            if (F_status_set_fine(state->status) == F_interrupt) return F_true;
          }

          if (triples.array[internal->l].a.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].a.used) {
              internal->range.start = 0;
              internal->range.stop = triples.array[internal->l].a.used - 1;

              private_fl_fss_basic_write(F_false, triples.array[internal->l].a, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (triples.array[internal->l].b.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].b.used) {
              internal->range.start = 0;
              internal->range.stop = triples.array[internal->l].b.used - 1;

              private_fl_fss_basic_write(F_false, triples.array[internal->l].b, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }

          if (triples.array[internal->l].c.used || (data->flag & f_fss_payload_header_map_flag_null_triple_e)) {
            if (triples.array[internal->l].c.used) {
              internal->range.start = 0;
              internal->range.stop = triples.array[internal->l].c.used - 1;

              private_fl_fss_basic_write(F_false, triples.array[internal->l].c, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
              if (F_status_is_error(state->status)) return F_true;
            }
            else if (data->flag & f_fss_payload_header_map_flag_null_triple_e) {
              state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
              if (F_status_is_error(state->status)) return F_true;
            }

            state->status = f_string_dynamic_append_assure(f_fss_extended_next_s, &destinations->array[destinations->used].value);
            if (F_status_is_error(state->status)) return F_true;
          }
        } // for

        // Remove the always added trailing space (except when all triples are NULL and f_fss_payload_header_map_flag_null_triple_e is not set).
        if (destinations->array[destinations->used].value.used) {
          destinations->array[destinations->used].value.used -= f_fss_extended_next_s.used;
        }
      }
    }
    else {
      if (data->flag & f_fss_payload_header_map_flag_null_triples_e) {
        if (data->flag & f_fss_payload_header_map_flag_join_triples_triple_e) {
          data->cache->used = 0;

          if (private_fl_payload_helper_header_map_destination_write_empty_three(data, state, internal, data->cache, f_fss_space_s) == F_true) return F_true;
          if (private_fl_payload_helper_header_map_destination_write_buffer(data, state, internal, data->cache, destinations) == F_true) return F_true;
        }
        else {
          if (private_fl_payload_helper_header_map_destination_write_empty_three(data, state, internal, &destinations->array[destinations->used].value, f_fss_extended_next_s) == F_true) return F_true;
        }
      }
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif
