#include "test-account.h"
#include "test-account-s_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accounts_append__parameter_checking(void **state) {

  const f_account_t data = f_account_t_initialize;

  {
    const f_status_t status = f_accounts_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_accounts_append__works(void **state) {

  mock_unwrap = 1;

  f_string_static_t home = macro_f_string_static_t_initialize_1("home", 0, 4);
  f_string_static_t label = macro_f_string_static_t_initialize_1("label", 0, 5);
  f_string_static_t name = macro_f_string_static_t_initialize_1("name", 0, 4);
  f_string_static_t password = macro_f_string_static_t_initialize_1("password", 0, 8);
  f_string_static_t shell = macro_f_string_static_t_initialize_1("shell", 0, 5);

  const f_account_t source = { .home = home, .label = label, .name = name, .password = password, .shell = shell };
  f_accounts_t destination = f_accounts_t_initialize;

  {
    const f_status_t status = f_accounts_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);

    assert_string_equal(destination.array[0].home.string, source.home.string);
    assert_string_equal(destination.array[0].label.string, source.label.string);
    assert_string_equal(destination.array[0].name.string, source.name.string);
    assert_string_equal(destination.array[0].password.string, source.password.string);
    assert_string_equal(destination.array[0].shell.string, source.shell.string);

    assert_int_equal(destination.array[0].home.used, source.home.used);
    assert_int_equal(destination.array[0].label.used, source.label.used);
    assert_int_equal(destination.array[0].name.used, source.name.used);
    assert_int_equal(destination.array[0].password.used, source.password.used);
    assert_int_equal(destination.array[0].shell.used, source.shell.used);
  }

  free((void *) destination.array[0].home.string);
  free((void *) destination.array[0].label.string);
  free((void *) destination.array[0].name.string);
  free((void *) destination.array[0].password.string);
  free((void *) destination.array[0].shell.string);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
