#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_triples__works_split(void **void_state) {

  help_payload__test("abstruse_triples", "split-abstruse_triples", 0, test__fl_fss_payload_header_map__abstruse_triples__split_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_triples__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_triples_e;
  headers->array[0].value.is.a_triples.used = 0;
  headers->array[0].key.used = 0;

  f_string_triples_t * const triples = &headers->array[0].value.is.a_triples;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    state->status = f_memory_array_increase_by(contents.used, sizeof(f_string_triple_t), (void **) &triples->array, &triples->used, &triples->size);
    assert_int_equal(state->status, F_okay);

    for (f_number_unsigned_t i = 0; i < contents.used; i += 3, ++triples->used) {

      triples->array[triples->used].a.used = 0;
      triples->array[triples->used].b.used = 0;
      triples->array[triples->used].c.used = 0;

      state->status = f_string_dynamic_append(contents.array[i], &triples->array[triples->used].a);
      assert_int_equal(state->status, F_okay);

      if (i + 1 < contents.used) {
        state->status = f_string_dynamic_append(contents.array[i + 1], &triples->array[triples->used].b);
        assert_int_equal(state->status, F_okay);

        if (i + 2 < contents.used) {
          state->status = f_string_dynamic_append(contents.array[i + 2], &triples->array[triples->used].c);
          assert_int_equal(state->status, F_okay);
        }
      }
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
