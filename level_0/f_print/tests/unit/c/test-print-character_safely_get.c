#include "test-print.h"
#include "test-print-character_safely_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_character_safely_get__returns_character_control(void **state) {

  for (uint8_t i = 0; i < 32 ; ++i) {

    const f_char_t character = (f_char_t) i;

    const f_string_static_t safe = f_print_character_safely_get(character);

    assert_int_equal(safe.used, f_print_sequence_set_control_s[i].used);
    assert_string_equal(safe.string, f_print_sequence_set_control_s[i].string);
  } // for
}

void test__f_print_character_safely_get__returns_character_delete(void **state) {

  const f_char_t character = (f_char_t) 0x7f;

  {
    const f_string_static_t safe = f_print_character_safely_get(character);

    assert_int_equal(safe.used, f_print_sequence_delete_s.used);
    assert_string_equal(safe.string, f_print_sequence_delete_s.string);
  }
}

void test__f_print_character_safely_get__returns_character_unknown(void **state) {

  const f_char_t character = (f_char_t) F_utf_byte_1_d;

  {
    const f_string_static_t safe = f_print_character_safely_get(character);

    assert_int_equal(safe.used, f_print_sequence_unknown_s.used);
    assert_string_equal(safe.string, f_print_sequence_unknown_s.string);
  }
}

void test__f_print_character_safely_get__returns_empty(void **state) {

  {
    const f_char_t character = 'a';

    const f_string_static_t safe = f_print_character_safely_get(character);

    assert_int_equal(safe.used, f_string_empty_s.used);
    assert_string_equal(safe.string, f_string_empty_s.string);
  }

  {
    const f_string_t string = "蠇";

    const f_string_static_t safe = f_print_character_safely_get(string[0]);

    assert_int_equal(safe.used, f_string_empty_s.used);
    assert_string_equal(safe.string, f_string_empty_s.string);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
