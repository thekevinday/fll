#include "test-fss.h"
#include "test-fss-extended_content_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_extended_content_read__parameter_checking(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t found = f_ranges_t_initialize;
  f_uint8s_t quotes = f_uint8s_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, &found, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, 0, &quotes, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, 0, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, &found, &quotes, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, &found, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, &found, &quotes, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, &found, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, 0, &quotes, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, 0, &quotes, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, 0, 0, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }
}

void test__fl_fss_extended_content_read__returns_data_not(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t found = f_ranges_t_initialize;
  f_uint8s_t quotes = f_uint8s_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, &found, 0, &delimits, &state);

    assert_int_equal(state.status, F_data_not);
  }

  {
    state.status = F_none;

    fl_fss_extended_content_read(f_string_empty_s, &range, &found, &quotes, &delimits, &state);

    assert_int_equal(state.status, F_data_not);
  }
}

void test__fl_fss_extended_content_read__works(void **void_state) {

  {
    // Note: These files are required to have the same number of lines and each line should probably be at max 255 characters.
    FILE *file_strings = data__file_open__named__all_read("strings", "extended");

    FILE *file_contents[] = {
      data__file_open__named_at__all_read("contents", "extended", 0),
      data__file_open__named_at__all_read("contents", "extended", 1),
      data__file_open__named_at__all_read("contents", "extended", 2),
      data__file_open__named_at__all_read("contents", "extended", 3),
      data__file_open__named_at__all_read("contents", "extended", 4),
      data__file_open__named_at__all_read("contents", "extended", 5),
      data__file_open__named_at__all_read("contents", "extended", 6),
      data__file_open__named_at__all_read("contents", "extended", 7),
    };

    assert_non_null(file_strings);
    assert_non_null(file_contents[0]);
    assert_non_null(file_contents[1]);
    assert_non_null(file_contents[2]);
    assert_non_null(file_contents[3]);
    assert_non_null(file_contents[4]);
    assert_non_null(file_contents[5]);
    assert_non_null(file_contents[6]);
    assert_non_null(file_contents[7]);

    size_t max = 0;
    char *line_string = 0;
    char *line_content[] = {
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
    };
    ssize_t result = 0;
    const uint8_t total_content = 8;

    f_string_static_t buffer_string = f_string_static_t_initialize;

    f_state_t state = f_state_t_initialize;
    f_range_t range = f_range_t_initialize;
    f_range_t found_object = f_range_t_initialize;
    f_ranges_t found = f_ranges_t_initialize;
    uint8_t quote = 0;
    f_uint8s_t quotes = f_uint8s_t_initialize;
    f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
    f_string_dynamic_t result_string = f_string_dynamic_t_initialize;
    f_string_dynamic_t delimit_string = f_string_dynamic_t_initialize;
    f_status_t status_object = F_okay;

    for (;;) {

      max = 255;

      result = getline(&line_string, &max, file_strings);
      if (result == -1) break;

      buffer_string.string = line_string;
      buffer_string.used = (f_number_unsigned_t) result;
      buffer_string.size = buffer_string.used;

      for (uint8_t i = 0; i < total_content; ++i) {

        max = 255;

        result = getline(&line_content[i], &max, file_contents[i]);
        assert_return_code(result, 0);

        // The newline is copied by getline(), and so remove that newline before comparing.
        line_content[i][result - 1] = 0;
      } // or

      state.status = F_none;
      range.start = 0;
      range.stop = buffer_string.used - 1;
      found_object.start = 1;
      found_object.stop = 0;

      fl_fss_extended_object_read(buffer_string, &range, &found_object, &quote, &delimits, &state);

      assert_true(state.status == F_fss_found_object || state.status == F_fss_found_object_content_not);

      status_object = state.status;
      state.status = F_none;

      fl_fss_extended_content_read(buffer_string, &range, &found, &quotes, &delimits, &state);

      if (status_object == F_fss_found_object) {
        assert_int_equal(state.status, F_fss_found_content);
      }
      else {
        assert_int_equal(state.status, F_data_not);
      }

      if (state.status == F_fss_found_content) {
        assert_true(found.used);
        assert_true(found.used <= (f_number_unsigned_t) total_content);

        {
          const f_status_t status = f_string_dynamic_append(buffer_string, &delimit_string);
          assert_int_equal(status, F_okay);
        }

        state.status = F_none;

        f_fss_apply_delimit(delimits, &delimit_string, &state);
        assert_int_equal(state.status, F_okay);

        {
          uint8_t i = 0;

          for (; i < found.used; ++i) {

            result_string.used = 0;

            {
              const f_status_t status = f_string_dynamic_partial_append_nulless(delimit_string, found.array[i], &result_string);
              assert_true(status == F_okay || status == F_data_not_eos);
            }

            {
              const f_status_t status = f_string_dynamic_terminate_after(&result_string);
              assert_int_equal(status, F_okay);
            }

            assert_string_equal(result_string.string, line_content[i]);
          } // for

          // All remaining positions in the file need to be a zero length string.
          for (; i < total_content; ++i) {
            assert_int_equal(line_content[i][0], 0);
          }
        }
      }
      else {
        assert_true(!found.used);
      }

      if (line_string) free(line_string);
      if (result_string.string) free(result_string.string);
      if (delimit_string.string) free(delimit_string.string);
      if (delimits.array) free(delimits.array);
      if (found.array) free(found.array);
      if (quotes.array) free(quotes.array);

      for (uint8_t i = 0; i < total_content; ++i) {

        if (line_content[i]) free(line_content[i]);

        line_content[i] = 0;
      } // for

      line_string = 0;
      result_string.string = 0;
      result_string.used = 0;
      result_string.size = 0;
      delimit_string.string = 0;
      delimit_string.used = 0;
      delimit_string.size = 0;
      delimits.array = 0;
      delimits.used = 0;
      delimits.size = 0;
      found.array = 0;
      found.used = 0;
      found.size = 0;
      quotes.array = 0;
      quotes.used = 0;
      quotes.size = 0;
    } // for

    for (uint8_t i = 0; i < total_content; ++i) {

      if (file_contents[i]) fclose(file_contents[i]);
      if (line_content[i]) free(line_content[i]);

      line_content[i] = 0;
    } // for

    if (file_strings) fclose(file_strings);

    if (delimits.array) free(delimits.array);
    if (found.array) free(found.array);
    if (quotes.array) free(quotes.array);
    if (line_string) free(line_string);
    if (result_string.string) free(result_string.string);
    if (delimit_string.string) free(delimit_string.string);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
