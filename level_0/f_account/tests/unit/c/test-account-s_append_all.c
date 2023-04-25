#include "test-account.h"
#include "test-account-s_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accounts_append_all__parameter_checking(void **state) {

  const f_accounts_t data = f_accounts_t_initialize;

  {
    const f_status_t status = f_accounts_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_accounts_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_accounts_t source = f_accounts_t_initialize;
  f_accounts_t destination = f_accounts_t_initialize;

  {
    const f_status_t status = f_accounts_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_accounts_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_accounts_append_all__works(void **state) {

  const int length = 5;
  f_accounts_t source = f_accounts_t_initialize;
  f_accounts_t destination = f_accounts_t_initialize;

  f_string_static_t home_0 = macro_f_string_static_t_initialize_1("home_0", 0, 6);
  f_string_static_t label_0 = macro_f_string_static_t_initialize_1("label_0", 0, 7);
  f_string_static_t name_0 = macro_f_string_static_t_initialize_1("name_0", 0, 6);
  f_string_static_t password_0 = macro_f_string_static_t_initialize_1("password_0", 0, 10);
  f_string_static_t shell_0 = macro_f_string_static_t_initialize_1("shell_0", 0, 7);

  f_string_static_t home_1 = macro_f_string_static_t_initialize_1("home_1", 0, 6);
  f_string_static_t label_1 = macro_f_string_static_t_initialize_1("label_1", 0, 7);
  f_string_static_t name_1 = macro_f_string_static_t_initialize_1("name_1", 0, 6);
  f_string_static_t password_1 = macro_f_string_static_t_initialize_1("password_1", 0, 10);
  f_string_static_t shell_1 = macro_f_string_static_t_initialize_1("shell_1", 0, 7);

  const f_account_t account_0 = { .home = home_0, .label = label_0, .name = name_0, .password = password_0, .shell = shell_0 };
  const f_account_t account_1 = { .home = home_1, .label = label_1, .name = name_1, .password = password_1, .shell = shell_1 };

  {
    const f_status_t status = f_accounts_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  memcpy(&source.array[source.used++], (void *) &account_0, sizeof(f_account_t));
  memcpy(&source.array[source.used++], (void *) &account_1, sizeof(f_account_t));

  {
    const f_status_t status = f_accounts_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    assert_string_equal(destination.array[0].home.string, account_0.home.string);
    assert_string_equal(destination.array[0].label.string, account_0.label.string);
    assert_string_equal(destination.array[0].name.string, account_0.name.string);
    assert_string_equal(destination.array[0].password.string, account_0.password.string);
    assert_string_equal(destination.array[0].shell.string, account_0.shell.string);

    assert_string_equal(destination.array[1].home.string, account_1.home.string);
    assert_string_equal(destination.array[1].label.string, account_1.label.string);
    assert_string_equal(destination.array[1].name.string, account_1.name.string);
    assert_string_equal(destination.array[1].password.string, account_1.password.string);
    assert_string_equal(destination.array[1].shell.string, account_1.shell.string);
  }

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
