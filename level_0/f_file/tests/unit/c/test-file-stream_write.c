#include "test-file.h"
#include "test-file-stream_write.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stream_write(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_write__parameter_checking(void **state) {

    f_file_t file = f_file_t_initialize;
    file.size_write = 0;

    {
      const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_write__returns_file_closed(void **state) {

  const f_file_t file = f_file_t_initialize;

  {
    const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }
}

void test__f_file_stream_write__returns_data_not(void **state) {

  f_file_t file = f_file_t_initialize;
  FILE file_stucture;
  file.stream = &file_stucture;

  {
    const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write(file, f_string_empty_s, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stream_write();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
