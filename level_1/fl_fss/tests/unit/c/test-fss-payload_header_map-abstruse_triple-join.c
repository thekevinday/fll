#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_triple__works_join(void **void_state) {

  help_payload__test("abstruse_triple", "join-abstruse_triple", f_fss_payload_header_map_flag_join_triple_e, test__fl_fss_payload_header_map__abstruse_triple__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_triple__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].value.type = f_abstruse_triple_e;
  headers->array[0].value.is.a_triple.a.used = 0;
  headers->array[0].value.is.a_triple.b.used = 0;
  headers->array[0].value.is.a_triple.c.used = 0;
  headers->array[0].key.used = 0;

  f_string_triple_t * const triple = &headers->array[0].value.is.a_triple;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    state->status = f_string_dynamic_append(contents.array[0], &triple->a);
    assert_int_equal(state->status, F_okay);

    if (contents.used > 1) {
      state->status = f_string_dynamic_append(contents.array[1], &triple->b);
      assert_int_equal(state->status, F_okay);

      if (contents.used > 2) {
        state->status = f_string_dynamic_append(contents.array[2], &triple->c);
        assert_int_equal(state->status, F_okay);
      }
    }
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
