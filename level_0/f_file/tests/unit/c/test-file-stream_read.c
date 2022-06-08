#include "test-file.h"
#include "test-file-stream_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_read__fails(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_feof_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_fread_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_file_stream_read(file, &buffer);

    assert_int_equal(status, F_status_set_error(F_file_read));
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_stream_read__parameter_checking(void **state) {

  f_file_t file = f_file_t_initialize;

  {
    const f_status_t status = f_file_stream_read(file, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  file.size_read = 0;

  {
    const f_status_t status = f_file_stream_read(file, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_dynamic_t string = f_string_dynamic_t_initialize;

    const f_status_t status = f_file_stream_read(file, &string);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_read__returns_file_closed(void **state) {

  const f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_stream_read(file, &buffer);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_stream_read__works(void **state) {

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
    will_return(__wrap_fread_unlocked, 0);

    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_read(file, &buffer);

    assert_int_equal(status, F_none_eof);
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
