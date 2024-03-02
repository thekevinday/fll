/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fl_fss project.
 */
#ifndef _TEST__FL_fss_payload_header_map__abstruse_int32s_join_h
#define _TEST__FL_fss_payload_header_map__abstruse_int32s_join_h

/**
 * Test that the function works for abstruse_int32s type.
 *
 * @see fl_fss_payload_header_map()
 */
extern void test__fl_fss_payload_header_map__abstruse_int32s__works_join(void **state);

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
 */
void test__fl_fss_payload_header_map__abstruse_int32s__join_load_contents_at(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state);

#endif // _TEST__FL_fss_payload_header_map__abstruse_int32s_join_h
