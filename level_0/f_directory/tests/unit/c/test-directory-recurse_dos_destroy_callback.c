#include "test-directory.h"
#include "test-directory-recurse_dos_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_recurse_dos_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_directory_recurse_do_t data = f_directory_recurse_do_t_initialize;
  f_directory_recurse_do_t data_array[] = { data };
  f_directory_recurse_dos_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_recurse_dos_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_recurse_dos_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_recurse_dos_t datas = f_directory_recurse_dos_t_initialize;

  {
    f_status_t status = f_memory_array_resize(1, sizeof(f_directory_recurse_do_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].path.string, &datas.array[0].path.used, &datas.array[0].path.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].path_cache.string, &datas.array[0].path_cache.used, &datas.array[0].path_cache.size);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.block.array, &datas.array[0].listing.block.used, &datas.array[0].listing.block.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.character.array, &datas.array[0].listing.character.used, &datas.array[0].listing.character.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.directory.array, &datas.array[0].listing.directory.used, &datas.array[0].listing.directory.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.regular.array, &datas.array[0].listing.regular.used, &datas.array[0].listing.regular.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.link.array, &datas.array[0].listing.link.used, &datas.array[0].listing.link.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.fifo.array, &datas.array[0].listing.fifo.used, &datas.array[0].listing.fifo.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.socket.array, &datas.array[0].listing.socket.used, &datas.array[0].listing.socket.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].listing.unknown.array, &datas.array[0].listing.unknown.used, &datas.array[0].listing.unknown.size, &f_string_dynamics_destroy_callback);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_recurse_dos_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].path.size, 0);
    assert_int_equal(datas.array[0].path_cache.size, 0);
    assert_int_equal(datas.array[0].listing.block.size, 0);
    assert_int_equal(datas.array[0].listing.character.size, 0);
    assert_int_equal(datas.array[0].listing.directory.size, 0);
    assert_int_equal(datas.array[0].listing.regular.size, 0);
    assert_int_equal(datas.array[0].listing.link.size, 0);
    assert_int_equal(datas.array[0].listing.fifo.size, 0);
    assert_int_equal(datas.array[0].listing.socket.size, 0);
    assert_int_equal(datas.array[0].listing.unknown.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
