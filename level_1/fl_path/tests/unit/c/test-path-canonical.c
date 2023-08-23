#include "test-path.h"
#include "test-path-canonical.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fll_path_canonical__back_paths(void **state) {

  // Paths that don't begin with '/' or '../' will expand to the full PWD.
  f_char_t pwd[PATH_MAX + 1];

  memset(pwd, 0, PATH_MAX + 1);

  getcwd(pwd, PATH_MAX);

  const unsigned int pwd_length = strnlen(pwd, PATH_MAX);

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("a/../", 0, 5),
    macro_f_string_static_t_initialize_1("a/../b", 0, 6),
    macro_f_string_static_t_initialize_1("a/../b/", 0, 7),
    macro_f_string_static_t_initialize_1("a/../b/c", 0, 8),
    macro_f_string_static_t_initialize_1("a/../b/c/", 0, 9),
    macro_f_string_static_t_initialize_1("a/../b/c//", 0, 10),
    macro_f_string_static_t_initialize_1("a/.././", 0, 7),
    macro_f_string_static_t_initialize_1("a/.././b", 0, 8),
    macro_f_string_static_t_initialize_1("a/.././b/", 0, 9),
    macro_f_string_static_t_initialize_1("a/.././b/c", 0, 10),
    macro_f_string_static_t_initialize_1("a/.././b/c/", 0, 11),
    macro_f_string_static_t_initialize_1("a/.././b/c//", 0, 12),
    macro_f_string_static_t_initialize_1("a/.././/", 0, 8),
    macro_f_string_static_t_initialize_1("a/.././/b", 0, 9),
    macro_f_string_static_t_initialize_1("a/.././/b/", 0, 10),
    macro_f_string_static_t_initialize_1("a/.././/b/c", 0, 11),
    macro_f_string_static_t_initialize_1("a/.././/b/c/", 0, 12),
    macro_f_string_static_t_initialize_1("a/.././/b/c//", 0, 13),
    macro_f_string_static_t_initialize_1("/z/../", 0, 6),
    macro_f_string_static_t_initialize_1("/z/../b", 0, 7),
    macro_f_string_static_t_initialize_1("/z/../b/", 0, 8),
    macro_f_string_static_t_initialize_1("/z/../b/c", 0, 9),
    macro_f_string_static_t_initialize_1("/z/../b/c/", 0, 10),
    macro_f_string_static_t_initialize_1("/z/../b/c//", 0, 11),
  };

  const f_string_static_t expected[] = {
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b", 0, 1),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("b/c", 0, 3),
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/b", 0, 2),
    macro_f_string_static_t_initialize_1("/b", 0, 2),
    macro_f_string_static_t_initialize_1("/b/c", 0, 4),
    macro_f_string_static_t_initialize_1("/b/c", 0, 4),
    macro_f_string_static_t_initialize_1("/b/c", 0, 4),
  };

  const uint8_t prepend[] = {
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
  };

  f_string_dynamic_t path = f_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 24; ++i) {

    const f_status_t status = fl_path_canonical(contents[i], &path);

    assert_int_equal(status, F_okay);

    // Assert_string_equal() is NULL terminated, so ensure NULL termination at end of path.used.
    path.string[path.used] = 0;

    if (prepend[i]) {
      f_char_t prepended_string[pwd_length + expected[i].used + 2];
      f_string_static_t prepended = macro_f_string_static_t_initialize_1(prepended_string, 0, pwd_length + expected[i].used);

      prepended_string[prepended.used] = 0;
      prepended_string[prepended.used + 1] = 0;

      if (pwd_length) {
        memcpy(prepended_string, pwd, pwd_length);
      }

      if (expected[i].used) {
        if (pwd_length && prepended_string[pwd_length] != f_path_separator_s.string[0]) {
          prepended_string[pwd_length] = f_path_separator_s.string[0];
          memcpy(prepended_string + pwd_length + 1, expected[i].string, expected[i].used);
          ++prepended.used;
        }
        else {
          memcpy(prepended_string + pwd_length, expected[i].string, expected[i].used);
        }
      }

      // The last slash is always removed.
      if (prepended.used && prepended_string[prepended.used - 1] == f_path_separator_s.string[0]) {
        prepended_string[prepended.used--] = 0;
      }

      assert_int_equal(prepended.used, path.used);
      assert_string_equal(prepended.string, path.string);
    }
    else {
      assert_int_equal(expected[i].used, path.used);
      assert_string_equal(expected[i].string, path.string);
    }
  } // for

  free((void *) path.string);
}

