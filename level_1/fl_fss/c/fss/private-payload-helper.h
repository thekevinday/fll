/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_fss_payload_helper_h
#define _PRIVATE_FL_fss_payload_helper_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Write to the next destinations value, doing nothing on empty buffer.
 *
 * @param data
 *   The fl_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, fl_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   The internal.range is modified.
 *   Must not be NULL.
 * @param buffer
 *   The buffer to write using the FLL Extended (FSS-0001) format.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see private_fl_fss_basic_write()
 * @see f_string_dynamic_strip_null()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_helper_header_map_destination_write_buffer(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Write to the next destinations value, and if empty adding the quotes on NULL if needed.
 *
 * @param data
 *   The fl_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, fl_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   The internal.range is modified.
 *   Must not be NULL.
 * @param buffer
 *   The buffer to write using the FLL Extended (FSS-0001) format.
 *   Must not be NULL.
 * @param append_on_empty
 *   Append the quoted empty string when the this flag is set.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see private_fl_fss_basic_write()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_strip_null()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_helper_header_map_destination_write_buffer_or_empty(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations, const uint64_t append_on_empty) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Write three quoted empty strings to the destination.
 *
 * @param data
 *   The fl_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, fl_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   The internal.range is modified.
 *   Must not be NULL.
 * @param destination
 *   The buffer to append to.
 *   Must not be NULL.
 * @param separator
 *   The separate to use between each quoted empty string.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see private_fl_fss_basic_write()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_helper_header_map_destination_write_empty_three(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_static_t * const destination, const f_string_static_t separator) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Write two quoted empty strings to the destination.
 *
 * @param data
 *   The fl_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, fl_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   The internal.range is modified.
 *   Must not be NULL.
 * @param destination
 *   The buffer to append to.
 *   Must not be NULL.
 * @param separator
 *   The separate to use between each quoted empty string.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see private_fl_fss_basic_write()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_helper_header_map_destination_write_empty_two(fl_fss_payload_header_state_t * const data, f_state_t * const state, fl_fss_payload_header_internal_t * const internal, f_string_static_t * const destination, const f_string_static_t separator) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_payload_helper_h
