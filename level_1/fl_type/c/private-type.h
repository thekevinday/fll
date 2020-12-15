/**
 * FLL - Level 1
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_type_h
#define _PRIVATE_FL_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for deleting the cells array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param cells
 *   The cells array to delete.
 */
#if !defined(_di_fl_type_cells_delete_)
  extern void private_fl_type_cells_delete(f_cells_t *cells) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_cells_delete_)

/**
 * Private implementation for resizing the cells array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param cells
 *   The cells array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_cells_t_resize().
 *
 * @see f_macro_cells_t_resize()
 */
#if !defined(_di_fl_type_cells_increase_) || !defined(_di_fl_type_cells_increase_by_)
  extern f_return_status private_fl_type_cells_resize(const f_array_length_t length, f_cells_t *cells) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_cells_increase_) || !defined(_di_fl_type_cells_increase_by_)

/**
 * Private implementation for deleting the cellss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param cellss
 *   The cellss array to delete.
 */
#if !defined(_di_fl_type_cellss_delete_)
  extern void private_fl_type_cellss_delete(f_cellss_t *cellss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_cellss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_cellss_t_resize().
 *
 * @see f_macro_cellss_t_resize()
 */
#if !defined(_di_fl_type_cellss_increase_) || !defined(_di_fl_type_cellss_increase_by_)
  extern f_return_status private_fl_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_cellss_increase_) || !defined(_di_fl_type_cellss_increase_by_)

/**
 * Private implementation for deleting the lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param lengths
 *   The lengths array to delete.
 */
#if !defined(_di_fl_type_array_lengths_delete_)
  extern void private_fl_type_array_lengths_delete(f_array_lengths_t *lengths) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_array_lengths_delete_)

/**
 * Private implementation for resizing the lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param lengths
 *   The lengths array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_array_lengths_t_resize().
 *
 * @see f_macro_array_lengths_t_resize()
 */
#if !defined(_di_fl_type_array_lengths_increase_) || !defined(_di_fl_type_array_lengths_increase_by_)
  extern f_return_status private_fl_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_array_lengths_increase_) || !defined(_di_fl_type_array_lengths_increase_by_)

/**
 * Private implementation for deleting the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param lengthss
 *   The lengthss array to delete.
 */
#if !defined(_di_fl_type_array_lengthss_delete_)
  extern void private_fl_type_array_lengthss_delete(f_array_lengthss_t *lengthss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_array_lengthss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_array_lengthss_t_resize().
 *
 * @see f_macro_array_lengthss_t_resize()
 */
#if !defined(_di_fl_type_array_lengthss_increase_) || !defined(_di_fl_type_array_lengthss_increase_by_)
  extern f_return_status private_fl_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_array_lengthss_increase_) || !defined(_di_fl_type_array_lengthss_increase_by_)

/**
 * Private implementation for deleting the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int8s
 *   The int8s array to delete.
 */
#if !defined(_di_fl_type_int8s_delete_)
  extern void private_fl_type_int8s_delete(f_int8s_t *int8s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int8s_delete_)

/**
 * Private implementation for resizing the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int8s
 *   The int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_int8s_t_resize().
 *
 * @see f_macro_int8s_t_resize()
 */
#if !defined(_di_fl_type_int8s_increase_) || !defined(_di_fl_type_int8s_increase_by_)
  extern f_return_status private_fl_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int8s_increase_) || !defined(_di_fl_type_int8s_increase_by_)

/**
 * Private implementation for deleting the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int8ss
 *   The int8ss array to delete.
 */
#if !defined(_di_fl_type_int8ss_delete_)
  extern void private_fl_type_int8ss_delete(f_int8ss_t *int8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int8ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_int8ss_t_resize().
 *
 * @see f_macro_int8ss_t_resize()
 */
#if !defined(_di_fl_type_int8ss_increase_) || !defined(_di_fl_type_int8ss_increase_by_)
  extern f_return_status private_fl_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int8ss_increase_) || !defined(_di_fl_type_int8ss_increase_by_)

