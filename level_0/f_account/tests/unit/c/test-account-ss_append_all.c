#include "test-account.h"
#include "test-account-ss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accountss_append_all__parameter_checking(void **state) {

  const f_accountss_t data = f_accountss_t_initialize;

  {
    const f_status_t status = f_accountss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_accountss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_accountss_t source = f_accountss_t_initialize;
  f_accountss_t destination = f_accountss_t_initialize;

  {
    const f_status_t status = f_accountss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_accountss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_accountss_append_all__works(void **state) {

  const int length = 5;
  const int length_inner = 2;
  f_accountss_t source = f_accountss_t_initialize;
  f_accountss_t destination = f_accountss_t_initialize;

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
    const f_status_t status = f_accountss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    for (; source.used < length; ++source.used) {

      const f_status_t status = f_accounts_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_none);

      memcpy(&source.array[source.used].array[source.array[source.used].used++], (void *) &account_0, sizeof(f_account_t));
      memcpy(&source.array[source.used].array[source.array[source.used].used++], (void *) &account_1, sizeof(f_account_t));
    } // for
  }

  {
    const f_status_t status = f_accountss_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.used; ++i) {

      assert_int_equal(destination.array[i].used, length_inner);
        assert_int_equal(destination.array[i].size, length_inner);

      assert_string_equal(destination.array[i].array[0].home.string, account_0.home.string);
      assert_string_equal(destination.array[i].array[0].label.string, account_0.label.string);
      assert_string_equal(destination.array[i].array[0].name.string, account_0.name.string);
      assert_string_equal(destination.array[i].array[0].password.string, account_0.password.string);
      assert_string_equal(destination.array[i].array[0].shell.string, account_0.shell.string);

      assert_string_equal(destination.array[i].array[1].home.string, account_1.home.string);
      assert_string_equal(destination.array[i].array[1].label.string, account_1.label.string);
      assert_string_equal(destination.array[i].array[1].name.string, account_1.name.string);
      assert_string_equal(destination.array[i].array[1].password.string, account_1.password.string);
      assert_string_equal(destination.array[i].array[1].shell.string, account_1.shell.string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].array);
  } // for

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
