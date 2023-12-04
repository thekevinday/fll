#include "test-iki.h"
#include "test-iki-content_partial_is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_content_partial_is__returns_false(void **state) {

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("xxxx' falsexxxx", 0, 15),
    macro_f_string_static_t_initialize_1("xxxx'falsexxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxxfalse'xxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxxfa'l'sexxxx", 0, 15),
    macro_f_string_static_t_initialize_1("xxxxf'alsexxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxx'false'xxxx", 0, 15),
    macro_f_string_static_t_initialize_1("xxxx\"falsexxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxxfalse\"xxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxxfa\"l\"sexxxx", 0, 15),
    macro_f_string_static_t_initialize_1("xxxxf\"alsexxxx", 0, 14),
    macro_f_string_static_t_initialize_1("xxxx\"false\"xxxx", 0, 15),
  };

  const f_range_t ranges[] = {
    macro_f_range_t_initialize_1(4, 10),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 10),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 5),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 10),
    macro_f_range_t_initialize_1(4, 9),
    macro_f_range_t_initialize_1(4, 5),
  };

  const f_string_static_t quotes[] = {
    f_string_ascii_quote_single_s,
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

  for (uint8_t i = 0; i < 11; ++i) {

    const f_status_t status = f_iki_content_partial_is(contents[i], ranges[i], quotes[i]);

    assert_int_equal(F_status_set_fine(status), F_false);
  } // for
}

void test__f_iki_content_partial_is__parameter_checking(void **state) {

  {
    const f_range_t range = f_range_t_initialize;

    const f_status_t status = f_iki_content_partial_is(f_string_empty_s, range, f_string_empty_s);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_iki_content_partial_is__returns_data_not(void **state) {

  {
    const f_range_t range = f_range_t_initialize;

    const f_status_t status = f_iki_content_partial_is(f_string_empty_s, range, f_string_ascii_quote_single_s);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_iki_content_partial_is__returns_data_not_eos(void **state) {

  {
    const f_range_t range = macro_f_range_t_initialize_1(f_string_ascii_a_s.used, f_string_ascii_a_s.used);

    const f_status_t status = f_iki_content_partial_is(f_string_ascii_a_s, range, f_string_ascii_quote_single_s);

    assert_int_equal(F_status_set_fine(status), F_data_not_eos);
  }
}

void test__f_iki_content_partial_is__returns_data_not_stop(void **state) {

  {
    f_range_t range = f_range_t_initialize;

    const f_status_t status = f_iki_content_partial_is(f_string_ascii_a_s, range, f_string_ascii_quote_single_s);

    assert_int_equal(F_status_set_fine(status), F_data_not_stop);
  }
}

void test__f_iki_content_partial_is__returns_true(void **state) {

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("xxxxworksxxxx", 0, 13),
    macro_f_string_static_t_initialize_1("xxxxalso worksxxxx", 0, 18),
    macro_f_string_static_t_initialize_1("xxxx\\'works\\'xxxx", 0, 17),
    macro_f_string_static_t_initialize_1("xxxx\\'wor ks\\'xxxx", 0, 18),
    macro_f_string_static_t_initialize_1("xxxx\\'work\\'s\\'xxxx", 0, 19),
    macro_f_string_static_t_initialize_1("xxxx\\\"works\\\"xxxx", 0, 17),
    macro_f_string_static_t_initialize_1("xxxx\\\"wor ks\\\"xxxx", 0, 18),
    macro_f_string_static_t_initialize_1("xxxx\\\"work\\\"s\\\"xxxx", 0, 19),
  };

  const f_range_t ranges[] = {
    macro_f_range_t_initialize_1(4, 8),
    macro_f_range_t_initialize_1(4, 13),
    macro_f_range_t_initialize_1(4, 12),
    macro_f_range_t_initialize_1(4, 13),
    macro_f_range_t_initialize_1(4, 14),
    macro_f_range_t_initialize_1(4, 12),
    macro_f_range_t_initialize_1(4, 13),
    macro_f_range_t_initialize_1(4, 14),
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

    const f_status_t status = f_iki_content_partial_is(contents[i], ranges[i], quotes[i]);

    assert_int_equal(F_status_set_fine(status), F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
