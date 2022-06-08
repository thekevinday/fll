#include "test-file.h"
#include "test-file-stream_read_until.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_read_until__fails(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_feof_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_fread_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_file_stream_read_until(file, 1, &buffer);

    assert_int_equal(status, F_status_set_error(F_file_read));
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_stream_read_until__parameter_checking(void **state) {

  f_file_t file = f_file_t_initialize;

  {
    const f_status_t status = f_file_stream_read_until(file, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  file.size_read = 0;

  {
    const f_status_t status = f_file_stream_read_until(file, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_dynamic_t string = f_string_dynamic_t_initialize;

    const f_status_t status = f_file_stream_read_until(file, 0, &string);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_read_until__returns_file_closed(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  file.size_read = 1;

  {
    const f_status_t status = f_file_stream_read_until(file, 0, &buffer);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_stream_read_until__works(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_feof_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_fread_unlocked, file.size_read);
    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_feof_unlocked, false);

    const f_status_t status = f_file_stream_read_until(file, 1, &buffer);

    assert_int_equal(status, F_none_stop);
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
