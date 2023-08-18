#include "test-file.h"
#include "test-file-name_directory.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_name_directory__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_name_directory(f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_name_directory__returns_data_not(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_name_directory(f_string_empty_s, &buffer);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_name_directory__works(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  f_string_static_t paths[] = {
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b/c", 0, 6),
    macro_f_string_static_t_initialize_1("/a/", 0, 3),
    macro_f_string_static_t_initialize_1("/a/b/", 0, 5),
    macro_f_string_static_t_initialize_1("/a/b/c/", 0, 7),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b/c", 0, 5),
    macro_f_string_static_t_initialize_1("a/", 0, 2),
    macro_f_string_static_t_initialize_1("a/b/", 0, 4),
    macro_f_string_static_t_initialize_1("a/b/c/", 0, 6),
  };

  f_string_static_t bases[] = {
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
  };

  for (uint8_t i = 0; i < 12; ++i) {

    buffer.used = 0;

    const f_status_t status = f_file_name_directory(paths[i], &buffer);

    assert_int_equal(status, F_okay);
    assert_int_equal(buffer.used, bases[i].used);
    assert_string_equal(buffer.string, bases[i].string);
  } // for

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
