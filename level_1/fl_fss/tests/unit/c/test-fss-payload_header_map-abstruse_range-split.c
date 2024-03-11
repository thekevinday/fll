#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_range__works_split(void **void_state) {

  help_payload__test("abstruse_range", "split-abstruse_range", 0, test__fl_fss_payload_header_map__abstruse_range__split_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_range__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].key.used = 0;
  headers->array[0].value.is.a_range.start = 0;
  headers->array[0].value.is.a_range.stop = 0;
  headers->array[0].value.type = f_abstruse_range_e;

  f_range_t * const quantity = &headers->array[0].value.is.a_range;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used > 1) {
    f_number_signed_t number = atoll(contents.array[0].string);

    if (!number) {
      assert_int_equal(contents.array[0].string[0], '0');
    }

    quantity->start = number;

    number = atoll(contents.array[1].string);

    if (!number) {
      assert_int_equal(contents.array[1].string[0], '0');
    }

    quantity->stop = number;
  }
  else {
    quantity->start = 1;
    quantity->stop = 0;
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
