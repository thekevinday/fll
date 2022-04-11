#include "test-file.h"
#include "test-file-stream_open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_open__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stream_open(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_open__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_stream_open(f_string_empty_s, f_string_empty_s, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_open__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_open(f_string_empty_s, f_string_empty_s, &file);

    assert_int_equal(status, F_data_not);
  }

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_open(path, f_string_empty_s, &file);

    assert_int_equal(status, F_data_not);
  }

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_open(f_string_empty_s, path, &file);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stream_open__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stream_open();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