void test__fll_path_canonical__empty_becomes_pwd(void **state) {

  f_char_t pwd[PATH_MAX + 1];

  memset(pwd, 0, PATH_MAX + 1);

  getcwd(pwd, PATH_MAX);

  const unsigned int pwd_length = strnlen(pwd, PATH_MAX);

  f_string_dynamic_t path = f_string_dynamic_t_initialize;

  {
    const f_status_t status = fl_path_canonical(f_string_empty_s, &path);

    assert_int_equal(status, F_okay);
    assert_int_equal(pwd_length, path.used);
    assert_string_equal(pwd, path.string);
  } // for

  free((void *) path.string);
}

void test__fll_path_canonical__present_paths(void **state) {

  // Paths that don't begin with '/' or '../' will expand to the full PWD.
  f_char_t pwd[PATH_MAX + 1];

  memset(pwd, 0, PATH_MAX + 1);

  getcwd(pwd, PATH_MAX);

  const unsigned int pwd_length = strnlen(pwd, PATH_MAX);

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("", 0, 1),
    macro_f_string_static_t_initialize_1("a", 0, 2),
    macro_f_string_static_t_initialize_1("a/", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 4),
    macro_f_string_static_t_initialize_1("a/b/", 0, 5),
    macro_f_string_static_t_initialize_1("a/b//", 0, 6),
    macro_f_string_static_t_initialize_1("./", 0, 2),
    macro_f_string_static_t_initialize_1("./a", 0, 3),
    macro_f_string_static_t_initialize_1("./a/", 0, 4),
    macro_f_string_static_t_initialize_1("./a/b", 0, 5),
    macro_f_string_static_t_initialize_1("./a/b/", 0, 6),
    macro_f_string_static_t_initialize_1("./a/b//", 0, 7),
    macro_f_string_static_t_initialize_1(".//", 0, 3),
    macro_f_string_static_t_initialize_1(".//a", 0, 4),
    macro_f_string_static_t_initialize_1(".//a/", 0, 5),
    macro_f_string_static_t_initialize_1(".//a/b", 0, 6),
    macro_f_string_static_t_initialize_1(".//a/b/", 0, 7),
    macro_f_string_static_t_initialize_1(".//a/b//", 0, 8),
  };

  const f_string_static_t expected[] = {
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
    macro_f_string_static_t_initialize_1("a/b", 0, 3),
  };

  f_string_dynamic_t path = f_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 18; ++i) {

    const f_status_t status = fl_path_canonical(contents[i], &path);

    assert_int_equal(status, F_okay);

    // Assert_string_equal() is NULL terminated, so ensure NULL termination at end of path.used.
    path.string[path.used] = 0;

    f_char_t prepended_string[pwd_length + expected[i].used + 2];
    f_string_static_t prepended = macro_f_string_static_t_initialize_1(prepended_string, 0, pwd_length + expected[i].used);

    prepended_string[prepended.used] = 0;
    prepended_string[prepended.used + 1] = 0;

    if (pwd_length) {
      memcpy(prepended_string, pwd, pwd_length);
    }

    if (expected[i].used) {
      if (pwd_length && prepended_string[pwd_length] != f_path_separator_s.string[0]) {
        prepended_string[pwd_length] = f_path_separator_s.string[0];
        memcpy(prepended_string + pwd_length + 1, expected[i].string, expected[i].used);
        ++prepended.used;
      }
      else {
        memcpy(prepended_string + pwd_length, expected[i].string, expected[i].used);
      }
    }

    // The last slash is always removed.
    if (prepended.used && prepended_string[prepended.used - 1] == f_path_separator_s.string[0]) {
      prepended_string[prepended.used--] = 0;
    }

    assert_int_equal(prepended.used, path.used);
    assert_string_equal(prepended.string, path.string);
  } // for

  free((void *) path.string);
}

