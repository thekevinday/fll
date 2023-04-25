#include "test-path.h"
#include "test-path-is_relative.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_is_relative__returns_false(void **state) {

  const f_string_static_t paths[] = {
    macro_f_string_static_t_initialize_1("/'false", 0, 7),
    macro_f_string_static_t_initialize_1("/false'", 0, 7),
    macro_f_string_static_t_initialize_1("/f a l s e", 0, 10),
    macro_f_string_static_t_initialize_1("/0+-12, false", 0, 13),
  };

  for (uint8_t i = 0; i < 4; ++i) {

    const f_status_t status = f_path_is_relative(paths[i]);

    assert_int_equal(F_status_set_fine(status), F_false);
  } // for
}

void test__f_path_is_relative__returns_data_not(void **state) {

  {
    const f_status_t status = f_path_is_relative(f_string_empty_s);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_path_is_relative__returns_true(void **state) {

  const f_string_static_t paths[] = {
    macro_f_string_static_t_initialize_1("'true/", 0, 6),
    macro_f_string_static_t_initialize_1("./true'", 0, 7),
    macro_f_string_static_t_initialize_1("t /r u e", 0, 8),
    macro_f_string_static_t_initialize_1("0+-12,/ true", 0, 12),
  };

  for (uint8_t i = 0; i < 4; ++i) {

    const f_status_t status = f_path_is_relative(paths[i]);

    assert_int_equal(F_status_set_fine(status), F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
