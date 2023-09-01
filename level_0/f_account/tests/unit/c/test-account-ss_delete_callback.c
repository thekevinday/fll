#include "test-account.h"
#include "test-account-ss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_accountss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);

  f_account_t data = {
    .id_user = 0,
    .id_group = 0,
    .home = base,
    .label = base,
    .name = base,
    .password = base,
    .shell = base,
  };

  f_account_t data_array[] = { data };
  f_accounts_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_accounts_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].home = base;
  datas_array[0].array[0].label = base;
  datas_array[0].array[0].name = base;
  datas_array[0].array[0].password = base;
  datas_array[0].array[0].shell = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].home = base;
  datas_array[0].array[0].label = base;
  datas_array[0].array[0].name = base;
  datas_array[0].array[0].password = base;
  datas_array[0].array[0].shell = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].home = base;
  datas_array[0].array[0].label = base;
  datas_array[0].array[0].name = base;
  datas_array[0].array[0].password = base;
  datas_array[0].array[0].shell = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].home = base;
  datas_array[0].array[0].label = base;
  datas_array[0].array[0].name = base;
  datas_array[0].array[0].password = base;
  datas_array[0].array[0].shell = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].home = base;
  datas_array[0].array[0].label = base;
  datas_array[0].array[0].name = base;
  datas_array[0].array[0].password = base;
  datas_array[0].array[0].shell = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_accountss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_accountss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_accountss_t datass = f_accountss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_accounts_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_account_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].home.string, &datass.array[0].array[0].home.used, &datass.array[0].array[0].home.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].label.string, &datass.array[0].array[0].label.used, &datass.array[0].array[0].label.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].name.string, &datass.array[0].array[0].name.used, &datass.array[0].array[0].name.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].password.string, &datass.array[0].array[0].password.used, &datass.array[0].array[0].password.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].shell.string, &datass.array[0].array[0].shell.used, &datass.array[0].array[0].shell.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_accountss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
