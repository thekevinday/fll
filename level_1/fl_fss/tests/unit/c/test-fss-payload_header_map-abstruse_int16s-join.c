#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_int16s__works_join(void **void_state) {

  help_payload__test("abstruse_int16s", "join-abstruse_int16s", f_fss_payload_header_map_flag_join_digits_e, test__fl_fss_payload_header_map__abstruse_int16s__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_int16s__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  f_int16s_t * const is_a = &headers->array[0].value.is.a_i16s;

  headers->array[0].key.used = 0;
  headers->array[0].value.is.a_i16s.used = 0;
  headers->array[0].value.type = f_abstruse_int16s_e;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  state->status = f_memory_array_increase_by(contents.used, sizeof(f_number_signed_t), (void **) &is_a->array, &is_a->used, &is_a->size);
  assert_true(F_status_is_error_not(state->status));

  for (is_a->used = 0; is_a->used < contents.used; ) {

    const f_number_signed_t number = atoll(contents.array[is_a->used].string);

    if (!number) {
      assert_int_equal(contents.array[is_a->used].string[0], '0');
    }

    is_a->array[is_a->used++] = number;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif