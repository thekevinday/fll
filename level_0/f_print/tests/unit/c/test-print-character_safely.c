#include "test-print.h"
#include "test-print-character_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_character_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(test.string[0], output);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely((f_char_t) 0x7f, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely((f_char_t) F_utf_byte_1_d, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    const f_string_static_t alternate = macro_f_string_static_t_initialize_1("蠇", 0, 2);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(alternate.string[0], output);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(test.string[0], output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_character_safely__returns_stream_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_file_t output = macro_f_file_t_initialize_2(0, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_character_safely(test.string[0], output);

    assert_int_equal(F_status_set_fine(status), F_stream_not);
  }
}

void test__f_print_character_safely__returns_utf(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("蠇", 0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely(test.string[0], output);

    assert_int_equal(status, F_utf);
  }
}

void test__f_print_character_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, f_print_sequence_delete_s.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely((f_char_t) 0x7f, output);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, f_print_sequence_unknown_s.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely((f_char_t) F_utf_byte_1_d, output);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely(test.string[0], output);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
