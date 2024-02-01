#include "test-fss.h"
#include "test-fss-embedded_list_object_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_embedded_list_object_read__parameter_checking(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_range_t found = f_range_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, &range, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, &range, &found, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, &range, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, 0, &found, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, 0, &found, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, 0, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }
}

void test__fl_fss_embedded_list_object_read__returns_data_not(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_range_t found = f_range_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_embedded_list_object_read(f_string_empty_s, &range, &found, &delimits, &state);

    assert_int_equal(state.status, F_data_not);
  }
}

void test__fl_fss_embedded_list_object_read__works(void **void_state) {

  {
    FILE *file_strings = data__file_open__named__all_read("strings", "embedded_list");
    FILE *file_objects = data__file_open__named__all_read("objects", "embedded_list");

    assert_non_null(file_strings);
    assert_non_null(file_objects);

    size_t max = 0;
    char *line_string = 0;
    char *line_object = 0;
    ssize_t result = 0;

    f_string_static_t buffer_string = f_string_static_t_initialize;

    f_state_t state = f_state_t_initialize;
    f_range_t range = f_range_t_initialize;
    f_range_t found = f_range_t_initialize;
    f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
    f_string_dynamic_t result_string = f_string_dynamic_t_initialize;
    f_string_dynamic_t delimit_string = f_string_dynamic_t_initialize;

    for (int line = 1;; ++line) {

      max = 255;

      result = getline(&line_string, &max, file_strings);
      if (result == -1) break;

      buffer_string.string = line_string;
      buffer_string.used = (f_number_unsigned_t) result;
      buffer_string.size = buffer_string.used;

      state.status = F_none;
      range.start = 0;
      range.stop = buffer_string.used - 1;
      found.start = 1;
      found.stop = 0;

      fl_fss_embedded_list_object_read(buffer_string, &range, &found, &delimits, &state);

      assert_true(state.status == F_fss_found_object || state.status == F_fss_found_object_not);

      if (state.status == F_fss_found_object) {
        max = 255;

        result = getline(&line_object, &max, file_objects);
        assert_return_code(result, 0);

        // The newline is copied by getline(), and so remove that newline before comparing.
        line_object[result - 1] = 0;

        if (found.start <= found.stop) {
          {
            const f_status_t status = f_string_dynamic_append(buffer_string, &delimit_string);
            assert_int_equal(status, F_okay);
          }

          state.status = F_none;

          f_fss_apply_delimit(delimits, &delimit_string, &state);
          assert_int_equal(state.status, F_okay);

          {
            const f_status_t status = f_string_dynamic_partial_append_nulless(delimit_string, found, &result_string);
            assert_true(status == F_okay || status == F_data_not_eos);
          }

          {
            const f_status_t status = f_string_dynamic_terminate_after(&result_string);
            assert_int_equal(status, F_okay);
          }

          assert_string_equal(result_string.string, line_object);
        }
        else {
          assert_int_equal(line_object[0], 0);
        }
      }

      if (line_string) free(line_string);
      if (line_object) free(line_object);
      if (result_string.string) free(result_string.string);
      if (delimit_string.string) free(delimit_string.string);
      if (delimits.array) free(delimits.array);

      line_string = 0;
      line_object = 0;
      result_string.string = 0;
      result_string.used = 0;
      result_string.size = 0;
      delimit_string.string = 0;
      delimit_string.used = 0;
      delimit_string.size = 0;
      delimits.array = 0;
      delimits.used = 0;
      delimits.size = 0;
    } // for

    if (file_strings) fclose(file_strings);
    if (file_objects) fclose(file_objects);

    if (delimits.array) free(delimits.array);
    if (line_string) free(line_string);
    if (line_object) free(line_object);
    if (result_string.string) free(result_string.string);
    if (delimit_string.string) free(delimit_string.string);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