void test__fll_path_canonical__root_paths(void **state) {

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("//", 0, 2),
    macro_f_string_static_t_initialize_1("///", 0, 3),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("//a", 0, 3),
    macro_f_string_static_t_initialize_1("///a", 0, 4),
    macro_f_string_static_t_initialize_1("/a/", 0, 3),
    macro_f_string_static_t_initialize_1("//a/", 0, 4),
    macro_f_string_static_t_initialize_1("///a/", 0, 5),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("//a/b", 0, 5),
    macro_f_string_static_t_initialize_1("///a/b", 0, 6),
    macro_f_string_static_t_initialize_1("/a/b/", 0, 5),
    macro_f_string_static_t_initialize_1("//a/b/", 0, 6),
    macro_f_string_static_t_initialize_1("///a/b/", 0, 7),
    macro_f_string_static_t_initialize_1("/a/b//", 0, 6),
    macro_f_string_static_t_initialize_1("//a/b//", 0, 7),
    macro_f_string_static_t_initialize_1("///a/b//", 0, 8),
  };

  const f_string_static_t expected[] = {
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/", 0, 1),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a", 0, 2),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
    macro_f_string_static_t_initialize_1("/a/b", 0, 4),
  };

  f_string_dynamic_t path = f_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 18; ++i) {

    const f_status_t status = fl_path_canonical(contents[i], &path);

    // Assert_string_equal() is NULL terminated, so ensure NULL termination at end of path.used.
    if (status == F_okay) {
      path.string[path.used] = 0;
    }

    assert_int_equal(status, F_okay);
    assert_int_equal(expected[i].used, path.used);
    assert_string_equal(expected[i].string, path.string);
  } // for

  free((void *) path.string);
}

