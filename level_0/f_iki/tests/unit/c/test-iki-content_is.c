#include "test-iki.h"
#include "test-iki-content_is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_content_is__returns_false(void **state) {

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize("'false", 0, 6),
    macro_f_string_static_t_initialize("false'", 0, 6),
    macro_f_string_static_t_initialize("fa'l'se", 0, 7),
    macro_f_string_static_t_initialize("f'alse", 0, 6),
    macro_f_string_static_t_initialize("'false'", 0, 2),
    macro_f_string_static_t_initialize("\"false", 0, 6),
    macro_f_string_static_t_initialize("false\"", 0, 6),
    macro_f_string_static_t_initialize("fa\"l\"se", 0, 7),
    macro_f_string_static_t_initialize("f\"alse", 0, 6),
    macro_f_string_static_t_initialize("\"false\"", 0, 2),
  };

  const f_string_static_t quotes[] = {
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
  };

  for (uint8_t i = 0; i < 10; ++i) {

    const f_status_t status = f_iki_content_is(contents[i], quotes[i]);

    assert_int_equal(F_status_set_fine(status), F_false);
  } // for
}

void test__f_iki_content_is__parameter_checking(void **state) {

  {
    const f_status_t status = f_iki_content_is(f_string_empty_s, f_string_empty_s);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_iki_content_is__returns_data_not(void **state) {

  {
    const f_status_t status = f_iki_content_is(f_string_empty_s, f_string_ascii_quote_single_s);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_iki_content_is__returns_true(void **state) {

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize("works", 0, 5),
    macro_f_string_static_t_initialize("also works", 0, 10),
    macro_f_string_static_t_initialize("\\'works\\'", 0, 9),
    macro_f_string_static_t_initialize("\\'wor ks\\'", 0, 10),
    macro_f_string_static_t_initialize("\\'work\\'s\\'", 0, 11),
    macro_f_string_static_t_initialize("\\\"works\\\"", 0, 9),
    macro_f_string_static_t_initialize("\\\"wor ks\\\"", 0, 10),
    macro_f_string_static_t_initialize("\\\"work\\\"s\\\"", 0, 11),
  };

  const f_string_static_t quotes[] = {
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_single_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
    f_string_ascii_quote_double_s,
  };

  for (uint8_t i = 0; i < 8; ++i) {

    const f_status_t status = f_iki_content_is(contents[i], quotes[i]);

    assert_int_equal(F_status_set_fine(status), F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
