#include "test-file.h"
#include "test-file-stream_write_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write_range__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stream_write_range(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_write_range__parameter_checking(void **state) {

    f_file_t file = f_file_t_initialize;
    file.size_write = 0;

    const f_string_range_t range = f_string_range_t_initialize;

    {
      const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_write_range__returns_file_closed(void **state) {

  const f_file_t file = f_file_t_initialize;
  const f_string_range_t range = f_string_range_t_initialize;

  {
    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }
}

void test__f_file_stream_write_range__returns_data_not(void **state) {

  f_file_t file = f_file_t_initialize;
  FILE file_stucture;
  file.stream = &file_stucture;

  {
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_string_range_t range = f_string_range_t_initialize;
    const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

    const f_status_t status = f_file_stream_write_range(file, path, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize(0, 0);

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_string_range_t range = f_string_range_t_initialize;

    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    const f_string_range_t range = f_string_range_t_initialize;
    const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_range(file, path, range, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize(0, 0);

    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write_range__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stream_write_range();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
