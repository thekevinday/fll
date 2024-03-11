#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void help_payload__test(const f_string_t context_variables, const f_string_t context_headers, const uint64_t flag, void (*load_contents)(const f_string_static_t object, const f_string_dynamics_t contents, f_abstruse_maps_t * const headers, f_state_t * const state, void * extra), void * extra) {

  // Note: Each line should probably be at max 255 characters.
  //       The payload begins with a digit on the first line representing the number of Content lines following the Object line.
  //       Following the digit is a single Object line.
  //       Following the Object line is a line for each Content designated by the first line (can be 0).
  //       Following this Content line (even if 0 lines) should be the end of the test file or the start of the next set for the next line in the headers file.
  FILE *file_variables = data__file_open__named("variables", "payload", context_variables);
  FILE *file_headers = 0;

  if (!file_variables) {
    printf("[  ERROR   ] --- Opening File: variables/payload-%s.txt returned NULL.\n", context_variables);
  }

  assert_non_null(file_variables);

  f_abstruse_maps_t headers = f_abstruse_maps_t_initialize;
  f_state_t state = f_state_t_initialize;
  fl_fss_payload_header_state_t data = fl_fss_payload_header_state_t_initialize;
  f_string_dynamic_t object = f_string_dynamic_t_initialize;
  f_string_dynamics_t contents = f_string_dynamics_t_initialize;
  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_string_maps_t destinations = f_string_maps_t_initialize;
  f_string_maps_t expects = f_string_maps_t_initialize;

  {
    state.status = F_none;
    state.data = &data;
    data.cache = &cache;
    data.flag = flag;

    for (uint16_t at = 0; ; ++at) {

      if (help__read_line_object(file_variables, &object)) break;
      if (help__read_line_contents__single(file_variables, &contents, F_true)) break;

      state.status = f_memory_array_increase(state.step_small, sizeof(f_abstruse_map_t), (void **) &headers.array, &headers.used, &headers.size);
      assert_true(F_status_is_error_not(state.status));

      load_contents(object, contents, &headers, &state, extra);

      if (object.string) free(object.string);

      object.string = 0;
      object.used = 0;
      object.size = 0;

      ++headers.used;

      file_headers = data__file_open__named_at("headers", "payload", context_headers, at);

      if (!file_headers) {
        printf("[  ERROR   ] --- Opening File: headers/payload-%s-%d.txt returned NULL.\n", context_headers, at);
      }

      assert_non_null(file_headers);

      help__read_line_object(file_headers, &object);

      for (;;) {
        state.status = f_memory_array_increase(state.step_small, sizeof(f_string_map_t), (void **) &expects.array, &expects.used, &expects.size);
        assert_true(F_status_is_error_not(state.status));

        if (help__read_line_expects__single(file_headers, object, &expects)) break;
      } // for

      fl_fss_payload_header_map(headers, &destinations, &state);

      if (state.status != F_okay || destinations.used != expects.used) {
        printf("[  ERROR   ] --- Failure mapping: headers/payload-%s-%d.txt.\n", context_headers, at);
      }

      assert_int_equal(state.status, F_okay);
      assert_int_equal(destinations.used, expects.used);

      for (f_number_unsigned_t i = 0; i < destinations.used; ++i) {

        if (destinations.array[i].key.used != expects.array[i].key.used || destinations.array[i].value.used != expects.array[i].value.used || strncmp(destinations.array[i].key.string, expects.array[i].key.string, expects.array[i].key.used) || strncmp(destinations.array[i].value.string, expects.array[i].value.string, expects.array[i].value.used)) {
          printf("[  ERROR   ] --- Match failure: [%lu] key[%lu]='%s', value[%lu]='%s' vs expected key[%lu]='%s', value[%lu]='%s'\n", i, destinations.array[i].key.used, destinations.array[i].key.string, destinations.array[i].value.used, destinations.array[i].value.string, expects.array[i].key.used, expects.array[i].key.string, expects.array[i].value.used, expects.array[i].value.string);
        }

        assert_string_equal(destinations.array[i].key.string, expects.array[i].key.string);
        assert_string_equal(destinations.array[i].value.string, expects.array[i].value.string);

        assert_int_equal(destinations.array[i].key.used, expects.array[i].key.used);
        assert_int_equal(destinations.array[i].value.used, expects.array[i].value.used);
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
