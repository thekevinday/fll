#include "test-account.h"
#include "test-account-s_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accounts_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  f_account_t data = f_account_t_initialize;
  f_account_t data_array[] = { data };

  {
    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_accounts_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_accounts_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_accounts_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_accounts_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_okay);

    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_accounts_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_accounts_destroy_callback__works(void **state) {

  mock_unwrap = 1;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_accounts_t datas = f_accounts_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_account_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datas.array[0].home);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datas.array[0].label);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datas.array[0].name);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datas.array[0].password);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datas.array[0].shell);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_accounts_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].home.size, 0);
    assert_int_equal(datas.array[0].label.size, 0);
    assert_int_equal(datas.array[0].name.size, 0);
    assert_int_equal(datas.array[0].password.size, 0);
    assert_int_equal(datas.array[0].shell.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
