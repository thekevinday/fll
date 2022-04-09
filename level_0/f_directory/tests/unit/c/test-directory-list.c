#include "test-directory.h"
#include "test-directory-list.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_list__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  f_string_dynamics_t names = f_string_dynamics_t_initialize;

  {
    int errnos[] = {
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_memory_not,
      F_failure,
    };

    for (int i = 0; i < 2; ++i) {

      will_return(__wrap_scandir, true);
      will_return(__wrap_scandir, errnos[i]);

      const f_status_t status = f_directory_list(path, 0, 0, &names);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  f_string_dynamics_resize(0, &names);
}

#ifndef _di_level_0_parameter_checking_
  void test__f_directory_list__parameter_checking(void **state) {

    const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

    {
      const f_status_t status = f_directory_list(path, 0, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_directory_list__returns_data_not(void **state) {

  f_string_dynamics_t names = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_directory_list(f_string_empty_s, 0, 0, &names);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamics_resize(0, &names);
}

void test__f_directory_list__returns_directory_empty(void **state) {

  f_string_dynamics_t names = f_string_dynamics_t_initialize;
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct dirent *directories[0];

    memset(directories, 0, sizeof(struct dirent *));

    will_return(__wrap_scandir, false);
    will_return(__wrap_scandir, directories);
    will_return(__wrap_scandir, 0);

    const f_status_t status = f_directory_list(path, 0, 0, &names);

    assert_int_equal(status, F_directory_empty);
  }

  f_string_dynamics_resize(0, &names);
}

void test__f_directory_list__works(void **state) {

  f_string_dynamics_t names = f_string_dynamics_t_initialize;
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct dirent *directories[1];

    // The scandir() allocates each struct dirent.
    directories[0] = (struct dirent *) malloc(sizeof(struct dirent));

    memset(directories[0], 0, sizeof(struct dirent));
    memcpy(directories[0]->d_name, path.string, sizeof(f_char_t) * path.used);
    directories[0]->d_name[path.used] = 0;

    will_return(__wrap_scandir, false);
    will_return(__wrap_scandir, directories);
    will_return(__wrap_scandir, 1);

    const f_status_t status = f_directory_list(path, 0, 0, &names);

    assert_int_equal(status, F_none);
  }

  f_string_dynamics_resize(0, &names);
}

#ifdef __cplusplus
} // extern "C"
#endif