void test__fll_path_canonical__tilde_remains(void **state) {

  // Paths that don't begin with '/' or '../' will expand to the full PWD.
  f_char_t pwd[PATH_MAX + 1];

  memset(pwd, 0, PATH_MAX + 1);

  getcwd(pwd, PATH_MAX);

  const unsigned int pwd_length = strnlen(pwd, PATH_MAX);

  const f_string_static_t contents[] = {
    macro_f_string_static_t_initialize_1("~", 0, 1),
    macro_f_string_static_t_initialize_1("~/", 0, 2),
    macro_f_string_static_t_initialize_1("~//", 0, 3),
    macro_f_string_static_t_initialize_1("~a", 0, 2),
    macro_f_string_static_t_initialize_1("a~", 0, 2),
    macro_f_string_static_t_initialize_1("a~b", 0, 3),
    macro_f_string_static_t_initialize_1("/~", 0, 2),
    macro_f_string_static_t_initialize_1("//~", 0, 3),
    macro_f_string_static_t_initialize_1("~ ", 0, 2),
    macro_f_string_static_t_initialize_1("~ /", 0, 3),
    macro_f_string_static_t_initialize_1("./~", 0, 3),
    macro_f_string_static_t_initialize_1("./~a", 0, 4),
    macro_f_string_static_t_initialize_1("./a~", 0, 4),
    macro_f_string_static_t_initialize_1("./a~b", 0, 5),
    macro_f_string_static_t_initialize_1("a/~/b", 0, 5),
    macro_f_string_static_t_initialize_1("a/~b", 0, 4),
    macro_f_string_static_t_initialize_1("a/~b/c", 0, 6),
    macro_f_string_static_t_initialize_1("/a/~/b", 0, 6),
    macro_f_string_static_t_initialize_1("/a/~b", 0, 5),
    macro_f_string_static_t_initialize_1("/a/~b/c", 0, 7),
    macro_f_string_static_t_initialize_1("//a/~/b", 0, 7),
    macro_f_string_static_t_initialize_1("//a/~b", 0, 6),
    macro_f_string_static_t_initialize_1("//a/~b/c", 0, 8),
  };

  const f_string_static_t expected[] = {
    macro_f_string_static_t_initialize_1("~", 0, 1),
    macro_f_string_static_t_initialize_1("~", 0, 1),
    macro_f_string_static_t_initialize_1("~", 0, 1),
    macro_f_string_static_t_initialize_1("~a", 0, 2),
    macro_f_string_static_t_initialize_1("a~", 0, 2),
    macro_f_string_static_t_initialize_1("a~b", 0, 3),
    macro_f_string_static_t_initialize_1("/~", 0, 2),
    macro_f_string_static_t_initialize_1("/~", 0, 2),
    macro_f_string_static_t_initialize_1("~ ", 0, 2),
    macro_f_string_static_t_initialize_1("~ ", 0, 2),
    macro_f_string_static_t_initialize_1("~", 0, 1),
    macro_f_string_static_t_initialize_1("~a", 0, 2),
    macro_f_string_static_t_initialize_1("a~", 0, 2),
    macro_f_string_static_t_initialize_1("a~b", 0, 3),
    macro_f_string_static_t_initialize_1("a/~/b", 0, 5),
    macro_f_string_static_t_initialize_1("a/~b", 0, 4),
    macro_f_string_static_t_initialize_1("a/~b/c", 0, 6),
    macro_f_string_static_t_initialize_1("/a/~/b", 0, 6),
    macro_f_string_static_t_initialize_1("/a/~b", 0, 5),
    macro_f_string_static_t_initialize_1("/a/~b/c", 0, 7),
    macro_f_string_static_t_initialize_1("/a/~/b", 0, 6),
    macro_f_string_static_t_initialize_1("/a/~b", 0, 5),
    macro_f_string_static_t_initialize_1("/a/~b/c", 0, 7),
  };

  const uint8_t prepend[] = {
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_false,
    F_false,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_true,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
  };

  f_string_dynamic_t path = f_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 23; ++i) {

    const f_status_t status = fl_path_canonical(contents[i], &path);

    assert_int_equal(status, F_okay);

    // Assert_string_equal() is NULL terminated, so ensure NULL termination at end of path.used.
    path.string[path.used] = 0;

    if (prepend[i]) {
      f_char_t prepended_string[pwd_length + expected[i].used + 2];
      f_string_static_t prepended = macro_f_string_static_t_initialize_1(prepended_string, 0, pwd_length + expected[i].used);

      prepended_string[prepended.used] = 0;
      prepended_string[prepended.used + 1] = 0;

      if (pwd_length) {
        memcpy(prepended_string, pwd, pwd_length);
      }

      if (expected[i].used) {
        if (pwd_length && prepended_string[pwd_length] != f_path_separator_s.string[0]) {
          prepended_string[pwd_length] = f_path_separator_s.string[0];
          memcpy(prepended_string + pwd_length + 1, expected[i].string, expected[i].used);
          ++prepended.used;
        }
        else {
          memcpy(prepended_string + pwd_length, expected[i].string, expected[i].used);
        }
      }

      // The last slash is always removed.
      if (prepended.used && prepended_string[prepended.used - 1] == f_path_separator_s.string[0]) {
        prepended_string[prepended.used--] = 0;
      }

      assert_int_equal(prepended.used, path.used);
      assert_string_equal(prepended.string, path.string);
    }
    else {
      assert_int_equal(expected[i].used, path.used);
      assert_string_equal(expected[i].string, path.string);
    }
  } // for

  free((void *) path.string);
}

void test__fll_path_canonical__parameter_checking(void **state) {

  {
    const f_status_t status = fl_path_canonical(f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
