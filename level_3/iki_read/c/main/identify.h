/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the identify functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_identify_h
#define _iki_read_identify_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process the arguments, associating replacements and wraps with a given vocabulary.
 *
 * This does not handle substitutions because substitutions must match both name and value (Object and Content).
 * This function does not know the value (Content).
 *
 * @param main
 *   The program and settings data.
 * @param replaces
 *   A map to the last matching replacment or a value of setting->data.vocabulary.used if there is no matching replacement.
 *   Must be an array of length setting->data.vocabulary.used.
 * @param wraps
 *   A map to the last matching wrap or a value of setting->data.vocabulary.used if there is no matching wrap.
 *   Must be an array of length setting->data.vocabulary.used.
 *
 * @return
 *   The matching setting->data.vocabulary index or if no match then setting->data.vocabulary.used.
 */
#ifndef _di_iki_read_identify_alteration_
  extern void iki_read_identify_alteration(iki_read_main_t * const main);
#endif // _di_iki_read_identify_alteration_

/**
 * Process the arguments, associating the last matching reassignment or substitution with a given vocabulary name and value (Object and Content).
 *
 * This function expects appropriate sanity checks are performed on the reassignments or substitutions array before calling.
 *
 * @param main
 *   The program and settings data.
 * @param name
 *   A range within setting->buffer representing the name (Object) to match.
 * @param value
 *   A range within setting->buffer representing the value (Content) to match.
 * @param triple
 *   The setting, such as setting->substitute, to update.
 *
 * @return
 *   The matched substitution.
 *   The value of the triple.used is returned on no match.
 */
#ifndef _di_iki_read_identify_substitution_
  extern f_array_length_t iki_read_identify_substitution(iki_read_main_t * const main, const f_string_range_t name, const f_string_range_t value, f_string_triples_t *triple);
#endif // _di_iki_read_identify_substitution_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_identify_h
