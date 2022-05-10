#include "test-iki.h"
#include "test-iki-object_partial_is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_object_partial_is__returns_false(void **state) {

  const f_string_static_t objects[] = {
    macro_f_string_static_t_initialize("xxxxfa lsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfalse@xxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfal;sexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxx/falsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxx'falsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfalse'xxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfa'l'sexxxx", 0, 15),
    macro_f_string_static_t_initialize("xxxxf'alsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxx'false'xxxx", 0, 15),
    macro_f_string_static_t_initialize("xxxx\"falsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfalse\"xxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxfa\"l\"sexxxx", 0, 15),
    macro_f_string_static_t_initialize("xxxxf\"alsexxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxx'false'xxxx", 0, 15),
  };

  const f_string_range_t ranges[] = {
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 10),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 10),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 10),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 10),
  };

  for (uint8_t i = 0; i < 14; ++i) {

    const f_status_t status = f_iki_object_partial_is(objects[i], ranges[i]);

    assert_int_equal(F_status_set_fine(status), F_false);
  } // for
}

void test__f_iki_object_partial_is__returns_data_not(void **state) {

  {
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_iki_object_partial_is(f_string_empty_s, range);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_iki_object_partial_is__returns_data_not_eos(void **state) {

  {
    const f_string_range_t range = macro_f_string_range_t_initialize(f_string_ascii_a_s.used, f_string_ascii_a_s.used);

    const f_status_t status = f_iki_object_partial_is(f_string_ascii_a_s, range);

    assert_int_equal(F_status_set_fine(status), F_data_not_eos);
  }
}

void test__f_iki_object_partial_is__returns_data_not_stop(void **state) {

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_iki_object_partial_is(f_string_ascii_a_s, range);

    assert_int_equal(F_status_set_fine(status), F_data_not_stop);
  }
}

void test__f_iki_object_partial_is__returns_true(void **state) {

  const f_string_static_t objects[] = {
    macro_f_string_static_t_initialize("xxxxworksxxxx", 0, 13),
    macro_f_string_static_t_initialize("xxxxwor_ksxxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxwork-sxxxx", 0, 14),
    macro_f_string_static_t_initialize("xxxxwor++ksxxxx", 0, 15),
    macro_f_string_static_t_initialize("xxxxw_-+sxxxx", 0, 13),
  };

  const f_string_range_t ranges[] = {
    macro_f_string_range_t_initialize(4, 8),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 9),
    macro_f_string_range_t_initialize(4, 10),
    macro_f_string_range_t_initialize(4, 8),
  };

  for (uint8_t i = 0; i < 5; ++i) {

    const f_status_t status = f_iki_object_partial_is(objects[i], ranges[i]);

    assert_int_equal(F_status_set_fine(status), F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
