#include "test-account.h"
#include "test-account-ss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accountss_append__parameter_checking(void **state) {

  f_accounts_t data = f_accounts_t_initialize;

  {
    const f_status_t status = f_accountss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_accountss_append__returns_data_not(void **state) {

  const int length = 5;
  f_accounts_t source = f_accountss_t_initialize;
  f_accountss_t destination = f_accountss_t_initialize;

  {
    const f_status_t status = f_accounts_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_accountss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_accountss_append__works(void **state) {

  const int length = 5;
  f_accounts_t sources = f_accounts_t_initialize;
  f_accountss_t destination = f_accountss_t_initialize;

  f_string_static_t home = macro_f_string_static_t_initialize_1("home", 0, 4);
  f_string_static_t label = macro_f_string_static_t_initialize_1("label", 0, 5);
  f_string_static_t name = macro_f_string_static_t_initialize_1("name", 0, 4);
  f_string_static_t password = macro_f_string_static_t_initialize_1("password", 0, 8);
  f_string_static_t shell = macro_f_string_static_t_initialize_1("shell", 0, 5);

  const f_account_t source = { .home = home, .label = label, .name = name, .password = password, .shell = shell };

  {
    const f_status_t status = f_accounts_resize(length, &sources);

    assert_int_equal(status, F_none);
    assert_int_equal(sources.used, 0);
    assert_int_equal(sources.size, length);
  }

  while (sources.used < length) {
    memcpy(&sources.array[sources.used++], (void *) &source, sizeof(f_account_t));
  } // while

  {
    const f_status_t status = f_accountss_append(sources, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, sources.used);
    assert_int_equal(destination.array[0].size, sources.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

      assert_string_equal(destination.array[0].array[i].home.string, source.home.string);
      assert_string_equal(destination.array[0].array[i].label.string, source.label.string);
      assert_string_equal(destination.array[0].array[i].name.string, source.name.string);
      assert_string_equal(destination.array[0].array[i].password.string, source.password.string);
      assert_string_equal(destination.array[0].array[i].shell.string, source.shell.string);

      assert_int_equal(destination.array[0].array[i].home.used, source.home.used);
      assert_int_equal(destination.array[0].array[i].label.used, source.label.used);
      assert_int_equal(destination.array[0].array[i].name.used, source.name.used);
      assert_int_equal(destination.array[0].array[i].password.used, source.password.used);
      assert_int_equal(destination.array[0].array[i].shell.used, source.shell.used);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) sources.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
