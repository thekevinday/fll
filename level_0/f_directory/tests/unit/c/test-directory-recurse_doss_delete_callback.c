#include "test-directory.h"
#include "test-directory-recurse_doss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_recurse_doss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);
  f_string_static_t base_array[] = { base };
  f_string_statics_t bases = macro_f_string_statics_t_initialize_1(base_array, 1, 0);

  f_directory_listing_t listing = {
    .block = bases,
    .character = bases,
    .directory = bases,
    .regular = bases,
    .link = bases,
    .fifo = bases,
    .socket = bases,
    .unknown = bases,
  };

  f_directory_recurse_do_t data = {
    .listing = listing,
    .path = base,
    .path_cache = base,
  };

  f_directory_recurse_do_t data_array[] = { data };
  f_directory_recurse_dos_t datas = { .array = data_array, .used = 0, .size = 1 };
  f_directory_recurse_dos_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].listing.block = bases;
  datas_array[0].array[0].listing.character = bases;
  datas_array[0].array[0].listing.directory = bases;
  datas_array[0].array[0].listing.regular = bases;
  datas_array[0].array[0].listing.link = bases;
  datas_array[0].array[0].listing.fifo = bases;
  datas_array[0].array[0].listing.socket = bases;
  datas_array[0].array[0].listing.unknown = bases;
  datas_array[0].array[0].path = base;
  datas_array[0].array[0].path_cache = base;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_recurse_doss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_recurse_doss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_recurse_doss_t datass = f_directory_recurse_doss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_directory_recurse_dos_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_directory_recurse_do_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].path.string, &datass.array[0].array[0].path.used, &datass.array[0].array[0].path.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].path_cache.string, &datass.array[0].array[0].path_cache.used, &datass.array[0].array[0].path_cache.size);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.block.array, &datass.array[0].array[0].listing.block.used, &datass.array[0].array[0].listing.block.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.character.array, &datass.array[0].array[0].listing.character.used, &datass.array[0].array[0].listing.character.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.directory.array, &datass.array[0].array[0].listing.directory.used, &datass.array[0].array[0].listing.directory.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.regular.array, &datass.array[0].array[0].listing.regular.used, &datass.array[0].array[0].listing.regular.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.link.array, &datass.array[0].array[0].listing.link.used, &datass.array[0].array[0].listing.link.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.fifo.array, &datass.array[0].array[0].listing.fifo.used, &datass.array[0].array[0].listing.fifo.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.socket.array, &datass.array[0].array[0].listing.socket.used, &datass.array[0].array[0].listing.socket.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].listing.unknown.array, &datass.array[0].array[0].listing.unknown.used, &datass.array[0].array[0].listing.unknown.size, &f_string_dynamics_delete_callback);
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
