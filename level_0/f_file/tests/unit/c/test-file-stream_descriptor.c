#include "test-file.h"
#include "test-file-stream_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_descriptor__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stream_descriptor(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_descriptor__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_stream_descriptor(f_string_empty_s, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_descriptor__returns_data_not(void **state) {

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_descriptor(f_string_empty_s, &file);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stream_descriptor__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stream_descriptor();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif