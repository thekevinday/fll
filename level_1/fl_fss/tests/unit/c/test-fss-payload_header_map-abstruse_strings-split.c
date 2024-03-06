#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_strings__works_split(void **void_state) {

  f_string_t *strings = 0;

  help_payload__test("abstruse_strings", "split-abstruse_strings", 0, test__fl_fss_payload_header_map__abstruse_strings__split_load_contents, (void *) &strings);

  if (strings) free(strings);
}

void test__fl_fss_payload_header_map__abstruse_strings__split_load_contents(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra) {

  f_string_t **strings = (f_string_t **) extra;

  if (*strings) free(*strings);

  *strings = calloc(contents.used + 1, sizeof(f_string_t *));
  assert_int_not_equal(*strings, 0);

  headers->array[0].value.is.a_strings = *strings;
  headers->array[0].key.used = 0;
  headers->array[0].value.type = f_abstruse_strings_e;

  state->status = f_string_dynamic_append(object, &headers->array[headers->used].key);
  assert_int_equal(state->status, F_okay);

  for (f_number_unsigned_t i = 0; i < contents.used; ++i) {
    headers->array[0].value.is.a_strings[i] = contents.array[i].string;
  } // for

  headers->array[0].value.is.a_strings[contents.used] = 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
