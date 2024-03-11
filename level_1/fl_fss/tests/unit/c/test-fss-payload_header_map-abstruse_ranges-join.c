#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_ranges__works_join(void **void_state) {

  help_payload__test("abstruse_ranges", "join-abstruse_ranges", f_fss_payload_header_map_flag_join_ranges_e, test__fl_fss_payload_header_map__abstruse_ranges__join_load_contents, 0);
}

void test__fl_fss_payload_header_map__abstruse_ranges__join_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  headers->array[0].key.used = 0;
  headers->array[0].value.is.a_ranges.used = 0;
  headers->array[0].value.type = f_abstruse_ranges_e;

  f_ranges_t * const quantitys = &headers->array[0].value.is.a_ranges;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  state->status = f_memory_array_increase_by(contents.used, sizeof(f_range_t), (void **) &quantitys->array, &quantitys->used, &quantitys->size);
  assert_int_equal(state->status, F_okay);

  f_number_signed_t number = 0;

  for (f_number_unsigned_t i = 0; i < contents.used; i += 2, ++quantitys->used) {

    if (i + 1 < contents.used) {
      number = atoll(contents.array[i].string);

      if (!number) {
        assert_int_equal(contents.array[i].string[0], '0');
      }

      quantitys->array[quantitys->used].start = number;
      quantitys->array[quantitys->used].stop = 0;

      number = atoll(contents.array[i + 1].string);

      if (!number) {
        assert_int_equal(contents.array[i + 1].string[0], '0');
      }

      quantitys->array[quantitys->used].stop = number;
    }
    else {
      quantitys->array[quantitys->used].start = 1;
      quantitys->array[quantitys->used].stop = 0;
    }
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
