#include "test-file.h"
#include "test-file-stream_write_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write_range__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t range = macro_f_string_range_t_initialize_1(0, 0);

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
    file.size_read = 1;

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_file_stream_write_range(file, test, range, 0);

    assert_int_equal(status, F_status_set_error(F_file_write));
  }
}

void test__f_file_stream_write_range__returns_stream_not(void **state) {

  const f_file_t file = f_file_t_initialize;
  const f_string_range_t range = f_string_range_t_initialize;

  {
    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

    assert_int_equal(F_status_set_fine(status), F_stream_not);
  }
}

void test__f_file_stream_write_range__returns_data_not(void **state) {

  f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_string_range_t range = f_string_range_t_initialize;
    const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

    const f_status_t status = f_file_stream_write_range(file, test, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, 0);

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
    const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_range(file, test, range, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, 0);

    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_range(file, f_string_empty_s, range, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write_range__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t range = macro_f_string_range_t_initialize_1(0, 0);

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
    file.size_write = 1;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_write_range(file, test, range, 0);

    assert_int_equal(status, F_none_stop);
  }

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
    file.size_write = test.used;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_write_range(file, test, range, 0);

    assert_int_equal(status, F_none_eos);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
