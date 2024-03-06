#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_dynamics__works_join(void **void_state) {

  help_payload__test("abstruse_dynamics", "join-abstruse_dynamics", f_fss_payload_header_map_flag_join_dynamics_e, test__fl_fss_payload_header_map__abstruse_dynamics__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_dynamics__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_dynamics_e;
  headers->array[0].value.is.a_dynamics.used = 0;
  headers->array[0].key.used = 0;

  f_string_dynamics_t * const dynamics = &headers->array[0].value.is.a_dynamics;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  state->status = f_memory_array_increase_by(contents.used, sizeof(f_string_dynamic_t), (void **) &dynamics->array, &dynamics->used, &dynamics->size);
  assert_int_equal(state->status, F_okay);

  for (f_number_unsigned_t i = 0; i < contents.used; ++i) {

    dynamics->array[i].used = 0;

    state->status = f_string_dynamic_append(contents.array[i], &dynamics->array[i]);
    assert_int_equal(state->status, F_okay);
  } // for

  dynamics->used = contents.used;
}

#ifdef __cplusplus
} // extern "C"
#endif
