#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_map_multi__works_split(void **void_state) {

  help_payload__test("abstruse_map_multi", "split-abstruse_map_multi", 0, test__fl_fss_payload_header_map__abstruse_map_multi__split_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_map_multi__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_map_multi_e;
  headers->array[0].value.is.a_map_multi.key.used = 0;
  headers->array[0].value.is.a_map_multi.value.used = 0;
  headers->array[0].key.used = 0;

  f_string_map_multi_t * const map = &headers->array[0].value.is.a_map_multi;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    state->status = f_string_dynamic_append(contents.array[0], &map->key);
    assert_int_equal(state->status, F_okay);

    if (contents.used > 1) {
      state->status = f_memory_array_increase(state->step_small, sizeof(f_string_dynamic_t), (void **) &map->value.array, &map->value.used, &map->value.size);
      assert_int_equal(state->status, F_okay);

      map->value.array[map->value.used].used = 0;

      state->status = f_string_dynamic_append(contents.array[1], &map->value.array[map->value.used]);
      assert_int_equal(state->status, F_okay);

      ++map->value.used;
    }
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