/**
 * Private implementation for deleting the uint8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint8s
 *   The uint8s array to delete.
 */
#if !defined(_di_fl_type_uint8s_delete_)
  extern void private_fl_type_uint8s_delete(f_uint8s_t *uint8s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint8s_delete_)

/**
 * Private implementation for resizing the uint8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint8s
 *   The uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_uint8s_t_resize().
 *
 * @see f_macro_uint8s_t_resize()
 */
#if !defined(_di_fl_type_uint8s_increase_) || !defined(_di_fl_type_uint8s_increase_by_)
  extern f_return_status private_fl_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint8s_increase_) || !defined(_di_fl_type_uint8s_increase_by_)

/**
 * Private implementation for deleting the uint8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint8ss
 *   The uint8ss array to delete.
 */
#if !defined(_di_fl_type_uint8ss_delete_)
  extern void private_fl_type_uint8ss_delete(f_uint8ss_t *uint8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint8ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_uint8ss_t_resize().
 *
 * @see f_macro_uint8ss_t_resize()
 */
#if !defined(_di_fl_type_uint8ss_increase_) || !defined(_di_fl_type_uint8ss_increase_by_)
  extern f_return_status private_fl_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint8ss_increase_) || !defined(_di_fl_type_uint8ss_increase_by_)

/**
 * Private implementation for deleting the int16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int16s
 *   The int16s array to delete.
 */
#if !defined(_di_fl_type_int16s_delete_)
  extern void private_fl_type_int16s_delete(f_int16s_t *int16s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int16s_delete_)

/**
 * Private implementation for resizing the int16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int16s
 *   The int16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_int16s_t_resize().
 *
 * @see f_macro_int16s_t_resize()
 */
#if !defined(_di_fl_type_int16s_increase_) || !defined(_di_fl_type_int16s_increase_by_)
  extern f_return_status private_fl_type_int16s_resize(const f_array_length_t length, f_int16s_t *int16s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int16s_increase_) || !defined(_di_fl_type_int16s_increase_by_)

/**
 * Private implementation for deleting the int16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int16ss
 *   The int16ss array to delete.
 */
#if !defined(_di_fl_type_int16ss_delete_)
  extern void private_fl_type_int16ss_delete(f_int16ss_t *int16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int16ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_int16ss_t_resize().
 *
 * @see f_macro_int16ss_t_resize()
 */
#if !defined(_di_fl_type_int16ss_increase_) || !defined(_di_fl_type_int16ss_increase_by_)
  extern f_return_status private_fl_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int16ss_increase_) || !defined(_di_fl_type_int16ss_increase_by_)

/**
 * Private implementation for deleting the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint16s
 *   The uint16s array to delete.
 */
#if !defined(_di_fl_type_uint16s_delete_)
  extern void private_fl_type_uint16s_delete(f_uint16s_t *uint16s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint16s_delete_)

/**
 * Private implementation for resizing the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint16s
 *   The uint16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_uint16s_t_resize().
 *
 * @see f_macro_uint16s_t_resize()
 */
#if !defined(_di_fl_type_uint16s_increase_) || !defined(_di_fl_type_uint16s_increase_by_)
  extern f_return_status private_fl_type_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint16s_increase_) || !defined(_di_fl_type_uint16s_increase_by_)

/**
 * Private implementation for deleting the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint16ss
 *   The uint16ss array to delete.
 */
#if !defined(_di_fl_type_uint16ss_delete_)
  extern void private_fl_type_uint16ss_delete(f_uint16ss_t *uint16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint16ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_uint16ss_t_resize().
 *
 * @see f_macro_uint16ss_t_resize()
 */
#if !defined(_di_fl_type_uint16ss_increase_) || !defined(_di_fl_type_uint16ss_increase_by_)
  extern f_return_status private_fl_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint16ss_increase_) || !defined(_di_fl_type_uint16ss_increase_by_)

