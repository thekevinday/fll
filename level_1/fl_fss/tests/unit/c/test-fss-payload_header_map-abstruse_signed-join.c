#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_signed__works_join(void **void_state) {

  help_payload__test("abstruse_signed", "join-abstruse_signed", f_fss_payload_header_map_flag_join_digits_e, test__fl_fss_payload_header_map__abstruse_signed__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_signed__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  for (f_number_unsigned_t i = 0; i < contents.used; ++i, ++headers->used) {

    const f_number_signed_t number = atoll(contents.array[i].string);

    if (!number) {
      assert_int_equal(contents.array[i].string[0], '0');
    }

    headers->array[headers->used].key.used = 0;

    state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
    assert_int_equal(state->status, F_okay);

    headers->array[headers->used].value.type = f_abstruse_signed_e;
    headers->array[headers->used].value.is.a_signed = number;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
