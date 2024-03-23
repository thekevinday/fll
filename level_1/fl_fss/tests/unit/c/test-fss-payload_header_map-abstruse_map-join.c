#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_map__works_join(void **void_state) {

  help_payload__test("abstruse_map", "join-abstruse_map", f_fss_payload_header_map_flag_join_map_e, test__fl_fss_payload_header_map__abstruse_map__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_map__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_map_e;
  headers->array[0].value.is.a_map.key.used = 0;
  headers->array[0].value.is.a_map.value.used = 0;
  headers->array[0].key.used = 0;

  f_string_map_t * const map = &headers->array[0].value.is.a_map;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    state->status = f_string_dynamic_append(contents.array[0], &map->key);
    assert_int_equal(state->status, F_okay);

    if (contents.used > 1) {
      state->status = f_string_dynamic_append(contents.array[1], &map->value);
      assert_int_equal(state->status, F_okay);
    }
  }
}

#ifdef __cplusplus
} // extern "C"
#endif