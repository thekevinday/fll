#include "test-file.h"
#include "test-file-stream_write_until.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write_until__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {

    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_file_stream_write_until(file, test, 1, 0);

    assert_int_equal(status, F_status_set_error(F_file_write));
  }
}

void test__f_file_stream_write_until__parameter_checking(void **state) {

  f_file_t file = f_file_t_initialize;
  file.size_write = 0;

  {
    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_write_until__returns_file_closed(void **state) {

  f_file_t file = f_file_t_initialize;
  file.stream = 0;

  {
    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 0, 0);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }
}

void test__f_file_stream_write_until__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  f_file_t file = f_file_t_initialize;
  file.stream = F_type_input_d;

  {
    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_stream_write_until(file, test, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 1, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 0, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_until(file, test, 0, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_until(file, f_string_empty_s, 1, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write_until__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;
    file.size_write = 1;
    file.stream = F_type_input_d;

    // The letter 't'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    // The letter 'e'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    // The letter 's'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    // The letter 't'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_write_until(file, test, test.used, 0);

    assert_int_equal(status, F_none_eos);
  }

  {
    f_file_t file = f_file_t_initialize;
    file.size_write = test.used;
    file.stream = F_type_input_d;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_write_until(file, test, test.used, 0);

    assert_int_equal(status, F_none_eos);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
