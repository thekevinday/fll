/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_iki_data_h
#define _PRIVATE_F_iki_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for appending the iki_data array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source iki_datas to append.
 * @param destination
 *   The iki_datas array the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_append().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_ranges_append_all().
 *
 * @see f_memory_array_append()
 * @see f_memory_array_increase_by()
 * @see f_ranges_append_all()
 *
 * @see f_iki_datass_append()
 * @see f_iki_datass_append_all()
 */
#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)
  extern f_status_t private_f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_iki_data_h
