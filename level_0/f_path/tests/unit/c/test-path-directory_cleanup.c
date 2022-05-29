#include "test-path.h"
#include "test-path-directory_cleanup.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_directory_cleanup__parameter_checking(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_path_directory_cleanup(path, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_path_directory_cleanup__works(void **state) {

  const f_string_static_t paths[] = {
    macro_f_string_static_t_initialize("path", 0, 4),
    macro_f_string_static_t_initialize("also path", 0, 9),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("/", 0, 1),
    macro_f_string_static_t_initialize("///", 0, 3),
    macro_f_string_static_t_initialize("///path", 0, 7),
    macro_f_string_static_t_initialize("///path////", 0, 11),
    macro_f_string_static_t_initialize("///also////path", 0, 15),
    macro_f_string_static_t_initialize("../", 0, 3),
    macro_f_string_static_t_initialize("..///", 0, 3),
    macro_f_string_static_t_initialize("..///path", 0, 9),
    macro_f_string_static_t_initialize("..///path////", 0, 11),
    macro_f_string_static_t_initialize("..///also////path", 0, 17),
    macro_f_string_static_t_initialize("also///..//path", 0, 15),
  };

  const f_string_static_t expecteds[] = {
    macro_f_string_static_t_initialize("path/", 0, 5),
    macro_f_string_static_t_initialize("also path/", 0, 10),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("/", 0, 1),
    macro_f_string_static_t_initialize("/", 0, 1),
    macro_f_string_static_t_initialize("/path/", 0, 6),
    macro_f_string_static_t_initialize("/path/", 0, 6),
    macro_f_string_static_t_initialize("/also/path/", 0, 11),
    macro_f_string_static_t_initialize("../", 0, 3),
    macro_f_string_static_t_initialize("../", 0, 3),
    macro_f_string_static_t_initialize("../path/", 0, 8),
    macro_f_string_static_t_initialize("../path/", 0, 8),
    macro_f_string_static_t_initialize("../also/path/", 0, 13),
    macro_f_string_static_t_initialize("also/../path/", 0, 13),
  };

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  for (f_array_length_t i = 0; i < 14; ++i, destination.used = 0) {

    const f_status_t status = f_path_directory_cleanup(paths[i], &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expecteds[i].used);

    if (destination.used) {
      assert_string_equal(destination.string, expecteds[i].string);

      // Check that string is NULL terminated.
      assert_true(destination.size > destination.used);
      assert_int_equal(destination.string[destination.used], 0);
    }

    // De-allocate each pass to ensure that the NULL termination check is accurate.
    f_string_dynamic_resize(0, &destination);
  } // for

  f_string_dynamic_resize(0, &destination);
}

#ifdef __cplusplus
} // extern "C"
#endif
