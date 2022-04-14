#include "test-file.h"
#include "test-file-descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_descriptor__fails(void **state) {

  {
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fileno, -1);

    const f_status_t status = f_file_descriptor(&file);

    assert_int_equal(F_status_set_fine(status), F_stream_not);
  }
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_descriptor__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_descriptor(0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_descriptor__works(void **state) {

  {
    const int id = 1;
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fileno, id);

    const f_status_t status = f_file_descriptor(&file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, id);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
