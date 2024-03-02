/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Helper for the fss project tests.
 */
#ifndef _HELP__FL_fss_number_h
#define _HELP__FL_fss_number_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the unit test for a number.
 *
 * @param context_variables
 *   The context name of the variables file for data__file_open__named().
 * @param context_headers
 *   The context name of the headers file for data__file_open__named_at().
 * @param flag
 *   The payload header state data flag.
 * @param load_contents_at
 *   A callback to perform the type-specific content loading translation of the number.
 */
void help_number__test_payload(const f_string_t context_variables, const f_string_t context_headers, const uint64_t flag, void (*load_contents_at)(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state));

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _HELP__FL_fss_number_h
