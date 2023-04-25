#include "test-file.h"
#include "test-file-stream_write_block.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write_block__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);


  {
    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_file_stream_write_block(file, test, 0);

    assert_int_equal(status, F_status_set_error(F_file_write));
  }
}

void test__f_file_stream_write_block__parameter_checking(void **state) {

  f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  file.size_write = 0;

  {
    const f_status_t status = f_file_stream_write_block(file, f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_write_block__returns_stream_not(void **state) {

  const f_file_t file = f_file_t_initialize;

  {
    const f_status_t status = f_file_stream_write_block(file, f_string_empty_s, 0);

    assert_int_equal(F_status_set_fine(status), F_stream_not);
  }
}

void test__f_file_stream_write_block__returns_data_not(void **state) {

  f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_stream_write_block(file, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write_block(file, f_string_empty_s, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write_block__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    f_array_length_t written = 0;

    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
    file.size_write = 1;

    // The letter 't'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, file.size_write);
    will_return(__wrap_ferror_unlocked, false);

    f_status_t status = f_file_stream_write_block(file, test, &written);

    assert_int_equal(status, F_none_stop);
    assert_int_equal(written, file.size_write);

    // The letter 'e'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, file.size_write);
    will_return(__wrap_ferror_unlocked, false);

    status = f_file_stream_write_block(file, test, &written);

    assert_int_equal(status, F_none_stop);
    assert_int_equal(written, file.size_write);

    // The letter 's'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, file.size_write);
    will_return(__wrap_ferror_unlocked, false);

    status = f_file_stream_write_block(file, test, &written);

    assert_int_equal(status, F_none_stop);
    assert_int_equal(written, file.size_write);

    // The letter 't'.
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, file.size_write);
    will_return(__wrap_ferror_unlocked, false);

    status = f_file_stream_write_block(file, test, &written);

    assert_int_equal(status, F_none_stop);
    assert_int_equal(written, file.size_write);
  }

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
    file.size_write = test.used;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_file_stream_write_block(file, test, 0);

    assert_int_equal(status, F_none_eos);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
