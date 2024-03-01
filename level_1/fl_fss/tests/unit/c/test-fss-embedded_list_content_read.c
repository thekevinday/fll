#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_embedded_list_content_read__parameter_checking(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_fss_nest_t found = f_fss_nest_t_initialize;
  f_ranges_t comments = f_ranges_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, &range, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, &range, &found, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, &range, 0, &delimits, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, &range, 0, 0, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, &found, &delimits, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, &found, 0, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, &found, &delimits, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, &found, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, &found, 0, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, 0, &delimits, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, 0, &delimits, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, 0, 0, 0, &comments, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }
}

void test__fl_fss_embedded_list_content_read__returns_data_not(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_fss_nest_t found = f_fss_nest_t_initialize;
  f_ranges_t comments = f_ranges_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_embedded_list_content_read(f_string_empty_s, &range, &found, &delimits, &comments, &state);

    assert_int_equal(state.status, F_data_not);
  }
}

void test__fl_fss_embedded_list_content_read__works(void **void_state) {

  {
    // Note: These files are required to have the same number of lines and each line should probably be at max 255 characters.
    FILE *file_strings = data__file_open__named("strings", "embedded_list", "all_read");

    FILE *file_contents[] = {
      data__file_open__named_at("contents", "embedded_list", "all_read", 0),
      data__file_open__named_at("contents", "embedded_list", "all_read", 1),
      data__file_open__named_at("contents", "embedded_list", "all_read", 2),
      data__file_open__named_at("contents", "embedded_list", "all_read", 3),
      data__file_open__named_at("contents", "embedded_list", "all_read", 4),
      data__file_open__named_at("contents", "embedded_list", "all_read", 5),
      data__file_open__named_at("contents", "embedded_list", "all_read", 6),
      data__file_open__named_at("contents", "embedded_list", "all_read", 7),
      data__file_open__named_at("contents", "embedded_list", "all_read", 8),
      data__file_open__named_at("contents", "embedded_list", "all_read", 9),
      data__file_open__named_at("contents", "embedded_list", "all_read", 10),
      data__file_open__named_at("contents", "embedded_list", "all_read", 11),
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
    assert_non_null(file_contents[8]);
    assert_non_null(file_contents[9]);
    assert_non_null(file_contents[10]);
    assert_non_null(file_contents[11]);

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
      0,
      0,
      0,
      0,
    };
    ssize_t result = 0;
    const uint8_t total_content = 12;

    f_string_static_t buffer_string = f_string_static_t_initialize;

    f_state_t state = f_state_t_initialize;
    f_range_t range = f_range_t_initialize;
    f_range_t found_object = f_range_t_initialize;
    f_fss_nest_t found = f_fss_nest_t_initialize;
    f_ranges_t comments = f_ranges_t_initialize;
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

        // The newline is copied by getline(), and so remove that newline before comparing.
        if (result > 0) {
          line_content[i][result - 1] = 0;
        }
        else {
          line_content[i][0] = 0;
        }
      } // or

      state.status = F_none;
      range.start = 0;
      range.stop = buffer_string.used - 1;
      found_object.start = 1;
      found_object.stop = 0;

      fl_fss_embedded_list_object_read(buffer_string, &range, &found_object, &delimits, &state);

      assert_true(state.status == F_fss_found_object || state.status == F_fss_found_object_not);

      status_object = state.status;
      state.status = F_none;

      if (status_object == F_fss_found_object) {
        fl_fss_embedded_list_content_read(buffer_string, &range, &found, &delimits, &comments, &state);

        assert_true(state.status == F_fss_found_content || state.status == F_data_not);

        if (state.status == F_fss_found_content) {
          // @todo
        }
        else {
          assert_true(!found.used);
        }
      }

      if (line_string) free(line_string);
      if (result_string.string) free(result_string.string);
      if (delimit_string.string) free(delimit_string.string);
      if (delimits.array) free(delimits.array);
      if (comments.array) free(comments.array);
      if (quotes.array) free(quotes.array);

      f_fss_nest_delete(&found);

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
      found.depth = 0;
      found.used = 0;
      found.size = 0;
      comments.array = 0;
      comments.used = 0;
      comments.size = 0;
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
    if (comments.array) free(comments.array);
    if (quotes.array) free(quotes.array);
    if (line_string) free(line_string);
    if (result_string.string) free(result_string.string);
    if (delimit_string.string) free(delimit_string.string);

    f_fss_nest_delete(&found);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