/**
 * Private implementation for deleting the int32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int32s
 *   The int32s array to delete.
 */
#if !defined(_di_fl_type_int32s_delete_)
  extern void private_fl_type_int32s_delete(f_int32s_t *int32s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int32s_delete_)

/**
 * Private implementation for resizing the int32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int32s
 *   The int32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_int32s_t_resize().
 *
 * @see f_macro_int32s_t_resize()
 */
#if !defined(_di_fl_type_int32s_increase_) || !defined(_di_fl_type_int32s_increase_by_)
  extern f_return_status private_fl_type_int32s_resize(const f_array_length_t length, f_int32s_t *int32s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int32s_increase_) || !defined(_di_fl_type_int32s_increase_by_)

/**
 * Private implementation for deleting the int32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int32ss
 *   The int32ss array to delete.
 */
#if !defined(_di_fl_type_int32ss_delete_)
  extern void private_fl_type_int32ss_delete(f_int32ss_t *int32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int32ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_int32ss_t_resize().
 *
 * @see f_macro_int32ss_t_resize()
 */
#if !defined(_di_fl_type_int32ss_increase_) || !defined(_di_fl_type_int32ss_increase_by_)
  extern f_return_status private_fl_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int32ss_increase_) || !defined(_di_fl_type_int32ss_increase_by_)

/**
 * Private implementation for deleting the uint32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint32s
 *   The uint32s array to delete.
 */
#if !defined(_di_fl_type_uint32s_delete_)
  extern void private_fl_type_uint32s_delete(f_uint32s_t *uint32s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint32s_delete_)

/**
 * Private implementation for resizing the uint32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint32s
 *   The uint32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_uint32s_t_resize().
 *
 * @see f_macro_uint32s_t_resize()
 */
#if !defined(_di_fl_type_uint32s_increase_) || !defined(_di_fl_type_uint32s_increase_by_)
  extern f_return_status private_fl_type_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint32s_increase_) || !defined(_di_fl_type_uint32s_increase_by_)

/**
 * Private implementation for deleting the uint32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint32ss
 *   The uint32ss array to delete.
 */
#if !defined(_di_fl_type_uint32ss_delete_)
  extern void private_fl_type_uint32ss_delete(f_uint32ss_t *uint32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint32ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_uint32ss_t_resize().
 *
 * @see f_macro_uint32ss_t_resize()
 */
#if !defined(_di_fl_type_uint32ss_increase_) || !defined(_di_fl_type_uint32ss_increase_by_)
  extern f_return_status private_fl_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint32ss_increase_) || !defined(_di_fl_type_uint32ss_increase_by_)

/**
 * Private implementation for deleting the int64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int64s
 *   The int64s array to delete.
 */
#if !defined(_di_fl_type_int64s_delete_)
  extern void private_fl_type_int64s_delete(f_int64s_t *int64s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int64s_delete_)

/**
 * Private implementation for resizing the int64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int64s
 *   The int64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_int64s_t_resize().
 *
 * @see f_macro_int64s_t_resize()
 */
#if !defined(_di_fl_type_int64s_increase_) || !defined(_di_fl_type_int64s_increase_by_)
  extern f_return_status private_fl_type_int64s_resize(const f_array_length_t length, f_int64s_t *int64s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int64s_increase_) || !defined(_di_fl_type_int64s_increase_by_)

/**
 * Private implementation for deleting the int64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int64ss
 *   The int64ss array to delete.
 */
#if !defined(_di_fl_type_int64ss_delete_)
  extern void private_fl_type_int64ss_delete(f_int64ss_t *int64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int64ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_int64ss_t_resize().
 *
 * @see f_macro_int64ss_t_resize()
 */
#if !defined(_di_fl_type_int64ss_increase_) || !defined(_di_fl_type_int64ss_increase_by_)
  extern f_return_status private_fl_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int64ss_increase_) || !defined(_di_fl_type_int64ss_increase_by_)

