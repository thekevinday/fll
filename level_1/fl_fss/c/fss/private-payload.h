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
#ifndef _PRIVATE_FL_fss_payload_h
#define _PRIVATE_FL_fss_payload_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Write the cache to the destination.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   This caller must reset data.cache.used as needed.
 *   if data.cache.used is not 0, then this will append a space before adding the converted number.
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
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   The internal.range is modified.
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
  extern uint8_t private_fl_payload_header_map_cache(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the dynamic string, writing it into the packet with the appropriate escaping as necessary.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param buffer
 *   The dynamic string to read from.
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_dynamic(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_static_t * const buffer, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the array of dynamic strings, writing it into the packet with the appropriate escaping as necessary.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param headers
 *   An abstruse map representing individual headers.
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   This modifies data.cache.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param buffers
 *   The array of dynamic strings to read from.
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_dynamics(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_statics_t * const buffers, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the map strings, writing it into the packet with the appropriate escaping as necessary.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param map
 *   The map to read from.
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_map(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_map_t * const map, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the case where a map is added with the appropriate NULL flag bits set.
 *
 * This adds the data.quote_null strings for both the map name and the map value, depending on the f_fss_payload_header_map_flag_null_map_name_e and f_fss_payload_header_map_flag_null_map_value_e flags.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_map_name_value_null(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the map strings, writing it into the packet with the appropriate escaping as necessary.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param maps
 *   The maps to read from.
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_maps_)
  extern uint8_t private_fl_payload_header_map_maps(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_maps_t * const maps, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_maps_)

/**
 * Process the signed number, converting it to a string and appending that string onto data->cache.
 * The resulting data->cache is then appended onto the destination value on success.
 * If the number is not appended to data->cache, then nothing is appended to the destination value.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   This caller must reset data.cache.used as needed.
 *   If data.cache.used is not 0, then this will append a space before adding the converted number.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_conversion_number_signed_to_string().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param number
 *   The signed number.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_conversion_number_unsigned_to_string()
 * @see f_string_dynamic_append_assure()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_number_signed(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_signed_t number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the unsigned number, converting it to a string and appending that string onto data->cache.
 * The resulting data->cache is then appended onto the destination value on success.
 * If the number is not appended to data->cache, then nothing is appended to the destination value.
 *
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   This caller must reset data.cache.used as needed.
 *   if data.cache.used is not 0, then this will append a space before adding the converted number.
 *
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_conversion_number_unsigned_to_string().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param number
 *   The unsigned number.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_conversion_number_unsigned_to_string()
 * @see f_string_dynamic_append_assure()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_number_unsigned(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, const f_number_unsigned_t number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

/**
 * Process the array of NULL terminated strings, writing it into the packet with the appropriate escaping as necessary.
 *
 * This expects that the appropriate used and flag checks are performed prior to calling this.
 *
 * @param headers
 *   An abstruse map representing individual headers.
 * @param data
 *   The f_fss_payload_header_state_t pointer.
 *   This modifies data.cache.
 *   Must not be NULL.
 * @param state
 *   The state passed directly from the fl_fss_payload_header_map() parameters.
 *
 *   This alters state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: private_fl_fss_basic_write().
 *
 *   Must not be NULL.
 * @param internal
 *   The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *   Must not be NULL.
 * @param buffers
 *   The array of NULL terminated strings to read from.
 *   Must not be NULL.
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *   This is updated as appropriate.
 *   Must not be NULL.
 *
 * @return
 *   F_true if the caller should break or exit due to an error or something similar.
 *   F_false, otherwise.
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_strip_null()
 *
 * @see private_fl_fss_basic_write()
 *
 * @see fl_fss_payload_header_map()
 */
#if !defined(_di_fl_fss_payload_header_map_)
  extern uint8_t private_fl_payload_header_map_strings(f_fss_payload_header_state_t * const data, f_state_t * const state, f_fss_payload_header_internal_t * const internal, f_string_t * const buffers, f_string_maps_t * const destinations) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_payload_header_map_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_payload_h