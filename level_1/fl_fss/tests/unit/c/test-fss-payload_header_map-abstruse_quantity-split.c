#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_quantity__works_split(void **void_state) {

  help_payload__test("abstruse_quantity", "split-abstruse_quantity", 0, test__fl_fss_payload_header_map__abstruse_quantity__split_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_quantity__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].key.used = 0;
  headers->array[0].value.is.a_quantity.start = 0;
  headers->array[0].value.is.a_quantity.total = 0;
  headers->array[0].value.type = f_abstruse_quantity_e;

  f_quantity_t * const quantity = &headers->array[0].value.is.a_quantity;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  if (contents.used) {
    f_number_signed_t number = atoll(contents.array[0].string);

    if (!number) {
      assert_int_equal(contents.array[0].string[0], '0');
    }

    quantity->start = number;

    if (contents.used > 1) {
      number = atoll(contents.array[1].string);

      if (!number) {
        assert_int_equal(contents.array[1].string[0], '0');
      }

      quantity->total = number;
    }
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
