#include "test-fss.h"
#include "test-fss-apply_delimit_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_apply_delimit_range__parameter_checking(void **state) {

  const f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
  f_state_t state_data = f_state_t_initialize;
  const f_string_range_t range = f_string_range_t_initialize;

  {
    f_fss_apply_delimit_range(delimits, range, 0, &state_data);

    assert_int_equal(state_data.status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_apply_delimit_range__returns_data_not(void **state) {

  f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
  f_state_t state_data = f_state_t_initialize;

  {
    const f_string_range_t range = f_string_range_t_initialize;
    f_string_static_t empty = f_string_static_t_initialize;

    f_fss_apply_delimit_range(delimits, range, &empty, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    const f_string_range_t range = f_string_range_t_initialize;

    f_fss_apply_delimit_range(delimits, range, &test, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, test.used - 1);
    f_string_static_t empty = f_string_static_t_initialize;

    f_fss_apply_delimit_range(delimits, range, &empty, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }
}

void test__f_fss_apply_delimit_range__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_char_t strings_0[] = "test";
  f_char_t strings_1[] = "test";
  f_char_t strings_2[] = "test";
  f_char_t strings_3[] = "test";
  f_char_t strings_4[] = "test";
  f_char_t strings_5[] = "test";
  f_char_t strings_6[] = "⸙test全test";

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1(strings_0, 0, 4),
    macro_f_string_static_t_initialize_1(strings_1, 0, 4),
    macro_f_string_static_t_initialize_1(strings_2, 0, 4),
    macro_f_string_static_t_initialize_1(strings_3, 0, 4),
    macro_f_string_static_t_initialize_1(strings_4, 0, 4),
    macro_f_string_static_t_initialize_1(strings_5, 0, 4),
    macro_f_string_static_t_initialize_1(strings_6, 0, 14),
  };

  const f_string_static_t expects[] = {
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("t\0st", 0, 4),
    macro_f_string_static_t_initialize_1("t\0\0t", 0, 4),
    macro_f_string_static_t_initialize_1("t\0s\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0s\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0\0test全\0est", 0, 14),
  };

  f_number_unsigned_t delimits_0[] = {
    tests[0].used + 2,
  };

  f_number_unsigned_t delimits_1[] = {
    1,
  };

  f_number_unsigned_t delimits_2[] = {
    1,
    2,
  };

  f_number_unsigned_t delimits_3[] = {
    1,
    3,
  };

  f_number_unsigned_t delimits_4[] = {
    0,
    1,
    3,
  };

  f_number_unsigned_t delimits_5[] = {
    0,
    1,
    2,
    3,
  };

  f_number_unsigned_t delimits_6[] = {
    0,
    1,
    2,
    10,
  };

  const f_number_unsigneds_t delimitss[] = {
    macro_f_number_unsigneds_t_initialize_1(delimits_0, 0, 1),
    macro_f_number_unsigneds_t_initialize_1(delimits_1, 0, 1),
    macro_f_number_unsigneds_t_initialize_1(delimits_2, 0, 2),
    macro_f_number_unsigneds_t_initialize_1(delimits_3, 0, 2),
    macro_f_number_unsigneds_t_initialize_1(delimits_4, 0, 3),
    macro_f_number_unsigneds_t_initialize_1(delimits_5, 0, 4),
    macro_f_number_unsigneds_t_initialize_1(delimits_6, 0, 4),
  };

  for (uint8_t i = 0; i < 7; ++i) {

    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, tests[i].used - 1);

    f_fss_apply_delimit_range(delimitss[i], range, &tests[i], &state_data);

    assert_int_equal(state_data.status, F_none);
    assert_int_equal(tests[i].used, expects[i].used);

    for (uint8_t j = 0; j < tests[i].used; ++j) {
      assert_int_equal(tests[i].string[j], expects[i].string[j]);
    } // for
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
