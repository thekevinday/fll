#include "test-directory.h"
#include "test-directory-recurse_doss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_recurse_doss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_directory_recurse_do_t data = f_directory_recurse_do_t_initialize;
  f_directory_recurse_do_t data_array[] = { data };
  f_directory_recurse_dos_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_recurse_dos_t datass_array[] = { datas };

  {
    will_return(__wrap_f_string_dynamic_resize, true);
    will_return(__wrap_f_string_dynamic_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, true);
    will_return(__wrap_f_string_dynamic_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamic_resize, false);
    will_return(__wrap_f_string_dynamic_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_recurse_doss_delete_callback__works(void **state) {

  mock_unwrap = 1;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_recurse_doss_t datass = f_directory_recurse_doss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_directory_recurse_dos_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_directory_recurse_do_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datass.array[0].array[0].path);
    assert_int_equal(status, F_okay);

    status = f_string_dynamic_resize(1, &datass.array[0].array[0].path_cache);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.block);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.character);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.directory);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.regular);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.link);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.fifo);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.socket);
    assert_int_equal(status, F_okay);

    status = f_string_dynamics_resize(1, &datass.array[0].array[0].listing.unknown);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_recurse_doss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
