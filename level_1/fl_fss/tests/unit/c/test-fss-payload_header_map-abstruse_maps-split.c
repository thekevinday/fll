#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_maps__works_split(void **void_state) {

  help_payload__test("abstruse_maps", "split-abstruse_maps", 0, test__fl_fss_payload_header_map__abstruse_maps__split_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_maps__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_maps_e;
  headers->array[0].value.is.a_maps.used = 0;
  headers->array[0].key.used = 0;

  f_string_maps_t * const maps = &headers->array[0].value.is.a_maps;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    state->status = f_memory_array_increase_by(contents.used, sizeof(f_string_map_t), (void **) &maps->array, &maps->used, &maps->size);
    assert_int_equal(state->status, F_okay);

    for (f_number_unsigned_t i = 0; i < contents.used; i += 2, ++maps->used) {

      maps->array[maps->used].key.used = 0;
      maps->array[maps->used].value.used = 0;

      state->status = f_string_dynamic_append(contents.array[i], &maps->array[maps->used].key);
      assert_int_equal(state->status, F_okay);

      if (i + 1 < contents.used) {
        state->status = f_string_dynamic_append(contents.array[i + 1], &maps->array[maps->used].value);
        assert_int_equal(state->status, F_okay);
      }
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
