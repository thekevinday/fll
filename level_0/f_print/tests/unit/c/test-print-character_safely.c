#include "test-print.h"
#include "test-print-character_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_character_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(test.string[0], stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely((f_char_t) 0x7f, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely((f_char_t) F_utf_byte_1_d, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    const f_string_static_t alternate = macro_f_string_static_t_initialize("蠇", 0, 2);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(alternate.string[0], stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_character_safely(test.string[0], stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_character_safely__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_print_character_safely(test.string[0], 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_character_safely__returns_utf(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("蠇", 0, 2);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely(test.string[0], stdout);

    assert_int_equal(status, F_utf);
  }
}

void test__f_print_character_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely((f_char_t) 0x7f, stdout);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely((f_char_t) F_utf_byte_1_d, stdout);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_character_safely(test.string[0], stdout);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
