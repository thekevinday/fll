#include "test-fss.h"
#include "test-fss-payload_header_map-abstruse_int16s.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__abstruse_int16s__works_combined(void **void_state) {

  // Note: Each line should probably be at max 255 characters.
  //       The payload begins with a digit on the first line representing the number of Content lines following the Object line.
  //       Following the digit is a single Object line.
  //       Following the Object line is a line for each Content designated by the first line (can be 0).
  //       Following this Content line (even if 0 lines) should be the end of the test file or the start of the next set for the next line in the headers file.
  FILE *file_variables = data__file_open__named("variables", "payload", "combined-abstruse_int16s");
  FILE *file_headers = 0;

  assert_non_null(file_variables);

  f_abstruse_maps_t headers = f_abstruse_maps_t_initialize;
  f_state_t state = f_state_t_initialize;
  f_fss_payload_header_state_t data = f_fss_payload_header_state_t_initialize;
  f_string_dynamic_t object = f_string_dynamic_t_initialize;
  f_string_dynamics_t contents = f_string_dynamics_t_initialize;
  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_string_maps_t destinations = f_string_maps_t_initialize;
  f_string_maps_t expects = f_string_maps_t_initialize;
  f_int16s_t *is_a = 0;

  {
    state.status = F_none;
    state.data = &data;
    data.cache = &cache;

    for (uint16_t at = 0; ; ++at) {

      if (help__read_line_object(file_variables, &object)) break;
      if (help__read_line_contents__single(file_variables, &contents)) break;

      state.status = f_memory_array_increase(state.step_small, sizeof(f_abstruse_map_t), (void **) &headers.array, &headers.used, &headers.size);
      assert_true(F_status_is_error_not(state.status));

      headers.array[0].key.used = 0;
      headers.array[0].value.is.a_i16s.used = 0;
      headers.array[0].value.type = f_abstruse_int16s_e;
      is_a = &headers.array[0].value.is.a_i16s;

      state.status = f_string_dynamic_append(object, &headers.array[headers.used].key);
      assert_int_equal(state.status, F_okay);

      state.status = f_memory_array_increase_by(contents.used, sizeof(f_number_signed_t), (void **) &is_a->array, &is_a->used, &is_a->size);
      assert_true(F_status_is_error_not(state.status));

      for (is_a->used = 0; is_a->used < contents.used; ) {

        const f_number_signed_t number = atoll(contents.array[is_a->used].string);

        if (!number) {
          assert_int_equal(contents.array[is_a->used].string[0], '0');
        }

        is_a->array[is_a->used++] = number;
      } // for

      if (object.string) free(object.string);

      object.string = 0;
      object.used = 0;
      object.size = 0;

      ++headers.used;

      file_headers = data__file_open__named_at("headers", "payload", "combined-abstruse_int16s", at);
      assert_non_null(file_headers);

      help__read_line_object(file_headers, &object);

      for (;;) {
        state.status = f_memory_array_increase(state.step_small, sizeof(f_string_map_t), (void **) &expects.array, &expects.used, &expects.size);
        assert_true(F_status_is_error_not(state.status));

        if (help__read_line_expects__single(file_headers, object, &expects)) break;
      } // for

      fl_fss_payload_header_map(headers, &destinations, &state);
      assert_int_equal(state.status, F_okay);
      assert_int_equal(destinations.used, expects.used);

      for (f_number_unsigned_t i = 0; i < destinations.used; ++i) {

        assert_int_equal(destinations.array[i].key.used, expects.array[i].key.used);
        assert_int_equal(destinations.array[i].value.used, expects.array[i].value.used);

        assert_string_equal(destinations.array[i].key.string, expects.array[i].key.string);
        assert_string_equal(destinations.array[i].value.string, expects.array[i].value.string);
      } // for

      if (object.string) free(object.string);
      if (cache.string) free(cache.string);
      if (file_headers) fclose(file_headers);

      f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &contents.array, &contents.used, &contents.size, &f_string_dynamics_delete_callback);
      f_memory_arrays_resize(0, sizeof(f_abstruse_map_t), (void **) &headers.array, &headers.used, &headers.size, &f_abstruse_maps_delete_callback);
      f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &destinations.array, &destinations.used, &destinations.size, &f_string_maps_delete_callback);
      f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &expects.array, &expects.used, &expects.size, &f_string_maps_delete_callback);

      file_headers = 0;

      object.string = 0;
      object.used = 0;
      object.size = 0;

      cache.string = 0;
      cache.used = 0;
      cache.size = 0;

      contents.array = 0;
      contents.used = 0;
      contents.size = 0;

      headers.array = 0;
      headers.used = 0;
      headers.size = 0;

      destinations.array = 0;
      destinations.used = 0;
      destinations.size = 0;

      expects.array = 0;
      expects.used = 0;
      expects.size = 0;
    } // for
  }

  if (file_variables) fclose(file_variables);
  if (file_headers) fclose(file_headers);

  if (object.string) free(object.string);
  if (cache.string) free(cache.string);

  f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &contents.array, &contents.used, &contents.size, &f_string_dynamics_delete_callback);
  f_memory_arrays_resize(0, sizeof(f_abstruse_map_t), (void **) &headers.array, &headers.used, &headers.size, &f_abstruse_maps_delete_callback);
  f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &destinations.array, &destinations.used, &destinations.size, &f_string_maps_delete_callback);
  f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &expects.array, &expects.used, &expects.size, &f_string_maps_delete_callback);
}

#ifdef __cplusplus
} // extern "C"
#endif
