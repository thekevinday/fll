/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_h
#define _PRIVATE_F_type_array_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the cellss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param cellss
 *   The cellss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_cellss_adjust()
 * @see f_type_cellss_decimate_by()
 */
#if !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)
  extern f_status_t private_f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)

/**
 * Private implementation for resizing the cellss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param cellss
 *   The cellss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_cellss_decrease_by()
 * @see f_type_cellss_increase()
 * @see f_type_cellss_increase_by()
 * @see f_type_cellss_resize()
 */
#if !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)
  extern f_status_t private_f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengthss
 *   The lengthss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_array_lengthss_adjust()
 * @see f_type_array_lengthss_decimate_by()
 */
#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  extern f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param lengthss
 *   The lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_array_lengthss_decrease_by()
 * @see f_type_array_lengthss_increase()
 * @see f_type_array_lengthss_increase_by()
 * @see f_type_array_lengthss_resize()
 */
#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)
  extern f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8ss
 *   The int8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int8ss_adjust()
 * @see f_type_int8ss_decimate_by()
 */
#if !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)
  extern f_status_t private_f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int8ss
 *   The int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int8ss_decrease_by()
 * @see f_type_int8ss_increase()
 * @see f_type_int8ss_increase_by()
 * @see f_type_int8ss_resize()
 */
#if !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)
  extern f_status_t private_f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)

/**
 * Private implementation for resizing the uint8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint8ss
 *   The uint8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint8ss_adjust()
 * @see f_type_uint8ss_decimate_by()
 */
#if !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)
  extern f_status_t private_f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)

/**
 * Private implementation for resizing the uint8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint8ss
 *   The uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint8ss_decrease_by()
 * @see f_type_uint8ss_increase()
 * @see f_type_uint8ss_increase_by()
 * @see f_type_uint8ss_resize()
 */
#if !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)
  extern f_status_t private_f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)

/**
 * Private implementation for resizing the int16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int16ss
 *   The int16ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int16ss_adjust()
 * @see f_type_int16ss_decimate_by()
 */
#if !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)
  extern f_status_t private_f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)

/**
 * Private implementation for resizing the int16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int16ss
 *   The int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int16ss_decrease_by()
 * @see f_type_int16ss_increase()
 * @see f_type_int16ss_increase_by()
 * @see f_type_int16ss_resize()
 */
#if !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)
  extern f_status_t private_f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16ss
 *   The uint16ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint16ss_adjust()
 * @see f_type_uint16ss_decimate_by()
 */
#if !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)
  extern f_status_t private_f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint16ss
 *   The uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint16ss_decrease_by()
 * @see f_type_uint16ss_increase()
 * @see f_type_uint16ss_increase_by()
 * @see f_type_uint16ss_resize()
 */
#if !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)
  extern f_status_t private_f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)

/**
 * Private implementation for resizing the int32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int32ss
 *   The int32ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int32ss_adjust()
 * @see f_type_int32ss_decimate_by()
 */
#if !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)
  extern f_status_t private_f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)

/**
 * Private implementation for resizing the int32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int32ss
 *   The int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int32ss_decrease_by()
 * @see f_type_int32ss_increase()
 * @see f_type_int32ss_increase_by()
 * @see f_type_int32ss_resize()
 */
#if !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)
  extern f_status_t private_f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)

/**
 * Private implementation for resizing the uint32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint32ss
 *   The uint32ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint32ss_adjust()
 * @see f_type_uint32ss_decimate_by()
 */
#if !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)
  extern f_status_t private_f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)

/**
 * Private implementation for resizing the uint32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint32ss
 *   The uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint32ss_decrease_by()
 * @see f_type_uint32ss_increase()
 * @see f_type_uint32ss_increase_by()
 * @see f_type_uint32ss_resize()
 */
#if !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)
  extern f_status_t private_f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)

/**
 * Private implementation for resizing the int64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int64ss
 *   The int64ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int64ss_adjust()
 * @see f_type_int64ss_decimate_by()
 */
#if !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)
  extern f_status_t private_f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)

/**
 * Private implementation for resizing the int64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int64ss
 *   The int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int64ss_decrease_by()
 * @see f_type_int64ss_increase()
 * @see f_type_int64ss_increase_by()
 * @see f_type_int64ss_resize()
 */
#if !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)
  extern f_status_t private_f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)

/**
 * Private implementation for resizing the uint64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint64ss
 *   The uint64ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint64ss_adjust()
 * @see f_type_uint64ss_decimate_by()
 */
#if !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)
  extern f_status_t private_f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)

/**
 * Private implementation for resizing the uint64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint64ss
 *   The uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint64ss_decrease_by()
 * @see f_type_uint64ss_increase()
 * @see f_type_uint64ss_increase_by()
 * @see f_type_uint64ss_resize()
 */
#if !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)
  extern f_status_t private_f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)

/**
 * Private implementation for resizing the int128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int128ss
 *   The int128ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int128ss_adjust()
 * @see f_type_int128ss_resize()
 */
#if !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)
  extern f_status_t private_f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)

/**
 * Private implementation for resizing the int128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int128ss
 *   The int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_int128ss_decrease_by()
 * @see f_type_int128ss_increase()
 * @see f_type_int128ss_increase_by()
 * @see f_type_int128ss_resize()
 */
#if !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)
  extern f_status_t private_f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128ss
 *   The uint128ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint128ss_adjust()
 * @see f_type_uint128ss_decimate_by()
 */
#if !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)
  extern f_status_t private_f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint128ss
 *   The uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_type_uint128ss_decrease_by()
 * @see f_type_uint128ss_increase()
 * @see f_type_uint128ss_increase_by()
 * @see f_type_uint128ss_resize()
 */
#if !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)
  extern f_status_t private_f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_h
