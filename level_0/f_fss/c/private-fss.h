/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * @param item
 *   The item to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_fss_nest_t_destroy().
 *
 * @see f_macro_fss_nest_t_destroy()
 *
 * @see f_fss_item_adjust()
 * @see f_fss_item_decimate_by()
 * @see f_fss_item_destroy()
 */
#if !defined(_di_f_fss_item_adjust_) || !defined(_di_f_fss_item_decimate_by_) || !defined(_di_f_fss_item_destroy_)
  extern f_status_t private_f_fss_item_adjust(const f_array_length_t length, f_fss_item_t *item) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_item_adjust_) || !defined(_di_f_fss_item_decimate_by_) || !defined(_di_f_fss_item_destroy_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param item
 *   The item to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: private_f_fss_nest_delete().
 *
 * @see private_f_fss_nest_delete()
 *
 * @see f_fss_item_decrease_by()
 * @see f_fss_item_delete()
 * @see f_fss_item_increase()
 * @see f_fss_item_increase_by()
 * @see f_fss_item_resize()
 */
#if !defined(_di_f_fss_item_decrease_by_) || !defined(_di_f_fss_item_delete_) || !defined(_di_f_fss_item_increase_) || !defined(_di_f_fss_item_increase_by_) || !defined(_di_f_fss_item_resize_)
  extern f_status_t private_f_fss_item_resize(const f_array_length_t length, f_fss_item_t *item) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_item_decrease_by_) || !defined(_di_f_fss_item_delete_) || !defined(_di_f_fss_item_increase_) || !defined(_di_f_fss_item_increase_by_) || !defined(_di_f_fss_item_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_nest_t_destroy().
 *
 * @see f_macro_fss_nest_t_destroy()
 *
 * @see f_fss_items_adjust()
 * @see f_fss_items_decimate_by()
 * @see f_fss_items_destroy()
 */
#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_items_destroy_)
  extern f_status_t private_f_fss_items_adjust(const f_array_length_t length, f_fss_items_t *items) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_items_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_nest_delete().
 *
 * @see private_f_fss_nest_delete()
 *
 * @see f_fss_items_decrease_by()
 * @see f_fss_items_delete()
 * @see f_fss_items_increase()
 * @see f_fss_items_increase_by()
 * @see f_fss_items_resize()
 */
#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_delete_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)
  extern f_status_t private_f_fss_items_resize(const f_array_length_t length, f_fss_items_t *items) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_delete_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)

/**
 * Private implementation for destroying.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param named
 *   The named to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_ranges_t_destroy().
 *   Errors (with error bit) from: f_macro_string_rangess_t_destroy().
 *   Errors (with error bit) from: f_macro_uint8ss_t_destroy().
 *
 * @see f_macro_string_ranges_t_destroy()
 * @see f_macro_string_rangess_t_destroy()
 * @see f_macro_uint8ss_t_destroy()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  extern f_status_t private_f_fss_named_destroy(f_fss_named_t *named) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

/**
 * Private implementation for deleting.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param named
 *   The named to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_ranges_t_delete().
 *   Errors (with error bit) from: f_macro_string_rangess_t_delete().
 *   Errors (with error bit) from: f_macro_uint8ss_t_delete().
 *
 * @see f_macro_string_ranges_t_delete()
 * @see f_macro_string_rangess_t_delete()
 * @see f_macro_uint8ss_t_delete()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_named_delete(f_fss_named_t *named) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_named_t_destroy().
 *
 * @see f_macro_fss_named_t_destroy()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 * @see f_fss_nameds_destroy()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_) || !defined(_di_f_fss_nameds_destroy_)
  extern f_status_t private_f_fss_nameds_adjust(const f_array_length_t length, f_fss_nameds_t *nameds) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_) || !defined(_di_f_fss_nameds_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_named_delete().
 *
 * @see private_f_fss_named_delete()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_delete()
 * @see f_fss_nameds_increase()
 * @see f_fss_nameds_increase_by()
 * @see f_fss_nameds_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_nameds_resize(const f_array_length_t length, f_fss_nameds_t *nameds) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_nest_t_destroy().
 *
 * @see f_macro_fss_nest_t_destroy()
 *
 * @see f_fss_nest_adjust()
 * @see f_fss_nest_decimate_by()
 * @see f_fss_nest_destroy()
 */
#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_) || !defined(_di_f_fss_nest_destroy_)
  extern f_status_t private_f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t *nest) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_) || !defined(_di_f_fss_nest_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_nest_delete().
 *
 * @see private_f_fss_nest_delete()
 *
 * @see f_fss_nest_decrease_by()
 * @see f_fss_nest_delete()
 * @see f_fss_nest_increase()
 * @see f_fss_nest_increase_by()
 * @see f_fss_nest_resize()
 */
#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_delete_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)
  extern f_status_t private_f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t *nest) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_delete_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_nest_t_destroy().
 *
 * @see f_macro_fss_nest_t_destroy()
 *
 * @see f_fss_nests_adjust()
 * @see f_fss_nests_decimate_by()
 * @see f_fss_nests_destroy()
 */
