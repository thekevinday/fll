/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fl_fss project.
 */
#ifndef _TEST__FL_fss_payload_header_map__abstruse_triples_split_h
#define _TEST__FL_fss_payload_header_map__abstruse_triples_split_h

/**
 * Test that the function works for abstruse_triples type.
 *
 * @see fl_fss_payload_header_maps()
 */
extern void test__fl_fss_payload_header_map__abstruse_triples__works_split(void **state);

/**
 * Callback to load the contents for the test.
 *
 * @param object
 *   The object parameter.
 * @param contents
 *   The contents parameter.
 * @param headers
 *   The headers parameter.
* @param state
 *   The state parameter.
 * @param extra
 *   (optional) The extra parameter.
 *   Set to NULL to not use.
 */
extern void test__fl_fss_payload_header_map__abstruse_triples__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra);

#endif // _TEST__FL_fss_payload_header_map__abstruse_triples_split_h
