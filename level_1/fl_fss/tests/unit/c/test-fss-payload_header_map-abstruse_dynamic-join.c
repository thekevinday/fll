#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_dynamic__works_join(void **void_state) {

  help_payload__test("abstruse_dynamic", "join-abstruse_dynamic", 0, test__fl_fss_payload_header_map__abstruse_dynamic__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_dynamic__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  for (f_number_unsigned_t i = 0; i < contents.used; ++i, ++headers->used) {

    headers->array[headers->used].key.used = 0;

    state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
    assert_int_equal(state->status, F_okay);

    headers->array[headers->used].value.type = f_abstruse_dynamic_e;
    headers->array[headers->used].value.is.a_dynamic.used = 0;

    state->status = f_string_dynamic_append(contents.array[i], &headers->array[headers->used].value.is.a_dynamic);
    assert_int_equal(state->status, F_okay);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