#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_) || !defined(_di_f_fss_nests_destroy_)
  extern f_status_t private_f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t *nests) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_) || !defined(_di_f_fss_nests_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_nest_delete().
 *
 * @see private_f_fss_nest_delete()
 *
 * @see f_fss_nests_decrease_by()
 * @see f_fss_nests_delete()
 * @see f_fss_nests_increase()
 * @see f_fss_nests_increase_by()
 * @see f_fss_nests_resize()
 */
#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_delete_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  extern f_status_t private_f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t *nests) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_delete_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_set_t_destroy().
 *
 * @see f_macro_fss_set_t_destroy()
 *
 * @see f_fss_set_adjust()
 * @see f_fss_set_decimate_by()
 * @see f_fss_set_destroy()
 */
#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_) || !defined(_di_f_fss_set_destroy_)
  extern f_status_t private_f_fss_set_adjust(const f_array_length_t length, f_fss_set_t *set) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_) || !defined(_di_f_fss_set_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_set_delete().
 *
 * @see private_f_fss_set_delete()
 *
 * @see f_fss_set_decrease_by()
 * @see f_fss_set_delete()
 * @see f_fss_set_increase()
 * @see f_fss_set_increase_by()
 * @see f_fss_set_resize()
 */
#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_delete_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)
  extern f_status_t private_f_fss_set_resize(const f_array_length_t length, f_fss_set_t *set) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_delete_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_set_quote_t_destroy().
 *
 * @see f_macro_fss_set_quote_t_destroy()
 *
 * @see f_fss_set_quote_adjust()
 * @see f_fss_set_quote_decimate_by()
 * @see f_fss_set_quote_destroy()
 */
#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_) || !defined(_di_f_fss_set_quote_destroy_)
  extern f_status_t private_f_fss_set_quote_adjust(const f_array_length_t length, f_fss_set_quote_t *set_quote) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_) || !defined(_di_f_fss_set_quote_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_set_quote_delete().
 *
 * @see private_f_fss_set_quote_delete()
 *
 * @see f_fss_set_quote_decrease_by()
 * @see f_fss_set_quote_delete()
 * @see f_fss_set_quote_increase()
 * @see f_fss_set_quote_increase_by()
 * @see f_fss_set_quote_resize()
 */
#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_delete_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  extern f_status_t private_f_fss_set_quote_resize(const f_array_length_t length, f_fss_set_quote_t *set_quote) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_delete_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_set_quote_t_destroy().
 *
 * @see f_macro_fss_set_quote_t_destroy()
 *
 * @see f_fss_set_quotes_adjust()
 * @see f_fss_set_quotes_decimate_by()
 * @see f_fss_set_quotes_destroy()
 */
#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_) || !defined(_di_f_fss_set_quotes_destroy_)
  extern f_status_t private_f_fss_set_quotes_adjust(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_) || !defined(_di_f_fss_set_quotes_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_set_quote_delete().
 *
 * @see private_f_fss_set_quote_delete()
 *
 * @see f_fss_set_quotes_decrease_by()
 * @see f_fss_set_quotes_delete()
 * @see f_fss_set_quotes_increase()
 * @see f_fss_set_quotes_increase_by()
 * @see f_fss_set_quotes_resize()
 */
#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_delete_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)
  extern f_status_t private_f_fss_set_quotes_resize(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_delete_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)

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
 *   Errors (with error bit) from: f_macro_fss_set_t_destroy().
 *
 * @see f_macro_fss_set_t_destroy()
 *
 * @see f_fss_sets_adjust()
 * @see f_fss_sets_decimate_by()
 * @see f_fss_sets_destroy()
 */
#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_) || !defined(_di_f_fss_sets_destroy_)
  extern f_status_t private_f_fss_sets_adjust(const f_array_length_t length, f_fss_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_) || !defined(_di_f_fss_sets_destroy_)

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
 *   Errors (with error bit) from: private_f_fss_set_delete().
 *
 * @see private_f_fss_set_delete()
 *
 * @see f_fss_sets_decrease_by()
 * @see f_fss_sets_delete()
 * @see f_fss_sets_increase()
 * @see f_fss_sets_increase_by()
 * @see f_fss_sets_resize()
 */
#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_delete_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)
  extern f_status_t private_f_fss_sets_resize(const f_array_length_t length, f_fss_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_delete_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_h