/**
 * Private implementation for deleting the uint64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint64s
 *   The uint64s array to delete.
 */
#if !defined(_di_fl_type_uint64s_delete_)
  extern void private_fl_type_uint64s_delete(f_uint64s_t *uint64s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint64s_delete_)

/**
 * Private implementation for resizing the uint64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint64s
 *   The uint64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_uint64s_t_resize().
 *
 * @see f_macro_uint64s_t_resize()
 */
#if !defined(_di_fl_type_uint64s_increase_) || !defined(_di_fl_type_uint64s_increase_by_)
  extern f_return_status private_fl_type_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint64s_increase_) || !defined(_di_fl_type_uint64s_increase_by_)

/**
 * Private implementation for deleting the uint64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint64ss
 *   The uint64ss array to delete.
 */
#if !defined(_di_fl_type_uint64ss_delete_)
  extern void private_fl_type_uint64ss_delete(f_uint64ss_t *uint64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint64ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_uint64ss_t_resize().
 *
 * @see f_macro_uint64ss_t_resize()
 */
#if !defined(_di_fl_type_uint64ss_increase_) || !defined(_di_fl_type_uint64ss_increase_by_)
  extern f_return_status private_fl_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint64ss_increase_) || !defined(_di_fl_type_uint64ss_increase_by_)

/**
 * Private implementation for deleting the int128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int128s
 *   The int128s array to delete.
 */
#if !defined(_di_fl_type_int128s_delete_)
  extern void private_fl_type_int128s_delete(f_int128s_t *int128s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int128s_delete_)

/**
 * Private implementation for resizing the int128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int128s
 *   The int128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_int128s_t_resize().
 *
 * @see f_macro_int128s_t_resize()
 */
#if !defined(_di_fl_type_int128s_increase_) || !defined(_di_fl_type_int128s_increase_by_)
  extern f_return_status private_fl_type_int128s_resize(const f_array_length_t length, f_int128s_t *int128s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int128s_increase_) || !defined(_di_fl_type_int128s_increase_by_)

/**
 * Private implementation for deleting the int128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param int128ss
 *   The int128ss array to delete.
 */
#if !defined(_di_fl_type_int128ss_delete_)
  extern void private_fl_type_int128ss_delete(f_int128ss_t *int128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int128ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_int128ss_t_resize().
 *
 * @see f_macro_int128ss_t_resize()
 */
#if !defined(_di_fl_type_int128ss_increase_) || !defined(_di_fl_type_int128ss_increase_by_)
  extern f_return_status private_fl_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_int128ss_increase_) || !defined(_di_fl_type_int128ss_increase_by_)

/**
 * Private implementation for deleting the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint128s
 *   The uint128s array to delete.
 */
#if !defined(_di_fl_type_uint128s_delete_)
  extern void private_fl_type_uint128s_delete(f_uint128s_t *uint128s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint128s_delete_)

/**
 * Private implementation for resizing the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint128s
 *   The uint128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_uint128s_t_resize().
 *
 * @see f_macro_uint128s_t_resize()
 */
#if !defined(_di_fl_type_uint128s_increase_) || !defined(_di_fl_type_uint128s_increase_by_)
  extern f_return_status private_fl_type_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint128s_increase_) || !defined(_di_fl_type_uint128s_increase_by_)

/**
 * Private implementation for deleting the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param uint128ss
 *   The uint128ss array to delete.
 */
#if !defined(_di_fl_type_uint128ss_delete_)
  extern void private_fl_type_uint128ss_delete(f_uint128ss_t *uint128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint128ss_delete_)

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
 *
 *   Errors (with error bit) from: f_macro_uint128ss_t_resize().
 *
 * @see f_macro_uint128ss_t_resize()
 */
#if !defined(_di_fl_type_uint128ss_increase_) || !defined(_di_fl_type_uint128ss_increase_by_)
  extern f_return_status private_fl_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_type_uint128ss_increase_) || !defined(_di_fl_type_uint128ss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_type_h
