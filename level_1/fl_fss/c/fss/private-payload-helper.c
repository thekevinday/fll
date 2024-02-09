#include "payload.h"
#include "../private-fss.h"
#include "private-payload-helper.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_helper_header_map_destination_write_buffer(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations) {

    if (buffer->used) {
      internal->range.start = 0;
      internal->range.stop = buffer->used - 1;

      private_fl_fss_basic_write(F_false, *buffer, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_helper_header_map_destination_write_buffer_or_empty(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations, const uint64_t append_on_empty) {

    if (buffer->used) {
      internal->range.start = 0;
      internal->range.stop = buffer->used - 1;

      private_fl_fss_basic_write(F_false, *buffer, 0, &internal->range, &destinations->array[destinations->used].value, state, (void * const) internal);
      if (F_status_is_error(state->status)) return F_true;

      state->status = f_string_dynamic_strip_null(&destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }
    else if (data->flag & append_on_empty) {
      state->status = f_string_dynamic_append(internal->quote_null, &destinations->array[destinations->used].value);
      if (F_status_is_error(state->status)) return F_true;
    }

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_helper_header_map_destination_write_empty_three(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const destination, const f_string_static_t separator) {

    state->status = f_memory_array_increase_by(internal->quote_null.used * 3 + separator.used * 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append_assure(separator, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append_assure(separator, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#if !defined(_di_fl_fss_payload_header_map_)
  uint8_t private_fl_payload_helper_header_map_destination_write_empty_two(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const destination, const f_string_static_t separator) {

    state->status = f_memory_array_increase_by(internal->quote_null.used * 2 + separator.used, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append_assure(separator, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = f_string_dynamic_append(internal->quote_null, destination);
    if (F_status_is_error(state->status)) return F_true;

    state->status = F_okay;

    return F_false;
  }
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif
