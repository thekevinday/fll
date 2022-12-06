/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_fss_h
#define _PRIVATE_F_fss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param items
 *   The items to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_item_t_adjust().
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see macro_f_fss_item_t_adjust()
 *
 * @see f_fss_items_adjust()
 * @see f_fss_items_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)
  extern f_status_t private_f_fss_items_adjust(const f_array_length_t length, f_fss_items_t * const items) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param items
 *   The items to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_item_t_resize().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see macro_f_fss_item_t_resize()
 *
 * @see f_fss_items_decrease_by()
 * @see f_fss_items_increase()
 * @see f_fss_items_increase_by()
 * @see f_fss_items_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)
  extern f_status_t private_f_fss_items_resize(const f_array_length_t length, f_fss_items_t * const items) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param named
 *   The named to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_string_ranges_t_adjust().
 *   Errors (with error bit) from: macro_f_string_rangess_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8ss_t_adjust().
 *
 * @see macro_f_string_ranges_t_adjust()
 * @see macro_f_string_rangess_t_adjust()
 * @see macro_f_uint8ss_t_adjust()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  extern f_status_t private_f_fss_named_adjust(const f_array_length_t length, f_fss_named_t * const named) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param named
 *   The named to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_string_ranges_t_resize().
 *   Errors (with error bit) from: macro_f_string_rangess_t_resize().
 *   Errors (with error bit) from: macro_f_uint8ss_t_resize().
 *
 * @see macro_f_string_ranges_t_resize()
 * @see macro_f_string_rangess_t_resize()
 * @see macro_f_uint8ss_t_resize()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_incease()
 * @see f_fss_nameds_incease_by()
 * @see f_fss_nameds_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_named_resize(const f_array_length_t length, f_fss_named_t * const named) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: private_f_fss_named_adjust().
 *
 * @see private_f_fss_named_adjust()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  extern f_status_t private_f_fss_nameds_adjust(const f_array_length_t length, f_fss_nameds_t * const nameds) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: private_f_fss_named_resize().
 *
 * @see private_f_fss_named_resize()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_increase()
 * @see f_fss_nameds_increase_by()
 * @see f_fss_nameds_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_nameds_resize(const f_array_length_t length, f_fss_nameds_t * const nameds) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: macro_f_fss_nest_t_adjust().
 *
 * @see macro_f_fss_nest_t_adjust()
 *
 * @see f_fss_nest_adjust()
 * @see f_fss_nest_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)
  extern f_status_t private_f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t * const nest) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: macro_f_fss_nest_t_resize().
 *
 * @see macro_f_fss_nest_t_resize()
 *
 * @see f_fss_nest_decrease_by()
 * @see f_fss_nest_increase()
 * @see f_fss_nest_increase_by()
 * @see f_fss_nest_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)
  extern f_status_t private_f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t * const nest) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: macro_f_fss_nest_t_adjust().
 *
 * @see macro_f_fss_nest_t_adjust()
 *
 * @see f_fss_nests_adjust()
 * @see f_fss_nests_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)
  extern f_status_t private_f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t * const nests) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: macro_f_fss_nest_t_resize().
 *
 * @see macro_f_fss_nest_t_resize()
 *
 * @see f_fss_nests_decrease_by()
 * @see f_fss_nests_increase()
 * @see f_fss_nests_increase_by()
 * @see f_fss_nests_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  extern f_status_t private_f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t * const nests) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set
 *   The set to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_adjust().
 *   Errors (with error bit) from: macro_f_fss_objects_t_adjust().
 *
 * @see macro_f_fss_contents_t_adjust()
 * @see macro_f_fss_objects_t_adjust()
 *
 * @see f_fss_set_adjust()
 * @see f_fss_set_decimate_by()
 */
#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)
  extern f_status_t private_f_fss_set_adjust(const f_array_length_t length, f_fss_set_t * const set) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set
 *   The set to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_resize().
 *   Errors (with error bit) from: macro_f_fss_objects_t_resize().
 *
 * @see macro_f_fss_contents_t_resize()
 * @see macro_f_fss_objects_t_resize()
 *
 * @see f_fss_set_decrease_by()
 * @see f_fss_set_increase()
 * @see f_fss_set_increase_by()
 * @see f_fss_set_resize()
 */
#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)
  extern f_status_t private_f_fss_set_resize(const f_array_length_t length, f_fss_set_t * const set) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quote
 *   The set_quote to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_adjust().
 *   Errors (with error bit) from: macro_f_fss_objects_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8s_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8ss_t_adjust().
 *
 * @see macro_f_fss_contents_t_adjust()
 * @see macro_f_fss_objects_t_adjust()
 * @see macro_f_uint8s_t_adjust()
 * @see macro_f_uint8ss_t_adjust()
 *
 * @see f_fss_set_quote_adjust()
 * @see f_fss_set_quote_decimate_by()
 */
#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)
  extern f_status_t private_f_fss_set_quote_adjust(const f_array_length_t length, f_fss_set_quote_t * const set_quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quote
 *   The set_quote to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_resize().
 *   Errors (with error bit) from: macro_f_fss_objects_t_resize().
 *   Errors (with error bit) from: macro_f_uint8s_t_resize().
 *   Errors (with error bit) from: macro_f_uint8ss_t_resize().
 *
 * @see macro_f_fss_contents_t_resize()
 * @see macro_f_fss_objects_t_resize()
 * @see macro_f_uint8s_t_resize()
 * @see macro_f_uint8ss_t_resize()
 *
 * @see f_fss_set_quote_decrease_by()
 * @see f_fss_set_quote_increase()
 * @see f_fss_set_quote_increase_by()
 * @see f_fss_set_quote_resize()
 */
#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  extern f_status_t private_f_fss_set_quote_resize(const f_array_length_t length, f_fss_set_quote_t * const set_quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quotes
 *   The set_quotes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_adjust().
 *   Errors (with error bit) from: macro_f_fss_objects_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8s_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8ss_t_adjust().
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see macro_f_fss_contents_t_adjust()
 * @see macro_f_fss_objects_t_adjust()
 * @see macro_f_uint8s_t_adjust()
 * @see macro_f_uint8ss_t_adjust()
 *
 * @see f_fss_set_quotes_adjust()
 * @see f_fss_set_quotes_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)
  extern f_status_t private_f_fss_set_quotes_adjust(const f_array_length_t length, f_fss_set_quotes_t * const set_quotes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quotes
 *   The set_quotes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_resize().
 *   Errors (with error bit) from: macro_f_fss_objects_t_resize().
 *   Errors (with error bit) from: macro_f_uint8s_t_resize().
 *   Errors (with error bit) from: macro_f_uint8ss_t_resize().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see macro_f_fss_contents_t_resize()
 * @see macro_f_fss_objects_t_resize()
 * @see macro_f_uint8s_t_resize()
 * @see macro_f_uint8ss_t_resize()
 *
 * @see f_fss_set_quotes_decrease_by()
 * @see f_fss_set_quotes_increase()
 * @see f_fss_set_quotes_increase_by()
 * @see f_fss_set_quotes_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)
  extern f_status_t private_f_fss_set_quotes_resize(const f_array_length_t length, f_fss_set_quotes_t * const set_quotes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_adjust().
 *   Errors (with error bit) from: macro_f_fss_objects_t_adjust().
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see macro_f_fss_contents_t_adjust()
 * @see macro_f_fss_objects_t_adjust()
 *
 * @see f_fss_sets_adjust()
 * @see f_fss_sets_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)
  extern f_status_t private_f_fss_sets_adjust(const f_array_length_t length, f_fss_sets_t * const sets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_fss_contents_t_resize().
 *   Errors (with error bit) from: macro_f_fss_objects_t_resize().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see macro_f_fss_contents_t_resize()
 * @see macro_f_fss_objects_t_resize()
 *
 * @see f_fss_sets_decrease_by()
 * @see f_fss_sets_increase()
 * @see f_fss_sets_increase_by()
 * @see f_fss_sets_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)
  extern f_status_t private_f_fss_sets_resize(const f_array_length_t length, f_fss_sets_t * const sets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_h
