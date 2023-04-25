#include "test-iki.h"
#include "test-iki-object_is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_object_is__returns_false(void **state) {

  const f_string_static_t objects[] = {
    macro_f_string_static_t_initialize_1("fa lse", 0, 6),
    macro_f_string_static_t_initialize_1("filse@", 0, 6),
    macro_f_string_static_t_initialize_1("fa;lse", 0, 6),
    macro_f_string_static_t_initialize_1("/false", 0, 6),
    macro_f_string_static_t_initialize_1("'false", 0, 6),
    macro_f_string_static_t_initialize_1("false'", 0, 6),
    macro_f_string_static_t_initialize_1("fa'l'se", 0, 7),
    macro_f_string_static_t_initialize_1("f'alse", 0, 6),
    macro_f_string_static_t_initialize_1("'false'", 0, 7),
    macro_f_string_static_t_initialize_1("\"false", 0, 7),
    macro_f_string_static_t_initialize_1("false\"", 0, 7),
    macro_f_string_static_t_initialize_1("fa\"l\"se", 0, 7),
    macro_f_string_static_t_initialize_1("f\"alse", 0, 6),
    macro_f_string_static_t_initialize_1("'false'", 0, 7),
  };

  for (uint8_t i = 0; i < 14; ++i) {

    const f_status_t status = f_iki_object_is(objects[i]);

    assert_int_equal(F_status_set_fine(status), F_false);
  } // for
}

void test__f_iki_object_is__returns_data_not(void **state) {

  {
    const f_status_t status = f_iki_object_is(f_string_empty_s);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_iki_object_is__returns_true(void **state) {

  const f_string_static_t objects[] = {
    macro_f_string_static_t_initialize_1("works", 0, 5),
    macro_f_string_static_t_initialize_1("wor_ks", 0, 6),
    macro_f_string_static_t_initialize_1("work-s", 0, 6),
    macro_f_string_static_t_initialize_1("wor++ks", 0, 7),
    macro_f_string_static_t_initialize_1("w_-+s", 0, 5),
  };

  for (uint8_t i = 0; i < 5; ++i) {

    const f_status_t status = f_iki_object_is(objects[i]);

    assert_int_equal(F_status_set_fine(status), F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
